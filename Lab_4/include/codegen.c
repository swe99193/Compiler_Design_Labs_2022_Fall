#ifndef __CODEGEN_C__
#define __CODEGEN_C__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "codegen.h"

char progName[100] = {0}; // program name(id)
int Label = 0;
int codegen_scope = 0; // scope for codegen.c only, base scope = 0
Symtab *st_local = NULL; // local symtab, function local var
Symtab *st_param = NULL; // param symtab, function parameter
char curFuncName[100] = {0}; // current function where gencode is located

int num_locals = 20; // max num of local variables in stack

/* main assembly code generation function */
void gencode_main(FILE *fp, char *program_id, AST_Node *_DeclList, AST_Node *_SubProgDeclList, AST_Node *_CompStmt){
	strcpy(progName, program_id);
    AST_DeclarationList *DeclList = _DeclList;

    fprintf(fp, ".class public %s\n", progName);
    fprintf(fp, ".super java/lang/Object\n\n");
    

    // global variables
    AST_Declaration *Decl = (AST_Declaration *)(DeclList->children);
    while(Decl){
        AST_IdentifierList *idList = Decl->idList;
        AST_Type *typeNode = Decl->Type_node;
        gencode_declare_global_var(fp, idList, typeNode);

        Decl = (AST_Declaration *)(Decl->next); // next sibling
    }

    fprintf(fp, ".method public static main([Ljava/lang/String;)V\n");
    fprintf(fp, "\t.limit locals 50\n");
    fprintf(fp, "\t.limit stack 50\n");

    Decl = (AST_Declaration *)(DeclList->children);
    while(Decl){
        AST_IdentifierList *idList = Decl->idList;
        AST_Type *typeNode = Decl->Type_node;
        gencode_init_global_var(fp, idList, typeNode);

        Decl = (AST_Declaration *)(Decl->next); // next sibling
    }

    gencode_compound_statement(fp, (AST_CompoundStatment_node *)_CompStmt);
    
    fprintf(fp, "\treturn\n");
    fprintf(fp, ".end method\n");

    gencode_function_declaration_list(fp, (AST_SubprogramDeclarationList *)_SubProgDeclList);
}

void gencode_init_global_var(FILE *fp, AST_IdentifierList *idList, AST_Type *typeNode){
/*
	ldc 0.0
	putstatic foo/g F

    ldc 0
    multianewarray [I 1
    putstatic foo/a [I

    ldc 0
    ldc 0
    multianewarray [[I 2
    putstatic foo/b [[I
*/
    AST_Id *id = (AST_Id *)(idList->children);

    int dtype = typeNode->dtype;

    if (dtype == Int_type) {
        while (id){
            fprintf(fp, "\tldc 0\n");
            fprintf(fp, "\tputstatic %s/%s I\n", progName, id->name);

            id = (AST_Id *)(id->next);
        }
    }
    else if(dtype == Real_type) {
        while (id){
            fprintf(fp, "\tldc 0.0\n");
            fprintf(fp, "\tputstatic %s/%s F\n", progName, id->name);

            id = (AST_Id *)(id->next);
        }
    }
    else if(dtype == String_type) {
        while (id){
            fprintf(fp, "\tldc \"\"\n"); // init empty string
            fprintf(fp, "\tputstatic %s/%s Ljava/lang/String;\n", progName, id->name);

            id = (AST_Id *)(id->next);
        }
    }
    else if(dtype == Array_type){
        AST_ArraySize *arraySize = (AST_ArraySize *)(typeNode->children);
        int arraydtype = typeNode->arraydtype;
        
        char type_flag = 'I'; // I, F
        char brackets[100] = {0};
        char size[100] = {0};

        type_flag = (arraydtype == Int_type) ? 'I': 'F';

        // count dimension
        int dim = 0;
        while(arraySize){
            brackets[dim] = '[';
            size[dim] = (arraySize->high - arraySize->low + 1);
            arraySize = (AST_ArraySize *)arraySize->next;
            dim++;
        }

        if (dim == 0){
            fprintf(stderr, "[ERROR] gencode: dimension 0 ..\n");
            return;
        }

        while (id){
            for (int i = 0; i < dim; i++)
                fprintf(fp, "\tldc %d\n", size[i]);
            fprintf(fp, "\tmultianewarray %s%c %d\n", brackets, type_flag, dim);
            fprintf(fp, "\tputstatic %s/%s %s%c\n", progName, id->name, brackets, type_flag);

            id = (AST_Id *)(id->next);
        }
    }
}

