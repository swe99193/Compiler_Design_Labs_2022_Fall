%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "loc.h"
#include "symtab.h"
#include "symtab.c"
#include "ast.h"
#include "ast.c"
#include "semantics.h"
#include "semantics.c"
#include "error.h"

#define YYLTYPE LocType

#define MAX_LINE_LENG      256
extern int line_no, col_no, opt_list;
extern char buffer[MAX_LINE_LENG];
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */
extern int yyleng;

// static Node root = NULL;

extern
#ifdef __cplusplus
"C"
#endif
int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

int dimension = 0;  // array
bool func_redeclared = false; // (success/failed)
bool program_param = true; // if it is main program's params
bool ret_val_missing = false; // if function return value missing
char curFunctionId[64];

void symtab_set_id_dtype(AST_Node *idList, AST_Node* Type);
int array_dim_error(Array *st, AST_Node* node);
bool param_num_incorrect(Symtab *st, AST_Node *ast_n);

%}

%locations

/* YYSTYPE union */
%union{
	// different types of values
	Value val;   
    int dummy;  // DEBUG
    int integer;
    char name[1024];
	
	// structures
	AST_Node* node;
}

%token PROGRAM VAR ARRAY OF INTEGER REAL STRING FUNCTION PROCEDURE PBEGIN END IF THEN ELSE WHILE DO NOT AND OR

%token LPAREN RPAREN SEMICOLON DOT COMMA COLON LBRACE RBRACE DOTDOT ASSIGNMENT ADDOP SUBOP MULOP DIVOP LTOP GTOP EQOP GETOP LETOP NEQOP

%token<val>  REALNUMBER INTEGERNUM SCIENTIFIC LITERALSTR

%token<name> IDENTIFIER


/* precedencies and associativities */
%left LPAREN RPAREN LBRACE RBRACE
%left MULOP DIVOP ADDOP SUBOP
%left GTOP LTOP EQOP GETOP LETOP NEQOP
%right ASSIGNMENT
%left COMMA

/* rule (non-terminal) definitions */
%type <node> Program IdentifierList Declarations
%type <node> Type ArraySize
%type <integer> StandardType
%type <node> SubprogramDeclarations SubprogramDeclaration SubprogramHead
%type <node> Arguments ParameterList Params OptionalVar
%type <node> CompoundStatement OptionalStatements StatementList Statement ProcedureStatement
%type <node> ExpressionList Expression
%type <node> Variable Array Num
%type <node> Function_call

%start Program

%%

    /* define your snytax here */
    /* @n return the sturct LocType of "n-th node", ex: @1 return the PROGRAM node's locType
       $n return the $$ result you assigned to the rule, ex: $1 */
prog : PROGRAM {
        root = NULL;
        /*
        printf("program node is @ line: %d, column: %d\n",
                    @1.first_line, @1.first_column);
        yylval.val, yylval.text, yylval.dval to get the data (type defined in %union) you assigned by scanner.
        */
    }
    ;

    /* define your snytax here */
Program 				: PROGRAM IDENTIFIER 
                        {
                            open_scope();
                            symtab_insert($2, Void_type);
                        }
                        LPAREN IdentifierList RPAREN SEMICOLON
                        {
                            program_param = false;
                        }
                        Declarations
                        SubprogramDeclarations
                        CompoundStatement
                        DOT
                        {
                            close_scope();

                            // ast_traversal(id_node($2)); 
                            // ast_traversal($4); 
                            // ast_traversal($7); 
                            // ast_traversal($8); 
                            // ast_traversal($9); 
                            // symtab_print();
                        }
                        ;
                        
