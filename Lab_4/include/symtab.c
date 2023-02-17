#ifndef __SYMTAB_C__
#define __SYMTAB_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "info.h"
#include "symtab.h"


/* current scope */
int cur_scope = -1;

/* flag variable for declaring */
// int declare = 0; // 1: declaring variable, 0: not

// linkedlist head
Symtab *Head = NULL;

Symtab *getGlobalSymtab(){
    return Head;
}


// Symbol Table Functions

// collect array info (reverse order)
void print_ArrayInfo_util(Array *cur, char *output){
    if(cur){
        print_ArrayInfo_util(cur->next, output);
        char buff[32] = {0};
        sprintf(buff, "[%d~%d]", cur->low, cur->high);
        strcat(output, buff);
    }
}

// collect array info, and store in output (string)
// return format: int[1~10][5~8]
void print_ArrayInfo(Symtab *cur, char *output) {
    if(cur->arraydtype == Int_type)
        strcpy(output, "int");
    else if(cur->arraydtype == Real_type)
        strcpy(output, "real");
    else
        strcpy(output, "[ERROR] ");

    // collect array info by traversing linked list

    // FIXME: bad homework spec, change it back later
    // print in reverse order
    print_ArrayInfo_util(cur->arrNode, output);

    // print in dimension order
    // Array* tmp = cur->arrNode;
    // while(tmp){
    //     char buff[32] = {0};
    //     sprintf(buff, "[%d~%d]", tmp->low, tmp->high);
    //     strcat(output, buff);
    //     tmp = tmp->next;
    // }
}

// print current symbol table
void symtab_print() {
    SHOW_SYMTAB_HEAD();

    Symtab *cur = Head;
    while (cur){
        int data_type = cur->dtype;
        char output[256] = {0};
        

        if (data_type == Void_type)
            strcpy(output, "void");
        else if (data_type == Int_type)
            strcpy(output, "int");
        else if (data_type == Real_type)
            strcpy(output, "real");
        else if (data_type == String_type)
            strcpy(output, "string");
        else if (data_type == Array_type)
        {
            print_ArrayInfo(cur, output);
        }
        else if (data_type == Function_type || data_type == Procedure_type){
            // return type info
            if(cur->return_type == Int_type)
                strcpy(output, "int ");
            else if(cur->return_type == Real_type)
                strcpy(output, "real ");
            else if(cur->return_type == Void_type)
                strcpy(output, "void ");
            else
                strcpy(output, "[ERROR] ");

            // collect params by traversing linked list
            Symtab* p_param = cur->paraminfo;
            if (p_param) {  // at least one param
                char buffer[128] = {0};   // int, real, int[3~6], ...
                while(p_param){
                    char _buff[128] = {0};
                    if(p_param->dtype == Int_type)
                        strcpy(_buff, "int");
                    else if(p_param->dtype == Real_type)
                        strcpy(_buff, "real");
                    else if(p_param->dtype == Array_type){
                        char tmp[100];
                        print_ArrayInfo(p_param, tmp);
                        strcpy(_buff, tmp);
                    }else
                        strcpy(_buff, "[ERROR]");

                    char _t_buff[130] = {0};
                    if (p_param->paraminfo)
                        sprintf(_t_buff, "%s, ", _buff);
                    else
                        sprintf(_t_buff, "%s", _buff); // last param
                    strcat(buffer, _t_buff);

                    p_param = p_param->paraminfo;
                }
                char param_str[132] = {0};
                sprintf(param_str, "(%s)", buffer);   // add brackets
                strcat(output, param_str);
            }
        } else
            strcpy(output, "[ERROR]");

        printf(SYMTAB_ENTRY_FORMAT, cur->name, cur->scope, output);

        cur = cur->next;
    }

    SHOW_SYMTAB_TAIL();
}


/* 
semantic analysis:
1. check undeclared variables
2. 

*/
/* search from current scope to the outer scope, return entry if exists 
    search in scope >= min_scope, if min_scope=0, search the whole table
*/
Symtab * symtab_search(char *name, int min_scope) {
    Symtab *cur = Head;
    while (cur && cur->scope >= min_scope){
        if(strcmp(cur->name, name) == 0)
            return cur;

        cur = cur->next;
    }

    return NULL;    // undeclared
}

/* search from cur_scope to the outer scope */
Symtab* symtab_global_search(char *name) {
    return symtab_search(name, 0);
}

