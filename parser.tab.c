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
#line 1 "parser.y"

#include <stdio.h>
#include <malloc.h>
#include "symboltab.h"
#include "translator.h"

extern int yylex(void);
int yyerror(const char *s);
extern int line;
command_list *case_jumps = NULL; /* For tracking case jumps */
int number = 0; /* Counter for numeric values */
int error_number = 0; /* Counter for errors */
var_node *current_varible = NULL, *next_varible = NULL; /* Variables for symbol table */
command *current_command = NULL; /* Current command in the command list */
command_list *temp_link = NULL; /* Temporary link for command lists */
char *num = NULL; /* Temporary storage for numeric values */
int p = 0; /* Counter for case values */
char case_val[10]; /* Array to store case values */

#line 91 "parser.tab.c"

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
  YYSYMBOL_MULOP = 16,                     /* MULOP  */
  YYSYMBOL_NUM = 17,                       /* NUM  */
  YYSYMBOL_CAST = 18,                      /* CAST  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_NOT = 21,                       /* NOT  */
  YYSYMBOL_RELOP = 22,                     /* RELOP  */
  YYSYMBOL_23_ = 23,                       /* ':'  */
  YYSYMBOL_24_ = 24,                       /* ';'  */
  YYSYMBOL_25_ = 25,                       /* ','  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_YYACCEPT = 31,                  /* $accept  */
  YYSYMBOL_program = 32,                   /* program  */
  YYSYMBOL_declarations = 33,              /* declarations  */
  YYSYMBOL_declaration = 34,               /* declaration  */
  YYSYMBOL_35_1 = 35,                      /* $@1  */
  YYSYMBOL_type = 36,                      /* type  */
  YYSYMBOL_idlist = 37,                    /* idlist  */
  YYSYMBOL_stmt = 38,                      /* stmt  */
  YYSYMBOL_assignment_stmt = 39,           /* assignment_stmt  */
  YYSYMBOL_input_stmt = 40,                /* input_stmt  */
  YYSYMBOL_output_stmt = 41,               /* output_stmt  */
  YYSYMBOL_if_stmt = 42,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 43,                /* while_stmt  */
  YYSYMBOL_switch_stmt = 44,               /* switch_stmt  */
  YYSYMBOL_caselist = 45,                  /* caselist  */
  YYSYMBOL_break_stmt = 46,                /* break_stmt  */
  YYSYMBOL_stmt_block = 47,                /* stmt_block  */
  YYSYMBOL_stmtlist = 48,                  /* stmtlist  */
  YYSYMBOL_boolexpr = 49,                  /* boolexpr  */
  YYSYMBOL_boolterm = 50,                  /* boolterm  */
  YYSYMBOL_boolfactor = 51,                /* boolfactor  */
  YYSYMBOL_expression = 52,                /* expression  */
  YYSYMBOL_term = 53,                      /* term  */
  YYSYMBOL_factor = 54                     /* factor  */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   241

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   277


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
      27,    28,     2,     2,    25,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    23,    24,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    67,    67,    74,    77,    78,    81,    81,    82,    85,
      86,    89,    90,    91,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   105,   109,   112,   120,   123,   128,   131,
     142,   143,   144,   147,   158,   159,   162,   175,   180,   184,
     191,   204,   205,   208,   209,   212,   213,   216,   217,   218,
     221,   232,   233,   236,   241,   244,   251,   262,   267,   270,
     275,   278,   284,   299,   310
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
  "BREAK", "ADDOP", "MULOP", "NUM", "CAST", "OR", "AND", "NOT", "RELOP",
  "':'", "';'", "','", "'='", "'('", "')'", "'{'", "'}'", "$accept",
  "program", "declarations", "declaration", "$@1", "type", "idlist",
  "stmt", "assignment_stmt", "input_stmt", "output_stmt", "if_stmt",
  "while_stmt", "switch_stmt", "caselist", "break_stmt", "stmt_block",
  "stmtlist", "boolexpr", "boolterm", "boolfactor", "expression", "term",
  "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      73,   -70,    20,    13,   -70,   -70,    56,   -70,    55,   -70,
       4,    80,   227,    95,   -70,   -70,    32,    10,    17,    50,
      57,    63,    84,   -70,   -70,   -70,   -70,   -70,   -70,   -70,
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   -70,   209,
     209,    94,   167,   198,   179,   -70,    90,   -70,   -70,    93,
     209,   -12,   110,   -70,    45,   122,   130,   105,    33,   118,
     -70,    -5,   134,    47,   151,   155,   -70,   209,    51,   209,
     -70,   209,   120,   132,   128,   186,   202,   140,   202,   209,
     161,   162,   128,   152,    54,   -70,   110,   -70,   -70,   -70,
     -70,   182,   -70,   158,   118,   185,   188,   -70,   187,   -70,
       5,   -70,   -70,   -70,   -70,   128,   -70,   128,   164,   204,
     196,    11,   -70,   -70,   -70,   -70,     6,   191,   195,   199,
     -70,   201,   207,   -70,   -70,   -70,   -70,   -70,    92,   104,
     116,    18,    42,   -70,   -70,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,     0,     1,    12,     0,     4,     0,     2,
       0,     0,     0,     0,    46,    22,     0,     0,     0,     0,
       0,     0,    44,    45,    47,    14,    15,    16,    17,    18,
      19,    20,    21,     8,     9,    10,     6,    13,    11,     0,
       0,     0,     0,     0,     0,    43,     0,    63,    64,     0,
       0,    24,    58,    60,     0,     0,    52,     0,     0,    51,
      54,     0,     0,     0,    52,     0,     7,     0,     0,     0,
      23,     0,    28,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    61,    57,    59,    27,    25,
      22,     0,    52,     0,    50,     0,     0,    53,    56,    41,
       0,    34,    22,    33,    62,     0,    55,     0,     0,     0,
       0,     0,    30,    31,    22,    29,     0,     0,     0,     0,
      37,     0,     0,    48,    48,    48,    48,    48,     0,     0,
       0,     0,     0,    38,    39,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   -70,   -70,   -70,   -69,   -70,   -70,
     -70,   -70,   -70,   -70,   111,   -70,   218,   114,   -42,   159,
     153,   -39,   141,   163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     7,    46,    36,     8,    24,    25,    26,
      27,    28,    29,    30,   109,    31,    32,    11,    58,    59,
      60,    61,    52,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    54,    65,    69,    63,    91,   110,   121,    96,   -41,
      69,    68,    70,   101,   103,   116,     5,    79,   -41,    15,
       4,    16,   -42,   122,   119,    17,    18,    19,    84,    20,
      21,   -42,    22,    93,    14,   -41,   112,    40,   113,   115,
      98,   120,     6,    15,    41,    16,   -40,     6,   -42,    17,
      18,    19,    76,    20,    21,   -40,    22,    10,    39,   -48,
      69,    77,    69,   -48,   -48,   -48,    69,   -48,   -48,    69,
     -48,     6,   -40,    72,     1,    81,    -5,    42,    12,    85,
      13,    15,   104,    16,    43,   -48,   -48,    17,    18,    19,
      44,    20,    21,    15,    22,    16,    37,    55,    38,    17,
      18,    19,    -5,    20,    21,    15,    22,    16,    45,     6,
      23,    17,    18,    19,    66,    20,    21,    15,    22,    16,
      67,     6,   133,    17,    18,    19,    71,    20,    21,    90,
      22,    16,    75,     6,   134,    17,    18,    19,    78,    20,
      21,    95,    22,    16,    88,     6,   135,    17,    18,    19,
      73,    20,    21,   102,    22,    16,    89,     6,    74,    17,
      18,    19,    80,    20,    21,   114,    22,    16,    56,     6,
      47,    17,    18,    19,    76,    20,    21,    76,    22,    82,
      64,     6,    47,    83,    48,    49,   106,    92,    57,    47,
      99,   100,   105,     6,    50,   107,    48,    49,   108,    62,
      57,    47,    69,    48,    49,    47,    50,    57,   116,   118,
      86,   111,    47,    50,   123,    48,    49,   117,   124,    48,
      49,     9,   125,    57,   126,    50,    48,    49,    33,    50,
     127,    97,    34,    35,    87,    94,    50,   128,   129,   130,
     131,   132
};