/* variable declaration, function param declaration */
IdentifierList  		: IDENTIFIER
                {
                            // printf("[Declare] line %4d:%3d, variable: %s\n", line_no, col_no - yyleng, yytext); // DEBUG
                    if(!program_param){ // skip program params
                        Symtab *tmp = symtab_insert($1, Uninit_type); 
                        bool redeclared = (tmp)? false: true;

                        if(redeclared)
                            semantics_redeclared($1, Uninit_type, @1.first_line, @1.first_column);

                        $$ = IdentifierList_node();
                        addChild($$, id_node($1, redeclared));
                    }

                }
                        | IdentifierList COMMA IDENTIFIER
                {
                    if(!program_param){
                        Symtab *tmp = symtab_insert($3, Uninit_type); 
                        bool redeclared = (tmp)? false: true;

                        if(redeclared)
                            semantics_redeclared($3, Uninit_type, @3.first_line, @3.first_column);

                        $$ = $1;
                        addChild($$, id_node($3, redeclared));
                    }
                }
                        ;

/* variable declaration */
Declarations 			: /* lambda */
                {
                            $$ = DeclarationList_node();    // first node
                }
                        | Declarations VAR IdentifierList COLON Type SEMICOLON
                {
                            $$ = $1;
                            AST_Node* decl = Declaration_node($3, $5);
                            addChild($$, decl);

                    symtab_set_id_dtype($3, $5);

                }
                ;
/* ex:
    var a, b, c: integer;
    var d, e: array [ 1 .. 10 ] of integer; 
    var g, h: real;
    var k: array [ 23 .. 57 ] of array [ 23 .. 57 ] of real;
*/

Type					: StandardType
                        {
                            $$ = Type_node($1, -1);   // (Int, Real)
                        }
                        | ArraySize StandardType
                        {
                            $$ = Type_node(Array_type, $2); // (Array)
                            AST_Type* tmp = (AST_Type*) $$;
                            tmp->children = $1; // array size node
                        }
                        ;

ArraySize               : ARRAY LBRACE INTEGERNUM DOTDOT INTEGERNUM RBRACE OF
                        {
                            dimension = 0;  // global variable
                            $$ = ArraySize_node($3.ival, $5.ival, dimension);  // first node
                        }
                        | ArraySize ARRAY LBRACE INTEGERNUM DOTDOT INTEGERNUM RBRACE OF
                        {
                            $$ = $1;
                            dimension += 1;
                            addNext($$, ArraySize_node($4.ival, $6.ival, dimension));
                        }
                        ;


StandardType			: INTEGER
                        {
                            $$ = Int_type;
                        }
                        | REAL
                        {
                            $$ = Real_type;
                        }
                        | STRING
                        ;


/* function declaration */
SubprogramDeclarations	: /* lambda */
                        {
                            $$ = SubprogramDeclarationList_node();  // create upon the first function declaration
                        }
                        | SubprogramDeclarations SubprogramDeclaration
                        {
                            $$ = $1;
                            addChild($$, $2);
                        }
                        ;

/* function declaration */
SubprogramDeclaration 	: { ret_val_missing = true; } // init
                        SubprogramHead Declarations CompoundStatement SEMICOLON
                        {
                            $$ = SubprogramDeclaration_node($2, $3, $4);

                            // missing return value; skip procedure
                            int functype = ((AST_SubprogramHead *)$2)->dtype;
                            if(functype == Function_type && ret_val_missing)
                                semantic_return_value_missing(curFunctionId, @2.first_line, @2.first_column);

                            ret_val_missing = false; // reset
                            func_redeclared = false; // reset
                            close_scope();
                        }
                        ;

/* function declaration */
SubprogramHead			: FUNCTION IDENTIFIER
                { 
                    Symtab *tmp = symtab_insert($2, Function_type); 
                    func_redeclared = (tmp)? false: true; // init

                    if(func_redeclared)
                        semantics_redeclared($2, Function_type, @1.first_line, @1.first_column);

                    strcpy(curFunctionId, $2);
                    
                    open_scope();
                } 
                        Arguments COLON StandardType SEMICOLON
                {
                    $$ = SubprogramHead_node(Function_type, id_node($2, func_redeclared), $4, $6);
                    
                    if(!func_redeclared){ // only if function declared successfully 
                        symtab_set_ret_type($6);

                    }


                }
                        | PROCEDURE IDENTIFIER 
                { 
                    Symtab *tmp = symtab_insert($2, Procedure_type);
                    func_redeclared = (tmp)? false: true; // init

                    if(func_redeclared)
                        semantics_redeclared($2, Procedure_type, @1.first_line, @1.first_column);

                    open_scope();
                } 
                        Arguments SEMICOLON
                {
                    $$ = SubprogramHead_node(Procedure_type, id_node($2, func_redeclared), $4, Void_type);

                    if(!func_redeclared) // only if function declared successfully 
                        symtab_set_ret_type(Void_type);

                }
                        ;


