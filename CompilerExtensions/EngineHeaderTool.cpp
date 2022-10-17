#include "Log.h"
#include "Parser.h"
#include "Class.h"


int main() {
//    auto func = &Class::func;
//    Class c;
//    c.CallFunction(func, 1);
//    auto consumer = std::make_shared<ReflectionInfoCollector>();
//    ParseSourceCode(ENGINE_SOURCE_DIR"/CompilerExtensions/play.cpp", consumer.get());

}

//void PrintCursor(CXCursor Cursor, const char *CommentSchemaFile);
//void printEntityInfo(const char *cb,
//                     CXClientData client_data,
//                     const CXIdxEntityInfo *info);
//void printCXIndexLoc(CXIdxLoc loc, CXClientData client_data);
//
//
//
//static CXString createCXString(const char *CS) {
//    CXString Str;
//    Str.data = (const void *) CS;
//    Str.private_flags = 0;
//    return Str;
//}
//
//
//static void printBaseClassInfo(CXClientData client_data,
//                               const CXIdxBaseClassInfo *info) {
//    printEntityInfo("<base>", client_data, info->base);
//    printf(" | cursor: ");
//    PrintCursor(info->cursor, NULL);
//    printf(" | loc: ");
//    printCXIndexLoc(info->loc, client_data);
//}
//
//static void index_indexDeclaration(CXClientData client_data,
//                                   const CXIdxDeclInfo *info) {
//    const CXIdxCXXClassDeclInfo *CXXClassInfo;
//    if ((CXXClassInfo = clang_index_getCXXClassDeclInfo(info))) {
//        for (int i = 0; i != CXXClassInfo->numBases; ++i) {
//            printBaseClassInfo(client_data, CXXClassInfo->bases[i]);
//            printf("\n");
//        }
//    }
//
//}
//static IndexerCallbacks IndexCB = {
//        nullptr,
//        nullptr,
//        nullptr,
//        nullptr,
//        nullptr,
//        nullptr,
//        index_indexDeclaration,
//        nullptr,
//};
//
//
//
//int main(){
//
////    const char* filename = ENGINE_SOURCE_DIR"/CompilerExtensions/play.cpp";
////    CXIndex index = clang_createIndex(0, 0);
////    CXTranslationUnit TU = clang_parseTranslationUnit(
////            index,
////            filename, nullptr, 0,
////            nullptr, 0,
////            CXTranslationUnit_None);
////    if(TU == nullptr){
////        Loge("Failed to parse translation unit file: {}", filename);
////        exit(-1);
////    }
////    CXIndexAction idxAction = clang_IndexAction_create(index);
////    int index_opts = 0;
////
////    int result = clang_indexTranslationUnit(idxAction, ,
////                                        &IndexCB,sizeof(IndexCB),
////                                        index_opts, TU);
////
////
////    if (index_data.fail_for_error)
////        exit(-1);
//
////    CXCursor cursor = clang_getTranslationUnitCursor(TU);
//
//    // 遍历AST
////    clang_visitChildren(cursor, [](CXCursor c, CXCursor parent, CXClientData clientData){
////
//////        if(clang_getCursorKind(c) == CXCursor_AnnotateAttr &&
//////        toString(clang_getCursorSpelling(c)) == "reflect" &&
//////                clang_getCursorKind(parent) == CXCursor_FieldDecl){
//////            printf("Name:%-20s Kind:%-20s Type:%-20s\n", toString(clang_getCursorSpelling(parent)).c_str(),
//////                   toString(clang_getCursorKindSpelling(clang_getCursorKind(parent))).c_str(),
//////                   toString(clang_getTypeSpelling(clang_getTypedefDeclUnderlyingType(parent))).c_str());
//////        }
//////        printf("Parent: ");
//////        PrintCursor(parent, nullptr);
//////        printf(" | ");
//////        printf("\n");
//////        return CXChildVisit_Recurse;
////
////        if (clang_isDeclaration(c.kind)) {
////            printf("\n");
////            PrintCursor(c, nullptr);
////            printf("\n\t└──");
////            PrintCursor(parent, nullptr);
////            return CXChildVisit_Recurse;
////        } else if (clang_isAttribute(c.kind)) {
////            printf(" ");
////            PrintCursor(c, nullptr);
////        }
////        return CXChildVisit_Continue;
////    }, nullptr);
//}