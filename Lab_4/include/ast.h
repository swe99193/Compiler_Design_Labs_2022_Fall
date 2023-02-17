#ifndef __AST_H__
#define __AST_H__

#include <stdint.h>
#include <stdbool.h>
#include "loc.h"
#include "symtab.h"


/* ---------------------NODE TYPES-------------------------- */

typedef enum Node_Type {
	BASIC_NODE,   // no special usage (for roots only)
	// declarations
	DECL_LIST, // declarations
	DECL,    // declaration
	ID_LIST,	// identifier list
	ID_NODE,	// identifier
	VAR_NODE,	// variable (identifier)
	ARRAYSIZE,	// array size node
	ARRIDX,	// array index node
	CONST_NODE,	// const
	TYPE_NODE,

	// function declaration
	SubProgDecl_LIST,
	SubProgDecl,
	SubProgHead,
	ARGUMENTS,
	PARAM_LIST,	// param list
	PARAMS,		// param

	// statements
	COMPSTMT,   // compound statement
	STMT_LIST,   // statements
	ASSIGN_NODE,  // assigment
	FUNC_CALL,    // function call
	IFELSE_NODE,      // if else statement
	WHILE_NODE,   // while statement
	// SIMPLE_NODE,  // continue or break statement
	// INCR_NODE,    // increment statement (non-expression one)
	// CALL_PARAMS,  // function call parameters

	// expressions
	EXPR_LIST,  // expression list
	EXPR,  // expression dummy node
	ARITHM_NODE,  // arithmetic expression
	REL_NODE,     // relational expression
	BOOL_NODE,    // boolean expression
	// EQU_NODE,     // equality expression
	// REF_NODE,	  // identifier in expression

	// functions
	// FUNC_DECLS,   // function declarations
	// FUNC_DECL,    // function declaration
	// RET_TYPE,     // function return type
	// DECL_PARAMS,  // function parameters
	// RETURN_NODE,  // return statement of functions
}Node_Type;

/* --------------------OPERATOR TYPES----------------------- */

typedef enum Arithm_op{
	Add_op,  // + operator
	Sub_op,  // - operator
	Mul_op,  // * operator
	Div_op, // / operator
	Incr_op, // ++ operator
	Decr_op, // -- operator
}Arithm_op;

typedef enum Bool_op{
	Or_op,  // || operator
	And_op, // && operator
	Not_op  // ! operator
}Bool_op;

typedef enum Rel_op{
	Greater_op,        // > operator
	Less_op,           // < operator
	Greater_equal_op,  // >= operator
	Less_equal_op,     // <= operator
	Equal_op,    // == operator
	Not_equal_op // != operator
}Rel_op;

typedef enum Equ_op{
	DUMMY
}Equ_op;

/* -----------------------AST NODES------------------------- */

/* basic node */
typedef struct AST_Node{
	enum Node_Type type; // node type
	struct AST_Node *next; // next sibiling
	// struct AST_Node *left;  // left child
	// struct AST_Node *mid; // mid child
	// struct AST_Node *right; // right child
	
}AST_Node;

/* basic node (list) */
typedef struct AST_List{
	enum Node_Type type; // node type
	struct AST_Node *children;	// Linkedlist: declarations, statements, 
}AST_List;


/* Declarations */
/* parent: AST_List */
typedef struct AST_DeclarationList{
	enum Node_Type type;
	struct AST_Node *children;	// list of Declaration
	// Note: above fields fixed format
}AST_DeclarationList;

/* parent: AST_Node */
typedef struct AST_Declaration{
	enum Node_Type type;
	struct AST_Node *next;
	// Note: above fields fixed format
	
	struct AST_Node *idList;	// IdentifierList node
	struct AST_Node *Type_node;	// Type node
}AST_Declaration;


/* identifier, const, type */
/* parent: AST_List */
typedef struct AST_IdentifierList{
	enum Node_Type type;
	struct AST_Node *children;	// list of id
	// Note: above fields fixed format
}AST_IdentifierList;

// this id node is for declaration
/* parent: AST_Node */
typedef struct AST_Id{
	enum Node_Type type;
	struct AST_Node *next;
	// Note: above fields fixed format

	Symtab *entry;	// symbol table entry
	char name[128];	
	enum dtype dtype; // int, real, array, function...
	bool redeclared;
}AST_Id;

// this id node is for expression & function call
typedef struct AST_var{
	enum Node_Type type;
	// Note: above fields fixed format
	
	Symtab *entry;	// symbol table entry
	char name[128];
	// enum dtype dtype;	// int, real, array, function; CANNOT be procedure
	int ref_type; // only int, real; 

	// only for array
	AST_Node *arrayidx; // list of array index node
	// int dim; // FIXME: total dimension

}AST_var;

/* parent: AST_Node */
typedef struct AST_ArraySize{
	enum Node_Type type;
	AST_Node* next;	// next size node
	// Note: above fields fixed format

	int low;
	int high;
	int dimension;
}AST_ArraySize;

/* parent: AST_Node */
typedef struct AST_Arrayidx{
	enum Node_Type type;
	AST_Node* next;	// next index node
	// Note: above fields fixed format

	int dimension;
	AST_Node* expr;	// Expression
}AST_Arrayidx;

typedef struct AST_Const{
	enum Node_Type type;
	// Note: above fields fixed format

	enum dtype dtype;
	Value val;
}AST_Const;


typedef struct AST_Type{
	enum Node_Type type;
	// Note: above fields fixed format

	enum dtype dtype;
	
	// (only for array)
	AST_Node* children;	// list of ArraySize
	enum dtype arraydtype;
}AST_Type;


