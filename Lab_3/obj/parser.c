/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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


#line 116 "obj/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_OBJ_PARSER_H_INCLUDED
# define YY_YY_OBJ_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    VAR = 259,
    ARRAY = 260,
    OF = 261,
    INTEGER = 262,
    REAL = 263,
    STRING = 264,
    FUNCTION = 265,
    PROCEDURE = 266,
    PBEGIN = 267,
    END = 268,
    IF = 269,
    THEN = 270,
    ELSE = 271,
    WHILE = 272,
    DO = 273,
    NOT = 274,
    AND = 275,
    OR = 276,
    LPAREN = 277,
    RPAREN = 278,
    SEMICOLON = 279,
    DOT = 280,
    COMMA = 281,
    COLON = 282,
    LBRACE = 283,
    RBRACE = 284,
    DOTDOT = 285,
    ASSIGNMENT = 286,
    ADDOP = 287,
    SUBOP = 288,
    MULOP = 289,
    DIVOP = 290,
    LTOP = 291,
    GTOP = 292,
    EQOP = 293,
    GETOP = 294,
    LETOP = 295,
    NEQOP = 296,
    REALNUMBER = 297,
    INTEGERNUM = 298,
    SCIENTIFIC = 299,
    LITERALSTR = 300,
    IDENTIFIER = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "parser.y"

	// different types of values
	Value val;   
    int dummy;  // DEBUG
    int integer;
    char name[1024];
	
	// structures
	AST_Node* node;

#line 226 "obj/parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_OBJ_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

#define YYUNDEFTOK  2
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    95,   107,   112,   106,   132,   147,   164,   167,   184,
     188,   196,   201,   210,   214,   218,   224,   227,   235,   235,
     253,   252,   276,   275,   298,   301,   307,   312,   320,   335,
     336,   340,   348,   351,   357,   362,   370,   373,   399,   403,
     407,   411,   418,   429,   454,   459,   466,   477,   481,   485,
     489,   493,   497,   501,   509,   513,   517,   521,   525,   529,
     533,   537,   541,   545,   549,   550,   558,   581,   613,   625,
     642,   646,   650,   656
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "VAR", "ARRAY", "OF",
  "INTEGER", "REAL", "STRING", "FUNCTION", "PROCEDURE", "PBEGIN", "END",
  "IF", "THEN", "ELSE", "WHILE", "DO", "NOT", "AND", "OR", "LPAREN",
  "RPAREN", "SEMICOLON", "DOT", "COMMA", "COLON", "LBRACE", "RBRACE",
  "DOTDOT", "ASSIGNMENT", "ADDOP", "SUBOP", "MULOP", "DIVOP", "LTOP",
  "GTOP", "EQOP", "GETOP", "LETOP", "NEQOP", "REALNUMBER", "INTEGERNUM",
  "SCIENTIFIC", "LITERALSTR", "IDENTIFIER", "$accept", "Program", "$@1",
  "$@2", "IdentifierList", "Declarations", "Type", "ArraySize",
  "StandardType", "SubprogramDeclarations", "SubprogramDeclaration", "$@3",
  "SubprogramHead", "$@4", "$@5", "Arguments", "ParameterList", "Params",
  "OptionalVar", "CompoundStatement", "OptionalStatements",
  "StatementList", "Statement", "ProcedureStatement", "ExpressionList",
  "Expression", "Variable", "Array", "Num", "Function_call", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

