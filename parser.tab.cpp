/* A Bison parser, made by GNU Bison 3.7.6.  */

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
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"


   #include "semantics.hpp"
   #include "SymbolTable.hpp"
   #include "RegisterManager.hpp"
   #include "hw3_output.hpp"
   #include "global.hpp"
   #include "trick.hpp"
   extern int yylineno;
   int yylex(void);
   int yyparse();
   void yyerror(const char*);


#line 86 "parser.tab.cpp"

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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_BYTE = 5,                       /* BYTE  */
  YYSYMBOL_B = 6,                          /* B  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_TRUE = 8,                       /* TRUE  */
  YYSYMBOL_FALSE = 9,                      /* FALSE  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_SWITCH = 14,                    /* SWITCH  */
  YYSYMBOL_CASE = 15,                      /* CASE  */
  YYSYMBOL_ASSIGN = 16,                    /* ASSIGN  */
  YYSYMBOL_DEFAULT = 17,                   /* DEFAULT  */
  YYSYMBOL_COLON = 18,                     /* COLON  */
  YYSYMBOL_SC = 19,                        /* SC  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_ID = 21,                        /* ID  */
  YYSYMBOL_NUM = 22,                       /* NUM  */
  YYSYMBOL_STRING = 23,                    /* STRING  */
  YYSYMBOL_IF = 24,                        /* IF  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_EQUALITY = 30,                  /* EQUALITY  */
  YYSYMBOL_RELOP = 31,                     /* RELOP  */
  YYSYMBOL_ADD_SUB_OP = 32,                /* ADD_SUB_OP  */
  YYSYMBOL_MULT_DIV_OP = 33,               /* MULT_DIV_OP  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_LPAREN = 35,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 36,                    /* RPAREN  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_Program = 38,                   /* Program  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_Funcs = 40,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 41,                  /* FuncDecl  */
  YYSYMBOL_42_2 = 42,                      /* $@2  */
  YYSYMBOL_RetType = 43,                   /* RetType  */
  YYSYMBOL_Formals = 44,                   /* Formals  */
  YYSYMBOL_FormalsList = 45,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 46,                /* FormalDecl  */
  YYSYMBOL_Statements = 47,                /* Statements  */
  YYSYMBOL_Statement = 48,                 /* Statement  */
  YYSYMBOL_49_3 = 49,                      /* $@3  */
  YYSYMBOL_50_4 = 50,                      /* $@4  */
  YYSYMBOL_51_5 = 51,                      /* $@5  */
  YYSYMBOL_52_6 = 52,                      /* $@6  */
  YYSYMBOL_53_7 = 53,                      /* $@7  */
  YYSYMBOL_54_8 = 54,                      /* $@8  */
  YYSYMBOL_55_9 = 55,                      /* $@9  */
  YYSYMBOL_56_10 = 56,                     /* $@10  */
  YYSYMBOL_57_11 = 57,                     /* $@11  */
  YYSYMBOL_58_12 = 58,                     /* $@12  */
  YYSYMBOL_59_13 = 59,                     /* $@13  */
  YYSYMBOL_60_14 = 60,                     /* $@14  */
  YYSYMBOL_61_15 = 61,                     /* $@15  */
  YYSYMBOL_62_16 = 62,                     /* $@16  */
  YYSYMBOL_IfStatement = 63,               /* IfStatement  */
  YYSYMBOL_64_17 = 64,                     /* $@17  */
  YYSYMBOL_ScopeM = 65,                    /* ScopeM  */
  YYSYMBOL_66_18 = 66,                     /* $@18  */
  YYSYMBOL_Scope = 67,                     /* Scope  */
  YYSYMBOL_68_19 = 68,                     /* $@19  */
  YYSYMBOL_M = 69,                         /* M  */
  YYSYMBOL_M_br = 70,                      /* M_br  */
  YYSYMBOL_N_ELSE = 71,                    /* N_ELSE  */
  YYSYMBOL_N = 72,                         /* N  */
  YYSYMBOL_Call = 73,                      /* Call  */
  YYSYMBOL_ExpList = 74,                   /* ExpList  */
  YYSYMBOL_Type = 75,                      /* Type  */
  YYSYMBOL_Exp = 76,                       /* Exp  */
  YYSYMBOL_CaseList = 77,                  /* CaseList  */
  YYSYMBOL_CaseDecl = 78,                  /* CaseDecl  */
  YYSYMBOL_NEWID = 79                      /* NEWID  */
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
      35,    36
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    32,    32,    32,    34,    35,    37,    37,    39,    40,
      42,    43,    45,    46,    48,    50,    51,    53,    54,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    61,    62,    62,    62,    62,    63,    63,    64,    64,
      65,    65,    65,    65,    67,    67,    69,    69,    71,    71,
      73,    75,    77,    79,    81,    82,    84,    85,    87,    88,
      89,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   107,   108,   109,   111,
     113,   114
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "INT", "BYTE",
  "B", "BOOL", "TRUE", "FALSE", "RETURN", "WHILE", "BREAK", "CONTINUE",
  "SWITCH", "CASE", "ASSIGN", "DEFAULT", "COLON", "SC", "COMMA", "ID",
  "NUM", "STRING", "IF", "ELSE", "LBRACE", "RBRACE", "OR", "AND",
  "EQUALITY", "RELOP", "ADD_SUB_OP", "MULT_DIV_OP", "NOT", "LPAREN",
  "RPAREN", "$accept", "Program", "$@1", "Funcs", "FuncDecl", "$@2",
  "RetType", "Formals", "FormalsList", "FormalDecl", "Statements",
  "Statement", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "IfStatement", "$@17",
  "ScopeM", "$@18", "Scope", "$@19", "M", "M_br", "N_ELSE", "N", "Call",
  "ExpList", "Type", "Exp", "CaseList", "CaseDecl", "NEWID", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291
};
#endif