/* function arguments */
Arguments               : /* lambda */ // (no argument)
                        {
                            $$ = Arguments_node(NULL);
                        }
                        | LPAREN ParameterList RPAREN
                        {
                            $$ = Arguments_node($2);
                        }
                        ;
/* function arguments */
ParameterList           : Params
                        {
                            $$ = ParameterList_node();  // create upon the first param
                            addChild($$, $1);
                        }
                        | ParameterList SEMICOLON Params
                        {
                            $$ = $1;
                            addChild($$, $3);
                        }
                        ;

/* function arguments */
Params                  : OptionalVar IdentifierList COLON Type
                {
                    $$ = Params_node($2, $4);   // belong to one type

                    symtab_set_id_dtype($2, $4);

                    
                    // add param info to function, only if function declared successfully
                    if(!func_redeclared){
                        symtab_addParamInfo(); 
                    }
                }
                        ;

/* function arguments */
OptionalVar             : /* lambda */
                        | VAR 
                        ;


CompoundStatement       : PBEGIN OptionalStatements END
                        {
                            $$ = CompoundStatement_node($2); 
                            // $2: StatementList_node
                        }
                        ;

OptionalStatements      : /* lambda */
                        {
                            $$ = NULL;
                        }
                        | StatementList
                        {
                            $$ = $1;
                        }
                        ;

StatementList           : Statement
                        {
                            $$ = StatementList_node();  // create upon the first statement
                            addChild($$, $1);
                        }
                        | StatementList SEMICOLON Statement
                        {
                            $$ = $1;
                            addChild($$, $3);
                        }
                        ;

Statement               : /* lambda */
                        {
                            $$ = NULL;
                        }
                        | Variable ASSIGNMENT Expression
                        {
                            // can put this to an assignment rule
                            $$ = Assignment_node($1, $3);

                           char LHSname[128];
                            strcpy(LHSname, ((AST_var *)$1)->name);

                            // undeclared function, assignment to its return value
                            if(func_redeclared && strcmp(LHSname, curFunctionId) == 0){
                                ((AST_var *)$1)->ref_type = Function_undecl;
                            }

                            // check LHS during function declaration, no side effect on other context
                            // redeclared function must have missing return value
                            if(!func_redeclared && strcmp(LHSname, curFunctionId) == 0)
                                ret_val_missing = false;
                                

                            // assignment type check
                            int Ltype = ((AST_var *)$1)->ref_type;
                            int Rtype = ((AST_Expression *)$3)->dtype;
                            semantic_assign_type_check(Ltype, Rtype, @1.first_line, @1.first_column);

 
                        }
                        | ProcedureStatement
                        {
                            $$ = $1;    /* pass node */
                        }
                        | CompoundStatement
                        {
                            $$ = $1;    /* pass node */
                        }
                        | IF Expression THEN Statement ELSE Statement
                        {
                            $$ = ifelse_node($2, $4, $6);
                        }
                        | WHILE Expression DO Statement
                        {
                            $$ = while_node($2, $4);
                        }
                        ;

