#include "ast.h"

int
main(void)
{
    AST* term =
        AST_NEW(AST_ADD,
                AST_NEW(AST_NUMBER, 4),
                AST_NEW(AST_ADD,
                    AST_NEW(AST_MUL,
                        AST_NEW(AST_NUMBER, 2),
                        AST_NEW(AST_NUMBER, 10),
                        ),
                    AST_NEW(AST_MUL,
                        AST_NEW(AST_NUMBER, 3),
                        AST_NEW(AST_ADD,
                            AST_NEW(AST_NUMBER, 5),
                            AST_NEW(AST_NUMBER, 1),
                            ),
                        ),
                    ),
               );

    ASTPrint(term);
    COUT("\n\n");

    COUT(".global main\n");
    COUT("main:\n");
    ASTEmit(term);
    COUT("\tret\n\n");

    ASTClean(term);
}