/* search in local symbol table
    return entry if exists 
*/
Symtab * symtab_local_search(Symtab *st_local, char *name) {
    Symtab *cur = st_local;
    while (cur){
        if(strcmp(cur->name, name) == 0)
            return cur;

        cur = cur->localVar;
    }

    return NULL;    // undeclared
}

/* search in param table
    return entry if exists 
*/
Symtab * symtab_param_search(Symtab *st_param, char *name) {
    Symtab *cur = st_param;
    while (cur){
        if(strcmp(cur->name, name) == 0)
            return cur;

        cur = cur->paraminfo;
    }

    return NULL;    // undeclared
}


/*
   foo -> a(0) -> b(1) -> c(2)
*/
int symtab_count_localVarIdx(Symtab *st_local, char *name){
    int count = 0;
    Symtab *cur = st_local;

    while (cur){
        if(strcmp(cur->name, name) == 0)
            return count;

        count++;
        cur = cur->localVar;
    }

    return -1;
}

Symtab * symtab_search_idx(char *name, int scope) {
    Symtab *cur = Head;
    int count_base = 0;
    int count_target = 0;

    // find beginning of scope
    while (cur && cur->scope >= scope){
        if(strcmp(cur->name, name) == 0)
            return cur;

        cur = cur->next;
    }

    // find target of scope
    cur = Head;
    while (cur && cur->scope >= scope){
        if(strcmp(cur->name, name) == 0)
            return cur;

        cur = cur->next;
    }

    return NULL;    // undeclared
}


/* 
semantic analysis:
1. check redefined variables
2. 
*/
/* search scope first, return NULL if exist; else insert and return entry */
Symtab * symtab_insert(char *name, int dtype){
    if(symtab_search(name, cur_scope)) {  // exists

        return NULL;
    } else{
        Symtab *cur = malloc(sizeof(Symtab));
        strcpy(cur->name, name);
        cur->scope = cur_scope;
        cur->dtype = dtype;
        
        cur->next = Head;
        cur->arrNode = NULL;
        cur->paraminfo = NULL;
        cur->localVar = NULL;

        SHOW_INSERT_SYMTAB(name);

        Head = cur;
        return cur;
    }
}

/* call this after array declaration, append a dimension node 
    entry shoud be the array symtab entry
*/
void symtab_addArrayDim(Symtab * entry, int low, int high, bool init_mem){
    Array* cur = entry->arrNode;
    Array* new_node = malloc(sizeof(Array));
    new_node->low = low;
    new_node->high = high;
    new_node->next = NULL;

    if(!cur){   // first dim
        entry->arrNode = new_node;
        cur = new_node;
    } else{
        while(cur->next)  // go to end
            cur = cur->next;

        cur->next = new_node;
        cur = cur->next;
    }
    // Note: cur now should point to the new array node
            // printf("[DEBUG] new Array dim (%d, %d) \n", cur->low, cur->high); //DEBUG

    // allocate array
    if (init_mem) {
        int N = high - low + 1;
        if (entry->arraydtype == Int_type){
            cur->intarr = malloc(N * sizeof(int));
            // printf("[DEBUG] Allocate int Array \n"); //DEBUG
        }
        else if(entry->arraydtype == Real_type){
            cur->floatarr = malloc(N * sizeof(float));
            // printf("[DEBUG] Allocate real Array \n"); //DEBUG
        }
        else
            printf("[ERROR] cannot allocate array, variable type error, id: %s\n", entry->name);
    }
    
}

/* Right after Function declaration, add parameter info to function entry
    The parameter entries should be inserted already
    Assume the function node also exist
    ex: Func <- param1 <- param2(Head)
    param info are appended at Symtab.paraminfo
 */
void symtab_addParamInfo() {
    // locate nearest function entry
    Symtab* cur = Head;

    if(cur->dtype == Function_type || cur->dtype == Procedure_type)
        return; // no param

    while(cur) {
        if(cur->dtype == Function_type || cur->dtype == Procedure_type)
            break;

        if(!cur->next){ // reached end
            printf("[ERROR] no function found\n");
            return;
        }
        cur = cur->next;
    }

    // copy parameter info one-by-one, start from the last parameter
    // insert between cur & pivot
    Symtab* source = Head;
    Symtab* pivot = NULL;

    while(source->scope == Head->scope && (source->dtype != Function_type) && (source->dtype != Procedure_type)) {
        Symtab *new_st = malloc(sizeof(Symtab));
        strcpy(new_st->name, source->name);    // name
        int type = new_st->dtype = source->dtype; // dtype
        new_st->scope = source->scope; //scope
        new_st->next = NULL;
        new_st->arrNode = NULL;
        new_st->paraminfo = NULL;
        new_st->localVar = NULL;

        // extra work: array info
        if(type == Array_type) {
            new_st->arraydtype = source->arraydtype; // arraydtype
            Array* source_arr = source->arrNode;

            while(source_arr){   // arrNode
                symtab_addArrayDim(new_st, source_arr->low, source_arr->high, false); // without allocating mem
                source_arr = source_arr->next;
            }
        }

        // adjust link: cur->new->pivot
        new_st->paraminfo = pivot;
        cur->paraminfo = new_st;

        pivot = new_st;
        source = source->next;
    }
}