#define YYPACT_NINF (-58)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      35,    -4,    56,   -58,   -58,    38,    16,   -58,     6,    68,
      66,   -58,   -58,   -58,   113,    16,   106,    -8,    -2,   -58,
      17,    96,    58,     4,     4,    33,   -58,   107,    98,   -58,
     -58,    92,    93,   101,   -58,   -58,   120,   -58,   -58,   -58,
     100,    86,   -58,     4,     4,    -9,   -58,   -58,   -58,   -58,
       3,    69,   -58,   -58,   -58,    95,     4,     4,   133,   -58,
      -1,     4,   -58,   -58,     2,   119,   -58,   135,   -58,   171,
     117,   131,   -58,     4,    -1,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    -1,    13,   171,
     139,     4,   -58,   171,   143,   143,   142,   137,   126,   -58,
     -35,    74,   154,   171,   171,   105,   105,   105,   105,    31,
      31,    31,    31,    31,    31,   -58,   -58,     4,   -58,   161,
     179,   157,   162,   -58,   144,   155,   -58,   -58,    -1,   171,
     -58,   -58,    45,   -58,    16,    78,   -58,   159,   146,   -58,
     -58,   179,    72,   189,   208,   186,   -58,    58,   -58,   -58,
     210,   -58,   -58
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     0,     5,     0,     0,
       0,     3,     6,     7,    16,     0,    18,     0,    32,    17,
       0,     0,     0,     0,     0,    42,    39,     0,    33,    34,
      38,     0,     0,     0,     7,     4,     0,    13,    14,    15,
       0,     0,     9,     0,     0,     0,    70,    71,    72,    64,
      66,     0,    60,    61,    65,     0,     0,     0,    67,    31,
      36,     0,    20,    22,     0,     0,     8,     0,    10,    58,
       0,     0,    62,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    36,     0,    44,
       0,     0,    35,    37,    24,    24,     0,     0,     0,    59,
       0,     0,     0,    56,    57,    46,    47,    48,    49,    51,
      50,    54,    52,    53,    55,    41,    43,     0,    68,     0,
      29,     0,     0,    19,     0,     0,    63,    73,    36,    45,
      69,    30,     0,    26,     0,     0,    23,     0,     0,    40,
      25,    29,     0,     0,     0,     0,    27,     0,    21,    11,
       0,    28,    12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -58,   -58,   -58,   -58,   -15,   183,    71,   -58,   -39,   -58,
     -58,   -58,   -58,   -58,   -58,   124,   -58,    79,   -58,   -11,
     -58,   -58,   -57,   -58,   148,    -3,   -17,   -58,   -41,   -58
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,    13,     8,    14,    40,    41,    42,    16,
      19,    20,    34,    94,    95,   121,   132,   133,   134,    26,
      27,    28,    29,    30,    88,    89,    52,    58,    53,    54
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    31,    68,    92,    72,    21,    15,    46,    47,    48,
      18,    18,    23,    23,    18,    24,    24,   102,    10,    22,
      51,    55,   -36,    43,    71,    73,    44,    32,    33,     9,
     115,    57,    10,    46,    47,    48,   116,    45,     1,   117,
      69,    70,     3,    31,    25,    25,    46,    47,    48,    49,
      50,    75,    76,    96,    90,    56,     4,    31,    93,   126,
       6,    57,     7,    36,   -66,    37,    38,    39,   140,   141,
      31,   139,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    74,    37,    38,    39,   119,    75,
      76,    67,    11,    37,    38,    39,   143,   127,    10,   147,
     117,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    31,    12,    87,   129,    75,    76,    15,    18,   142,
      59,    35,    60,    61,    66,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    75,    76,    62,
      99,    81,    82,    83,    84,    85,    86,    63,    65,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    75,
      76,    91,    97,    98,   100,   120,   123,   124,   118,   125,
     128,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    75,    76,   131,   135,   138,   136,   137,   144,   145,
     130,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,   148,   149,   150,   152,    64,   151,   122,
     146,   101
};

