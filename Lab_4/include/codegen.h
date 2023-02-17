#ifndef __CODEGEN_H__
#define __CODEGEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "symtab.h"
#include "symtab.c"
#include "ast.h"
#include "ast.c"


void gencode_main(FILE *fp, char *program_id, AST_Node *DeclList, AST_Node *SubProgDeclList, AST_Node *CompStmt);

/* variable */
void gencode_init_global_var(FILE *fp, AST_IdentifierList *idList, AST_Type *typeNode);
void gencode_declare_global_var(FILE *fp, AST_IdentifierList *idList, AST_Type *typeNode);
void gencode_ref_variable(FILE *fp, AST_var *ast_var);
void gencode_store_variable(FILE *fp, AST_var *ast_var);

/* statement */
void gencode_compound_statement(FILE *fp, AST_CompoundStatment_node *CompStmt);
void gencode_statement(FILE *fp, AST_Statement *Stmt);
void gencode_assignment(FILE *fp, AST_Assignment *Stmt);
void gencode_ifelse(FILE *fp, AST_ifelse *Stmt);
void gencode_while(FILE *fp, AST_while *Stmt);
void gencode_function_call(FILE *fp, AST_ProcedureStatement *Stmt);
// void gencode_print(FILE *fp, AST_Expression *expr);
void gencode_set_function_info_util(Symtab *entry, char *funcName, char *arg_flag, char *ret_flag);

/* functions */
void gencode_function_declaration_list(FILE *fp, AST_SubprogramDeclarationList *SubProgDeclList);
void gencode_function_declaration(FILE *fp, AST_SubprogramDeclaration *SubProgDecl);
void gencode_function_declare_local_var(FILE *fp, Symtab *st_local, Symtab *st_param);

/* expression */
void gencode_expression(FILE *fp, AST_Expression *expr);

#endif
