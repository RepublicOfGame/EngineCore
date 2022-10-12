#include "iostream"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Sema/Sema.h"
#include "llvm/Support/raw_ostream.h"

namespace {
    using namespace clang;
    struct SerializationAttrInfo : public ParsedAttrInfo {
        SerializationAttrInfo() {
            std::cout << "::SerializationAttrInfo()" << std::endl;
            // Can take up to 15 optional arguments, to emulate accepting a variadic
            // number of arguments. This just illustrates how many arguments a
            // `ParsedAttrInfo` can hold, we will not use that much in this example.
            OptArgs = 15;
            // GNU-style __attribute__(("example")) and C++-style [[example]] and
            // [[plugin::example]] supported.
            static constexpr Spelling S[] = {{ParsedAttr::AS_GNU, "Serializable"},
                                             {ParsedAttr::AS_CXX11, "Serializable"},
                                             {ParsedAttr::AS_CXX11, "plugin::Serializable"}};
            Spellings = S;
        }

        bool diagAppertainsToDecl(Sema &S, const ParsedAttr &Attr,
                                  const Decl *D) const override {
            std::cout << "diagAppertainsToDecl()" << std::endl;
            // This attribute appertains to functions only.
            if (!isa<FunctionDecl>(D)) {
//                S.Diag(Attr.getLoc(), diag::warn_attribute_wrong_decl_type_str)
//                        << Attr << "functions";
                return false;
            }
            return true;
        }

        AttrHandling handleDeclAttribute(Sema &S, Decl *D,
                                         const ParsedAttr &Attr) const override {
            std::cout << "handleDeclAttribute()" << std::endl;

            // Check if the decl is at file scope.
            if (!D->getDeclContext()->isFileContext()) {
                unsigned ID = S.getDiagnostics().getCustomDiagID(
                        DiagnosticsEngine::Error,
                        "'example' attribute only allowed at file scope");
                S.Diag(Attr.getLoc(), ID);
                return AttributeNotApplied;
            }
            // We make some rules here:
            // 1. Only accept at most 3 arguments here.
            // 2. The first argument must be a string literal if it exists.
            if (Attr.getNumArgs() > 3) {
                unsigned ID = S.getDiagnostics().getCustomDiagID(
                        DiagnosticsEngine::Error,
                        "'example' attribute only accepts at most three arguments");
                S.Diag(Attr.getLoc(), ID);
                return AttributeNotApplied;
            }
            // If there are arguments, the first argument should be a string literal.
            if (Attr.getNumArgs() > 0) {
                auto *Arg0 = Attr.getArgAsExpr(0);
                StringLiteral *Literal =
                        dyn_cast<StringLiteral>(Arg0->IgnoreParenCasts());
                if (!Literal) {
                    unsigned ID = S.getDiagnostics().getCustomDiagID(
                            DiagnosticsEngine::Error, "first argument to the 'example' "
                                                      "attribute must be a string literal");
                    S.Diag(Attr.getLoc(), ID);
                    return AttributeNotApplied;
                }
                SmallVector<Expr *, 16> ArgsBuf;
                for (unsigned i = 0; i < Attr.getNumArgs(); i++) {
                    ArgsBuf.push_back(Attr.getArgAsExpr(i));
                }
                D->addAttr(AnnotateAttr::Create(S.Context, "Serializable", ArgsBuf.data(),
                                                ArgsBuf.size(), Attr.getRange()));
            } else {
                // Attach an annotate attribute to the Decl.
                D->addAttr(AnnotateAttr::Create(S.Context, "Serializable", nullptr, 0,
                                                Attr.getRange()));
            }
            return AttributeApplied;
        }
    };

} // namespace

static ParsedAttrInfoRegistry::Add<SerializationAttrInfo> X("Serializable", "");