#define YYPACT_NINF (-61)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -61,     9,    10,   -61,   -61,   -61,   -61,   -61,   -61,    10,
       2,   -61,   -61,   -61,   -61,   -13,    46,   -61,   -61,    34,
       2,     5,    46,   -61,    49,   -61,   153,    79,   -61,    64,
      77,    60,    62,   -61,   129,   -61,    85,    80,     2,    -9,
     -61,   -61,   -61,   105,   -61,    21,    21,   -61,    93,    82,
      92,   -61,   -61,    21,    21,   102,   153,   -61,   -61,   -61,
     -61,   -61,    57,    21,    -3,   -61,   -61,   -61,   116,   -61,
     -61,   -61,    21,    21,    21,    21,    21,   -61,   -61,   172,
     172,   -61,   153,   -61,   -61,   -61,   -61,    21,   -61,   152,
     -61,   101,   166,   -61,   -61,    21,    21,     4,    47,   118,
     -61,   172,   -61,   125,   153,   159,   -61,   -61,   -61,    21,
      32,    74,   126,   132,   -61,   -61,   -61,   -61,   -61,   -61,
     112,   -61,   -61,   -61,   -61,   153,    76,   -61,   147,   136,
     -61,    76,   -61,   154,   -61,   143,   -61,   -61,   153,   -61,
     153,   153,   153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     9,    58,    59,    60,     3,     4,
       0,     8,     5,    81,    80,     0,    10,     6,    11,    12,
       0,     0,     0,    14,     0,    13,     0,     0,    51,     0,
       0,     0,     0,    48,     0,    15,    30,     0,     0,     0,
      69,    70,    26,    66,    68,     0,     0,    65,     0,    64,
       0,    36,    38,     0,     0,     0,     0,     7,    16,    53,
      46,    24,     0,     0,     0,    27,    67,    71,     0,    28,
      50,    50,     0,     0,     0,     0,     0,    37,    39,    53,
      44,    17,    49,    52,    31,    50,    25,     0,    18,     0,
      55,     0,    56,    61,    29,     0,     0,    74,    75,    63,
      62,    32,    40,     0,     0,     0,    19,    22,    54,     0,
      73,    72,     0,     0,    46,    47,    20,    23,    57,    50,
       0,    45,    21,    33,    41,     0,     0,    34,     0,     0,
      42,    77,    35,     0,    50,     0,    76,    50,     0,    43,
       0,    78,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,   164,   -61,   -61,   -61,   -61,   171,   -61,
     -54,   -33,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,    61,   -61,
     -61,   -61,   -60,   -61,   -61,    97,   -22,    98,    36,    -6,
      75,   -61,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     8,     9,    21,    10,    17,    18,    19,
      34,    35,   106,   122,   117,    86,    65,    94,   112,   125,
     132,    77,    78,   113,   126,   135,    36,   103,    84,    85,
      55,    56,    95,    50,    60,    83,    47,    91,    38,    92,
     130,   131,    49
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,    58,    82,    13,    37,    40,    41,    63,    13,     3,
      23,    96,    37,     4,     5,     6,    39,     7,    14,    43,
      44,    48,    16,    14,    39,   104,    64,    13,    62,    40,
      41,    45,    46,    90,    37,    73,    74,    75,    11,    67,
      68,    24,    14,    43,    44,    11,    39,    79,    80,    58,
       5,     6,    20,     7,    22,    45,    46,    89,    20,   123,
      37,    71,    72,    73,    74,    75,    97,    98,    99,   100,
     101,   115,    39,    87,   138,    26,    88,   140,    -1,    74,
      75,   105,    37,    51,   141,    13,   142,    40,    41,   110,
     111,   128,   127,   129,    39,    53,    52,    54,    42,    61,
      14,    43,    44,    37,    72,    73,    74,    75,    58,    58,
      59,    66,    69,    45,    46,    39,    37,    64,    37,    37,
      37,    70,    71,    72,    73,    74,    75,    76,    39,    81,
      39,    39,    39,     5,     6,    13,     7,   108,   124,    27,
      28,    29,    30,    31,    70,    71,    72,    73,    74,    75,
      14,    75,    93,    32,   134,    33,    57,     5,     6,    13,
       7,   114,   119,    27,    28,    29,    30,    31,   120,   133,
     139,   107,   137,    12,    14,   121,   102,    32,   116,    33,
      70,    71,    72,    73,    74,    75,   109,    70,    71,    72,
      73,    74,    75,    25,    70,    71,    72,    73,    74,    75,
      70,    71,    72,    73,    74,    75,   136,   118
};

