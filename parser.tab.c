/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parser.y"

#include <stdio.h>
#include <malloc.h>
#include "symboltab.h"
#include "translator.h"

extern int yylex (void);
int yyerror( const char *s);
extern int line;

//lies didnt find a workaround for now 
command_list *case_jumps = NULL; /* For tracking all case jumps CAN BE DELETED found work around*/
//double future me still need to figure it out 

int number = 0; /* Counter for numeric values */
int error_number = 0; /* Counter for errors */
var_node *current_varible = NULL, *next_varible = NULL; /* Variables for symbol table */
command *current_command = NULL; /* Current command in the command list */
command_list *temp_link = NULL; /* Temporary link for command lists */
char *num = NULL; /* Temporary storage for numeric values */
int p = 0; /* Counter for case values */
char case_val[10]; /* Array to store case values */


#line 96 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_CASE = 4,                       /* CASE  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_OUTPUT = 7,                     /* OUTPUT  */
  YYSYMBOL_INPUT = 8,                      /* INPUT  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_SWITCH = 11,                    /* SWITCH  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_DEFAULT = 13,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 14,                     /* BREAK  */
  YYSYMBOL_ADDOP = 15,                     /* ADDOP  */
  YYSYMBOL_NUM = 16,                       /* NUM  */
  YYSYMBOL_MULOP = 17,                     /* MULOP  */
  YYSYMBOL_CAST = 18,                      /* CAST  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_RELOP = 22,                     /* RELOP  */
  YYSYMBOL_ERROR = 23,                     /* ERROR  */
  YYSYMBOL_24_ = 24,                       /* ':'  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* ','  */
  YYSYMBOL_27_ = 27,                       /* '}'  */
  YYSYMBOL_28_ = 28,                       /* '='  */
  YYSYMBOL_29_ = 29,                       /* '('  */
  YYSYMBOL_30_ = 30,                       /* ')'  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_declarations = 34,              /* declarations  */
  YYSYMBOL_declaration = 35,               /* declaration  */
  YYSYMBOL_36_1 = 36,                      /* $@1  */
  YYSYMBOL_type = 37,                      /* type  */
  YYSYMBOL_idlist = 38,                    /* idlist  */
  YYSYMBOL_stmt = 39,                      /* stmt  */
  YYSYMBOL_assignment_stmt = 40,           /* assignment_stmt  */
  YYSYMBOL_input_stmt = 41,                /* input_stmt  */
  YYSYMBOL_output_stmt = 42,               /* output_stmt  */
  YYSYMBOL_if_stmt = 43,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 44,                /* while_stmt  */
  YYSYMBOL_switch_stmt = 45,               /* switch_stmt  */
  YYSYMBOL_caselist = 46,                  /* caselist  */
  YYSYMBOL_break_stmt = 47,                /* break_stmt  */
  YYSYMBOL_stmt_block = 48,                /* stmt_block  */
  YYSYMBOL_stmtlist = 49,                  /* stmtlist  */
  YYSYMBOL_boolexpr = 50,                  /* boolexpr  */
  YYSYMBOL_boolterm = 51,                  /* boolterm  */
  YYSYMBOL_boolfactor = 52,                /* boolfactor  */
  YYSYMBOL_expression = 53,                /* expression  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_factor = 55                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   168

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  122

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   278


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,    30,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,    25,
       2,    28,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    27,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   102,   102,   112,   113,   116,   116,   117,   120,   121,
     124,   125,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   141,   148,   161,   169,   183,   190,   202,   208,
     237,   242,   250,   278,   283,   286,   289,   290,   293,   305,
     313,   319,   327,   335,   347,   353,   362,   368,   377,   384,
     400,   412,   419
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "CASE", "INT",
  "FLOAT", "OUTPUT", "INPUT", "IF", "ELSE", "SWITCH", "WHILE", "DEFAULT",
  "BREAK", "ADDOP", "NUM", "MULOP", "CAST", "OR", "AND", "NOT", "RELOP",
  "ERROR", "':'", "';'", "','", "'}'", "'='", "'('", "')'", "'{'",
  "$accept", "program", "declarations", "declaration", "$@1", "type",
  "idlist", "stmt", "assignment_stmt", "input_stmt", "output_stmt",
  "if_stmt", "while_stmt", "switch_stmt", "caselist", "break_stmt",
  "stmt_block", "stmtlist", "boolexpr", "boolterm", "boolfactor",
  "expression", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-33)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,    29,     2,   -51,    -5,   -51,   -51,   -51,    83,   -51,
     -51,    36,    99,    49,   110,    40,    57,    62,    82,    88,
      91,    85,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,   -51,   122,   122,
     126,    98,    24,   105,   -51,   107,   -51,   -51,   113,   112,
      46,   128,   -51,    -8,   109,   116,   114,    -9,   127,   -51,
       8,   118,    16,   119,    55,   -51,   122,   120,    39,   122,
     -51,   122,   129,   130,    81,   115,   115,    81,   115,   122,
     121,   125,    81,    81,    43,   -51,   -51,   128,   -51,   -51,
     -51,   143,    68,   127,   147,   -51,   144,   -51,   -51,   -51,
     -51,   -51,    81,   -51,    81,    22,    11,   -51,   -51,   142,
     136,   137,   -51,   138,   -51,   -51,   -51,    48,    69,     5,
     -51,   -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,    11,    37,     3,     0,     2,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    36,    12,    13,    14,    15,    16,    17,
      18,    19,     8,     9,     5,    10,    20,    21,     0,     0,
       0,     0,     0,     0,    34,     0,    50,    51,     0,     0,
       0,    45,    47,     0,     0,     0,     0,     0,    39,    41,
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    48,    44,    46,    24,
      23,     0,     0,    38,     0,    40,    43,    33,    33,    28,
      27,    49,     0,    42,     0,     0,     0,    26,    25,     0,
       0,     0,    31,     0,    37,    37,    37,     0,     0,     0,
      30,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,   -51,   -51,   -51,   -51,   -51,    20,   -51,   -51,
     -51,   -51,   -51,   -51,    65,   -51,   162,   -50,   -41,    89,
      90,   -38,    97,    96
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     7,    45,    34,     8,    23,    24,    25,
      26,    27,    28,    29,   105,    30,    31,    11,    57,    58,
      59,    60,    51,    52
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      50,    53,    64,     4,    62,     5,    14,    69,    15,   -32,
      76,    68,    16,    17,    18,   109,    19,    20,   -32,    21,
      10,    77,    72,    69,   111,    61,   109,    46,    84,     3,
      79,    69,   -32,     6,    92,   110,     6,    14,   112,    15,
      47,    96,    48,    16,    17,    18,    81,    19,    20,    14,
      21,    15,    35,    49,    69,    16,    17,    18,    69,    19,
      20,    69,    21,    22,   117,   118,   119,     6,    38,    86,
      14,    70,    15,   101,    76,   120,    16,    17,    18,     6,
      19,    20,    14,    21,    15,    83,    39,    76,    16,    17,
      18,    40,    19,    20,    91,    21,   121,    94,   103,    55,
       6,    46,    99,   100,    32,    33,    63,    12,    46,    13,
      44,    41,     6,    67,    47,    46,    48,    42,    46,    56,
      43,    47,   107,    48,   108,    46,    56,    49,    47,    54,
      48,    47,    65,    48,    49,    36,    56,    37,    47,    73,
      48,    49,    66,    75,    49,    71,    74,    78,    80,    82,
      85,    49,    97,   102,    89,    90,    98,   104,   113,    69,
     114,   115,   116,   106,     9,    93,    87,    88,    95
};

static const yytype_int8 yycheck[] =
{
      38,    39,    43,     1,    42,     3,     1,    15,     3,     4,
      19,    49,     7,     8,     9,     4,    11,    12,    13,    14,
      25,    30,    30,    15,    13,     1,     4,     3,    66,     0,
      22,    15,    27,    31,    75,    13,    31,     1,    27,     3,
      16,    79,    18,     7,     8,     9,    30,    11,    12,     1,
      14,     3,     3,    29,    15,     7,     8,     9,    15,    11,
      12,    15,    14,    27,   114,   115,   116,    31,    28,    30,
       1,    25,     3,    30,    19,    27,     7,     8,     9,    31,
      11,    12,     1,    14,     3,    30,    29,    19,     7,     8,
       9,    29,    11,    12,    74,    14,    27,    77,    30,     1,
      31,     3,    82,    83,     5,     6,     1,    24,     3,    26,
      25,    29,    31,     1,    16,     3,    18,    29,     3,    21,
      29,    16,   102,    18,   104,     3,    21,    29,    16,     3,
      18,    16,    25,    18,    29,    25,    21,    27,    16,    30,
      18,    29,    29,    29,    29,    17,    30,    20,    30,    30,
      30,    29,    31,    10,    25,    25,    31,    10,    16,    15,
      24,    24,    24,    98,     2,    76,    69,    71,    78
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,    34,     0,     1,     3,    31,    35,    38,    48,
      25,    49,    24,    26,     1,     3,     7,     8,     9,    11,
      12,    14,    27,    39,    40,    41,    42,    43,    44,    45,
      47,    48,     5,     6,    37,     3,    25,    27,    28,    29,
      29,    29,    29,    29,    25,    36,     3,    16,    18,    29,
      53,    54,    55,    53,     3,     1,    21,    50,    51,    52,
      53,     1,    53,     1,    50,    25,    29,     1,    53,    15,
      25,    17,    30,    30,    30,    29,    19,    30,    20,    22,
      30,    30,    30,    30,    53,    30,    30,    54,    55,    25,
      25,    39,    50,    51,    39,    52,    53,    31,    31,    39,
      39,    30,    10,    30,    10,    46,    46,    39,    39,     4,
      13,    13,    27,    16,    24,    24,    24,    49,    49,    49,
      27,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    36,    35,    35,    37,    37,
      38,    38,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    40,    41,    42,    43,    43,    44,    44,    45,
      45,    45,    46,    46,    47,    48,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      55,    55,    55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     0,     5,     2,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     4,     5,     5,     7,     7,     5,     5,    10,
      10,     7,     5,     0,     2,     3,     2,     0,     3,     1,
       3,     1,     4,     3,     3,     1,     3,     1,     3,     4,
       1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations stmt_block  */
