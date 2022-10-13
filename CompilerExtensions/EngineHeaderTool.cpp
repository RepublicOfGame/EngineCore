#include <clang-c/Index.h>
#include <string>
#include "Log.h"


std::string toString(const CXString& str){
    std::string s(clang_getCString(str));
    clang_disposeString(str);
    return s;
}

int main(){
    const char* filename = ENGINE_SOURCE_DIR"/CompilerExtensions/play.cpp";
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit unit = clang_parseTranslationUnit(
            index,
            filename, nullptr, 0,
            nullptr, 0,
            CXTranslationUnit_None);
    if(unit == nullptr){
        Loge("Failed to parse translation unit file: {}", filename);
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(cursor, [](CXCursor c, CXCursor parent, CXClientData clientData){
        printf("Name:%-20s Type:%-20s\n", toString(clang_getCursorSpelling(c)).c_str(),
               toString(clang_getCursorKindSpelling(clang_getCursorKind(c))).c_str());
        return CXChildVisit_Recurse;
    }, nullptr);
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}