// declare
void gencode_declare_global_var(FILE *fp, AST_IdentifierList *idList, AST_Type *typeNode){
/*
    .field public static a I
    .field public static b F
    .field public static d [I
    .field public static e [F
    .field public static k [[F
    .field public static l [[I
*/
    AST_Id *id = (AST_Id *)(idList->children);
    char type_flag[100] = {0}; // I, F
    char brackets[100] = {0};

    int dtype = typeNode->dtype;

    if (dtype == Int_type) {
        strcpy(type_flag, "I");
    }
    else if(dtype == Real_type) {
       strcpy(type_flag, "F");
    }
    else if(dtype == String_type) {
        strcpy(type_flag, "Ljava/lang/String;");
    }
    else if(dtype == Array_type){
        AST_ArraySize *arraySize = (AST_ArraySize *)(typeNode->children);
        int arraydtype = typeNode->arraydtype;

        strcpy(type_flag, (arraydtype == Int_type) ? "I": "F");

        // count dimension
        int dim = 0;
        while(arraySize){
            brackets[dim] = '['; // add brackets
            dim++;
            arraySize = (AST_ArraySize *)arraySize->next;
        }

        if (dim == 0){
            fprintf(stderr, "[ERROR] dimension 0 ..\n");
            return;
        }
    }

    while (id){
        printf("declare variable: %s\n", id->name);// DEBUG
        fprintf(fp, ".field public static %s %s%s\n", id->name, brackets, type_flag);

        id = (AST_Id *)(id->next);
    }
}