#line 103 "parser.y"
{
    /* Translate the entire program into commands and print them */
    (yyvsp[0].stmt) = translate_comand((yyvsp[0].stmt), 'H', "ALT", "", "", "");
    command_print((yyvsp[0].stmt));
    free_tree(); /* Free the syntax tree */
    free_list((yyvsp[0].stmt)); /* Free the command list */
}
#line 1496 "parser.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 116 "parser.y"
                             { set_varible_type((yyvsp[0].type)); }
#line 1502 "parser.tab.c"
    break;

  case 7: /* declaration: error ';'  */
#line 117 "parser.y"
             { yyerrok; }
#line 1508 "parser.tab.c"
    break;

  case 8: /* type: INT  */
#line 120 "parser.y"
          { (yyval.type) = (yyvsp[0].type); }
#line 1514 "parser.tab.c"
    break;

  case 9: /* type: FLOAT  */
#line 121 "parser.y"
        { (yyval.type) = (yyvsp[0].type); }
#line 1520 "parser.tab.c"
    break;

  case 10: /* idlist: idlist ',' ID  */
#line 124 "parser.y"
                      { set_varible_name((yyvsp[0].id)); }
#line 1526 "parser.tab.c"
    break;

  case 11: /* idlist: ID  */
#line 125 "parser.y"
     { set_varible_name((yyvsp[0].id)); }
