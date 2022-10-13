#include "Parser.h"
#include "Log.h"
#include <memory>

static IndexerCallbacks cb;

void ParseSourceCode(const std::string &filepath, ClangAstConsumer *consumer) {
    CXIndex index = clang_createIndex(0, 0);
    CXTranslationUnit TU = clang_parseTranslationUnit(
            index,
            filepath.c_str(), nullptr, 0,
            nullptr, 0,
            CXTranslationUnit_None);
    if (TU == nullptr) {
        Loge("Failed to parse translation unit file: {}", filepath);
        exit(-1);
    }
    CXIndexAction idxAction = clang_IndexAction_create(index);
    cb.indexDeclaration = [](CXClientData client_data, const CXIdxDeclInfo *info) {
        auto *consumer = static_cast<ClangAstConsumer *>(client_data);
        consumer->OnIndexDeclaration(info);
    };
    int index_opts = 0;
    int result = clang_indexTranslationUnit(idxAction, consumer,
                                            &cb, sizeof(cb),
                                            index_opts, TU);
    if (result != 0) {
        Loge("Failed to index translation unit.");
        exit(-1);
    }
}

void ClangAstConsumer::OnIndexDeclaration(const CXIdxDeclInfo *info) {
    const CXIdxCXXClassDeclInfo *classInfo = clang_index_getCXXClassDeclInfo(info);
    if (classInfo == nullptr) return;

    printf("ClassName: %-20s", classInfo->declInfo->entityInfo->name);
    for (int i = 0; i != classInfo->numBases; ++i) {
        if (!i) printf("Base: ");
        if (clang_isVirtualBase(classInfo->bases[i]->cursor)) {
            printf("virtual ");
        }
        printf("%-20s", classInfo->bases[i]->base->name);
    }
    printf("\n");
}