// Rvalue (load)
void gencode_ref_variable(FILE *fp, AST_var *ast_var){
/*
    getstatic foo/b I
    
    iload 1

    getstatic foo/b [[I
    ldc 1
    ldc 1
    isub
    aaload
        // load array sub dimension

    getstatic foo/b [[I
    ldc 1
    ldc 1
    isub
    aaload
    ldc 2
    ldc 1
    isub
    iaload
        // load array value
*/
    AST_var *node = ast_var;
    char varName[128];
    int localVarIdx = -1; // local variables declared order

    strcpy(varName, node->name);

    // external function
    if(strcmp(varName, "readlnI") == 0){
        gencode_function_call(fp, ProcedureStatement_node(node, NULL));
        return;
    }

    // search symtab, local first
    Symtab* entry = NULL;
    if (codegen_scope > 0){
        entry = symtab_local_search(st_local, varName);
        localVarIdx = symtab_count_localVarIdx(st_local, varName);
    }
    
    if(entry == NULL)
        entry = symtab_global_search(varName);

    if(entry == NULL){
        fprintf(stderr, "[ERROR] gencode: undeclared variable %s\n", varName);
        return;
    }

    printf("[load] var name: %s, localVarIdx: %d\n", varName, localVarIdx); // DEBUG

    if(entry->dtype == Int_type || entry->dtype == Real_type || entry->dtype == String_type){
        /* var ref */
        char type_flag[100] = {0};
        if (entry->dtype == Int_type)
            strcpy(type_flag, "I");
        else if(entry->dtype == Real_type)
            strcpy(type_flag, "F");
        else if(entry->dtype == String_type)
            strcpy(type_flag, "Ljava/lang/String;");

        if(entry->scope == 0){
            // global var
            // getstatic foo/b I
            fprintf(fp, "\tgetstatic %s/%s %s\n", progName, varName, type_flag);
        } else{
            // local var
            // iload 1
            // TODO: local string
            if (entry->dtype == Int_type)
                strcpy(type_flag, "i");
            else if(entry->dtype == Real_type)
                strcpy(type_flag, "f");
            fprintf(fp, "\t%sload %d\n", type_flag, localVarIdx);
        }

        return;

    } else if (entry->dtype == Array_type) {
        /* array ref */
        Array* symtab_Array = entry->arrNode;

        int dim = 0;
        char brackets[100] = {0};
        char type_flag = (entry->arraydtype == Int_type) ? 'I': 'F';

        // traverse symtab array
        while(symtab_Array){
            brackets[dim] = '['; // add brackets
            dim++;
            symtab_Array = symtab_Array->next;
        }
        
        if (dim == 0){
            fprintf(stderr, "[ERROR] dimension 0 ..\n");
            return;
        }

        if(entry->scope == 0)
            fprintf(fp, "\tgetstatic %s/%s %s%c\n", progName, varName, brackets, type_flag);
            // global
        else
            fprintf(fp, "\taload %d\n", localVarIdx);
            // local

        symtab_Array = entry->arrNode;
        AST_Arrayidx * ast_arrayidx = (AST_Arrayidx *)(node->arrayidx);
        while(ast_arrayidx && symtab_Array->next) {
            int low_bound = symtab_Array->low;
            AST_Expression* idxExpr = ast_arrayidx->expr;

            gencode_expression(fp, idxExpr);
            fprintf(fp, "\tldc %d\n", low_bound);
            fprintf(fp, "\tisub\n");
            fprintf(fp, "\taaload\n");

            ast_arrayidx = (AST_Arrayidx *)ast_arrayidx->next;
            symtab_Array = symtab_Array->next;
        }

        if(ast_arrayidx == NULL)
            printf("[gencode] reference array sub dimension\n"); // DEBUG

        type_flag = (entry->arraydtype == Int_type) ? 'i': 'f';
        if(ast_arrayidx){
            int low_bound = symtab_Array->low;
            AST_Expression* idxExpr = ast_arrayidx->expr;
            gencode_expression(fp, idxExpr);
            fprintf(fp, "\tldc %d\n", low_bound);
            fprintf(fp, "\tisub\n");
            fprintf(fp, "\t%caload\n", type_flag);
        }
        return;
    
    } else if (entry->dtype == Function_type) {
        // function call(no params)
        // create a dummy AST_ProcedureStatement
        gencode_function_call(fp, ProcedureStatement_node(node, NULL));
        return;
        
    }else{
        fprintf(stderr, "[ERROR] gencode: load reference type error\n");
        return;

    }
}