#line 1532 "parser.tab.c"
    break;

  case 12: /* stmt: assignment_stmt  */
#line 128 "parser.y"
                      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1538 "parser.tab.c"
    break;

  case 13: /* stmt: input_stmt  */
#line 129 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1544 "parser.tab.c"
    break;

  case 14: /* stmt: output_stmt  */
#line 130 "parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1550 "parser.tab.c"
    break;

  case 15: /* stmt: if_stmt  */
#line 131 "parser.y"
          { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1556 "parser.tab.c"
    break;

  case 16: /* stmt: while_stmt  */
#line 132 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1562 "parser.tab.c"
    break;

  case 17: /* stmt: switch_stmt  */
#line 133 "parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1568 "parser.tab.c"
    break;

  case 18: /* stmt: break_stmt  */
#line 134 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1574 "parser.tab.c"
    break;

  case 19: /* stmt: stmt_block  */
#line 135 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1580 "parser.tab.c"
    break;

  case 20: /* stmt: error ';'  */
#line 136 "parser.y"
            { yyerrok; (yyval.stmt) = NULL; }
#line 1586 "parser.tab.c"
    break;

  case 21: /* stmt: error '}'  */
#line 137 "parser.y"
            { yyerrok; (yyval.stmt) = NULL; }
#line 1592 "parser.tab.c"
    break;

  case 22: /* assignment_stmt: ID '=' expression ';'  */
#line 142 "parser.y"
{
    /* Add an assignment command to the command list */
    (yyval.stmt) = add_assign_commadn((yyvsp[-3].id), (yyvsp[-1].expression).last, (yyvsp[-1].expression).type, (yyvsp[-1].expression).head);
}
#line 1601 "parser.tab.c"
    break;

  case 23: /* input_stmt: INPUT '(' ID ')' ';'  */
#line 149 "parser.y"
{
    /* Generate an input command for the specified variable */
    (yyval.stmt) = NULL;
    if (!(current_varible = search_varible((yyvsp[-2].id)))){
         yyerror("Undefined variable in input statement");
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
    }
    else
        (yyval.stmt) = translate_comand(NULL, current_varible->type, "INP", current_varible->name, "", "");
}
#line 1616 "parser.tab.c"
    break;

  case 24: /* output_stmt: OUTPUT '(' expression ')' ';'  */
#line 162 "parser.y"
{
    /* Generate an output command for the expression */
    (yyval.stmt) = translate_comand((yyvsp[-2].expression).head, (yyvsp[-2].expression).type, "PRT", (yyvsp[-2].expression).last, "", "");
    free_state((yyvsp[-2].expression).last); /* Free the state after output */
}
#line 1626 "parser.tab.c"
    break;

  case 25: /* if_stmt: IF '(' boolexpr ')' stmt ELSE stmt  */
#line 170 "parser.y"
{
    /* Merge the boolean expression and statements for the if-else construct */
    /*if->bool->smnt if false */
    /*uses temp list to add later the jump line */
    (yyval.stmt) = merege_comand((yyvsp[-4].boolean).head, (yyvsp[-2].stmt));
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label((yyvsp[-4].boolean).false, get_last_command((yyval.stmt)));/*here is the continue for false update the jump */
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label(temp_link, get_last_command((yyval.stmt)));
}
#line 1644 "parser.tab.c"
    break;

  case 26: /* if_stmt: IF '(' error ')' stmt ELSE stmt  */
#line 184 "parser.y"
    {
        yyerrok;
        (yyval.stmt) = NULL;
    }
#line 1653 "parser.tab.c"
    break;

  case 27: /* while_stmt: WHILE '(' boolexpr ')' stmt  */
#line 191 "parser.y"
{
    /* Generate commands for the while loop */
    (yyval.stmt) = add_label(NULL);
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[-2].boolean).head);
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    update_list_to_label(temp_link, (yyval.stmt));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label((yyvsp[-2].boolean).false, get_last_command((yyval.stmt)));
}
#line 1669 "parser.tab.c"
    break;

  case 28: /* while_stmt: WHILE '(' error ')' stmt  */