/* function call (non-expression) */
ProcedureStatement      : IDENTIFIER
                        {
                            AST_Node *n = var_node($1);
                            $$ = ProcedureStatement_node(n, NULL);
                            
                            ((AST_var *)n)->entry = symtab_link_entry($1);
                            // ((AST_var *)n)->dtype

                            if(((AST_var *)n)->entry == NULL)
                                semantic_undeclared($1, 1, @1.first_line, @1.first_column);
                        }
                        | IDENTIFIER LPAREN ExpressionList RPAREN
                        {
                            AST_Node *n = var_node($1);
                            $$ = ProcedureStatement_node(n, $3);

                            Symtab *entry = symtab_link_entry($1);
                            ((AST_var *)n)->entry = entry;
                            // ((AST_var *)n)->dtype

                            if(entry == NULL)
                                semantic_undeclared($1, 1, @1.first_line, @1.first_column);

                            // if undeclared, skip params check
                            // traverse ExpressionList
                            if(entry != NULL){
                                Symtab *st = entry->paraminfo;
                                AST_Node *ast_n = ((AST_ExpressionList *)$3)->children;
                                if(param_num_incorrect(st, ast_n)){
                                    semantic_param_number_error($1, @1.first_line, @1.first_column);
                                }
                            }
                        }
                        ;

// func(a,b,c)
ExpressionList          : Expression
                        {
                            $$ = ExpressionList_node();  // create upon the first match
                            addChild($$, $1);
                        }
                        | ExpressionList COMMA Expression   
                        {
                            $$ = $1;
                            addChild($$, $3);
                        }
                        ;

Expression              : Expression ADDOP Expression
                        {
                            $$ = arithm_node(Add_op, $1, $3);
                            AST_Expression * Lexpr = (AST_Expression *)$1;
                            AST_Expression * Rexpr = (AST_Expression *)$3;

                            semantic_op_type_check(Lexpr->dtype, Rexpr->dtype, @2.first_line, @2.first_column, "+");

                            // printf("[Declare] line %4d:%3d , add\n", @1.first_line, @1.first_column); // DEBUG

                        }
                        | Expression SUBOP Expression
                        {
                            $$ = arithm_node(Sub_op, $1, $3);
                        }
                        | Expression MULOP Expression
                        {
                            $$ = arithm_node(Mul_op, $1, $3);
                        }
                        | Expression DIVOP Expression
                        {
                            $$ = arithm_node(Div_op, $1, $3);
                        }
                        | Expression GTOP Expression
                        {
                            $$ = relation_node(Greater_op, $1, $3);
                        }
                        | Expression LTOP Expression
                        {
                            $$ = relation_node(Less_op, $1, $3);
                        }
                        | Expression GETOP Expression
                        {
                            $$ = relation_node(Greater_equal_op, $1, $3);
                        }
                        | Expression LETOP Expression
                        {
                            $$ = relation_node(Less_equal_op, $1, $3);
                            AST_Expression * Lexpr = (AST_Expression *)$1;
                            AST_Expression * Rexpr = (AST_Expression *)$3;

                            semantic_op_type_check(Lexpr->dtype, Rexpr->dtype, @2.first_line, @2.first_column, "<=");
                        }
                        | Expression EQOP Expression
                        {
                            $$ = relation_node(Equal_op, $1, $3);
                        }
                        | Expression NEQOP Expression
                        {
                            $$ = relation_node(Not_equal_op, $1, $3);
                        }
                        | Expression AND Expression
                        {
                            $$ = bool_node(And_op, $1, $3);
                        }
                        | Expression OR Expression
                        {
                            $$ = bool_node(Or_op, $1, $3);
                        }
                        | NOT Expression
                        {
                            $$ = bool_node(Not_op, $2, NULL);
                        }
                        | LPAREN Expression RPAREN  // (1+2+...)
                        {
                            $$ = $2; /* pass information */
                        }
                        | Variable
                        {
                            $$ = Expression_node($1, ((AST_var *)$1)->ref_type); /* pass information */
                        }
                        | Num
                        {
                            $$ = Expression_node($1, ((AST_Const *)$1)->dtype);
                        }
                        | SUBOP Num
                        {
                            $$ = Expression_node($2, ((AST_Const *)$2)->dtype);
                        }
                        | SUBOP SUBOP SUBOP Num
                        {
                            $$ = Expression_node($4, ((AST_Const *)$4)->dtype);
                        }
                        | LITERALSTR
                        | Function_call
                        {
                            AST_Node *n = ((AST_ProcedureStatement *)$1)->id;
                            int ref_type = ((AST_var *)n)->ref_type;
                            $$ = Expression_node($1, ref_type);
                        }
                        ;
