#pragma once

#include <string>
#include <memory>

class ClangAstConsumer {
public:

    ClangAstConsumer();

    virtual void OnIndexDeclaration(const CXIdxDeclInfo *) {}
};