#line 203 "parser.y"
    {
        yyerrok;
        (yyval.stmt) = NULL;
    }
#line 1678 "parser.tab.c"
    break;

  case 29: /* switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'  */
#line 209 "parser.y"
{
   // Generate temporary for switch expression
    next_varible = add_temp_var(current_varible->type);
    
    // Start with case comparisons
    (yyvsp[-7].expression).head = merege_comand((yyvsp[-7].expression).head, (yyvsp[-4].stmt));
    
    // Add jump to default case
   // $3.head = translate_comand($3.head, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyvsp[-7].expression).head));
    
    // Add default label
    (yyvsp[-7].expression).head = add_label((yyvsp[-7].expression).head);
    
    // Add default case code
    (yyvsp[-7].expression).head = merege_comand((yyvsp[-7].expression).head, (yyvsp[-1].stmt));
    
    // Add end label
    (yyvsp[-7].expression).head = add_label((yyvsp[-7].expression).head);
    
    // Update all jumps (both case jumps and the initial default jump)
    update_list_to_label(temp_link, get_last_command((yyvsp[-7].expression).head));
   update_list_to_label(case_jumps, get_last_command((yyvsp[-7].expression).head));
    
    // Clean up
    case_jumps = NULL;
    (yyval.stmt) = (yyvsp[-7].expression).head;
}
#line 1711 "parser.tab.c"
    break;

  case 30: /* switch_stmt: SWITCH '(' error ')' '{' caselist DEFAULT ':' stmtlist '}'  */
