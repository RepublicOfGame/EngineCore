#include "Parser.h"
#include "Log.h"
#include <memory>

static IndexerCallbacks cb;

std::string ToString(CXString InString) {
  std::string S(clang_getCString(InString));
  clang_disposeString(InString);
  return S;
}

void ParseSourceCode(std::filesystem::path &Path, ClangAstConsumer *consumer) {
  std::string filepath = Path.string();

  CXIndex index = clang_createIndex(0, 0);
  const char *commandLineArgs[] = {"-x", "c++", 0};
  CXTranslationUnit TU = clang_parseTranslationUnit(
      index, filepath.c_str(), commandLineArgs,
      (sizeof commandLineArgs / sizeof *commandLineArgs) - 1, nullptr, 0,
      CXTranslationUnit_None);
  if (TU == nullptr) {
    Loge("Failed to parse translation unit file: {}", filepath);
    exit(-1);
  }
  //  // 一阶段: 预处理解析
  //  CXCursor cursor = clang_getTranslationUnitCursor(TU);
  //  clang_visitChildren(
  //      cursor,
  //      [](CXCursor c, CXCursor parent, CXClientData clientData) {
  //        printf("[STEP1]: %s %s\n",
  //               ToString(clang_getCursorKindSpelling(c.kind)).c_str(),
  //               ToString(clang_getCursorDisplayName(c)).c_str());
  //
  //        return CXChildVisit_Recurse;
  //      },
  //      nullptr);

  CXIndexAction idxAction = clang_IndexAction_create(index);
  cb.indexDeclaration = [](CXClientData client_data,
                           const CXIdxDeclInfo *info) {
    auto *consumer = static_cast<ClangAstConsumer *>(client_data);
    consumer->OnIndexDeclaration(info);
  };
  int index_opts = 0;
  int result = clang_indexTranslationUnit(idxAction, consumer, &cb, sizeof(cb),
                                          index_opts, TU);
  if (result != 0) {
    Loge("Failed to index translation unit.");
    exit(-1);
  }
}

void ClangAstConsumer::OnIndexDeclaration(const CXIdxDeclInfo *declInfo) {
  printf("[INFO] %s\n",
         ToString(clang_getCursorKindSpelling(declInfo->cursor.kind)).c_str());
  if (const CXIdxCXXClassDeclInfo *ClassInfo =
          clang_index_getCXXClassDeclInfo(declInfo))
    this->OnDeclClass(ClassInfo);
  else if (clang_getCursorKind(declInfo->cursor) == CXCursor_FieldDecl)
    this->OnDeclField(declInfo);
  else if (clang_getCursorKind(declInfo->cursor) == CXCursor_CXXMethod) {
    this->OnDeclMethod(declInfo);
  }
}

void ReflectionInfoCollector::OnDeclClass(
    const CXIdxCXXClassDeclInfo *classInfo) {
  printf("[Class] ClassName: %-20s", classInfo->declInfo->entityInfo->name);
  for (unsigned i = 0; i != classInfo->numBases; ++i) {
    if (!i)
      printf("Base: ");
    if (clang_isVirtualBase(classInfo->bases[i]->cursor)) {
      printf("virtual ");
    }
    printf("%-20s", classInfo->bases[i]->base->name);
  }
  printf("\n");
}

void ReflectionInfoCollector::OnDeclField(const CXIdxDeclInfo *declInfo) {
  if (HasAttribute(declInfo, ANPROPERTY)) {
    auto offset = clang_Cursor_getOffsetOfField(declInfo->cursor) / 8;
    CXString S = clang_getTypeSpelling(GetUnderlyingType(declInfo->cursor));
    printf("[Field] Type: %-10s Name: %-10s Offset: %-10lld\n",
           clang_getCString(S), declInfo->entityInfo->name, offset);
    clang_disposeString(S);
  }
}

void ReflectionInfoCollector::OnDeclMethod(const CXIdxDeclInfo *declInfo) {
  CXType ResultType = clang_getCursorResultType(declInfo->cursor);
  const char *FunctionName = declInfo->entityInfo->name;

  if (HasAttribute(declInfo, ANFUNCTION)) {
    CXString SR = clang_getTypeSpelling(ResultType);
    printf("[Method] Name: %-10s Ret: %-10s", declInfo->entityInfo->name,
           clang_getCString(SR));
    clang_disposeString(SR);
    int NumArgs = clang_Cursor_getNumArguments(declInfo->cursor);
    for (int i = 0; i < NumArgs; i++) {
      CXCursor Cursor = clang_Cursor_getArgument(declInfo->cursor, i);
      CXString S = clang_getCursorSpelling(Cursor);
      CXString ST = clang_getTypeSpelling(GetUnderlyingType(Cursor));
      printf("[Args] Name: %-5s Type: %-5s", clang_getCString(S),
             clang_getCString(ST));
      clang_disposeString(S);
      clang_disposeString(ST);
    }
  } else if (strcmp(FunctionName, "GENERATED_BODY") == 0) {
    unsigned line;
    clang_getExpansionLocation(clang_getCursorLocation(declInfo->cursor),
                               nullptr, &line, nullptr, nullptr);
    Generator->AddGeneratedBody(line);
    printf("[GENERATED_BODY] line: %d", line);
  }
}

bool ReflectionInfoCollector::HasAttribute(const CXIdxDeclInfo *declInfo,
                                           const char *prefix) {
  for (unsigned i = 0; i < declInfo->numAttributes; i++) {
    CXString S = clang_getCursorSpelling(declInfo->attributes[i]->cursor);
    const char *ss = clang_getCString(S);
    int cmp = strcmp(AttributeParser(ss).Notation.c_str(), prefix);
    clang_disposeString(S);
    if (cmp == 0)
      return true;
  }
  return false;
}

CXType ReflectionInfoCollector::GetUnderlyingType(const CXCursor &cursor) {
  CXType type = clang_getCursorType(cursor);
  while (type.kind == CXType_Typedef) {
    type = clang_getTypedefDeclUnderlyingType(clang_getTypeDeclaration(type));
  };
  return type;
}
