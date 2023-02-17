%{
/*
 * scanner.l
 *
 * lex input file for pascal scanner
 *
 */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symtab.h"
	#include "ast.h"
	#include "semantics.h"
	#include "parser.h"

int fileno(FILE *);

#define YY_USER_ACTION \
    yylloc.first_line = line_no; \
    yylloc.first_column = col_no; \
    col_no += yyleng;

#define MAX_LINE_LENG      256
#define LIST       strcat(buffer, yytext)
#define LIST_FLUSH do{ if(opt_list) printf("%s", buffer); *buffer = 0; }while(0)
#define LOG(TYPE) \
    do{ LIST; \
        if(opt_token) \
        fprintf(stderr, "token(type:%-10s) on line %4d, %3d : %s\n", \
            #TYPE, line_no, col_no - yyleng, yytext); \
    } while(0)

#ifdef __cplusplus
extern "C" int yylex(void);
#endif

int opt_list = 1, opt_token = 0;
int line_no = 1, col_no = 1;
char buffer[MAX_LINE_LENG];

int enter_inline_comment = 0;
int list_program = 1;
%}

%option nounput
%option noinput

A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]


%x IN_COMMENT INLINECOMMENT STRING

%%
                             /* v could do something */
{P}{R}{O}{G}{R}{A}{M}       {LOG(KEYWORD); return(PROGRAM);    }
{V}{A}{R}                   {LOG(KEYWORD); return(VAR);        }
{A}{R}{R}{A}{Y}             {LOG(KEYWORD); return(ARRAY);      }
{O}{F}                      {LOG(KEYWORD); return(OF);         }
{I}{N}{T}{E}{G}{E}{R}       {LOG(KEYWORD); return(INTEGER);    }
{R}{E}{A}{L}                {LOG(KEYWORD); return(REAL);       }
{S}{T}{R}{I}{N}{G}          {LOG(KEYWORD); return(STRING);     }
{F}{U}{N}{C}{T}{I}{O}{N}    {LOG(KEYWORD); return(FUNCTION);   }
{P}{R}{O}{C}{E}{D}{U}{R}{E} {LOG(KEYWORD); return(PROCEDURE);  }
{B}{E}{G}{I}{N}             {LOG(KEYWORD); return(PBEGIN);     }
{E}{N}{D}                   {LOG(KEYWORD); return(END);        }
{I}{F}                      {LOG(KEYWORD); return(IF);         }
{T}{H}{E}{N}                {LOG(KEYWORD); return(THEN);       }
{E}{L}{S}{E}                {LOG(KEYWORD); return(ELSE);       }
{W}{H}{I}{L}{E}             {LOG(KEYWORD); return(WHILE);      }
{D}{O}                      {LOG(KEYWORD); return(DO);         }
{N}{O}{T}                   {LOG(KEYWORD); return(NOT);        }
{A}{N}{D}                   {LOG(KEYWORD); return(AND);        }
{O}{R}                      {LOG(KEYWORD); return(OR);         }

"("                         {LOG(KEYWORD); return(LPAREN);     }
")"                         {LOG(KEYWORD); return(RPAREN);     }
";"                         {LOG(KEYWORD); return(SEMICOLON);  }
"."                         {LOG(KEYWORD); return(DOT);        }
","                         {LOG(KEYWORD); return(COMMA);      }
":"                         {LOG(KEYWORD); return(COLON);      }
"["                         {LOG(KEYWORD); return(LBRACE);     }
"]"                         {LOG(KEYWORD); return(RBRACE);     }
".."                        {LOG(KEYWORD); return(DOTDOT);     }
":="                        {LOG(KEYWORD); return(ASSIGNMENT); }
"+"                         {LOG(KEYWORD); return(ADDOP);      }
"-"                         {LOG(KEYWORD); return(SUBOP);      }
"*"                         {LOG(KEYWORD); return(MULOP);      }
"/"                         {LOG(KEYWORD); return(DIVOP);      }
">"                         {LOG(KEYWORD); return(GTOP);       }
"<"                         {LOG(KEYWORD); return(LTOP);       }
"="                         {LOG(KEYWORD); return(EQOP);       }
">="                        {LOG(KEYWORD); return(GETOP);      }
"<="                        {LOG(KEYWORD); return(LETOP);      }
"!="                        {LOG(KEYWORD); return(NEQOP);      }


  /* define identifier here */
  /* handle by two cases */
[a-zA-Z][a-zA-Z0-9]*     {  // FIXME
                            // printf("Match: %s\n", yytext);  // DEBUG
                            strcpy(yylval.name, yytext);  
                            LOG(IDENTIFIER); 
                            return(IDENTIFIER);      
                          }
[a-zA-Z][a-zA-Z0-9_]*[a-zA-Z0-9] {  // FIXME
                                    // printf("Match: %s\n", yytext); // DEBUG
                                    strcpy(yylval.name, yytext); 
                                    LOG(IDENTIFIER); 
                                    return(IDENTIFIER);      
                                  }

  /* define INTEGERNUM, REALNUMBER, SCIENTIFIC here */

  /* SCIENTIFIC: handle by two cases*/
[0-9]+.[0-9]+[Ee][+-]*[0-9]+   { 
                                yylval.val.fval = atof(yytext); 
                                LOG(NUMBER); 
                                return(SCIENTIFIC);      
                              }
[0-9]+[Ee][+-]*[0-9]+          { 
                                yylval.val.fval = atof(yytext); 
                                LOG(NUMBER); 
                                return(SCIENTIFIC);      
                              }

  /* INTEGERNUM, REALNUMBER */
[0-9]+                      {yylval.val.ival = atoi(yytext); LOG(NUMBER); return(INTEGERNUM);      }
[0-9]+\.[0-9]+              {yylval.val.fval = atof(yytext); LOG(NUMBER); return(REALNUMBER);      }


  /* define single/multiple line comment here */
\/\/                        { enter_inline_comment = 1; BEGIN(INLINECOMMENT);}
<INLINECOMMENT>.*           {LIST;}

"/*"                        { BEGIN(IN_COMMENT);      }
<IN_COMMENT>.               {LIST;}
<IN_COMMENT>"*/"            { BEGIN(INITIAL);}

  /* define string constant (LITERALSTR) here */
\"([^\"]|\\\"|\\n)*\"            {LOG(STRING); return(LITERALSTR);}

  /* define pragma here */
"#"(" ")?"pragma"(" ")+"list"(" ")+"on"          { list_program = 1; LIST;}
"#"(" ")?"pragma"(" ")+"list"(" ")+"off"         { list_program = 0; }



 /*
    yylval.text = strdup, strndup ... (yytext)
    yylval.dval = atoi, atof, strtod, strtol ... (yytext)
 */

[ \t\f\r]    LIST;

<INITIAL,IN_COMMENT,INLINECOMMENT>\n {
    LIST;
  if (list_program) {
    LIST_FLUSH;
  } else {
    *buffer = 0;
  }
  
  line_no++, col_no = 1;

  if (enter_inline_comment) {
    enter_inline_comment = 0;
    BEGIN(INITIAL);
  }
}

\n {
  LIST;
  LIST_FLUSH;
  line_no++, col_no = 1;
}

.  { LIST; fprintf(stderr, "[ERROR] line %4d:%3d lexical analyzer error %s\n", line_no, col_no - yyleng, yytext); }
