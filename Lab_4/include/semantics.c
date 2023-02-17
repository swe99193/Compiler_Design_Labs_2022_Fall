#ifndef __SEMANTICS_C__
#define __SEMANTICS_C__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "info.h"
#include "symtab.h"
#include "semantics.h"


// Note: parser.y will check redeclaration for us
void semantics_redeclared(char *name, int dtype, int line, int col){
    if(dtype == Int_type 
    || dtype == Real_type 
    || dtype == Array_type
    || dtype == Uninit_type
    || dtype == Void_type)
        fprintf(stderr, REDEF_VAR, line, col, name);
    else if(dtype == Function_type || dtype == Procedure_type){
        // fprintf(stderr, REDEF_FUN, line_no, col_no - yyleng, name);

        // FIXME: bad homework spec, change it back later
        // print the location of function
        fprintf(stderr, REDEF_FUN, line, col, name);
    }
    else 
        fprintf(stderr, "[ERROR] semantics_redeclared()\n");
}


// Note: parser.y will check redeclaration for us
void semantic_undeclared(char *name, int dtype, int line, int col){
    if(dtype == 0) // variable
        fprintf(stderr, UNDEC_VAR, line, col, name);
    else if(dtype == 1){    // function
        fprintf(stderr, UNDEC_FUN, line, col, name);
    }
    else 
        fprintf(stderr, "[ERROR] semantic_undeclared()\n");
}

/* type check of operation on two expressions */
void semantic_op_type_check(int Ltype, int Rtype, int line, int col, char* op){
    if(Ltype!=Uninit_type && Rtype!=Uninit_type && Ltype != Rtype)
        fprintf(stderr, ARITH_TYPE, line, col, op);
}

/* 
    type check of assignment 
    Assginment to uninitialized variable does NOT belong to type error
*/
void semantic_assign_type_check(int Ltype, int Rtype, int line, int col){
    // FIXME: assignment to undeclared function

    // Note: incorrect array dim is type error
    if(Ltype==Array_dim_insuff || Ltype == Function_undecl)
        fprintf(stderr, ASSIG_TYPE, line, col);
    else if(Ltype!=Uninit_type && Rtype!=Uninit_type && Ltype != Rtype)
        fprintf(stderr, ASSIG_TYPE, line, col);
}

/* error: array dimension access */
void semantic_arr_dim_err(char *name, int line, int col){
    fprintf(stderr, INDEX_MANY, line, col, name);
}

/* error: array index type */
void semantic_arr_idx_type_err(int line, int col){
    fprintf(stderr, INDEX_TYPE, line, col);
}

/* error: function missing return value */
void semantic_return_value_missing(char *funcName, int line, int col){
    fprintf(stderr, RETURN_VAL, line, col, funcName);
}

/* error: function missing return value */
void semantic_param_number_error(char *funcName, int line, int col){
    fprintf(stderr, WRONG_ARGS, line, col, funcName);
}

#endif