/* Lvalue (store)
    before calling this function, the stored value is on the top of stack 
*/
void gencode_store_variable(FILE *fp, AST_var *ast_var){
/*
    putstatic foo/b I

    istore 1

    ldc 10 <-- stored value
    getstatic foo/arr [[I
    ldc 1
    ldc 1
    isub
    aaload
    swap <-- swap stored value
    ldc 2
    ldc 1
    isub
    swap <-- swap stored value
    iastore
*/
    AST_var *node = ast_var;
    char varName[128];
    int localVarIdx = -1; // local variables declared order

    strcpy(varName, node->name);

    // search symtab, local first
    Symtab* entry = NULL;
    if (codegen_scope > 0){
        entry = symtab_local_search(st_local, varName);
        localVarIdx = symtab_count_localVarIdx(st_local, varName);
    }
    
    if(entry == NULL)
        entry = symtab_global_search(varName);

    if(entry == NULL){
        fprintf(stderr, "[ERROR] gencode: undeclared variable %s\n", varName);
        return;
    }

    printf("[store] var name: %s, localVarIdx: %d\n", varName, localVarIdx); // DEBUG

    if(entry->dtype == Int_type || entry->dtype == Real_type || entry->dtype == String_type){
        /* var ref */
        char type_flag[100] = {0};
        if (entry->dtype == Int_type)
            strcpy(type_flag, "I");
        else if(entry->dtype == Real_type)
            strcpy(type_flag, "F");
        else if(entry->dtype == String_type)
            strcpy(type_flag, "Ljava/lang/String;");

        if(entry->scope == 0){
            // global var
            // putstatic foo/b I
            fprintf(fp, "\tputstatic %s/%s %s\n", progName, varName, type_flag);
        } else{
            // local var
            // istore 1
            // TODO: local string
            if (entry->dtype == Int_type)
                strcpy(type_flag, "i");
            else if(entry->dtype == Real_type)
                strcpy(type_flag, "f");
            fprintf(fp, "\t%sstore %d\n", type_flag, localVarIdx);
        }

        return;

    } else if (entry->dtype == Array_type) {
        /* array ref */
        Array* symtab_Array = entry->arrNode;

        int dim = 0;
        char brackets[100] = {0};
        char type_flag = (entry->arraydtype == Int_type) ? 'I': 'F';

        // traverse symtab array
        while(symtab_Array){
            brackets[dim] = '['; // add brackets
            dim++;
            symtab_Array = symtab_Array->next;
        }
        
        if (dim == 0){
            fprintf(stderr, "[ERROR] dimension 0 ..\n");
            return;
        }
        
        if(entry->scope == 0)
            fprintf(fp, "\tgetstatic %s/%s %s%c\n", progName, varName, brackets, type_flag);
            // global
        else
            fprintf(fp, "\taload %d\n", localVarIdx);
            // local

        symtab_Array = entry->arrNode;
        AST_Arrayidx * ast_arrayidx = (AST_Arrayidx *)(node->arrayidx);

        while(symtab_Array && ast_arrayidx) {
            int low_bound = symtab_Array->low;
            AST_Expression* idxExpr = ast_arrayidx->expr;

            if(symtab_Array->next == NULL)
                fprintf(fp, "\tswap\n"); // place stored value at stack top

            gencode_expression(fp, idxExpr);
            fprintf(fp, "\tldc %d\n", low_bound);
            fprintf(fp, "\tisub\n");

            if(symtab_Array->next)
                fprintf(fp, "\taaload\n");

            ast_arrayidx = (AST_Arrayidx *)ast_arrayidx->next;
            symtab_Array = symtab_Array->next;
        }
        if(symtab_Array || ast_arrayidx)
            fprintf(stderr, "[ERROR] gencode: store array, dimension not consistent with symtab entry\n");

        type_flag = (entry->arraydtype == Int_type) ? 'i': 'f';
        fprintf(fp, "\tswap\n"); // place stored value at stack top
        fprintf(fp, "\t%castore\n", type_flag);
        return;
    
    } else{
        fprintf(stderr, "[ERROR] gencode: store reference type error\n");
        return;
    }
}

void gencode_compound_statement(FILE *fp, AST_CompoundStatment_node *CompStmt){
// begin stmt1->stmt2->stmt3 end
    if(CompStmt == NULL || (AST_StatementList *)(CompStmt->stmtList) == NULL){
        printf("[codegen] empty CompoundStatement or statementList\n");
        return;
    }

    // traverse linked list of statements
    AST_Statement *stmt = ((AST_StatementList *)(CompStmt->stmtList))->children;
    while(stmt){
        gencode_statement(fp, stmt);
        stmt = stmt->next;
    }
}

void gencode_statement(FILE *fp, AST_Statement *Stmt){
    if(Stmt == NULL){
        printf("[codegen] empty statement\n");
        return;
    }

    if(Stmt->type == COMPSTMT)
        gencode_compound_statement(fp, Stmt);
    else if(Stmt->type == ASSIGN_NODE){
        gencode_assignment(fp, Stmt);
    }
    else if(Stmt->type == IFELSE_NODE){
        gencode_ifelse(fp, Stmt);
    }
    else if(Stmt->type == WHILE_NODE){
        gencode_while(fp, Stmt);
    }
    else if(Stmt->type == FUNC_CALL){
        gencode_function_call(fp, Stmt);
    }
    
}

void gencode_assignment(FILE *fp, AST_Assignment *Stmt){
    gencode_expression(fp, Stmt->expr);

    AST_var* node = Stmt->variable;
    if(strcmp(node->name, curFuncName) == 0){
        // return value
        // FIXME: take the data type of the first expr AST
        printf("[gencode] assign RHS type: %d\n", ((AST_Expression *)Stmt->expr)->dtype); //DEBUG
        if(((AST_Expression *)Stmt->expr)->dtype == Int_type)
            fprintf(fp, "\tistore %d\n", num_locals-1);
        else
            fprintf(fp, "\tfstore %d\n", num_locals-1);
    }
    else
        gencode_store_variable(fp, Stmt->variable);
}


