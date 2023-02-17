#ifndef __SYMTAB_H__
#define __SYMTAB_H__


/* maximum size of hash table */
// #define SIZE 211

/* maximum size of tokens-identifiers */
#define MAXTOKENLEN 128
#define MAXARRAYSIZE 1024

/* how parameter is passed */
#define BY_VALUE 1
#define BY_REFER 2

/* Types of values that we can have */
typedef union Value{
	int ival;
	double fval;
	char cval;
	char *sval;
}Value;

typedef enum dtype{
	Uninit_type,
	Void_type,	// PROGRAM, void, NULL
	Int_type,
	Real_type,
	Array_type,
	String_type,
	Function_type,
	Procedure_type,
	Array_dim_insuff, // this garbage is for mf testcase
	Function_undecl // this garbage is for mf testcase
}dtype;


// /* array info, no data */
// typedef struct ArrayInfo{
// 	int low;	// lower bound
// 	int high;

// 	// array
// 	ArrayInfo* next;
// }ArrayInfo;

// /* parameter info, no data */
// typedef struct ParamInfo{
// 	char name[MAXTOKENLEN];
// 	dtype dtype;	// data type

// 	// array
// 	ArrayInfo* arrNode;	// linked list (in dimension order)
// 	dtype arraydtype;

// 	struct Param *next;
// }ParamInfo;

/* array struct */
typedef struct Array{
	int low;	// lower bound
	int high;
	int* intarr;	// value (dynamically allocated)
	float* floatarr;
	struct Array *next;
}Array;


typedef struct Symtab{
	char name[MAXTOKENLEN];
	int scope;
	enum dtype dtype;	// data type: int, real, function, ...
	struct Symtab *next;

	// int, real, function variable
	Value val;	// value

	// array, value stored in linked list
	Array* arrNode;	// linked list (in dimension order)
	enum dtype arraydtype;

	// function, procedure
	struct Symtab *paraminfo;	// linked list (in declaration order)
	struct Symtab *localVar;	// linked list, as a local symtab (parameters & local variables) 
	// (in order) param1->param2->local1->local2

	// struct varInfo *paramInfo;
	enum dtype return_type;
	// FIXME: add all referenced variable info
	// struct Symtab *refVar;
	// struct varInfo *refVar;
}Symtab;


/* 
	(for reference, not used) prototype for paramInfo, refVar 
	only store info, e.g., no array space allocated
*/
typedef struct varInfo{
	char name[MAXTOKENLEN];
	int scope; // when function call, if scope == function scope, it is declared within function, else from outer scope

	// array
	Array* arrNode;	// linked list (in dimension order)
	enum dtype arraydtype;
}varInfo;




#endif