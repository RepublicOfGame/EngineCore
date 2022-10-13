#pragma once

#include <clang-c/Index.h>
#include <string>
#include <memory>


class ClangAstConsumer {
public:

    ClangAstConsumer() = default;

    virtual void OnIndexDeclaration(const CXIdxDeclInfo *declInfo);

    virtual void OnDeclClass(const CXIdxCXXClassDeclInfo *classInfo) = 0;

    virtual void OnDeclField(const CXIdxDeclInfo *declInfo) = 0;
};

class ReflectionInfoCollector : public ClangAstConsumer {
public:
    constexpr static char AttributeReflection[] = "reflect";

    void OnDeclClass(const CXIdxCXXClassDeclInfo *ptr) override;

    void OnDeclField(const CXIdxDeclInfo *declInfo) override;

    static bool HasReflectionAttribute(const CXIdxDeclInfo *declInfo);

    static CXType GetType(const CXCursor);
};

extern void ParseSourceCode(const std::string &filepath, ClangAstConsumer *consumer);