/* expression */
Variable                : IDENTIFIER 
            /* int, real, function call(no params), function return var */
                        {
                            $$ = var_node($1);
                            AST_var *this = (AST_var *) $$;
                            
                            Symtab *entry = this->entry = symtab_link_entry($1);

                            if(entry == NULL){
                                semantic_undeclared($1, 0, @1.first_line, @1.first_column);
                                this->ref_type = Uninit_type;
                            }
                            else {
                                if (entry->dtype == Int_type 
                                    || entry->dtype == Real_type)
                                    this->ref_type = entry->dtype;
                                else if(entry->dtype == Array_type)
                                    this->ref_type = Array_type;
                                else // function
                                    this->ref_type = entry->return_type;
                            }

                        }
                        | IDENTIFIER Array /* array */
                        {
                            $$ = var_node($1);
                            AST_var *this = (AST_var *) $$;   
                            
                            Symtab *entry = this->entry = symtab_link_entry($1);
                            // tmp->dtype
                            
                            this->arrayidx = $2; // array index node
                            // tmp->dim = $2; // FIXME: array dimension

                            if(entry == NULL){
                                semantic_undeclared($1, 0, @1.first_line, @1.first_column);
                                this->ref_type = Uninit_type;
                            }
                            else {
                                this->ref_type = entry->arraydtype;

                                // array dim check
                                int flag = array_dim_error(entry->arrNode, $2);
                                if(flag == 1) { // too many dim
                                    semantic_arr_dim_err($1, @1.first_line, @1.first_column);
                                }else if(flag == -1){ // too few dim
                                    this->ref_type = Array_dim_insuff; // not assignable
                                }

                            }


                        }
                        ;
/* expression */
Array                   : LBRACE Expression RBRACE
                        {
                            dimension = 0;  // global variable
                            $$ = Arrayidx_node($2, dimension);  // first node

                            // array index check
                            int dtype = ((AST_Expression *)$2)->dtype;
                            if( dtype != Int_type 
                                && dtype != Uninit_type){
                                semantic_arr_idx_type_err(@2.first_line, @2.first_column);
                            }
                        }
                        | Array LBRACE Expression RBRACE
                        {
                            $$ = $1;
                            dimension += 1;
                            AST_Node *n = Arrayidx_node($3, dimension);  // next dimension
                            addNext($$, n);


                            // array index check
                            int dtype = ((AST_Expression *)$3)->dtype;
                            if( dtype != Int_type 
                                && dtype != Uninit_type){
                                semantic_arr_idx_type_err(@3.first_line, @3.first_column);
                            }
                        }
                        ;
/* expression */
Num                     : REALNUMBER
                        {
                            $$ = const_node(Real_type, $1); // $1 (numeric value)
                        }
                        | INTEGERNUM
                        {
                            $$ = const_node(Int_type, $1);
                        }
                        | SCIENTIFIC
                        {
                            $$ = const_node(Real_type, $1);
                        }
                        ;
/* expression */
Function_call           :IDENTIFIER LPAREN ExpressionList RPAREN
                        {
                            AST_Node *n = var_node($1);
                            $$ = ProcedureStatement_node(n, $3);

                            Symtab *entry = symtab_link_entry($1);
                            ((AST_var *)n)->entry = entry;
                            

                            if(entry == NULL) {
                                semantic_undeclared($1, 1, @1.first_line, @1.first_column);
                                ((AST_var *)n)->ref_type = Uninit_type;
                            }
                            else{
                                // retreive dtype & return type from symtab
                                if(entry->dtype == Array_type)
                                    ((AST_var *)n)->ref_type = entry->arraydtype;
                                else if(entry->dtype == Function_type)
                                    ((AST_var *)n)->ref_type = entry->return_type;
                                else
                                    ((AST_var *)n)->ref_type = Uninit_type;
                            }

                            // if undeclared, skip params check
                            // traverse ExpressionList
                            if(entry != NULL){
                                Symtab *st = entry->paraminfo;
                                AST_Node *ast_n = ((AST_ExpressionList *)$3)->children;
                                if(param_num_incorrect(st, ast_n)){
                                    semantic_param_number_error($1, @1.first_line, @1.first_column);
                                }
                            }

                        }
                        ;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "[ERROR] line %4d:%3d %s, Unmatched token: %s\n",
            line_no, col_no - yyleng, buffer, yytext);
}