static const yytype_uint8 yycheck[] =
{
      15,    18,    41,    60,    45,    16,     4,    42,    43,    44,
      12,    12,    14,    14,    12,    17,    17,    74,    26,    27,
      23,    24,    24,    19,    33,    22,    22,    10,    11,    23,
      87,    28,    26,    42,    43,    44,    23,    33,     3,    26,
      43,    44,    46,    60,    46,    46,    42,    43,    44,    45,
      46,    20,    21,    64,    57,    22,     0,    74,    61,   100,
      22,    28,    46,     5,    31,     7,     8,     9,    23,    24,
      87,   128,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    15,     7,     8,     9,    91,    20,
      21,     5,    24,     7,     8,     9,   135,    23,    26,    27,
      26,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,   128,    46,    18,   117,    20,    21,     4,    12,   134,
      13,    25,    24,    31,    24,    20,    21,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    20,    21,    46,
      23,    36,    37,    38,    39,    40,    41,    46,    28,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    20,
      21,    28,    43,    28,    33,    22,    24,    30,    29,    43,
      16,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    20,    21,     4,    27,    30,    24,    43,    29,    43,
      29,    20,    21,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    24,     6,    29,     6,    34,   147,    95,
     141,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    48,    46,     0,    49,    22,    46,    51,    23,
      26,    24,    46,    50,    52,     4,    56,    51,    12,    57,
      58,    66,    27,    14,    17,    46,    66,    67,    68,    69,
      70,    73,    10,    11,    59,    25,     5,     7,     8,     9,
      53,    54,    55,    19,    22,    33,    42,    43,    44,    45,
      46,    72,    73,    75,    76,    72,    22,    28,    74,    13,
      24,    31,    46,    46,    52,    28,    24,     5,    55,    72,
      72,    33,    75,    22,    15,    20,    21,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    18,    71,    72,
      72,    28,    69,    72,    60,    61,    66,    43,    28,    23,
      33,    71,    69,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    69,    23,    26,    29,    72,
      22,    62,    62,    24,    30,    43,    75,    23,    16,    72,
      29,     4,    63,    64,    65,    27,    24,    43,    30,    69,
      23,    24,    51,    55,    29,    43,    64,    27,    24,     6,
      29,    53,     6
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    49,    50,    48,    51,    51,    52,    52,    53,
      53,    54,    54,    55,    55,    55,    56,    56,    58,    57,
      60,    59,    61,    59,    62,    62,    63,    63,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,    12,     1,     3,     0,     6,     1,
       2,     7,     8,     1,     1,     1,     0,     2,     0,     5,
       0,     7,     0,     5,     0,     3,     1,     3,     4,     0,
       1,     3,     0,     1,     1,     3,     0,     3,     1,     1,
       6,     4,     1,     4,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     1,     2,     4,     1,     1,     1,     2,     3,     4,
       1,     1,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 107 "parser.y"
                        {
                            open_scope();
                            symtab_insert((yyvsp[0].name), Void_type);
                        }
#line 1637 "obj/parser.c"
    break;

  case 3:
#line 112 "parser.y"
                        {
                            program_param = false;
                        }
#line 1645 "obj/parser.c"
    break;

  case 4:
#line 119 "parser.y"
                        {
                            close_scope();

                            // ast_traversal(id_node($2)); 
                            // ast_traversal($4); 
                            // ast_traversal($7); 
                            // ast_traversal($8); 
                            // ast_traversal($9); 
                            // symtab_print();
                        }
#line 1660 "obj/parser.c"
    break;

  case 5:
#line 133 "parser.y"
                {
                            // printf("[Declare] line %4d:%3d, variable: %s\n", line_no, col_no - yyleng, yytext); // DEBUG
                    if(!program_param){ // skip program params
                        Symtab *tmp = symtab_insert((yyvsp[0].name), Uninit_type); 
                        bool redeclared = (tmp)? false: true;

                        if(redeclared)
                            semantics_redeclared((yyvsp[0].name), Uninit_type, (yylsp[0]).first_line, (yylsp[0]).first_column);

                        (yyval.node) = IdentifierList_node();
                        addChild((yyval.node), id_node((yyvsp[0].name), redeclared));
                    }

                }
#line 1679 "obj/parser.c"
    break;

  case 6:
#line 148 "parser.y"
                {
                    if(!program_param){
                        Symtab *tmp = symtab_insert((yyvsp[0].name), Uninit_type); 
                        bool redeclared = (tmp)? false: true;

                        if(redeclared)
                            semantics_redeclared((yyvsp[0].name), Uninit_type, (yylsp[0]).first_line, (yylsp[0]).first_column);

                        (yyval.node) = (yyvsp[-2].node);
                        addChild((yyval.node), id_node((yyvsp[0].name), redeclared));
                    }
                }
#line 1696 "obj/parser.c"
    break;

  case 7:
#line 164 "parser.y"
                {
                            (yyval.node) = DeclarationList_node();    // first node
                }
#line 1704 "obj/parser.c"
    break;

  case 8:
#line 168 "parser.y"
                {
                            (yyval.node) = (yyvsp[-5].node);
                            AST_Node* decl = Declaration_node((yyvsp[-3].node), (yyvsp[-1].node));
                            addChild((yyval.node), decl);

                    symtab_set_id_dtype((yyvsp[-3].node), (yyvsp[-1].node));

                }
#line 1717 "obj/parser.c"
    break;

  case 9:
#line 185 "parser.y"
                        {
                            (yyval.node) = Type_node((yyvsp[0].integer), -1);   // (Int, Real)
                        }
#line 1725 "obj/parser.c"
    break;

  case 10:
#line 189 "parser.y"
                        {
                            (yyval.node) = Type_node(Array_type, (yyvsp[0].integer)); // (Array)
                            AST_Type* tmp = (AST_Type*) (yyval.node);
                            tmp->children = (yyvsp[-1].node); // array size node
                        }
#line 1735 "obj/parser.c"
    break;

  case 11:
#line 197 "parser.y"
                        {
                            dimension = 0;  // global variable
                            (yyval.node) = ArraySize_node((yyvsp[-4].val).ival, (yyvsp[-2].val).ival, dimension);  // first node
                        }
#line 1744 "obj/parser.c"
    break;

  case 12:
#line 202 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-7].node);
                            dimension += 1;
                            addNext((yyval.node), ArraySize_node((yyvsp[-4].val).ival, (yyvsp[-2].val).ival, dimension));
                        }