void gencode_ifelse(FILE *fp, AST_ifelse *Stmt){
/*
    EXPR1 == EXPR2
    ifne IF
    ELSE_STMT
    goto ENDIF
IF:
    IF_STMT
ENDIF:
*/
    int curLabel = Label;
    Label++;

    gencode_expression(fp, Stmt->expr);
    fprintf(fp, "ifne IF_%d\n", curLabel);

    if(Stmt->expr->type == COMPSTMT)
        gencode_compound_statement(fp, Stmt->elsestmt);
    else
        gencode_statement(fp, Stmt->elsestmt);

    fprintf(fp, "\tgoto ENDIF_%d\n", curLabel);

    fprintf(fp, "IF_%d:\n", curLabel);

    if(Stmt->expr->type == COMPSTMT)
        gencode_compound_statement(fp, Stmt->ifstmt);
    else
        gencode_statement(fp, Stmt->ifstmt);

    fprintf(fp, "ENDIF_%d:\n", curLabel);
}

void gencode_while(FILE *fp, AST_while *Stmt){
/*
    goto COND
WHILE:
    STMT
COND:
    EXPR1 == EXPR2
    ifne WHILE
*/
    int curLabel = Label;
    Label++;

    fprintf(fp, "\tgoto COND_%d\n", curLabel);
    fprintf(fp, "WHILE_%d:\n", curLabel);

    if(Stmt->expr->type == COMPSTMT)
        gencode_compound_statement(fp, Stmt->stmt);
    else
        gencode_statement(fp, Stmt->stmt);

    fprintf(fp, "COND_%d:\n", curLabel);

    gencode_expression(fp, Stmt->expr);

    fprintf(fp, "ifne WHILE_%d\n", curLabel);
}

/* function call (statement)
    see gencode_expression & gencode_ref_variable for RHS function call
 */
void gencode_function_call(FILE *fp, AST_ProcedureStatement *Stmt){
    char *function_id = ((AST_var *)Stmt->id)->name;
    AST_ExpressionList *exprList = (AST_ExpressionList *)Stmt->exprList;
    AST_Expression *expr = (exprList != NULL)? exprList->children : NULL;
    // expr point to the first param; if no param, point to NULL

    printf("function id: %s\n", ((AST_var *)Stmt->id)->name);// DEBUG

    // Note: writeln only accept one parameter
    if(strcmp(function_id, "writelnI") == 0){
        gencode_expression(fp, expr);
        fprintf(fp, "\tinvokestatic io/writelnI(I)V\n");
    }
    else if(strcmp(function_id, "writelnR") == 0){
        gencode_expression(fp, expr);
        fprintf(fp, "\tinvokestatic io/writelnR(F)V\n");
    }
    else if(strcmp(function_id, "writelnS") == 0){
        gencode_expression(fp, expr);
        fprintf(fp, "\tinvokestatic io/writelnS(Ljava/lang/String;)V\n");
    }else if(strcmp(function_id, "readlnI") == 0){
        fprintf(fp, "\tinvokestatic io/readlnI()I\n");
    }else{
        // function call (with params or no params)
        char funcName[128] = {0};
        char arg_flag[100] = {0};
        char ret_flag[100] = {0};

        strcpy(funcName, function_id);
        Symtab *entry = symtab_global_search(funcName);

        if(entry == NULL){
            fprintf(stderr, "[ERROR] gencode: cannot find entry of function call: %s\n", funcName);
            return;
        }
        gencode_set_function_info_util(entry, funcName, arg_flag, ret_flag);
        printf("[gencode] function call: %s\n", funcName);

        // prepare parameters
        while(expr){
            gencode_expression(fp, expr);
            expr = expr->next;
        }
        // call
        fprintf(fp, "\tinvokestatic %s/%s(%s)%s\n", progName, funcName, arg_flag, ret_flag);
    }

}

