#pragma once

#include "CodeGenerator.h"
#include "ResourceID.h"
#include <clang-c/Index.h>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

class AttributeParser {
public:
  std::string S;
  std::string Notation;

  AttributeParser(const char *s) : S(s) {
    for (size_t i = 0; i < S.size(); i++) {
      if (s[i] == '(') {
        Notation = S.substr(0, i);
        break;
      }
    }
  }
};

class ClangAstConsumer {
public:
  ClangAstConsumer() = default;

  virtual void OnIndexDeclaration(const CXIdxDeclInfo *declInfo);

  virtual void OnDeclClass(const CXIdxCXXClassDeclInfo *classInfo) = 0;

  virtual void OnDeclField(const CXIdxDeclInfo *declInfo) = 0;

  virtual void OnDeclMethod(const CXIdxDeclInfo *declInfo) = 0;
};

class ReflectionInfoCollector : public ClangAstConsumer {
public:
  static constexpr const char *ANFUNCTION = "NFUNCTION";
  static constexpr const char *ANPROPERTY = "NPROPERTY";
  static constexpr const char *ANCLASS = "NCLASS";
  CodeGenerator *Generator;

  ReflectionInfoCollector(CodeGenerator *generator) : Generator(generator) {}

  void OnDeclClass(const CXIdxCXXClassDeclInfo *ptr) override;

  void OnDeclField(const CXIdxDeclInfo *declInfo) override;

  void OnDeclMethod(const CXIdxDeclInfo *declInfo) override;

  static bool HasAttribute(const CXIdxDeclInfo *declInfo, const char *prefix);

  static CXType GetUnderlyingType(const CXCursor &cursor);
};

enum Annotation {
  FUNCTION = StringToRID(ReflectionInfoCollector::ANFUNCTION),
  PROPERTY = StringToRID(ReflectionInfoCollector::ANPROPERTY),
  CLASS = StringToRID(ReflectionInfoCollector::ANCLASS)
};

extern void ParseSourceCode(std::filesystem::path &Path,
                            ClangAstConsumer *consumer);
