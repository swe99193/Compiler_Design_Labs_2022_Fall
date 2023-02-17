%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "error.h"

#define MAX_LINE_LENG      256
extern int line_no, col_no, opt_list;
extern char buffer[MAX_LINE_LENG];
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */
extern int yyleng;

extern int yylex(void);
static void yyerror(const char *msg);
%}

%token PROGRAM VAR ARRAY OF INTEGER REAL STRING FUNCTION PROCEDURE PBEGIN END IF THEN ELSE WHILE DO NOT AND OR

%token LPAREN RPAREN SEMICOLON DOT COMMA COLON LBRACE RBRACE DOTDOT ASSIGNMENT ADDOP SUBOP MULOP DIVOP LTOP GTOP EQOP GETOP LETOP NEQOP

%token IDENTIFIER REALNUMBER INTEGERNUM SCIENTIFIC LITERALSTR

%union {
  int val;
  char* text;
  double dval;
}


%%

    /* define your snytax here */
Program 				: PROGRAM IDENTIFIER LPAREN IdentifierList RPAREN SEMICOLON
                        Declarations
                        SubprogramDeclarations
                        CompoundStatement
                        DOT
                        ;

IdentifierList  		: IDENTIFIER
                        | IdentifierList COMMA IDENTIFIER
                        ;

Declarations 			: /* lambda */
                        | Declarations VAR IdentifierList COLON Type SEMICOLON
                        ;

Type					: StandardType
                        | ArraySize StandardType
                        ;

ArraySize               : ARRAY LBRACE INTEGERNUM DOTDOT INTEGERNUM RBRACE OF
                        | ArraySize ARRAY LBRACE INTEGERNUM DOTDOT INTEGERNUM RBRACE OF
                        ;

StandardType			: INTEGER
                        | REAL
                        | STRING
                        ;

SubprogramDeclarations	: /* lambda */
                        | SubprogramDeclarations SubprogramDeclaration  
                        ;

SubprogramDeclaration 	: SubprogramHead Declarations CompoundStatement SEMICOLON
                        ;

SubprogramHead			: FUNCTION IDENTIFIER Arguments COLON StandardType SEMICOLON
                        | PROCEDURE IDENTIFIER Arguments SEMICOLON
                        ;

Arguments               : /* lambda */
                        | LPAREN ParameterList RPAREN
                        ;

/* function arguments */
ParameterList           : Params
                        | ParameterList SEMICOLON Params
                        ;

/* function arguments */
Params                  : OptionalVar IdentifierList COLON Type
                        ;

OptionalVar             : /* lambda */
                        | VAR 
                        ;

CompoundStatement       : PBEGIN OptionalStatements END
                        ;

OptionalStatements      : /* lambda */
                        | StatementList
                        ;

StatementList           : Statement
                        | StatementList SEMICOLON Statement
                        ;

Statement               : /* lambda */
                        | Variable ASSIGNMENT Expression
                        | ProcedureStatement
                        | CompoundStatement
                        | IF Expression THEN Statement ELSE Statement
                        | WHILE Expression DO Statement
                        ;

ProcedureStatement      : IDENTIFIER
                        | IDENTIFIER LPAREN ExpressionList RPAREN
                        ;


ExpressionList          : Expression
                        | ExpressionList COMMA Expression
                        ;

Expression              : Expression ADDOP Expression
                        | Expression SUBOP Expression
                        | Expression MULOP Expression
                        | Expression DIVOP Expression
                        | Expression GTOP Expression
                        | Expression LTOP Expression
                        | Expression GETOP Expression
                        | Expression LETOP Expression
                        | Expression EQOP Expression
                        | Expression NEQOP Expression
                        | Expression AND Expression
                        | Expression OR Expression
                        | NOT Expression
                        | LPAREN Expression RPAREN  // (1+2+...)
                        | Variable
                        | Num
                        | SUBOP Num
                        | SUBOP SUBOP SUBOP Num
                        | LITERALSTR
                        | Function_call
                        ;

Variable                : IDENTIFIER 
                        | IDENTIFIER Array
                        ;


Array                   : LBRACE Expression RBRACE
                        | Array LBRACE Expression RBRACE
                        ;

Num                     : REALNUMBER
                        | INTEGERNUM
                        | SCIENTIFIC
                        ;

Function_call           :IDENTIFIER LPAREN ExpressionList RPAREN
                        ;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "[ERROR] line %4d:%3d %s, Unmatched token: %s\n",
            line_no, col_no - yyleng, buffer, yytext);
}

int main(int argc, const char *argv[]) {

    if(argc > 2)
        fprintf( stderr, "Usage: ./parser [filename]\n" ), exit(0);

    FILE *fp = argc == 1 ? stdin : fopen(argv[1], "r");

    if(fp == NULL)
        fprintf( stderr, "Open file error\n" ), exit(-1);

    yyin = fp;
    yyparse();
    return 0;
}