/* function declaration */

/* parent: AST_List */
typedef struct AST_SubprogramDeclarationList{
	enum Node_Type type;
	struct AST_Node *children;	// list of SubprogramDeclaration
	// Note: above fields fixed format
}AST_SubprogramDeclarationList;

/* parent: AST_Node */
typedef struct AST_SubprogramDeclaration{
	enum Node_Type type;
	AST_Node* next;
	// Note: above fields fixed format
	
	AST_Node* head;	// SubprogramHead
	AST_Node* declList;	// DeclarationList
	AST_Node* compstmt;	// CompoundStatement
}AST_SubprogramDeclaration;


typedef struct AST_SubprogramHead{
	enum Node_Type type;
	// Note: above fields fixed format
	
	enum dtype dtype;	// Function, Procedure
	AST_Node* id;	// identifier
	AST_Node* arguments;	// Arguments
	enum dtype return_type;	// return type
}AST_SubprogramHead;


typedef struct AST_Arguments{
	enum Node_Type type;
	// Note: above fields fixed format
	
	AST_Node* paramList;	// ParameterList
}AST_Arguments;


/* parent: AST_List */
typedef struct AST_ParameterList{
	enum Node_Type type;
	struct AST_Node *children;	// list of Params
	// Note: above fields fixed format
}AST_ParameterList;

/* parent: AST_Node */
typedef struct AST_Params{
	enum Node_Type type;
	AST_Node* next;
	// Note: above fields fixed format

	AST_Node* idList;		// IdentifierList
	AST_Node* Type_node;	// Type node
}AST_Params;



/* Statements */

/* basic node (statement) */
/* parent: AST_Node */
typedef struct AST_Statement{
	enum Node_Type type; // node type
	struct AST_Node *next; // next sibiling
	// Note: above fields fixed format
}AST_Statement;

// stmt3: can also be a statment node
/* parent: AST_Statement */
typedef struct AST_CompoundStatment_node{
	enum Node_Type type; // node type
	AST_Node* next;
	// Note: above fields fixed format
	
	AST_Node* stmtList;	// Statement_List
}AST_CompoundStatment_node;


/* parent: AST_List */
typedef struct AST_StatementList{
	enum Node_Type type; // node type
	struct AST_Node *children;	// list of statement
	// Note: above fields fixed format
}AST_StatementList;

// stmt1
/* parent: AST_Statement */
typedef struct AST_Assignment{
	enum Node_Type type; // node type
	AST_Node* next; // next statement
	// Note: above fields fixed format

	AST_Node* variable;		// Variable
	AST_Node* expr;	// Expression
}AST_Assignment;

// stmt2
/* parent: AST_Statement */
typedef struct AST_ProcedureStatement{
	enum Node_Type type; // node type
	AST_Node* next;
	// Note: above fields fixed format

	AST_Node* id;		// identifier
	AST_Node* exprList;	// ExpressionList
}AST_ProcedureStatement;

// stmt3 ⬆⬆⬆⬆⬆
// Compound Statement

// stmt4
/* parent: AST_Statement */
typedef struct AST_ifelse{
	enum Node_Type type; // node type
	AST_Node* next;
	// Note: above fields fixed format

	AST_Node* expr;		// Expression
	AST_Node* ifstmt;		// Statement: Assignment/CompoundStmt/ProcedureStmt/ifelse/while
	AST_Node* elsestmt;	// Statement
}AST_ifelse;

// stmt5
/* parent: AST_Statement */
typedef struct AST_while{
	enum Node_Type type; // node type
	AST_Node* next;
	// Note: above fields fixed format
	
	AST_Node* expr;		// Expression
	AST_Node* stmt;		// Statement
}AST_while;


/* Expression */

/* parent: AST_List */
typedef struct AST_ExpressionList{
	enum Node_Type type; // node type
	struct AST_Node *children;	// list of Expression
	// Note: above fields fixed format
}AST_ExpressionList;


/* Basic node: expression
	dummy node for passing info 
*/
/* parent: AST_Node */
typedef struct AST_Expression{
	enum Node_Type type; // node type
	AST_Node* next;
	enum dtype dtype; // data type after expression
	// Note: above fields fixed format
	
	AST_Node *subExpr;
}AST_Expression;


/* basic node: operator expression node (left and right expression) */
/* parent: AST_Expression */
typedef struct AST_operator_expr{
	enum Node_Type type; // node type
	AST_Node* next;
	enum dtype dtype;
	// Note: above fields fixed format

	enum Arithm_op op;

	AST_Node* Lexpr;
	AST_Node* Rexpr;
}AST_operator_expr;


/* parent: AST_Expression */
typedef struct AST_arithm{
	enum Node_Type type; // node type
	AST_Node* next;
	enum dtype dtype;
	// Note: above fields fixed format

	enum Arithm_op op;

	AST_Node* Lexpr;
	AST_Node* Rexpr;
}AST_arithm;

/* parent: AST_Expression */
typedef struct AST_relation{
	enum Node_Type type; // node type
	AST_Node* next;
	enum dtype dtype;
	// Note: above fields fixed format

	enum Rel_op op;

	AST_Node* Lexpr;
	AST_Node* Rexpr;
}AST_relation;

/* parent: AST_Expression */
typedef struct AST_bool{
	enum Node_Type type; // node type
	AST_Node* next;
	enum dtype dtype;
	// Note: above fields fixed format

	enum Bool_op op;

	AST_Node* Lexpr;
	AST_Node* Rexpr;
}AST_bool;


#endif