#line 1754 "obj/parser.c"
    break;

  case 13:
#line 211 "parser.y"
                        {
                            (yyval.integer) = Int_type;
                        }
#line 1762 "obj/parser.c"
    break;

  case 14:
#line 215 "parser.y"
                        {
                            (yyval.integer) = Real_type;
                        }
#line 1770 "obj/parser.c"
    break;

  case 16:
#line 224 "parser.y"
                        {
                            (yyval.node) = SubprogramDeclarationList_node();  // create upon the first function declaration
                        }
#line 1778 "obj/parser.c"
    break;

  case 17:
#line 228 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node);
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 1787 "obj/parser.c"
    break;

  case 18:
#line 235 "parser.y"
                          { ret_val_missing = true; }
#line 1793 "obj/parser.c"
    break;

  case 19:
#line 237 "parser.y"
                        {
                            (yyval.node) = SubprogramDeclaration_node((yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node));

                            // missing return value; skip procedure
                            int functype = ((AST_SubprogramHead *)(yyvsp[-3].node))->dtype;
                            if(functype == Function_type && ret_val_missing)
                                semantic_return_value_missing(curFunctionId, (yylsp[-3]).first_line, (yylsp[-3]).first_column);

                            ret_val_missing = false; // reset
                            func_redeclared = false; // reset
                            close_scope();
                        }
#line 1810 "obj/parser.c"
    break;

  case 20:
#line 253 "parser.y"
                { 
                    Symtab *tmp = symtab_insert((yyvsp[0].name), Function_type); 
                    func_redeclared = (tmp)? false: true; // init

                    if(func_redeclared)
                        semantics_redeclared((yyvsp[0].name), Function_type, (yylsp[-1]).first_line, (yylsp[-1]).first_column);

                    strcpy(curFunctionId, (yyvsp[0].name));
                    
                    open_scope();
                }
