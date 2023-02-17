// #include <stdio.h>
// #include <stdlib.h>
// typedef enum Node_Type {
// 	BASIC_NODE,   // no special usage (for roots only)
// 	// declarations
// 	DECL_LIST, // declarations
// 	DECL,    // declaration
// 	CONST,   // constant
// 	ID_LIST,	// identifier list
// 	ID_NODE,	// identifier
// 	VAR_NODE,	// variable (identifier)
// 	ARRAYSIZE,	// array size node
// 	ARRIDX,	// array index node
// 	CONST_NODE,	// const
// 	TYPE,

// 	// function decl
// 	SubProgDecl_LIST,
// 	SubProgDecl,
// 	SubProgHead,
// 	ARGUMENTS,
// 	PARAM_LIST,	// param list
// 	PARAMS,		// param

// 	// statements
// 	COMPSTMT,   // compound statement
// 	STMT_LIST,   // statements
// 	ASSIGN_NODE,  // assigment
// 	FUNC_CALL,    // function call
// 	IFELSE_NODE,      // if else statement
// 	WHILE_NODE,   // while statement
// 	// SIMPLE_NODE,  // continue or break statement
// 	// INCR_NODE,    // increment statement (non-expression one)
// 	// CALL_PARAMS,  // function call parameters

// 	// expressions
// 	EXPR_LIST,  // expression list
// 	ARITHM_NODE,  // arithmetic expression
// 	REL_NODE,     // relational expression
// 	BOOL_NODE,    // boolean expression
// 	// EQU_NODE,     // equality expression
// 	// REF_NODE,	  // identifier in expression

// 	// functions
// 	// FUNC_DECLS,   // function declarations
// 	// FUNC_DECL,    // function declaration
// 	// RET_TYPE,     // function return type
// 	// DECL_PARAMS,  // function parameters
// 	// RETURN_NODE,  // return statement of functions
// }Node_Type;

// typedef struct AST_Node{
// 	enum Node_Type type; // node type
// 	enum Node_Type type2; // node type
// 	struct AST_Node *left;  // left child
// 	struct AST_Node *mid; // mid child
// 	struct AST_Node *right; // right child
// 	struct AST_Node *next; // next sibiling
	
// }AST_Node;

// typedef struct AST_DeclarationList{
// 	enum Node_Type type;
// 	enum Node_Type type2;
// 	struct AST_Node *children;	// list of Declaration
// }AST_DeclarationList;

// void main()
// {
//     AST_DeclarationList* f = malloc (sizeof (AST_DeclarationList));
//    f->type = 1;
//    f->type2 = 3;
//    AST_Node *ptr = f;
//     // printf("type is %d %d\n", ((AST_Node *)f)->type, ((AST_Node *)f)->type3);
//     printf("type is %d %d\n", ptr->type, ptr->type2);
    

// }