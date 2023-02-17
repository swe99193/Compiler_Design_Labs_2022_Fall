#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

char *tmp;

void test(char *name){
   int a = 10;
   char b = 'Q';
   char c = 'A';
   printf(name, a, b, c);
}

void main()
{
//    // Node_Type n_type = BOOL_NODE;
//    // int type = n_type;
//    // if(n_type == BOOL_NODE)
//    //  printf("Hit: %d\n", type);
//    // else
//    //  printf("Not Hit %d\n", type);

   //  int v = 0;
   // if(!v){
   //  printf("is false\n");
   // }

char name[100];
strcpy(name, " \n");
test(name);
//    // char header[100] = "YOUR HEADER: ";
//    // char str[100];
//    // sprintf(str, "%s[%d~%d]", header, -3, 9);
//    // printf("%s\n", str);
}