#line 1826 "obj/parser.c"
    break;

  case 21:
#line 265 "parser.y"
                {
                    (yyval.node) = SubprogramHead_node(Function_type, id_node((yyvsp[-5].name), func_redeclared), (yyvsp[-3].node), (yyvsp[-1].integer));
                    
                    if(!func_redeclared){ // only if function declared successfully 
                        symtab_set_ret_type((yyvsp[-1].integer));

                    }


                }
#line 1841 "obj/parser.c"
    break;

  case 22:
#line 276 "parser.y"
                { 
                    Symtab *tmp = symtab_insert((yyvsp[0].name), Procedure_type);
                    func_redeclared = (tmp)? false: true; // init

                    if(func_redeclared)
                        semantics_redeclared((yyvsp[0].name), Procedure_type, (yylsp[-1]).first_line, (yylsp[-1]).first_column);

                    open_scope();
                }
#line 1855 "obj/parser.c"
    break;

  case 23:
#line 286 "parser.y"
                {
                    (yyval.node) = SubprogramHead_node(Procedure_type, id_node((yyvsp[-3].name), func_redeclared), (yyvsp[-1].node), Void_type);

                    if(!func_redeclared) // only if function declared successfully 
                        symtab_set_ret_type(Void_type);

                }
#line 1867 "obj/parser.c"
    break;

  case 24:
#line 298 "parser.y"
                        {
                            (yyval.node) = Arguments_node(NULL);
                        }
#line 1875 "obj/parser.c"
    break;

  case 25:
#line 302 "parser.y"
                        {
                            (yyval.node) = Arguments_node((yyvsp[-1].node));
                        }
#line 1883 "obj/parser.c"
    break;

  case 26:
#line 308 "parser.y"
                        {
                            (yyval.node) = ParameterList_node();  // create upon the first param
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 1892 "obj/parser.c"
    break;

  case 27:
#line 313 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 1901 "obj/parser.c"
    break;

  case 28:
#line 321 "parser.y"
                {
                    (yyval.node) = Params_node((yyvsp[-2].node), (yyvsp[0].node));   // belong to one type

                    symtab_set_id_dtype((yyvsp[-2].node), (yyvsp[0].node));

                    
                    // add param info to function, only if function declared successfully
                    if(!func_redeclared){
                        symtab_addParamInfo(); 
                    }
                }
#line 1917 "obj/parser.c"
    break;

  case 31:
#line 341 "parser.y"
                        {
                            (yyval.node) = CompoundStatement_node((yyvsp[-1].node)); 
                            // $2: StatementList_node
                        }
#line 1926 "obj/parser.c"
    break;

  case 32:
#line 348 "parser.y"
                        {
                            (yyval.node) = NULL;
                        }
#line 1934 "obj/parser.c"
    break;

  case 33:
#line 352 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);
                        }
#line 1942 "obj/parser.c"
    break;

  case 34:
#line 358 "parser.y"
                        {
                            (yyval.node) = StatementList_node();  // create upon the first statement
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 1951 "obj/parser.c"
    break;

  case 35:
#line 363 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 1960 "obj/parser.c"
    break;

  case 36:
#line 370 "parser.y"
                        {
                            (yyval.node) = NULL;
                        }
#line 1968 "obj/parser.c"
    break;

  case 37:
#line 374 "parser.y"
                        {
                            // can put this to an assignment rule
                            (yyval.node) = Assignment_node((yyvsp[-2].node), (yyvsp[0].node));

                           char LHSname[128];
                            strcpy(LHSname, ((AST_var *)(yyvsp[-2].node))->name);

                            // undeclared function, assignment to its return value
                            if(func_redeclared && strcmp(LHSname, curFunctionId) == 0){
                                ((AST_var *)(yyvsp[-2].node))->ref_type = Function_undecl;
                            }

                            // check LHS during function declaration, no side effect on other context
                            // redeclared function must have missing return value
                            if(!func_redeclared && strcmp(LHSname, curFunctionId) == 0)
                                ret_val_missing = false;
                                

                            // assignment type check
                            int Ltype = ((AST_var *)(yyvsp[-2].node))->ref_type;
                            int Rtype = ((AST_Expression *)(yyvsp[0].node))->dtype;
                            semantic_assign_type_check(Ltype, Rtype, (yylsp[-2]).first_line, (yylsp[-2]).first_column);

 
                        }
#line 1998 "obj/parser.c"
    break;

  case 38:
#line 400 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);    /* pass node */
                        }
