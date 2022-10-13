#pragma once

#include <clang-c/Index.h>
#include <string>
#include <memory>


class ClangAstConsumer {
public:

    ClangAstConsumer() = default;

    virtual void OnIndexDeclaration(const CXIdxDeclInfo *);
};

extern void ParseSourceCode(const std::string &filepath, ClangAstConsumer *consumer);