static const yytype_int8 yycheck[] =
{
      39,    40,    44,    15,    43,    74,     1,     1,    77,     4,
      15,    50,    24,    82,    83,     4,     3,    22,    13,     1,
       0,     3,     4,    17,    13,     7,     8,     9,    67,    11,
      12,    13,    14,    75,    30,    30,   105,    27,   107,   108,
      79,    30,    29,     1,    27,     3,     4,    29,    30,     7,
       8,     9,    19,    11,    12,    13,    14,     1,    26,     3,
      15,    28,    15,     7,     8,     9,    15,    11,    12,    15,
      14,    29,    30,    28,     1,    28,     3,    27,    23,    28,
      25,     1,    28,     3,    27,    29,    30,     7,     8,     9,
      27,    11,    12,     1,    14,     3,     1,     3,     3,     7,
       8,     9,    29,    11,    12,     1,    14,     3,    24,    29,
      30,     7,     8,     9,    24,    11,    12,     1,    14,     3,
      27,    29,    30,     7,     8,     9,    16,    11,    12,     1,
      14,     3,    27,    29,    30,     7,     8,     9,    20,    11,
      12,     1,    14,     3,    24,    29,    30,     7,     8,     9,
      28,    11,    12,     1,    14,     3,    24,    29,    28,     7,
       8,     9,    28,    11,    12,     1,    14,     3,     1,    29,
       3,     7,     8,     9,    19,    11,    12,    19,    14,    28,
       1,    29,     3,    28,    17,    18,    28,     1,    21,     3,
      29,    29,    10,    29,    27,    10,    17,    18,    10,     1,
      21,     3,    15,    17,    18,     3,    27,    21,     4,    13,
      69,   100,     3,    27,    23,    17,    18,    13,    23,    17,
      18,     3,    23,    21,    23,    27,    17,    18,     1,    27,
      23,    78,     5,     6,    71,    76,    27,   123,   124,   125,
     126,   127
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    32,    33,     0,     3,    29,    34,    37,    47,
       1,    48,    23,    25,    30,     1,     3,     7,     8,     9,
      11,    12,    14,    30,    38,    39,    40,    41,    42,    43,
      44,    46,    47,     1,     5,     6,    36,     1,     3,    26,
      27,    27,    27,    27,    27,    24,    35,     3,    17,    18,
      27,    52,    53,    54,    52,     3,     1,    21,    49,    50,
      51,    52,     1,    52,     1,    49,    24,    27,    52,    15,
      24,    16,    28,    28,    28,    27,    19,    28,    20,    22,
      28,    28,    28,    28,    52,    28,    53,    54,    24,    24,
       1,    38,     1,    49,    50,     1,    38,    51,    52,    29,
      29,    38,     1,    38,    28,    10,    28,    10,    10,    45,
       1,    45,    38,    38,     1,    38,     4,    13,    13,    13,
      30,     1,    17,    23,    23,    23,    23,    23,    48,    48,
      48,    48,    48,    30,    30,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    31,    32,    32,    33,    33,    35,    34,    34,    36,
      36,    37,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    38,    39,    39,    40,    40,    41,    41,    42,
      42,    42,    42,    43,    43,    43,    44,    44,    44,    44,
      45,    45,    45,    46,    46,    47,    47,    48,    48,    48,
      49,    49,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    54,    54,    54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     0,     0,     5,     3,     1,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     3,     5,     4,     5,     4,     7,
       7,     7,     7,     5,     5,     5,    10,     7,    10,    10,
       5,     0,     5,     2,     1,     3,     3,     2,     0,     2,
       3,     1,     1,     3,     1,     4,     3,     3,     1,     3,
       1,     3,     4,     1,     1
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
#line 68 "parser.y"
{
    (yyvsp[0].stmt) = translate_comand((yyvsp[0].stmt), 'H', "ALT", "", "", "");
    command_print((yyvsp[0].stmt));
    free_tree();
    free_list((yyvsp[0].stmt));
}
#line 1511 "parser.tab.c"
    break;

  case 3: /* program: error  */
#line 74 "parser.y"
        { yyerrok; yyclearin; }
#line 1517 "parser.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 81 "parser.y"
                             { set_varible_type((yyvsp[0].type)); }
#line 1523 "parser.tab.c"
    break;

  case 8: /* declaration: idlist ':' error  */
#line 82 "parser.y"
                   { yyerrok; yyclearin; }
#line 1529 "parser.tab.c"
    break;

  case 9: /* type: INT  */
#line 85 "parser.y"
          { (yyval.type) = (yyvsp[0].type); }
#line 1535 "parser.tab.c"
    break;

  case 10: /* type: FLOAT  */
#line 86 "parser.y"
        { (yyval.type) = (yyvsp[0].type); }
#line 1541 "parser.tab.c"
    break;

  case 11: /* idlist: idlist ',' ID  */
#line 89 "parser.y"
                      { set_varible_name((yyvsp[0].id)); }
#line 1547 "parser.tab.c"
    break;

  case 12: /* idlist: ID  */
#line 90 "parser.y"
     { set_varible_name((yyvsp[0].id)); }
#line 1553 "parser.tab.c"
    break;

  case 13: /* idlist: idlist ',' error  */
#line 91 "parser.y"
                   { yyerrok; yyclearin; }
#line 1559 "parser.tab.c"
    break;

  case 14: /* stmt: assignment_stmt  */
#line 94 "parser.y"
                      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1565 "parser.tab.c"
    break;

  case 15: /* stmt: input_stmt  */
#line 95 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1571 "parser.tab.c"
    break;

  case 16: /* stmt: output_stmt  */
#line 96 "parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1577 "parser.tab.c"
    break;

  case 17: /* stmt: if_stmt  */
#line 97 "parser.y"
          { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1583 "parser.tab.c"
    break;

  case 18: /* stmt: while_stmt  */
#line 98 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1589 "parser.tab.c"
    break;

  case 19: /* stmt: switch_stmt  */
#line 99 "parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1595 "parser.tab.c"
    break;

  case 20: /* stmt: break_stmt  */
#line 100 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1601 "parser.tab.c"
    break;

  case 21: /* stmt: stmt_block  */
#line 101 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1607 "parser.tab.c"
    break;

  case 22: /* stmt: error  */
#line 102 "parser.y"
        { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1613 "parser.tab.c"
    break;

  case 23: /* assignment_stmt: ID '=' expression ';'  */
#line 106 "parser.y"
{
    (yyval.stmt) = add_assign_commadn((yyvsp[-3].id), (yyvsp[-1].expression).last, (yyvsp[-1].expression).type, (yyvsp[-1].expression).head);
}
#line 1621 "parser.tab.c"
    break;

  case 24: /* assignment_stmt: ID '=' expression  */
#line 109 "parser.y"
                    { fprintf(stderr, "ERROR: line %d: missing semicolon after assignment\n", line-1); (yyval.stmt) = NULL; }
#line 1627 "parser.tab.c"
    break;

  case 25: /* input_stmt: INPUT '(' ID ')' ';'  */
#line 113 "parser.y"
{
    (yyval.stmt) = NULL;
    if (!(current_varible = search_varible((yyvsp[-2].id))))
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
    else
        (yyval.stmt) = translate_comand(NULL, current_varible->type, "INP", current_varible->name, "", "");
}
#line 1639 "parser.tab.c"
    break;

  case 26: /* input_stmt: INPUT '(' ID ')'  */
#line 120 "parser.y"
                   { fprintf(stderr, "ERROR: line %d: missing semicolon after input statement\n", line-1); (yyval.stmt) = NULL; }
#line 1645 "parser.tab.c"
    break;

  case 27: /* output_stmt: OUTPUT '(' expression ')' ';'  */
#line 124 "parser.y"
{
    (yyval.stmt) = translate_comand((yyvsp[-2].expression).head, (yyvsp[-2].expression).type, "PRT", (yyvsp[-2].expression).last, "", "");
    free_state((yyvsp[-2].expression).last);
}
#line 1654 "parser.tab.c"
    break;

  case 28: /* output_stmt: OUTPUT '(' expression ')'  */
#line 128 "parser.y"
                            { fprintf(stderr, "ERROR: line %d: missing semicolon after output statement\n", line-1); (yyval.stmt) = NULL; }
#line 1660 "parser.tab.c"
    break;

  case 29: /* if_stmt: IF '(' boolexpr ')' stmt ELSE stmt  */
#line 132 "parser.y"
{
    (yyval.stmt) = merege_comand((yyvsp[-4].boolean).head, (yyvsp[-2].stmt));
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label((yyvsp[-4].boolean).false, get_last_command((yyval.stmt)));
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label(temp_link, get_last_command((yyval.stmt)));
}
#line 1675 "parser.tab.c"
    break;

  case 30: /* if_stmt: IF '(' error ')' stmt ELSE stmt  */
#line 142 "parser.y"
                                  { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1681 "parser.tab.c"
    break;

  case 31: /* if_stmt: IF '(' boolexpr ')' error ELSE stmt  */
#line 143 "parser.y"
                                      { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1687 "parser.tab.c"
    break;

  case 32: /* if_stmt: IF '(' boolexpr ')' stmt ELSE error  */
#line 144 "parser.y"
                                      { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1693 "parser.tab.c"
    break;

  case 33: /* while_stmt: WHILE '(' boolexpr ')' stmt  */
#line 148 "parser.y"
{
    (yyval.stmt) = add_label(NULL);
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[-2].boolean).head);
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    update_list_to_label(temp_link, (yyval.stmt));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label((yyvsp[-2].boolean).false, get_last_command((yyval.stmt)));
}
#line 1708 "parser.tab.c"
    break;

  case 34: /* while_stmt: WHILE '(' error ')' stmt  */
#line 158 "parser.y"
                           { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1714 "parser.tab.c"
    break;

  case 35: /* while_stmt: WHILE '(' boolexpr ')' error  */
#line 159 "parser.y"
                               { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1720 "parser.tab.c"
    break;

  case 36: /* switch_stmt: SWITCH '(' expression ')' '{' caselist DEFAULT ':' stmtlist '}'  */
#line 163 "parser.y"
{
    next_varible = add_temp_var(current_varible->type);
    (yyvsp[-7].expression).head = merege_comand((yyvsp[-7].expression).head, (yyvsp[-4].stmt));
    temp_link = add_new_command_list(NULL, get_last_command((yyvsp[-7].expression).head));
    (yyvsp[-7].expression).head = add_label((yyvsp[-7].expression).head);
    (yyvsp[-7].expression).head = merege_comand((yyvsp[-7].expression).head, (yyvsp[-1].stmt));
    (yyvsp[-7].expression).head = add_label((yyvsp[-7].expression).head);
    update_list_to_label(temp_link, get_last_command((yyvsp[-7].expression).head));
    update_list_to_label(case_jumps, get_last_command((yyvsp[-7].expression).head));
    case_jumps = NULL;
    (yyval.stmt) = (yyvsp[-7].expression).head;
}
#line 1737 "parser.tab.c"
    break;

  case 37: /* switch_stmt: SWITCH '(' expression ')' '{' caselist '}'  */
#line 176 "parser.y"
{
    fprintf(stderr, "ERROR: line %d: missing DEFAULT in switch statement\n", line-1);
    (yyval.stmt) = NULL;
}
#line 1746 "parser.tab.c"
    break;

  case 38: /* switch_stmt: SWITCH '(' error ')' '{' caselist DEFAULT ':' stmtlist '}'  */
#line 180 "parser.y"
                                                             { 
    yyerrok; yyclearin;
     (yyval.stmt) = NULL;
     }
#line 1755 "parser.tab.c"
    break;

  case 39: /* switch_stmt: SWITCH '(' expression ')' '{' error DEFAULT ':' stmtlist '}'  */
#line 184 "parser.y"
                                                               { 
    yyerrok; 
    yyclearin; 
    (yyval.stmt) = NULL; }
#line 1764 "parser.tab.c"
    break;

  case 40: /* caselist: caselist CASE NUM ':' stmtlist  */
#line 192 "parser.y"
{
    num = (yyvsp[-2].num).value;
    next_varible = add_temp_var(current_varible->type);
    (yyval.stmt) = translate_comand((yyvsp[-4].stmt), current_varible->type, "EQL", next_varible->name, current_varible->name, num);
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "MPZ", "", next_varible->name, "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.stmt)));
    (yyval.stmt) = merege_comand((yyval.stmt), (yyvsp[0].stmt));
    (yyval.stmt) = translate_comand((yyval.stmt), 'J', "UMP", "", "", "");
    case_jumps = add_new_command_list(case_jumps, get_last_command((yyval.stmt)));
    (yyval.stmt) = add_label((yyval.stmt));
    update_list_to_label(temp_link, get_last_command((yyval.stmt)));
}
#line 1781 "parser.tab.c"
    break;

  case 41: /* caselist: %empty  */
#line 204 "parser.y"
              { (yyval.stmt) = NULL; case_jumps = NULL; }
#line 1787 "parser.tab.c"
    break;

  case 42: /* caselist: caselist CASE error ':' stmtlist  */
#line 205 "parser.y"
                                   { yyerrok; yyclearin; (yyval.stmt) = (yyvsp[-4].stmt); }
#line 1793 "parser.tab.c"
    break;

  case 43: /* break_stmt: BREAK ';'  */
#line 208 "parser.y"
                      { (yyval.stmt) = NULL; }
#line 1799 "parser.tab.c"
    break;

  case 44: /* break_stmt: BREAK  */
#line 209 "parser.y"
        { fprintf(stderr, "ERROR: line %d: missing semicolon after break\n", line-1); (yyval.stmt) = NULL; }
#line 1805 "parser.tab.c"
    break;

  case 45: /* stmt_block: '{' stmtlist '}'  */
#line 212 "parser.y"
                             { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1811 "parser.tab.c"
    break;

  case 46: /* stmt_block: '{' error '}'  */
#line 213 "parser.y"
                { yyerrok; yyclearin; (yyval.stmt) = NULL; }
#line 1817 "parser.tab.c"
    break;

  case 47: /* stmtlist: stmtlist stmt  */
#line 216 "parser.y"
                        { (yyval.stmt) = merege_comand((yyvsp[-1].stmt), (yyvsp[0].stmt)); }
#line 1823 "parser.tab.c"
    break;

  case 48: /* stmtlist: %empty  */
#line 217 "parser.y"
              { (yyval.stmt) = NULL; }
#line 1829 "parser.tab.c"
    break;

  case 49: /* stmtlist: stmtlist error  */
#line 218 "parser.y"
                 { yyerrok; yyclearin; (yyval.stmt) = (yyvsp[-1].stmt); }
#line 1835 "parser.tab.c"
    break;

  case 50: /* boolexpr: boolexpr OR boolterm  */
#line 222 "parser.y"
{
    (yyval.boolean).head = translate_comand((yyvsp[-2].boolean).head, 'J', "UMP", "", "", "");
    temp_link = add_new_command_list(NULL, get_last_command((yyval.boolean).head));
    (yyval.boolean).head = add_label((yyval.boolean).head);
    update_list_to_label((yyvsp[-2].boolean).false, get_last_command((yyval.boolean).head));
    (yyval.boolean).head = merege_comand((yyval.boolean).head, (yyvsp[0].boolean).head);
    add_label((yyval.boolean).head);
    update_list_to_label(temp_link, get_last_command((yyval.boolean).head));
    (yyval.boolean).false = (yyvsp[0].boolean).false;
}
#line 1850 "parser.tab.c"
    break;

  case 51: /* boolexpr: boolterm  */
#line 232 "parser.y"
           { (yyval.boolean).head = (yyvsp[0].boolean).head; (yyval.boolean).false = (yyvsp[0].boolean).false; }
#line 1856 "parser.tab.c"
    break;

  case 52: /* boolexpr: error  */
#line 233 "parser.y"
        { yyerrok; yyclearin; (yyval.boolean).head = NULL; (yyval.boolean).false = NULL; }
#line 1862 "parser.tab.c"
    break;

  case 53: /* boolterm: boolterm AND boolfactor  */
#line 237 "parser.y"
{
    (yyval.boolean).head = merege_comand((yyvsp[-2].boolean).head, (yyvsp[0].boolean).head);
    (yyval.boolean).false = merge_comnd_list((yyvsp[-2].boolean).false, (yyvsp[0].boolean).false);
}
#line 1871 "parser.tab.c"
    break;

  case 54: /* boolterm: boolfactor  */
#line 241 "parser.y"
             { (yyval.boolean).false = (yyvsp[0].boolean).false; (yyval.boolean).head = (yyvsp[0].boolean).head; }
#line 1877 "parser.tab.c"
    break;

  case 55: /* boolfactor: NOT '(' boolexpr ')'  */
#line 245 "parser.y"
{
    (yyval.boolean).head = translate_comand((yyvsp[-1].boolean).head, 'J', "UMP", "", "", "");
    (yyval.boolean).false = add_new_command_list(NULL, get_last_command((yyval.boolean).head));
    add_label((yyval.boolean).head);
    update_list_to_label((yyvsp[-1].boolean).false, get_last_command((yyval.boolean).head));
}
#line 1888 "parser.tab.c"
    break;

  case 56: /* boolfactor: expression RELOP expression  */
#line 252 "parser.y"
{
    if ((yyvsp[-2].expression).type == 'I' && (yyvsp[0].expression).type == 'R')
        (yyvsp[-2].expression).head = convert_to_float((yyvsp[-2].expression).head, (yyvsp[-2].expression).last);
    else if ((yyvsp[0].expression).type == 'I' && (yyvsp[-2].expression).type == 'R')
        (yyvsp[0].expression).head = convert_to_float((yyvsp[0].expression).head, (yyvsp[0].expression).last);
    (yyval.boolean).head = build_relop_command((yyvsp[-1].relop), (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).head, (yyvsp[0].expression).head, type_decider((yyvsp[-2].expression).type, (yyvsp[0].expression).type));
    (yyval.boolean).false = add_new_command_list(NULL, get_last_command((yyval.boolean).head));
}
#line 1901 "parser.tab.c"
    break;

  case 57: /* expression: expression ADDOP term  */
#line 263 "parser.y"
{
    (yyval.expression).type = type_decider((yyvsp[-2].expression).type, (yyvsp[0].expression).type);
    (yyval.expression).head = build_arithmetic_command((yyvsp[-1].op), (yyval.expression).type, (yyval.expression).last, (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).type, (yyvsp[0].expression).type, (yyvsp[-2].expression).head, (yyvsp[0].expression).head);
}
#line 1910 "parser.tab.c"
    break;

  case 58: /* expression: term  */
#line 267 "parser.y"
       { (yyval.expression).type = (yyvsp[0].expression).type; (yyval.expression).head = (yyvsp[0].expression).head; strcpy((yyval.expression).last, (yyvsp[0].expression).last); }
#line 1916 "parser.tab.c"
    break;

  case 59: /* term: term MULOP factor  */
#line 271 "parser.y"
{
    (yyval.expression).type = type_decider((yyvsp[-2].expression).type, (yyvsp[0].expression).type);
    (yyval.expression).head = build_arithmetic_command((yyvsp[-1].op), (yyval.expression).type, (yyval.expression).last, (yyvsp[-2].expression).last, (yyvsp[0].expression).last, (yyvsp[-2].expression).type, (yyvsp[0].expression).type, (yyvsp[-2].expression).head, (yyvsp[0].expression).head);
}
#line 1925 "parser.tab.c"
    break;

  case 60: /* term: factor  */
#line 275 "parser.y"
         { (yyval.expression).type = (yyvsp[0].expression).type; (yyval.expression).head = (yyvsp[0].expression).head; strcpy((yyval.expression).last, (yyvsp[0].expression).last); }
#line 1931 "parser.tab.c"
    break;

  case 61: /* factor: '(' expression ')'  */
#line 279 "parser.y"
{
    (yyval.expression).type = (yyvsp[-1].expression).type;
    (yyval.expression).head = (yyvsp[-1].expression).head;
    strcpy((yyval.expression).last, (yyvsp[-1].expression).last);
}
#line 1941 "parser.tab.c"
    break;

  case 62: /* factor: CAST '(' expression ')'  */
#line 285 "parser.y"
{
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
#line 1960 "parser.tab.c"
    break;

  case 63: /* factor: ID  */
#line 300 "parser.y"
{
    (yyval.expression).head = NULL;
    if (!(current_varible = search_varible((yyvsp[0].id)))) {
        fprintf(stderr, "ERROR: unknown variable, not defined in the symbol table");
        (yyval.expression).type = 0;
    } else {
        strcpy((yyval.expression).last, (yyvsp[0].id));
        (yyval.expression).type = current_varible->type;
    }
}
#line 1975 "parser.tab.c"
    break;

  case 64: /* factor: NUM  */
#line 311 "parser.y"
{
    strcpy((yyval.expression).last, (yyvsp[0].num).value);
    (yyval.expression).type = (yyvsp[0].num).type;
    (yyval.expression).head = NULL;
}
#line 1985 "parser.tab.c"
    break;


#line 1989 "parser.tab.c"

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

#line 318 "parser.y"


int yyerror(const char *err)
{
    fprintf(stderr, "ERROR: line %d: %s\n", line-1, err);
    error_number = 1;
    return 1;
}