void gencode_set_function_info_util(Symtab *entry, char *funcName, char *arg_flag, char *ret_flag){
        // collect function param info
        Symtab *cur = entry->paraminfo;
        while(cur){
            if(cur->dtype == Int_type)
                strcat(arg_flag, "I");
            else if(cur->dtype == Real_type)
                strcat(arg_flag, "F");
            else if(cur->dtype == Array_type){
                Array *symtab_array = cur->arrNode;
                while(symtab_array){
                    strcat(arg_flag, "[");
                    symtab_array = symtab_array->next;
                }

                if (cur->arraydtype == Int_type) 
                    strcat(arg_flag, "I");
                else if(cur->arraydtype == Real_type) 
                    strcat(arg_flag, "F");
            }
            cur = cur->paraminfo;
        }

        if (entry->return_type == Int_type) 
            strcpy(ret_flag, "I");
        else if(entry->return_type == Real_type) 
            strcpy(ret_flag, "F");
        else
            strcpy(ret_flag, "V"); // no return value
}

void gencode_function_declaration_list(FILE *fp, AST_SubprogramDeclarationList *SubProgDeclList){
    // traverse linked list of function declarations
    AST_SubprogramDeclaration *decl = SubProgDeclList->children;
    while(decl){
        gencode_function_declaration(fp, decl);
        decl = decl->next;
    }
}

void gencode_function_declaration(FILE *fp, AST_SubprogramDeclaration *SubProgDecl){
// AST_SubprogramDeclaration -> SubprogramHead Declarations CompoundStatement

    char funcName[128] = {0};
    char arg_flag[100] = {0};
    char ret_flag[100] = {0};

    AST_Id* id= ((AST_SubprogramHead *)(SubProgDecl->head))->id;
    strcpy(funcName, id->name);

    Symtab *entry = symtab_global_search(funcName);

    if(entry){
        printf("[gencode] function declare id name: %s, scope: %d, symtab type: %d, ret type: %d\n", entry->name, entry->scope, entry->dtype, entry->return_type);
    }else{
        fprintf(stderr, "[ERROR] gencode: cannot find function entry: %s\n", funcName);
        return;
    }

    gencode_set_function_info_util(entry, funcName, arg_flag, ret_flag);

    fprintf(fp, "\n.method public static %s(%s)%s\n", funcName, arg_flag, ret_flag);
    fprintf(fp, "\t.limit locals %d\n", num_locals);
    fprintf(fp, "\t.limit stack 100\n");

    codegen_scope++;

    st_local = entry->localVar;
    st_param = entry->paraminfo;
    strcpy(curFuncName, funcName);

    if(st_local == NULL)
        printf("[gencode] st_local is NULL: %s\n", funcName);
    if(st_param == NULL)
        printf("[gencode] st_param is NULL: %s\n", funcName);

    // Symtab *tmp = st_local;
    // while(tmp){
    //     printf("[gencode] function %s's: %s\n", funcName, tmp->name); // DEBUG
    //     tmp = tmp->localVar;
    // }

    gencode_function_declare_local_var(fp, st_local, st_param);

    gencode_compound_statement(fp, SubProgDecl->compstmt);

    if(entry->dtype == Function_type){
        if(entry->return_type == Int_type){
            fprintf(fp, "\tiload %d\n", num_locals-1);
            fprintf(fp, "\tireturn\n");
        }
        else{
            fprintf(fp, "\tfload %d\n", num_locals-1);
            fprintf(fp, "\tfreturn\n");
        }
    }
    else if(entry->dtype == Procedure_type)
        fprintf(fp, "\treturn\n");
    else
        fprintf(stderr, "[ERROR] gencode: not a function type\n");

    fprintf(fp, ".end method\n\n");

    st_local = st_param = NULL; // clear local symtab
    memset(curFuncName, 0, strlen(curFuncName));
    codegen_scope--;
}