/* 
    Note: process AST_Node & Symtab at the same time
    
    Call this after id symtab are inserted.

    Note: handle redeclared variables (don't make changes to existing entry)

    AST_Node: set dtype of each id node, 
    Symtab: set symtab dtype, link symtab to each id node
    traverse linked list of id node
*/
void symtab_set_id_dtype(AST_Node *idList, AST_Node* Type){
    AST_Id *cur = (AST_Id *) ((AST_IdentifierList*) idList)->children;
    AST_Type *p_Type= (AST_Type *) Type;
    enum dtype dtype = p_Type->dtype;
        
    if (dtype == Int_type || dtype == Real_type){
        while(cur){
            cur->dtype = dtype;

            if(cur->redeclared){
                cur = (AST_Id *) cur->next;
                continue;
            }

            Symtab *entry = symtab_search(cur->name, cur_scope);
            if(entry == NULL) {
                /* printf("[ERROR] symtab not found, cannot set type"); */
                continue;
            }
            entry->dtype = dtype; // symtab set type

            cur->entry = entry; // link to symtab
            cur = (AST_Id *) cur->next;
        }
    }
    else if (dtype == Array_type){
        while(cur){
            cur->dtype = dtype;

            if(cur->redeclared){
                cur = (AST_Id *) cur->next;
                continue;
            }

            Symtab *entry = symtab_search(cur->name, cur_scope);
            if(entry == NULL) {
                /* printf("[ERROR] symtab not found, cannot set type"); */
                continue;
            }
            entry->dtype = dtype; // symtab set type
            entry->arraydtype = p_Type->arraydtype; // set array data type

            cur->entry = entry; // link to symtab
            cur = (AST_Id *) cur->next;


            // extra work: add dimension in symtab
            AST_ArraySize *ptr = (AST_ArraySize *) p_Type->children;
            while(ptr){
                int low = ptr->low;
                int high = ptr->high;
                /* printf("low, high: %d, %d", low, high); // DEBUG */
                symtab_addArrayDim(entry, low, high, false); // FIXME: mem turn off
                ptr = (AST_ArraySize *) ptr->next;
            }
        }
    }
}

/*
    traverse symtab (arrayinfo) & AST_Node (AST_Arrayidx) at the same time
*/
int array_dim_error(Array *st, AST_Node* ast_n){
    while(st && ast_n){
        st = st->next;
        ast_n = ast_n->next;
    }

    if(st == NULL && ast_n == NULL) // same size
        return 0;
    else if(st == NULL) // too many index
        return 1;
    else                // too few index
        return -1;
}


bool param_num_incorrect(Symtab *st, AST_Node *ast_n){
    int cnt = 0;

    while(ast_n){
        ast_n = ast_n->next;
        cnt += 1;
    }
    /* printf("[ERROR] cnt: %d\n", cnt); // DEBUG */
    while(st){
        st = st->paraminfo;
        cnt -=1;
    }
    /* printf("[ERROR] cnt: %d\n", cnt); // DEBUG */

    return cnt != 0;
}



int main(int argc, const char *argv[]) {

    if(argc > 2)
        fprintf( stderr, "Usage: ./parser [filename]\n" ), exit(0);

    FILE *fp = argc == 1 ? stdin : fopen(argv[1], "r");

    if(fp == NULL)
        fprintf( stderr, "Open file error\n" ), exit(-1);

    yyin = fp;
    yyparse();
    /* if(root){
        // do pass here
    } */
    return 0;
}
