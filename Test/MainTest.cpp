#include <gtest/gtest.h>
#include "iostream"

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"
using namespace clang;

class ExampleAttrInfo : public ParsedAttrInfo {
public:
    ExampleAttrInfo() {
        Spellings = {{ParsedAttr::AS_GNU,"example"}};
    }
    AttrHandling handleDeclAttribute(Sema &S, Decl *D,
                                     const ParsedAttr &Attr) const override {
        // Handle the attribute
        std::cout << "Hello!" << std::endl;
        return AttributeApplied;
    }
};

static ParsedAttrInfoRegistry::Add<ExampleAttrInfo> Z("example_attr","example attribute description");

__attribute__((example))
int a;
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
}