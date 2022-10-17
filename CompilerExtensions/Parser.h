#pragma once

#include <clang-c/Index.h>
#include <string>
#include <memory>
#include "ResourceID.h"

class ClangAstConsumer {
public:

    ClangAstConsumer() = default;

    virtual void OnIndexDeclaration(const CXIdxDeclInfo *declInfo);

    virtual void OnDeclClass(const CXIdxCXXClassDeclInfo *classInfo) = 0;

    virtual void OnDeclField(const CXIdxDeclInfo *declInfo) = 0;
};

class ReflectionInfoCollector : public ClangAstConsumer {
public:
    static constexpr const char *AnnotationReflect = "reflect";

    void OnDeclClass(const CXIdxCXXClassDeclInfo *ptr) override;

    void OnDeclField(const CXIdxDeclInfo *declInfo) override;

    static bool HasReflectionAttribute(const CXIdxDeclInfo *declInfo);

    static CXType GetUnderlyingType(const CXCursor &cursor);
};

enum Annotation {
    Reflect = StringToRID(ReflectionInfoCollector::AnnotationReflect)
};

extern void ParseSourceCode(const std::string &filepath, ClangAstConsumer *consumer);
