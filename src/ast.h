#pragma once
#include "logs.h"

#define AST_NEW(tag, ...) ASTNew((AST) {tag, {.tag = (struct tag) {__VA_ARGS__}}})

typedef struct AST AST;

struct AST
{
    enum
    {
        AST_NUMBER,
        AST_ADD,
        AST_MUL
    } tag;
    union
    {
        struct AST_NUMBER { int number; } AST_NUMBER;
        struct AST_ADD { AST* left, * right; } AST_ADD;
        struct AST_MUL { AST* left, * right; } AST_MUL;
    } data;
};

AST* ASTNew(AST ast)
{
    AST* pN = malloc(sizeof(AST));
    *pN = ast;

    return pN;
}

static inline void 
ASTPrint(AST* p)
{
    AST ast = *p;
    switch (ast.tag)
    {
        case AST_NUMBER:
            {
                struct AST_NUMBER data = ast.data.AST_NUMBER;
                COUT("%d", data.number);
            }
            break;

        case AST_ADD:
            {
                struct AST_ADD data = ast.data.AST_ADD;
                COUT("(");
                ASTPrint(data.left);
                COUT(" + ");
                ASTPrint(data.right);
                COUT(")");
            }
            break;

        case AST_MUL:
            {
                struct AST_MUL data = ast.data.AST_MUL;
                COUT("(");
                ASTPrint(data.left);
                COUT(" * ");
                ASTPrint(data.right);
                COUT(")");
            }
            break;
    }
}

static inline void
ASTEmit(AST* p)
{
    AST ast = *p;
    switch (ast.tag)
    {
        case AST_NUMBER:
            {
                struct AST_NUMBER data = ast.data.AST_NUMBER;
                COUT("\tmov rax, %d\n", data.number);
            }
            break;

        case AST_ADD:
            {
                struct AST_ADD data = ast.data.AST_ADD;
                ASTEmit(data.left);
                COUT("\tpush rax\n");
                ASTEmit(data.right);
                COUT("\tpop rbx\n");
                COUT("\tadd rax, rbx\n");
            }
            break;

        case AST_MUL:
            {
                struct AST_MUL data = ast.data.AST_MUL;
                ASTEmit(data.left);
                COUT("\tpush rax\n");
                ASTEmit(data.right);
                COUT("\tpop rbx\n");
                COUT("\tmul rbx\n");
            }
            break;
    }
}

static inline void
ASTClean(AST* p)
{
    AST ast = *p;
    switch (ast.tag)
    {
        case AST_NUMBER:
            break;

        case AST_ADD:
            {
                struct AST_ADD data = ast.data.AST_ADD;
                ASTClean(data.left);
                ASTClean(data.right);
            }
            break;

        case AST_MUL:
            {
                struct AST_MUL data = ast.data.AST_MUL;
                ASTClean(data.left);
                ASTClean(data.right);
            }
            break;
    }

    free(p);
}