/* initialize local variables (exclude param) on stack */
void gencode_function_declare_local_var(FILE *fp, Symtab *st_local, Symtab *st_param){
/*
    ldc 0
    iload 1
                // int a = 0

    ldc 5
    ldc 5
    multianewarray [[I 2
    astore 3
                // int arr[5][5]
*/
    int localVarIdx = 0;

    // locate the first local var
    // st_local: param0(0) -> param1(1) -> local0(2) -> local1(3)
    // st_param: param0 -> param1
    while(st_param && st_local){
        st_param = st_param->paraminfo;
        st_local = st_local->localVar;
        localVarIdx++;
    }
    
    while(st_local) {
        printf("[gencode] declare function local variable: %s\n", st_local->name);
        if (st_local->dtype == Int_type) {
            fprintf(fp, "\tldc 0\n");
            fprintf(fp, "\tistore %d\n", localVarIdx);
        }
        else if(st_local->dtype == Real_type) {
            fprintf(fp, "\tldc 0.0\n");
            fprintf(fp, "\tfstore %d\n", localVarIdx);
        }else if (st_local->dtype == Array_type) {
            int dim = 0;
            char brackets[100] = {0};
            char type_flag = (st_local->arraydtype == Int_type) ? 'I': 'F';

            Array* symtab_Array = st_local->arrNode;
            while(symtab_Array) {
                brackets[dim] = '['; // add brackets
                dim++;

                int size = symtab_Array->high - symtab_Array->low + 1;
                fprintf(fp, "\tldc %d\n", size);

                symtab_Array = symtab_Array->next;
            }

            if (dim == 0){
                fprintf(stderr, "[ERROR] dimension 0 ..\n");
                return;
            }

            fprintf(fp, "\tmultianewarray %s%c %d\n", brackets, type_flag, dim);
            fprintf(fp, "\tastore %d\n", localVarIdx);
        
        } else{
            fprintf(stderr, "[ERROR] gencode: store reference type error\n");
        }

        st_local = st_local->localVar;
        localVarIdx++;
    }
}