#line 238 "parser.y"
    {
        yyerrok;
        (yyval.stmt) = NULL;
    }
#line 1720 "parser.tab.c"
    break;

  case 31: /* switch_stmt: SWITCH '(' expression ')' '{' caselist '}'  */
#line 243 "parser.y"
{
    fprintf(stderr, "ERROR: line %d: switch statement missing 'DEFAULT' case\n", line);
    yyerrok;
    (yyval.stmt) = NULL;  // Yrecove /handle jump
}
#line 1730 "parser.tab.c"
    break;

  case 32: /* caselist: caselist CASE NUM ':' stmtlist  */
#line 251 "parser.y"
{
    // Generate comparison
    num = (yyvsp[-2].num).value;
    next_varible = add_temp_var(current_varible->type);
    (yyval.stmt) = translate_comand((yyvsp[-4].stmt), current_varible->type, "EQL", next_varible->name, current_varible->name, num);
    
    // Generate conditional jump to next case
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "MPZ", "", next_varible->name, "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    
    // Add case body
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    
    //this is where switch case issue accores it gives the last line HALT 
    // Add unconditional jump to end of switch
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
   //the case jump is to keep count of the amount of cases can be done more efficently
   //need to implement this better can be done with counter or somthing to count line 
   //of each case 
   //for now this works
    case_jumps = add_new_command_list(case_jumps, get_last_command((yyval.stmt)));
    
    // Add label for next case
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label(temp_link, get_last_command((yyval.stmt)));
}
#line 1761 "parser.tab.c"
    break;

  case 33: /* caselist: %empty  */
#line 278 "parser.y"
{ 
    (yyval.stmt) = NULL; 
   case_jumps = NULL; 
}
#line 1770 "parser.tab.c"
    break;

  case 34: /* break_stmt: BREAK ';'  */
#line 283 "parser.y"
                      { (yyval.stmt) = NULL; }
#line 1776 "parser.tab.c"
    break;

  case 35: /* stmt_block: '{' stmtlist '}'  */