/* Simlar to symtab_addParamInfo()
    add both parameters and local variables to function entry
    ex: Func <- param1 <- param2 <- local1 <- local2(Head)
    local variable entries are appended at Symtab.localVar
 */
void symtab_function_addLocalVar() {
    // locate nearest function entry
    Symtab* cur = Head;

    if(cur->dtype == Function_type || cur->dtype == Procedure_type)
        return; // no param

    while(cur) {
        if(cur->dtype == Function_type || cur->dtype == Procedure_type)
            break;

        if(!cur->next){ // reached end
            printf("[ERROR] no function found\n");
            return;
        }
        cur = cur->next;
    }

    // copy local var one-by-one, start from the last parameter
    // insert between cur & pivot
    Symtab* source = Head;
    Symtab* pivot = NULL;

    while(source->scope == Head->scope && (source->dtype != Function_type) && (source->dtype != Procedure_type)) {
        Symtab *new_st = malloc(sizeof(Symtab));
        strcpy(new_st->name, source->name);    // name
        int type = new_st->dtype = source->dtype; // dtype
        new_st->scope = source->scope; //scope
        new_st->next = NULL;
        new_st->arrNode = NULL;
        new_st->paraminfo = NULL;
        new_st->localVar = NULL;

        // printf("[symtab] add local var to function entry: %s\n", new_st->name);

        // extra work: array info
        if(type == Array_type) {
            new_st->arraydtype = source->arraydtype; // arraydtype
            Array* source_arr = source->arrNode;

            while(source_arr){   // arrNode
                symtab_addArrayDim(new_st, source_arr->low, source_arr->high, false); // without allocating mem
                source_arr = source_arr->next;
            }
        }

        // adjust link: cur->new->pivot
        new_st->localVar = pivot;
        cur->localVar = new_st;

        pivot = new_st;
        source = source->next;
    }
}

/* set function, procedure return type */
void symtab_set_ret_type(int return_type){
    // locate nearest function entry
    Symtab* cur = Head;
    while(cur) {
        if(cur->dtype == Function_type || cur->dtype == Procedure_type){
            cur->return_type = return_type;
            return; // (no param also handled)
        }
        if(!cur->next){ // reached end
            printf("[ERROR] no function can be linked\n");
            return;
        }
        cur = cur->next;
    }
}

/* search from cur_scope to the outer scope */
Symtab* symtab_link_entry(char *name) {
    return symtab_search(name, 0);
}

// /* This function only for function return variable
//     only search in cur_scope
// */
// Symtab* symtab_link_func_var(char *name) {
//     return symtab_search(name, cur_scope);
// }

void open_scope(){
    SHOW_OPEN_SCOPE();
    cur_scope++;
}

// free list of array node
// Note: you must set all pointers to NULL after free
void freeArray(Array *cur){
    while (cur){
        Array *prev = cur;
        cur = cur->next;
        
        prev->next = NULL;

        free(prev->intarr);
        free(prev->floatarr);
        prev->intarr = NULL;
        prev->floatarr = NULL;

        free(prev);
    }
}

// free list of param node
// void freeParam(Param *cur){
//     while (cur){
//         Param *prev = cur;
//         cur = cur->next;
//         free(prev);
//     }
// }

/* delete all variables in this scope 
ex: t1 <- t2 <- t3(remove) <- t4(remove)
*/
// Note: you must set all pointers to NULL after free
void close_scope(){
    SHOW_CLOSE_SCOPE();
    symtab_print();


    Symtab *cur = Head;
    while (cur){
        if(cur->scope != cur_scope)
            break;
        Symtab *prev = cur;
        cur = cur->next;

        prev->next = NULL;

        freeArray(prev->arrNode);
        prev->arrNode = NULL; 
        prev->paraminfo = NULL; 
        prev->localVar = NULL; 

        // FIXME: free paramInfo

        free(prev);
    }
    Head = cur;

    cur_scope--;
}

#endif