void gencode_expression(FILE *fp, AST_Expression *expr){
/*
    after this function, the final value is located at the top of operand stack 
*/
    if(expr == NULL){
        fprintf(stderr, "[ERROR] gencode: expression is NULL\n");
        return;
    }

    if(expr->type == EXPR){
        // variables, constant, function call
        if(expr->subExpr->type == VAR_NODE){
            // variable, constant, function call (no params)
            // Note: call readlnI here
            gencode_ref_variable(fp, (AST_var *)expr->subExpr);
        }
        else if(expr->subExpr->type == CONST_NODE){
            AST_Const *node = expr->subExpr;
            if(node->dtype == Int_type)
                fprintf(fp, "\tldc %d\n", node->val.ival);
            else if(node->dtype == Real_type)
                fprintf(fp, "\tldc %f\n", node->val.fval);
            else if(node->dtype == String_type)
                fprintf(fp, "\tldc %s\n", node->val.sval);

            return;
        }
        else if(expr->subExpr->type == FUNC_CALL){
            // function call (with params)
            gencode_function_call(fp, (AST_ProcedureStatement *)expr->subExpr);
            return;
        }

    }else if(expr->type == ARITHM_NODE){
        // Note: post order visit
        int dtype = ((AST_arithm *)expr)->dtype;
        if(dtype != Int_type && dtype != Real_type && dtype != String_type){
            fprintf(stderr, "[ERROR] gencode: expression type error: %d\n", dtype);
            return;
        }

        if(dtype != String_type){
            gencode_expression(fp, ((AST_arithm *)expr)->Lexpr);
            gencode_expression(fp, ((AST_arithm *)expr)->Rexpr);

            char type_flag = (dtype == Int_type)? 'i': 'f'; // i, f
            switch(((AST_arithm *)expr)->op){
            case Add_op:
                fprintf(fp, "\t%cadd\n", type_flag);
                break;
            case Sub_op:
                fprintf(fp, "\t%csub\n", type_flag);
                break;
            case Mul_op:
                fprintf(fp, "\t%cmul\n", type_flag);
                break;
            case Div_op:
                fprintf(fp, "\t%cdiv\n", type_flag);
                break;
            }
        }else{
            // string concatentation
            fprintf(fp, "\tnew java/lang/StringBuffer\n");
            fprintf(fp, "\tdup\n");
            fprintf(fp, "\tinvokespecial java/lang/StringBuffer/<init>()V\n");
            
            gencode_expression(fp, ((AST_arithm *)expr)->Lexpr);

            fprintf(fp, "\tinvokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;\n");

            gencode_expression(fp, ((AST_arithm *)expr)->Rexpr);

            fprintf(fp, "\tinvokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;\n");
            fprintf(fp, "\tinvokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;\n");
            // now a new string is at operand stack top
        }
        return;
    } else if(expr->type == REL_NODE){
/*
ex: expr1 == expr2

    EXPR1
    EXPR2
    if_icmpeq TRUE
    ldc 0
    goto END_relop
TRUE:
    ldc 1
END_relop:

    EXPR1
    EXPR2
    fcmpg
    ldc 0
    if_icmpeq TRUE
    ldc 0
    goto END_relop
TRUE:
    ldc 1
END_relop:
*/

        // Note: post order visit
        int curLabel = Label;
        Label++;
        gencode_expression(fp, ((AST_relation *)expr)->Lexpr);
        gencode_expression(fp, ((AST_relation *)expr)->Rexpr);
        int dtype = ((AST_relation *)expr)->dtype;
        
        // need two target at operand stack top
        switch(((AST_relation *)expr)->op){
            case Greater_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmpgt TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc 1\n");
                    fprintf(fp, "\tif_icmpeq TRUE_%d\n", curLabel);
                }
                break;
            case Less_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmplt TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc -1\n");
                    fprintf(fp, "\tif_icmpeq TRUE_%d\n", curLabel); 
                }
                break;
            case Less_equal_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmple TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc 1\n");
                    fprintf(fp, "\tif_icmplt TRUE_%d\n", curLabel); 
                }
                break;
            case Greater_equal_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmpge TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc -1\n");
                    fprintf(fp, "\tif_icmpgt TRUE_%d\n", curLabel);  
                }
                break;
            case Equal_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmpeq TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc 0\n");
                    fprintf(fp, "\tif_icmpeq TRUE_%d\n", curLabel);
                }
                break;
            case Not_equal_op:
                if(dtype == Int_type)
                    fprintf(fp, "\tif_icmpne TRUE_%d\n", curLabel);
                else{
                    fprintf(fp, "\tfcmpg\n");
                    fprintf(fp, "\tldc 0\n");
                    fprintf(fp, "\tif_icmpne TRUE_%d\n", curLabel);
                }
                break;
        }
        fprintf(fp, "\tldc 0\n");
        fprintf(fp, "\tgoto END_relop_%d\n", curLabel);
        fprintf(fp, "TRUE_%d:\n", curLabel);
        fprintf(fp, "\tldc 1\n");
        fprintf(fp, "END_relop_%d:\n", curLabel);

        return;
    }else if(expr->type == BOOL_NODE){
/*
    EXPR
    ifeq TRUE
    ldc 0
    goto END_bool
TRUE:
    ldc 1
END_bool:
*/
        // Note: post order visit
        int curLabel = Label;
        Label++;
        switch(((AST_bool *)expr)->op){
            case Or_op:
                fprintf(stderr, "[ERROR] gencode: OR op is not implemented\n");
                // fprintf(fp, "\tif_icmplt ");
                break;
            case And_op:
                fprintf(stderr, "[ERROR] gencode: AND op is not implemented\n");
                // fprintf(fp, "\tif_icmpge ");
                break;
            case Not_op:
                gencode_expression(fp, ((AST_bool *)expr)->Lexpr);

                fprintf(fp, "\tifeq TRUE_%d\n", curLabel);
                fprintf(fp, "\tldc 0\n");
                fprintf(fp, "\tgoto END_bool_%d\n", curLabel);
                fprintf(fp, "TRUE_%d:\n", curLabel);
                fprintf(fp, "\tldc 1\n");
                fprintf(fp, "END_bool_%d:\n", curLabel);
                break;
        }
    
    }else {
        fprintf(stderr, "[ERROR] gencode: expression type error\n");
        return;
    }

}



#endif