#line 286 "parser.y"
                             { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1782 "parser.tab.c"
    break;

  case 36: /* stmtlist: stmtlist stmt  */
#line 289 "parser.y"
                        { (yyval.stmt) = merege_comand((yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 1788 "parser.tab.c"
    break;

  case 37: /* stmtlist: %empty  */
#line 290 "parser.y"
            { (yyval.stmt) = NULL; }
#line 1794 "parser.tab.c"
    break;

  case 38: /* boolexpr: boolexpr OR boolterm  */
#line 294 "parser.y"
{
    /* Generate commands for logical OR */
    (yyval.boolean).head = translate_comand((yyvsp[-2].boolean).head, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.boolean).head));
    (yyval.boolean).head = add_label((yyval.boolean).head);
    update_list_to_label((yyvsp[-2].boolean).false, get_last_command((yyval.boolean).head));
    (yyval.boolean).head = merege_comand((yyval.boolean).head, (yyvsp[0].boolean).head);
    add_label((yyval.boolean).head);
    update_list_to_label(temp_link, get_last_command((yyval.boolean).head));
    (yyval.boolean).false = (yyvsp[0].boolean).false;
}
#line 1810 "parser.tab.c"
    break;

  case 39: /* boolexpr: boolterm  */
#line 306 "parser.y"
{
    /* Boolean term */
    (yyval.boolean).head = (yyvsp[0].boolean).head;
    (yyval.boolean).false = (yyvsp[0].boolean).false;
}
#line 1820 "parser.tab.c"
    break;

  case 40: /* boolterm: boolterm AND boolfactor  */
#line 314 "parser.y"
{
    /* Generate commands for logical AND */
    (yyval.boolean).head = merege_comand((yyvsp[-2].boolean).head, (yyvsp[0].boolean).head);
    (yyval.boolean).false = merge_comnd_list((yyvsp[-2].boolean).false, (yyvsp[0].boolean).false);
}
#line 1830 "parser.tab.c"
    break;

  case 41: /* boolterm: boolfactor  */
#line 320 "parser.y"
{
    /* Boolean factor */
    (yyval.boolean).false = (yyvsp[0].boolean).false;
    (yyval.boolean).head = (yyvsp[0].boolean).head;
}
#line 1840 "parser.tab.c"
    break;

  case 42: /* boolfactor: NOT '(' boolexpr ')'  */
#line 328 "parser.y"
{
    /* Generate commands for logical NOT */
    (yyval.boolean).head = translate_comand((yyvsp[-1].boolean).head, 'J', "UMP", "", "", "");
    (yyval.boolean).false = add_new_command_list(NULL, get_last_command((yyval.boolean).head));
    add_label((yyval.boolean).head);
    update_list_to_label((yyvsp[-1].boolean).false, get_last_command((yyval.boolean).head));
}
#line 1852 "parser.tab.c"
    break;

  case 43: /* boolfactor: expression RELOP expression  */
#line 336 "parser.y"
{
    /* Generate commands for relational operators */
    if ((yyvsp[-2].expression).type == 'I' && (yyvsp[0].expression).type == 'R')
        (yyvsp[-2].expression).head = convert_to_float((yyvsp[-2].expression).head, (yyvsp[-2].expression).last);
    else if ((yyvsp[0].expression).type == 'I' && (yyvsp[-2].expression).type == 'R')
        (yyvsp[0].expression).head = convert_to_float((yyvsp[0].expression).head, (yyvsp[0].expression).last);
    (yyval.boolean).head = build_relop_command((yyvsp[-1].relop), (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).head, (yyvsp[0].expression).head, type_decider ((yyvsp[-2].expression).type, (yyvsp[0].expression).type));
    (yyval.boolean).false = add_new_command_list(NULL, get_last_command((yyval.boolean).head));/*update the line number for the jump*/
}
#line 1866 "parser.tab.c"
    break;

  case 44: /* expression: expression ADDOP term  */
#line 348 "parser.y"
{
    /* Generate commands for addition/subtraction */
    (yyval.expression).type = type_decider ((yyvsp[-2].expression).type, (yyvsp[0].expression).type);
    (yyval.expression).head = build_arithmetic_command((yyvsp[-1].op), (yyval.expression).type, (yyval.expression).last, (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).type, (yyvsp[0].expression).type, (yyvsp[-2].expression).head, (yyvsp[0].expression).head);
}
#line 1876 "parser.tab.c"
    break;

  case 45: /* expression: term  */
#line 354 "parser.y"
{
    /* Term in an expression */
    (yyval.expression).type = (yyvsp[0].expression).type;
    (yyval.expression).head = (yyvsp[0].expression).head;
    strcpy((yyval.expression).last, (yyvsp[0].expression).last);
}
#line 1887 "parser.tab.c"
    break;

  case 46: /* term: term MULOP factor  */
#line 363 "parser.y"
{
    /* Generate commands for multiplication/division */
    (yyval.expression).type = type_decider ((yyvsp[-2].expression).type, (yyvsp[0].expression).type);
    (yyval.expression).head = build_arithmetic_command((yyvsp[-1].op), (yyval.expression).type, (yyval.expression).last, (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).type, (yyvsp[0].expression).type, (yyvsp[-2].expression).head, (yyvsp[0].expression).head);
}
#line 1897 "parser.tab.c"
    break;

  case 47: /* term: factor  */
#line 369 "parser.y"
{
    /* Factor in a term */
    (yyval.expression).type = (yyvsp[0].expression).type;
    (yyval.expression).head = (yyvsp[0].expression).head;
    strcpy((yyval.expression).last, (yyvsp[0].expression).last);
}
#line 1908 "parser.tab.c"
    break;

  case 48: /* factor: '(' expression ')'  */
#line 378 "parser.y"
{
    /* Parenthesized expression */
    (yyval.expression).type = (yyvsp[-1].expression).type;
    (yyval.expression).head = (yyvsp[-1].expression).head;
    strcpy((yyval.expression).last, (yyvsp[-1].expression).last);
}
#line 1919 "parser.tab.c"
    break;

  case 49: /* factor: CAST '(' expression ')'  */
#line 385 "parser.y"
{
    /* Cast expression */
    number = cast((yyvsp[-3].cast_op));
    if (number == 1 && (yyvsp[-1].expression).type == 'R') {
        (yyval.expression).head = convert_to_int((yyvsp[-1].expression).head, (yyvsp[-1].expression).last);
        (yyval.expression).type = 'I';
    } else if (number == 2 && (yyvsp[-1].expression).type == 'I') {
        (yyval.expression).head = convert_to_float((yyvsp[-1].expression).head, (yyvsp[-1].expression).last);
        (yyval.expression).type = 'R';
    } else {
        (yyval.expression).type = (yyvsp[-1].expression).type;
        (yyval.expression).head = (yyvsp[-1].expression).head;
    }
    strcpy((yyval.expression).last, (yyvsp[-1].expression).last);
}
#line 1939 "parser.tab.c"
    break;

  case 50: /* factor: ID  */
#line 401 "parser.y"
{
    /* Identifier */
    (yyval.expression).head = NULL;
    if (!(current_varible = search_varible((yyvsp[0].id)))) {
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
        (yyval.expression).type = 0;
    } else {
        strcpy((yyval.expression).last, (yyvsp[0].id));
        (yyval.expression).type = current_varible->type;
    }
}
#line 1955 "parser.tab.c"
    break;

  case 51: /* factor: NUM  */
#line 413 "parser.y"
{
    /* Numeric value */
    strcpy((yyval.expression).last, (yyvsp[0].num).value);
    (yyval.expression).type = (yyvsp[0].num).type;
    (yyval.expression).head = NULL;
}
#line 1966 "parser.tab.c"
    break;

  case 52: /* factor: '(' error ')'  */
#line 420 "parser.y"
    {
        yyerrok;
        (yyval.expression).type = 0;
        (yyval.expression).head = NULL;
    }
#line 1976 "parser.tab.c"
    break;


#line 1980 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

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
                      yytoken, &yylval);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 427 "parser.y"


int yyerror(const char *err)
{
    /* Error handling function */
    fprintf(stderr, "ERROR: line  %d: %s\n", line, err);
    error_number++;
    return 1;
}