#line 2006 "obj/parser.c"
    break;

  case 39:
#line 404 "parser.y"
                        {
                            (yyval.node) = (yyvsp[0].node);    /* pass node */
                        }
#line 2014 "obj/parser.c"
    break;

  case 40:
#line 408 "parser.y"
                        {
                            (yyval.node) = ifelse_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2022 "obj/parser.c"
    break;

  case 41:
#line 412 "parser.y"
                        {
                            (yyval.node) = while_node((yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2030 "obj/parser.c"
    break;

  case 42:
#line 419 "parser.y"
                        {
                            AST_Node *n = var_node((yyvsp[0].name));
                            (yyval.node) = ProcedureStatement_node(n, NULL);
                            
                            ((AST_var *)n)->entry = symtab_link_entry((yyvsp[0].name));
                            // ((AST_var *)n)->dtype

                            if(((AST_var *)n)->entry == NULL)
                                semantic_undeclared((yyvsp[0].name), 1, (yylsp[0]).first_line, (yylsp[0]).first_column);
                        }
#line 2045 "obj/parser.c"
    break;

  case 43:
#line 430 "parser.y"
                        {
                            AST_Node *n = var_node((yyvsp[-3].name));
                            (yyval.node) = ProcedureStatement_node(n, (yyvsp[-1].node));

                            Symtab *entry = symtab_link_entry((yyvsp[-3].name));
                            ((AST_var *)n)->entry = entry;
                            // ((AST_var *)n)->dtype

                            if(entry == NULL)
                                semantic_undeclared((yyvsp[-3].name), 1, (yylsp[-3]).first_line, (yylsp[-3]).first_column);

                            // if undeclared, skip params check
                            // traverse ExpressionList
                            if(entry != NULL){
                                Symtab *st = entry->paraminfo;
                                AST_Node *ast_n = ((AST_ExpressionList *)(yyvsp[-1].node))->children;
                                if(param_num_incorrect(st, ast_n)){
                                    semantic_param_number_error((yyvsp[-3].name), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
                                }
                            }
                        }
#line 2071 "obj/parser.c"
    break;

  case 44:
#line 455 "parser.y"
                        {
                            (yyval.node) = ExpressionList_node();  // create upon the first match
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 2080 "obj/parser.c"
    break;

  case 45:
#line 460 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-2].node);
                            addChild((yyval.node), (yyvsp[0].node));
                        }
#line 2089 "obj/parser.c"
    break;

  case 46:
#line 467 "parser.y"
                        {
                            (yyval.node) = arithm_node(Add_op, (yyvsp[-2].node), (yyvsp[0].node));
                            AST_Expression * Lexpr = (AST_Expression *)(yyvsp[-2].node);
                            AST_Expression * Rexpr = (AST_Expression *)(yyvsp[0].node);

                            semantic_op_type_check(Lexpr->dtype, Rexpr->dtype, (yylsp[-1]).first_line, (yylsp[-1]).first_column, "+");

                            // printf("[Declare] line %4d:%3d , add\n", @1.first_line, @1.first_column); // DEBUG

                        }
#line 2104 "obj/parser.c"
    break;

  case 47:
#line 478 "parser.y"
                        {
                            (yyval.node) = arithm_node(Sub_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2112 "obj/parser.c"
    break;

  case 48:
#line 482 "parser.y"
                        {
                            (yyval.node) = arithm_node(Mul_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2120 "obj/parser.c"
    break;

  case 49:
#line 486 "parser.y"
                        {
                            (yyval.node) = arithm_node(Div_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2128 "obj/parser.c"
    break;

  case 50:
#line 490 "parser.y"
                        {
                            (yyval.node) = relation_node(Greater_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2136 "obj/parser.c"
    break;

  case 51:
#line 494 "parser.y"
                        {
                            (yyval.node) = relation_node(Less_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2144 "obj/parser.c"
    break;

  case 52:
#line 498 "parser.y"
                        {
                            (yyval.node) = relation_node(Greater_equal_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2152 "obj/parser.c"
    break;

  case 53:
#line 502 "parser.y"
                        {
                            (yyval.node) = relation_node(Less_equal_op, (yyvsp[-2].node), (yyvsp[0].node));
                            AST_Expression * Lexpr = (AST_Expression *)(yyvsp[-2].node);
                            AST_Expression * Rexpr = (AST_Expression *)(yyvsp[0].node);

                            semantic_op_type_check(Lexpr->dtype, Rexpr->dtype, (yylsp[-1]).first_line, (yylsp[-1]).first_column, "<=");
                        }
#line 2164 "obj/parser.c"
    break;

  case 54:
#line 510 "parser.y"
                        {
                            (yyval.node) = relation_node(Equal_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2172 "obj/parser.c"
    break;

  case 55:
#line 514 "parser.y"
                        {
                            (yyval.node) = relation_node(Not_equal_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2180 "obj/parser.c"
    break;

  case 56:
#line 518 "parser.y"
                        {
                            (yyval.node) = bool_node(And_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2188 "obj/parser.c"
    break;

  case 57:
#line 522 "parser.y"
                        {
                            (yyval.node) = bool_node(Or_op, (yyvsp[-2].node), (yyvsp[0].node));
                        }
#line 2196 "obj/parser.c"
    break;

  case 58:
#line 526 "parser.y"
                        {
                            (yyval.node) = bool_node(Not_op, (yyvsp[0].node), NULL);
                        }
#line 2204 "obj/parser.c"
    break;

  case 59:
#line 530 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-1].node); /* pass information */
                        }
#line 2212 "obj/parser.c"
    break;

  case 60:
#line 534 "parser.y"
                        {
                            (yyval.node) = Expression_node((yyvsp[0].node), ((AST_var *)(yyvsp[0].node))->ref_type); /* pass information */
                        }
#line 2220 "obj/parser.c"
    break;

  case 61:
#line 538 "parser.y"
                        {
                            (yyval.node) = Expression_node((yyvsp[0].node), ((AST_Const *)(yyvsp[0].node))->dtype);
                        }
#line 2228 "obj/parser.c"
    break;

  case 62:
#line 542 "parser.y"
                        {
                            (yyval.node) = Expression_node((yyvsp[0].node), ((AST_Const *)(yyvsp[0].node))->dtype);
                        }
#line 2236 "obj/parser.c"
    break;

  case 63:
#line 546 "parser.y"
                        {
                            (yyval.node) = Expression_node((yyvsp[0].node), ((AST_Const *)(yyvsp[0].node))->dtype);
                        }
#line 2244 "obj/parser.c"
    break;

  case 65:
#line 551 "parser.y"
                        {
                            AST_Node *n = ((AST_ProcedureStatement *)(yyvsp[0].node))->id;
                            int ref_type = ((AST_var *)n)->ref_type;
                            (yyval.node) = Expression_node((yyvsp[0].node), ref_type);
                        }
#line 2254 "obj/parser.c"
    break;

  case 66:
#line 560 "parser.y"
                        {
                            (yyval.node) = var_node((yyvsp[0].name));
                            AST_var *this = (AST_var *) (yyval.node);
                            
                            Symtab *entry = this->entry = symtab_link_entry((yyvsp[0].name));

                            if(entry == NULL){
                                semantic_undeclared((yyvsp[0].name), 0, (yylsp[0]).first_line, (yylsp[0]).first_column);
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
#line 2280 "obj/parser.c"
    break;

  case 67:
#line 582 "parser.y"
                        {
                            (yyval.node) = var_node((yyvsp[-1].name));
                            AST_var *this = (AST_var *) (yyval.node);   
                            
                            Symtab *entry = this->entry = symtab_link_entry((yyvsp[-1].name));
                            // tmp->dtype
                            
                            this->arrayidx = (yyvsp[0].node); // array index node
                            // tmp->dim = $2; // FIXME: array dimension

                            if(entry == NULL){
                                semantic_undeclared((yyvsp[-1].name), 0, (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                this->ref_type = Uninit_type;
                            }
                            else {
                                this->ref_type = entry->arraydtype;

                                // array dim check
                                int flag = array_dim_error(entry->arrNode, (yyvsp[0].node));
                                if(flag == 1) { // too many dim
                                    semantic_arr_dim_err((yyvsp[-1].name), (yylsp[-1]).first_line, (yylsp[-1]).first_column);
                                }else if(flag == -1){ // too few dim
                                    this->ref_type = Array_dim_insuff; // not assignable
                                }

                            }


                        }
#line 2314 "obj/parser.c"
    break;

  case 68:
#line 614 "parser.y"
                        {
                            dimension = 0;  // global variable
                            (yyval.node) = Arrayidx_node((yyvsp[-1].node), dimension);  // first node

                            // array index check
                            int dtype = ((AST_Expression *)(yyvsp[-1].node))->dtype;
                            if( dtype != Int_type 
                                && dtype != Uninit_type){
                                semantic_arr_idx_type_err((yylsp[-1]).first_line, (yylsp[-1]).first_column);
                            }
                        }
#line 2330 "obj/parser.c"
    break;

  case 69:
#line 626 "parser.y"
                        {
                            (yyval.node) = (yyvsp[-3].node);
                            dimension += 1;
                            AST_Node *n = Arrayidx_node((yyvsp[-1].node), dimension);  // next dimension
                            addNext((yyval.node), n);


                            // array index check
                            int dtype = ((AST_Expression *)(yyvsp[-1].node))->dtype;
                            if( dtype != Int_type 
                                && dtype != Uninit_type){
                                semantic_arr_idx_type_err((yylsp[-1]).first_line, (yylsp[-1]).first_column);
                            }
                        }
#line 2349 "obj/parser.c"
    break;

  case 70:
#line 643 "parser.y"
                        {
                            (yyval.node) = const_node(Real_type, (yyvsp[0].val)); // $1 (numeric value)
                        }
#line 2357 "obj/parser.c"
    break;

  case 71:
#line 647 "parser.y"
                        {
                            (yyval.node) = const_node(Int_type, (yyvsp[0].val));
                        }
#line 2365 "obj/parser.c"
    break;

  case 72:
#line 651 "parser.y"
                        {
                            (yyval.node) = const_node(Real_type, (yyvsp[0].val));
                        }
#line 2373 "obj/parser.c"
    break;

  case 73:
#line 657 "parser.y"
                        {
                            AST_Node *n = var_node((yyvsp[-3].name));
                            (yyval.node) = ProcedureStatement_node(n, (yyvsp[-1].node));

                            Symtab *entry = symtab_link_entry((yyvsp[-3].name));
                            ((AST_var *)n)->entry = entry;
                            

                            if(entry == NULL) {
                                semantic_undeclared((yyvsp[-3].name), 1, (yylsp[-3]).first_line, (yylsp[-3]).first_column);
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
                                AST_Node *ast_n = ((AST_ExpressionList *)(yyvsp[-1].node))->children;
                                if(param_num_incorrect(st, ast_n)){
                                    semantic_param_number_error((yyvsp[-3].name), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
                                }
                            }

                        }
#line 2411 "obj/parser.c"
    break;


#line 2415 "obj/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 692 "parser.y"


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