static const yytype_uint8 yycheck[] =
{
      10,    34,    56,     6,    26,     8,     9,    16,     6,     0,
      20,    71,    34,     3,     4,     5,    26,     7,    21,    22,
      23,    27,    35,    21,    34,    85,    35,     6,    38,     8,
       9,    34,    35,    36,    56,    31,    32,    33,     2,    45,
      46,    36,    21,    22,    23,     9,    56,    53,    54,    82,
       4,     5,    16,     7,    20,    34,    35,    63,    22,   119,
      82,    29,    30,    31,    32,    33,    72,    73,    74,    75,
      76,   104,    82,    16,   134,    26,    19,   137,    31,    32,
      33,    87,   104,    19,   138,     6,   140,     8,     9,    95,
      96,    15,   125,    17,   104,    35,    19,    35,    19,    19,
      21,    22,    23,   125,    30,    31,    32,    33,   141,   142,
      25,     6,    19,    34,    35,   125,   138,    35,   140,   141,
     142,    28,    29,    30,    31,    32,    33,    35,   138,    27,
     140,   141,   142,     4,     5,     6,     7,    36,    26,    10,
      11,    12,    13,    14,    28,    29,    30,    31,    32,    33,
      21,    33,    36,    24,    18,    26,    27,     4,     5,     6,
       7,    36,    36,    10,    11,    12,    13,    14,    36,    22,
      27,    19,    18,     9,    21,   114,    79,    24,    19,    26,
      28,    29,    30,    31,    32,    33,    20,    28,    29,    30,
      31,    32,    33,    22,    28,    29,    30,    31,    32,    33,
      28,    29,    30,    31,    32,    33,   131,   109
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    38,    39,     0,     3,     4,     5,     7,    40,    41,
      43,    75,    40,     6,    21,    79,    35,    44,    45,    46,
      75,    42,    20,    79,    36,    45,    26,    10,    11,    12,
      13,    14,    24,    26,    47,    48,    63,    73,    75,    79,
       8,     9,    19,    22,    23,    34,    35,    73,    76,    79,
      70,    19,    19,    35,    35,    67,    68,    27,    48,    25,
      71,    19,    79,    16,    35,    53,     6,    76,    76,    19,
      28,    29,    30,    31,    32,    33,    35,    58,    59,    76,
      76,    27,    47,    72,    65,    66,    52,    16,    19,    76,
      36,    74,    76,    36,    54,    69,    69,    76,    76,    76,
      76,    76,    72,    64,    69,    76,    49,    19,    36,    20,
      76,    76,    55,    60,    36,    48,    19,    51,    74,    36,
      36,    65,    50,    69,    26,    56,    61,    48,    15,    17,
      77,    78,    57,    22,    18,    62,    77,    18,    69,    27,
      69,    47,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    39,    38,    40,    40,    42,    41,    43,    43,
      44,    44,    45,    45,    46,    47,    47,    48,    49,    48,
      50,    48,    51,    48,    52,    48,    53,    48,    54,    48,
      48,    48,    55,    56,    57,    48,    58,    48,    59,    48,
      60,    61,    62,    48,    64,    63,    66,    65,    68,    67,
      69,    70,    71,    72,    73,    73,    74,    74,    75,    75,
      75,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    78,
      79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,     9,     1,     1,
       0,     1,     1,     3,     2,     1,     2,     3,     0,     4,
       0,     6,     0,     5,     0,     3,     0,     3,     0,     4,
       1,     3,     0,     0,     0,    10,     0,     3,     0,     3,
       0,     0,     0,    11,     0,     6,     0,     3,     0,     2,
       0,     0,     2,     0,     4,     3,     1,     3,     1,     1,
       1,     3,     3,     3,     1,     1,     1,     2,     1,     1,
       1,     2,     4,     4,     3,     3,     2,     1,     4,     5,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
  case 2: /* $@1: %empty  */
#line 32 "parser.ypp"
          {SymbolTable::GetInstance();}
#line 1275 "parser.tab.cpp"
    break;

  case 4: /* Funcs: %empty  */
#line 34 "parser.ypp"
        {}
#line 1281 "parser.tab.cpp"
    break;

  case 6: /* $@2: %empty  */
#line 37 "parser.ypp"
                                        {SymbolTable::GetInstance()->push_ret(yyvsp[-3]); SymbolTable::GetInstance()->add_Func(new Variable(new Func(yyvsp[-3],yyvsp[0]),yyvsp[-2]));}
#line 1287 "parser.tab.cpp"
    break;

  case 7: /* FuncDecl: RetType NEWID LPAREN Formals $@2 RPAREN LBRACE Statements RBRACE  */
#line 37 "parser.ypp"
                                                                                                                                                                                            {SymbolTable::GetInstance()->pop_func();}
#line 1293 "parser.tab.cpp"
    break;

  case 8: /* RetType: Type  */
#line 39 "parser.ypp"
               {yyval=yyvsp[0];}
#line 1299 "parser.tab.cpp"
    break;

  case 9: /* RetType: VOID  */
#line 40 "parser.ypp"
               {yyval=new Void();}
#line 1305 "parser.tab.cpp"
    break;

  case 10: /* Formals: %empty  */
#line 42 "parser.ypp"
          {yyval = new FormalsList();}
#line 1311 "parser.tab.cpp"
    break;

  case 11: /* Formals: FormalsList  */
#line 43 "parser.ypp"
                      {yyval = yyvsp[0];}
#line 1317 "parser.tab.cpp"
    break;

  case 12: /* FormalsList: FormalDecl  */
#line 45 "parser.ypp"
                         {yyval = new FormalsList(); (dynamic_cast<FormalsList *>(yyval))->add(yyvsp[0]);}
#line 1323 "parser.tab.cpp"
    break;

  case 13: /* FormalsList: FormalDecl COMMA FormalsList  */
#line 46 "parser.ypp"
                                       {yyval=yyvsp[0];    (dynamic_cast<FormalsList *>(yyval))->add(yyvsp[-2]); }
#line 1329 "parser.tab.cpp"
    break;

  case 14: /* FormalDecl: Type NEWID  */
#line 48 "parser.ypp"
                        {yyval= new Variable(yyvsp[-1], yyvsp[0]);}
#line 1335 "parser.tab.cpp"
    break;

  case 15: /* Statements: Statement  */
#line 50 "parser.ypp"
                       {yyval = new Statement(); dynamic_cast<Statement *>(yyval)->merge(dynamic_cast<Statement *>(yyvsp[0]));}
#line 1341 "parser.tab.cpp"
    break;

  case 16: /* Statements: Statements Statement  */
#line 51 "parser.ypp"
                               {yyval = new Statement(); dynamic_cast<Statement *>(yyval)->merge(dynamic_cast<Statement *>(yyvsp[-1])); dynamic_cast<Statement *>(yyval)->merge(dynamic_cast<Statement *>(yyvsp[0]));}
#line 1347 "parser.tab.cpp"
    break;

  case 17: /* Statement: LBRACE Scope RBRACE  */
#line 53 "parser.ypp"
                                {yyval = new Statement(); dynamic_cast<Statement *>(yyval)->merge(dynamic_cast<Statement *>(yyvsp[-1]));}
#line 1353 "parser.tab.cpp"
    break;

  case 18: /* $@3: %empty  */
#line 54 "parser.ypp"
                        {SymbolTable::GetInstance()->add_var(new Variable(yyvsp[-2], yyvsp[-1])); }
#line 1359 "parser.tab.cpp"
    break;

  case 19: /* Statement: Type NEWID SC $@3  */
#line 54 "parser.ypp"
                                                                                      {yyval = new Statement();}
#line 1365 "parser.tab.cpp"
    break;

  case 20: /* $@4: %empty  */
#line 55 "parser.ypp"
                                   {SymbolTable::GetInstance()->add_var(new Variable(yyvsp[-4], yyvsp[-3], yyvsp[-1])); SymbolTable::GetInstance()->assign(yyvsp[-3],yyvsp[-1]);}
#line 1371 "parser.tab.cpp"
    break;

  case 21: /* Statement: Type NEWID ASSIGN Exp SC $@4  */
#line 55 "parser.ypp"
                                                                                                                                               {yyval = new Statement();}
#line 1377 "parser.tab.cpp"
    break;

  case 22: /* $@5: %empty  */
#line 56 "parser.ypp"
                              {SymbolTable::GetInstance()->assign(yyvsp[-3],yyvsp[-1]);}
#line 1383 "parser.tab.cpp"
    break;

  case 23: /* Statement: NEWID ASSIGN Exp SC $@5  */
#line 56 "parser.ypp"
                                                                           {yyval = new Statement();}
#line 1389 "parser.tab.cpp"
    break;

  case 24: /* $@6: %empty  */
#line 57 "parser.ypp"
                  {}
#line 1395 "parser.tab.cpp"
    break;

  case 25: /* Statement: Call SC $@6  */
#line 57 "parser.ypp"
                     {yyval = new Statement();}
#line 1401 "parser.tab.cpp"
    break;

  case 26: /* $@7: %empty  */
#line 58 "parser.ypp"
                    {SymbolTable::GetInstance()->check_return(new Void());}
#line 1407 "parser.tab.cpp"
    break;

  case 27: /* Statement: RETURN SC $@7  */
#line 58 "parser.ypp"
                                                                            {yyval = new Statement();}
#line 1413 "parser.tab.cpp"
    break;

  case 28: /* $@8: %empty  */
#line 59 "parser.ypp"
                        {SymbolTable::GetInstance()->check_return(yyvsp[-1]);}
#line 1419 "parser.tab.cpp"
    break;

  case 29: /* Statement: RETURN Exp SC $@8  */
#line 59 "parser.ypp"
                                                                        {yyval = new Statement();}
#line 1425 "parser.tab.cpp"
    break;

  case 30: /* Statement: IfStatement  */
#line 60 "parser.ypp"
                               {yyval = new Statement(dynamic_cast<IfStatement *>(yyvsp[0]));}
#line 1431 "parser.tab.cpp"
    break;

  case 31: /* Statement: IfStatement N_ELSE ScopeM  */
#line 61 "parser.ypp"
                                               {yyval = new Statement(dynamic_cast<IfStatement *>(yyvsp[-2]), dynamic_cast<MarkerN *>(yyvsp[-1]), dynamic_cast<Scope *>(yyvsp[0]));}
#line 1437 "parser.tab.cpp"
    break;

  case 32: /* $@9: %empty  */
#line 62 "parser.ypp"
                                {if(!is_bool(yyvsp[0])) output::errorMismatch(yylineno);}
#line 1443 "parser.tab.cpp"
    break;

  case 33: /* $@10: %empty  */
#line 62 "parser.ypp"
                                                                                             {SymbolTable::GetInstance()->push_while(new ReturnType("while"));}
#line 1449 "parser.tab.cpp"
    break;

  case 34: /* $@11: %empty  */
#line 62 "parser.ypp"
                                                                                                                                                                          {SymbolTable::GetInstance()->pop_while();}
#line 1455 "parser.tab.cpp"
    break;

  case 35: /* Statement: WHILE M_br LPAREN Exp $@9 RPAREN M $@10 Statement $@11  */
#line 62 "parser.ypp"
                                                                                                                                                                                                                     {yyval = new Statement(dynamic_cast<MarkerM *>(yyvsp[-8]), yyvsp[-6], dynamic_cast<MarkerM *>(yyvsp[-3]), dynamic_cast<Statement *>(yyvsp[-1]));}
#line 1461 "parser.tab.cpp"
    break;

  case 36: /* $@12: %empty  */
#line 63 "parser.ypp"
                   {SymbolTable::GetInstance()->check_while(new ReturnType("break"));}
#line 1467 "parser.tab.cpp"
    break;

  case 37: /* Statement: BREAK SC $@12  */
#line 63 "parser.ypp"
                                                                                       {yyval = new Statement(1);}
#line 1473 "parser.tab.cpp"
    break;

  case 38: /* $@13: %empty  */
#line 64 "parser.ypp"
                      {SymbolTable::GetInstance()->check_while(new ReturnType("continue"));}
#line 1479 "parser.tab.cpp"
    break;

  case 39: /* Statement: CONTINUE SC $@13  */
#line 64 "parser.ypp"
                                                                                             {yyval = new Statement(2);}
#line 1485 "parser.tab.cpp"
    break;

  case 40: /* $@14: %empty  */
#line 65 "parser.ypp"
                              {if(!is_num(yyvsp[-1])) output::errorMismatch(yylineno);}
#line 1491 "parser.tab.cpp"
    break;

  case 41: /* $@15: %empty  */
#line 65 "parser.ypp"
                                                                                               {SymbolTable::GetInstance()->push(); SymbolTable::GetInstance()->enter_switch();}
#line 1497 "parser.tab.cpp"
    break;

  case 42: /* $@16: %empty  */
#line 65 "parser.ypp"
                                                                                                                                                                                          {SymbolTable::GetInstance()->pop(); SymbolTable::GetInstance()->exit_switch();}
#line 1503 "parser.tab.cpp"
    break;

  case 43: /* Statement: SWITCH LPAREN Exp N $@14 RPAREN LBRACE $@15 CaseList $@16 RBRACE  */
#line 65 "parser.ypp"
                                                                                                                                                                                                                                                                                 {yyval = new Statement(dynamic_cast<Exp *>(yyvsp[-8]), dynamic_cast<MarkerN *>(yyvsp[-7]), dynamic_cast<CaseList *>(yyvsp[-2]));}
#line 1509 "parser.tab.cpp"
    break;

  case 44: /* $@17: %empty  */
#line 67 "parser.ypp"
                            {if(!is_bool(yyvsp[0])) output::errorMismatch(yylineno);}
#line 1515 "parser.tab.cpp"
    break;

  case 45: /* IfStatement: IF LPAREN Exp $@17 RPAREN ScopeM  */
#line 67 "parser.ypp"
                                                                                              {yyval = new IfStatement(yyvsp[-3], yyvsp[0]);}
#line 1521 "parser.tab.cpp"
    break;

  case 46: /* $@18: %empty  */
#line 69 "parser.ypp"
         {SymbolTable::GetInstance()->push();}
#line 1527 "parser.tab.cpp"
    break;

  case 47: /* ScopeM: $@18 M Statement  */
#line 69 "parser.ypp"
                                                           {SymbolTable::GetInstance()->pop(); yyval=new Scope(yyvsp[-1], yyvsp[0]);}
#line 1533 "parser.tab.cpp"
    break;

  case 48: /* $@19: %empty  */
#line 71 "parser.ypp"
        {SymbolTable::GetInstance()->push();}
#line 1539 "parser.tab.cpp"
    break;

  case 49: /* Scope: $@19 Statements  */
#line 71 "parser.ypp"
                                                         {SymbolTable::GetInstance()->pop(); yyval = new Statement(); dynamic_cast<Statement *>(yyval)->merge(dynamic_cast<Statement *>(yyvsp[0]));}
#line 1545 "parser.tab.cpp"
    break;

  case 50: /* M: %empty  */
#line 73 "parser.ypp"
    {yyval=new MarkerM();}
#line 1551 "parser.tab.cpp"
    break;

  case 51: /* M_br: %empty  */
#line 75 "parser.ypp"
       {yyval=new MarkerM(true);}
#line 1557 "parser.tab.cpp"
    break;

  case 52: /* N_ELSE: ELSE N  */
#line 77 "parser.ypp"
               {yyval=yyvsp[0];}
#line 1563 "parser.tab.cpp"
    break;

  case 53: /* N: %empty  */
#line 79 "parser.ypp"
    {yyval=new MarkerN();}
#line 1569 "parser.tab.cpp"
    break;

  case 54: /* Call: NEWID LPAREN ExpList RPAREN  */
#line 81 "parser.ypp"
                                   {yyval=new Call(yyvsp[-3], yyvsp[-1]);}
#line 1575 "parser.tab.cpp"
    break;

  case 55: /* Call: NEWID LPAREN RPAREN  */
#line 82 "parser.ypp"
                              {yyval=new Call(yyvsp[-2]);}
#line 1581 "parser.tab.cpp"
    break;

  case 56: /* ExpList: Exp  */
#line 84 "parser.ypp"
              {yyval = new ExpList(); (dynamic_cast<ExpList *>(yyval))->add(yyvsp[0]);}
#line 1587 "parser.tab.cpp"
    break;

  case 57: /* ExpList: Exp COMMA ExpList  */
#line 85 "parser.ypp"
                            {yyval=yyvsp[0];    (dynamic_cast<ExpList *>(yyval))->add(yyvsp[-2]); }
#line 1593 "parser.tab.cpp"
    break;

  case 58: /* Type: INT  */
#line 87 "parser.ypp"
           {yyval=new Int();}
#line 1599 "parser.tab.cpp"
    break;

  case 59: /* Type: BYTE  */
#line 88 "parser.ypp"
               {yyval=new Byte();}
#line 1605 "parser.tab.cpp"
    break;

  case 60: /* Type: BOOL  */
#line 89 "parser.ypp"
               {yyval=new Bool();}
#line 1611 "parser.tab.cpp"
    break;

  case 61: /* Exp: LPAREN Exp RPAREN  */
#line 91 "parser.ypp"
                        {yyval=yyvsp[-1];}
#line 1617 "parser.tab.cpp"
    break;

  case 62: /* Exp: Exp MULT_DIV_OP Exp  */
#line 92 "parser.ypp"
                              {yyval= binop(yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1623 "parser.tab.cpp"
    break;

  case 63: /* Exp: Exp ADD_SUB_OP Exp  */
#line 93 "parser.ypp"
                             {yyval= binop(yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1629 "parser.tab.cpp"
    break;

  case 64: /* Exp: NEWID  */
#line 94 "parser.ypp"
                {}
#line 1635 "parser.tab.cpp"
    break;

  case 65: /* Exp: Call  */
#line 95 "parser.ypp"
               {}
#line 1641 "parser.tab.cpp"
    break;

  case 66: /* Exp: NUM  */
#line 96 "parser.ypp"
              {}
#line 1647 "parser.tab.cpp"
    break;

  case 67: /* Exp: NUM B  */
#line 97 "parser.ypp"
                {yyval=new NumB(dynamic_cast<Num *>(yyvsp[-1])->val);}
#line 1653 "parser.tab.cpp"
    break;

  case 68: /* Exp: STRING  */
#line 98 "parser.ypp"
                 {}
#line 1659 "parser.tab.cpp"
    break;

  case 69: /* Exp: TRUE  */
#line 99 "parser.ypp"
               {yyval=new Boolean(true);}
#line 1665 "parser.tab.cpp"
    break;

  case 70: /* Exp: FALSE  */
#line 100 "parser.ypp"
                {yyval=new Boolean(false);}
#line 1671 "parser.tab.cpp"
    break;

  case 71: /* Exp: NOT Exp  */
#line 101 "parser.ypp"
                  {yyval=new Boolean(yyvsp[0]);}
#line 1677 "parser.tab.cpp"
    break;

  case 72: /* Exp: Exp AND M Exp  */
#line 102 "parser.ypp"
                        {yyval=new Boolean(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1683 "parser.tab.cpp"
    break;

  case 73: /* Exp: Exp OR M Exp  */
#line 103 "parser.ypp"
                       {yyval=new Boolean(yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1689 "parser.tab.cpp"
    break;

  case 74: /* Exp: Exp EQUALITY Exp  */
#line 104 "parser.ypp"
                           {yyval=new Boolean(yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1695 "parser.tab.cpp"
    break;

  case 75: /* Exp: Exp RELOP Exp  */
#line 105 "parser.ypp"
                        {yyval=new Boolean(yyvsp[-2], yyvsp[-1], yyvsp[0]);}
#line 1701 "parser.tab.cpp"
    break;

  case 76: /* CaseList: CaseDecl CaseList  */
#line 107 "parser.ypp"
                             {yyval = new CaseList(dynamic_cast<CaseDecl *>(yyvsp[-1]), dynamic_cast<CaseList *>(yyvsp[0]));}
#line 1707 "parser.tab.cpp"
    break;

  case 77: /* CaseList: CaseDecl  */
#line 108 "parser.ypp"
                   {yyval = new CaseList(dynamic_cast<CaseDecl *>(yyvsp[0]));}
#line 1713 "parser.tab.cpp"
    break;

  case 78: /* CaseList: DEFAULT COLON M Statements  */
#line 109 "parser.ypp"
                                       {yyval = new CaseList(dynamic_cast<CaseDecl *>(new CaseDecl(dynamic_cast<MarkerM *>(yyvsp[-1]), dynamic_cast<Statement *>(yyvsp[0]))));}
#line 1719 "parser.tab.cpp"
    break;

  case 79: /* CaseDecl: CASE NUM COLON M Statements  */
#line 111 "parser.ypp"
                                       {yyval = new CaseDecl(dynamic_cast<MarkerM *>(yyvsp[-1]), dynamic_cast<Statement *>(yyvsp[0]), dynamic_cast<Num *>(yyvsp[-3]));}
#line 1725 "parser.tab.cpp"
    break;

  case 81: /* NEWID: B  */
#line 114 "parser.ypp"
          {yyval=new Id(yytext);}
#line 1731 "parser.tab.cpp"
    break;


#line 1735 "parser.tab.cpp"

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
      yyerror (YY_("syntax error"));
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

  return yyresult;
}

#line 116 "parser.ypp"



void yyerror(const char*){
    output::errorSyn(yylineno);
}




std::string line;
int main(){
    load_const();
    auto p= yyparse();
    load_funcs();
    CodeBuffer::instance().printGlobalBuffer();
    CodeBuffer::instance().printCodeBuffer();
    return p;
}
