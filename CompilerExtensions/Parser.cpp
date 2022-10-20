#include "Parser.h"
#include "Log.h"
#include <memory>

static IndexerCallbacks cb;

void ParseSourceCode(const std::string &filepath, ClangAstConsumer *consumer) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit TU = clang_parseTranslationUnit(
      index, filepath.c_str(), nullptr, 0,
      nullptr, 0, CXTranslationUnit_None);
  if (TU == nullptr) {
    Loge("Failed to parse translation unit file: {}", filepath);
    exit(-1);
  }
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
  //  printf("[INFO] %d\n", clang_getCursorKind(declInfo->cursor));
  if (const CXIdxCXXClassDeclInfo *classInfo =
          clang_index_getCXXClassDeclInfo(declInfo))
    this->OnDeclClass(classInfo);
  else if (clang_getCursorKind(declInfo->cursor) == CXCursor_FieldDecl &&
           clang_Cursor_hasAttrs(declInfo->cursor))
    this->OnDeclField(declInfo);
  else if (clang_getCursorKind(declInfo->cursor) == CXCursor_CXXMethod &&
           clang_Cursor_hasAttrs(declInfo->cursor)) {
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
  if (HasAttribute(declInfo, ANFUNCTION)) {
    CXString SR =
        clang_getTypeSpelling(clang_getCursorResultType(declInfo->cursor));
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
