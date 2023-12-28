/* A Bison parser, made by GNU Bison 3.7.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         guidoarparse
#define yylex           guidoarlex
#define yyerror         guidoarerror
#define yydebug         guidoardebug
#define yynerrs         guidoarnerrs

/* First part of user prologue.  */
#line 1 "guido.y"


#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

#include "guidoelement.h"
#include "gmnreader.h"
#include "guidorational.h"

#include "guidoparser.h"
#include "guidoparse.h++"
// #include "guidolex.c++"


#ifdef WIN32
# pragma warning (disable : 4267 4005)
#endif

// #define YYERROR_VERBOSE
static void guidotagerror (guido::guidoparser* p, const std::string* str, int line, int col);
static int guidoarerror (YYLTYPE* locp, guido::guidoparser* context, const char*s);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);

// #define parseDebug 
#ifdef parseDebug
#define debug(msg)		cerr << msg << endl;
#define vdebug(msg,v)	cerr << msg << " " << v << endl;
#else
#define debug(msg)
#define vdebug(msg, v)
#endif
#define forcedebug(msg)			cerr << msg << endl;
#define forcevdebug(msg, v)		cerr << msg << " " << v << endl;


#define scanner context->fScanner

using namespace std;
using namespace guido;


static void vadd (std::vector<guido::Sguidoelement>* v1, std::vector<guido::Sguidoelement>* v2)
{
	for (auto elt: *v2)
		v1->push_back(elt);
}

namespace guido
{


#line 130 "guidoparse.c++"

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

#include "guidoparse.h++"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_PNUMBER = 4,                    /* PNUMBER  */
  YYSYMBOL_NNUMBER = 5,                    /* NNUMBER  */
  YYSYMBOL_FLOAT = 6,                      /* FLOAT  */
  YYSYMBOL_STARTCHORD = 7,                 /* STARTCHORD  */
  YYSYMBOL_ENDCHORD = 8,                   /* ENDCHORD  */
  YYSYMBOL_STARTSEQ = 9,                   /* STARTSEQ  */
  YYSYMBOL_ENDSEQ = 10,                    /* ENDSEQ  */
  YYSYMBOL_STARTPARAM = 11,                /* STARTPARAM  */
  YYSYMBOL_ENDPARAM = 12,                  /* ENDPARAM  */
  YYSYMBOL_STARTRANGE = 13,                /* STARTRANGE  */
  YYSYMBOL_ENDRANGE = 14,                  /* ENDRANGE  */
  YYSYMBOL_SEP = 15,                       /* SEP  */
  YYSYMBOL_IDSEP = 16,                     /* IDSEP  */
  YYSYMBOL_BAR = 17,                       /* BAR  */
  YYSYMBOL_TAGNAME = 18,                   /* TAGNAME  */
  YYSYMBOL_IDT = 19,                       /* IDT  */
  YYSYMBOL_DIATONIC = 20,                  /* DIATONIC  */
  YYSYMBOL_CHROMATIC = 21,                 /* CHROMATIC  */
  YYSYMBOL_SOLFEGE = 22,                   /* SOLFEGE  */
  YYSYMBOL_EMPTYT = 23,                    /* EMPTYT  */
  YYSYMBOL_RESTT = 24,                     /* RESTT  */
  YYSYMBOL_DOT = 25,                       /* DOT  */
  YYSYMBOL_DDOT = 26,                      /* DDOT  */
  YYSYMBOL_TDOT = 27,                      /* TDOT  */
  YYSYMBOL_SHARPT = 28,                    /* SHARPT  */
  YYSYMBOL_FLATT = 29,                     /* FLATT  */
  YYSYMBOL_TAB = 30,                       /* TAB  */
  YYSYMBOL_MLS = 31,                       /* MLS  */
  YYSYMBOL_SEC = 32,                       /* SEC  */
  YYSYMBOL_UNIT = 33,                      /* UNIT  */
  YYSYMBOL_MULT = 34,                      /* MULT  */
  YYSYMBOL_DIV = 35,                       /* DIV  */
  YYSYMBOL_EQUAL = 36,                     /* EQUAL  */
  YYSYMBOL_STRING = 37,                    /* STRING  */
  YYSYMBOL_EXTRA = 38,                     /* EXTRA  */
  YYSYMBOL_ENDVAR = 39,                    /* ENDVAR  */
  YYSYMBOL_VARNAME = 40,                   /* VARNAME  */
  YYSYMBOL_FRETTE = 41,                    /* FRETTE  */
  YYSYMBOL_COMMENT = 42,                   /* COMMENT  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_gmn = 44,                       /* gmn  */
  YYSYMBOL_header = 45,                    /* header  */
  YYSYMBOL_score = 46,                     /* score  */
  YYSYMBOL_voicelist = 47,                 /* voicelist  */
  YYSYMBOL_sep = 48,                       /* sep  */
  YYSYMBOL_voice = 49,                     /* voice  */
  YYSYMBOL_symbols = 50,                   /* symbols  */
  YYSYMBOL_vardecl = 51,                   /* vardecl  */
  YYSYMBOL_varname = 52,                   /* varname  */
  YYSYMBOL_tag = 53,                       /* tag  */
  YYSYMBOL_positiontag = 54,               /* positiontag  */
  YYSYMBOL_rangetag = 55,                  /* rangetag  */
  YYSYMBOL_tagname = 56,                   /* tagname  */
  YYSYMBOL_tagid = 57,                     /* tagid  */
  YYSYMBOL_tagarg = 58,                    /* tagarg  */
  YYSYMBOL_tagparam = 59,                  /* tagparam  */
  YYSYMBOL_tagparams = 60,                 /* tagparams  */
  YYSYMBOL_chord = 61,                     /* chord  */
  YYSYMBOL_chordsymbols = 62,              /* chordsymbols  */
  YYSYMBOL_tagchordsymbol = 63,            /* tagchordsymbol  */
  YYSYMBOL_chordsymbol = 64,               /* chordsymbol  */
  YYSYMBOL_rangechordtag = 65,             /* rangechordtag  */
  YYSYMBOL_taglist = 66,                   /* taglist  */
  YYSYMBOL_music = 67,                     /* music  */
  YYSYMBOL_rest = 68,                      /* rest  */
  YYSYMBOL_note = 69,                      /* note  */
  YYSYMBOL_noteid = 70,                    /* noteid  */
  YYSYMBOL_notename = 71,                  /* notename  */
  YYSYMBOL_accidentals = 72,               /* accidentals  */
  YYSYMBOL_accidental = 73,                /* accidental  */
  YYSYMBOL_octave = 74,                    /* octave  */
  YYSYMBOL_duration = 75,                  /* duration  */
  YYSYMBOL_dots = 76,                      /* dots  */
  YYSYMBOL_comment = 77,                   /* comment  */
  YYSYMBOL_comments = 78,                  /* comments  */
  YYSYMBOL_id = 79,                        /* id  */
  YYSYMBOL_number = 80,                    /* number  */
  YYSYMBOL_pnumber = 81,                   /* pnumber  */
  YYSYMBOL_nnumber = 82,                   /* nnumber  */
  YYSYMBOL_floatn = 83,                    /* floatn  */
  YYSYMBOL_signednumber = 84               /* signednumber  */
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  143

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   118,   118,   119,   122,   123,   124,   125,   128,   129,
     130,   131,   134,   135,   136,   139,   140,   143,   144,   147,
     148,   149,   150,   151,   152,   155,   156,   157,   160,   165,
     166,   169,   170,   173,   176,   179,   180,   181,   184,   185,
     186,   187,   188,   189,   190,   193,   194,   197,   198,   204,
     207,   208,   211,   212,   213,   214,   217,   218,   219,   220,
     223,   226,   227,   233,   234,   237,   238,   241,   242,   245,
     246,   249,   250,   251,   252,   255,   256,   259,   260,   263,
     264,   267,   268,   269,   270,   273,   274,   275,   281,   284,
     285,   288,   290,   292,   294,   296,   298,   299,   300
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
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "PNUMBER",
  "NNUMBER", "FLOAT", "STARTCHORD", "ENDCHORD", "STARTSEQ", "ENDSEQ",
  "STARTPARAM", "ENDPARAM", "STARTRANGE", "ENDRANGE", "SEP", "IDSEP",
  "BAR", "TAGNAME", "IDT", "DIATONIC", "CHROMATIC", "SOLFEGE", "EMPTYT",
  "RESTT", "DOT", "DDOT", "TDOT", "SHARPT", "FLATT", "TAB", "MLS", "SEC",
  "UNIT", "MULT", "DIV", "EQUAL", "STRING", "EXTRA", "ENDVAR", "VARNAME",
  "FRETTE", "COMMENT", "$accept", "gmn", "header", "score", "voicelist",
  "sep", "voice", "symbols", "vardecl", "varname", "tag", "positiontag",
  "rangetag", "tagname", "tagid", "tagarg", "tagparam", "tagparams",
  "chord", "chordsymbols", "tagchordsymbol", "chordsymbol",
  "rangechordtag", "taglist", "music", "rest", "note", "noteid",
  "notename", "accidentals", "accidental", "octave", "duration", "dots",
  "comment", "comments", "id", "number", "pnumber", "nnumber", "floatn",
  "signednumber", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,     6,   -74,   -74,   -74,    13,    26,   -25,   -25,   -74,
      -9,   -74,   -74,    29,   -25,   -74,    25,    63,   -74,   -25,
     -74,   -74,   -74,   -74,    37,   -74,   -25,    38,   -25,   -74,
     104,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    98,   -74,
     -74,    42,   -74,    22,   102,   -74,   -74,   -74,   -74,    91,
     112,   -74,   -74,   -74,   -74,   -74,    90,   -74,   -74,   -74,
      92,    96,   -25,   -25,   117,    67,   -74,    14,   -74,   104,
     -74,   104,   134,   135,   135,    46,   -74,   136,    20,   -74,
     -74,    91,   -74,    43,   -74,   137,   -74,   -74,   -74,   104,
     -74,   104,   -74,    74,   -74,   117,    14,   117,   -25,   129,
     107,   -74,   -74,   -74,   -74,    94,   -74,   -74,   -74,   -74,
     -74,   -74,    78,   108,   110,   114,   -74,    43,    46,   133,
     138,   -74,   -74,    74,    43,   135,   -74,   -74,    20,    20,
     -74,   -74,    46,   -74,   -74,   -74,    46,   -74,   -74,   -74,
     -74,   -74,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    19,    28,    88,     0,     0,     2,    10,     5,
       0,     4,     8,     0,    12,    89,     0,     0,     1,     3,
       6,     7,    11,    18,     0,     9,    15,     0,    13,    90,
       0,    17,    37,    34,    71,    72,    73,    74,    81,    23,
      21,    29,    30,    35,    31,    22,    20,    64,    63,    79,
      69,    24,    92,    93,    94,    95,     0,    96,    97,    98,
       0,     0,    16,    14,    61,     0,    50,    52,    57,     0,
      56,     0,     0,     0,     0,    85,    19,     0,     0,    77,
      78,    79,    75,    81,    80,     0,    25,    27,    26,     0,
      49,     0,    61,    54,    58,    62,    53,     0,    59,     0,
      83,    84,    86,    87,    65,     0,    36,    91,    42,    44,
      45,    47,     0,    43,    39,    38,    76,    81,    85,     0,
       0,    51,    62,    55,    81,     0,    33,    32,     0,     0,
      41,    40,    85,    67,    70,    60,    85,    82,    48,    46,
      43,    68,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   -74,   142,   -74,   -74,    35,    73,   144,     5,
     -74,   -17,   -74,   -74,   -74,    24,    23,   -74,   -74,   -74,
       8,    33,   -74,   -47,   -16,   -74,   -74,   -74,   -74,   -74,
      75,    76,   -71,   -73,     2,   128,    30,   -67,   -74,   -74,
     131,   -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,    13,    27,     8,    17,     9,   109,
      40,    64,    42,    43,    44,   110,   111,   112,    45,    65,
      66,    67,    68,    69,    70,    47,    48,    49,    50,    81,
      82,    83,    75,   104,    71,    16,   113,    57,    58,    59,
     114,   115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    46,    11,    15,    61,    10,   100,   101,    21,    22,
      23,    10,   118,    18,    12,     2,    23,     4,    29,    51,
      93,    22,    39,    52,    53,    54,    55,    24,    15,    84,
      23,    32,    33,     1,     2,     2,    14,    25,    77,   107,
      52,    53,    54,    55,    26,   133,   132,     2,     4,   123,
      92,    28,    95,   136,    97,    76,     4,   108,   137,   141,
       3,    84,    63,   142,    29,    23,     3,     4,     4,    94,
      30,   102,   103,    31,    56,    90,   122,    73,    74,    92,
      32,    33,    91,    34,    35,    36,    37,    38,    41,    46,
     127,    32,    33,   128,    52,    53,    54,   120,    94,   121,
      94,    30,    96,     3,    98,     4,   122,    51,   126,    72,
      39,    32,    33,    78,    34,    35,    36,    37,    38,    79,
      80,    32,    33,    85,    34,    35,    36,    37,    38,    86,
      89,    87,    73,    74,     3,    88,     4,    99,    52,   106,
     119,   124,   125,   130,   129,   134,     4,   131,    19,   105,
      20,   138,   135,   139,    62,    60,   116,   117,     0,   140
};

static const yytype_int16 yycheck[] =
{
      17,    17,     0,     1,    24,     0,    73,    74,     6,     7,
       8,     6,    83,     0,     8,     9,    14,    42,    16,    17,
      67,    19,    17,     3,     4,     5,     6,    36,    26,    49,
      28,    17,    18,     7,     9,     9,     1,     8,    16,    19,
       3,     4,     5,     6,    15,   118,   117,     9,    42,    96,
      67,    16,    69,   124,    71,    13,    42,    37,   125,   132,
      40,    81,    27,   136,    62,    63,    40,    42,    42,    67,
       7,    25,    26,    10,    37,     8,    93,    34,    35,    96,
      17,    18,    15,    20,    21,    22,    23,    24,   105,   105,
      12,    17,    18,    15,     3,     4,     5,    89,    96,    91,
      98,     7,    69,    40,    71,    42,   123,   105,    14,    11,
     105,    17,    18,    11,    20,    21,    22,    23,    24,    28,
      29,    17,    18,    11,    20,    21,    22,    23,    24,    39,
      13,    39,    34,    35,    40,    39,    42,     3,     3,     3,
       3,    12,    35,    33,    36,    12,    42,    33,     6,    76,
       6,   128,    14,   129,    26,    24,    81,    81,    -1,   129
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    40,    42,    44,    45,    46,    49,    51,
      52,    77,     8,    47,    49,    77,    78,    50,     0,    46,
      51,    77,    77,    77,    36,     8,    15,    48,    49,    77,
       7,    10,    17,    18,    20,    21,    22,    23,    24,    52,
      53,    54,    55,    56,    57,    61,    67,    68,    69,    70,
      71,    77,     3,     4,     5,     6,    37,    80,    81,    82,
      83,    84,    78,    49,    54,    62,    63,    64,    65,    66,
      67,    77,    11,    34,    35,    75,    13,    16,    11,    28,
      29,    72,    73,    74,    84,    11,    39,    39,    39,    13,
       8,    15,    54,    66,    77,    54,    64,    54,    64,     3,
      80,    80,    25,    26,    76,    50,     3,    19,    37,    52,
      58,    59,    60,    79,    83,    84,    73,    74,    75,     3,
      63,    63,    54,    66,    12,    35,    14,    12,    15,    36,
      33,    33,    75,    76,    12,    14,    75,    80,    59,    58,
      79,    76,    76
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    45,    45,    46,    46,
      46,    46,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    50,    50,    50,    51,    51,    51,    52,    53,
      53,    54,    54,    55,    56,    57,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      62,    62,    63,    63,    63,    63,    64,    64,    64,    64,
      65,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    75,    75,    75,    76,    76,    76,    77,    78,
      78,    79,    80,    81,    82,    83,    84,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     2,     2,     3,
       1,     2,     1,     2,     3,     1,     2,     3,     2,     0,
       2,     2,     2,     2,     2,     4,     4,     4,     1,     1,
       1,     1,     4,     4,     1,     1,     3,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     1,     3,     3,
       1,     3,     1,     2,     2,     3,     1,     1,     2,     2,
       4,     1,     2,     1,     1,     3,     6,     4,     5,     1,
       4,     1,     1,     1,     1,     1,     2,     1,     1,     0,
       1,     0,     4,     2,     2,     0,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1
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
        yyerror (&yylloc, context, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

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

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, context); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, guido::guidoparser* context)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, guido::guidoparser* context)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, context);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, guido::guidoparser* context)
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), context);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, context); \
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
  YYLTYPE *yylloc;
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, guido::guidoparser* context)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (context);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (guido::guidoparser* context)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
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
      yyerror_range[1] = yylloc;
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
  case 3: /* gmn: header score  */
#line 119 "guido.y"
                                                                                                { debug("header score"); context->setHeader((yyvsp[-1].velt)); delete (yyvsp[0].elt); }
#line 1688 "guidoparse.c++"
    break;

  case 4: /* header: comment  */
#line 122 "guido.y"
                                                                                                { debug("header comment"); (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt);}
#line 1694 "guidoparse.c++"
    break;

  case 5: /* header: vardecl  */
#line 123 "guido.y"
                                                                                                                { debug("header variable"); (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt);}
#line 1700 "guidoparse.c++"
    break;

  case 6: /* header: header vardecl  */
#line 124 "guido.y"
                                                                                                        { debug("header + variable"); (yyval.velt)=(yyvsp[-1].velt); (yyvsp[-1].velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1706 "guidoparse.c++"
    break;

  case 7: /* header: header comment  */
#line 125 "guido.y"
                                                                                                        { debug("header + comment"); (yyval.velt)=(yyvsp[-1].velt); (yyvsp[-1].velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1712 "guidoparse.c++"
    break;

  case 8: /* score: STARTCHORD ENDCHORD  */
#line 128 "guido.y"
                                                                                        { debug("new score"); (yyval.elt) = context->newScore(); }
#line 1718 "guidoparse.c++"
    break;

  case 9: /* score: STARTCHORD voicelist ENDCHORD  */
#line 129 "guido.y"
                                                                                        { debug("score voicelist"); (yyval.elt) = context->newScore(); (*(yyval.elt))->push( *(yyvsp[-1].velt)); delete (yyvsp[-1].velt); }
#line 1724 "guidoparse.c++"
    break;

  case 10: /* score: voice  */
#line 130 "guido.y"
                                                                                                                { debug("score voice"); (yyval.elt) = context->newScore(); (*(yyval.elt))->push( *(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1730 "guidoparse.c++"
    break;

  case 11: /* score: score comment  */
#line 131 "guido.y"
                                                                                                        { debug("score comment"); (yyval.elt) = (yyvsp[-1].elt); context->addFooter(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1736 "guidoparse.c++"
    break;

  case 12: /* voicelist: voice  */
#line 134 "guido.y"
                                                                                                        { debug("new voicelist"); (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back (*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1742 "guidoparse.c++"
    break;

  case 13: /* voicelist: comments voice  */
#line 135 "guido.y"
                                                                                                    { debug("add voicelist"); (yyval.velt) = new vector<Sguidoelement>; if ((yyvsp[-1].velt)) { for (auto c: *(yyvsp[-1].velt)) context->beforeVoice((yyvsp[0].elt), c); }; (yyval.velt)->push_back (*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1748 "guidoparse.c++"
    break;

  case 14: /* voicelist: voicelist sep voice  */
#line 136 "guido.y"
                                                                                                { debug("add voicelist"); (yyval.velt) = (yyvsp[-2].velt); (yyval.velt)->push_back (*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1754 "guidoparse.c++"
    break;

  case 15: /* sep: SEP  */
#line 139 "guido.y"
                                                                                                                { debug("SEP"); (yyval.velt)=0; }
#line 1760 "guidoparse.c++"
    break;

  case 16: /* sep: SEP comments  */
#line 140 "guido.y"
                                                                                                        { debug("SEP comments"); (yyval.velt)=(yyvsp[0].velt); }
#line 1766 "guidoparse.c++"
    break;

  case 17: /* voice: STARTSEQ symbols ENDSEQ  */
#line 143 "guido.y"
                                                                                        { debug("new voice"); (yyval.elt) = context->newVoice(); (*(yyval.elt))->push( *(yyvsp[-1].velt)); delete (yyvsp[-1].velt); }
#line 1772 "guidoparse.c++"
    break;

  case 18: /* voice: voice comment  */
#line 144 "guido.y"
                                                                                                        { debug("voice comment"); (yyval.elt) = (yyvsp[-1].elt); context->afterVoice((yyval.elt), *(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1778 "guidoparse.c++"
    break;

  case 19: /* symbols: %empty  */
#line 147 "guido.y"
                                                                                                                { debug("new symbols"); (yyval.velt) = new vector<Sguidoelement>; }
#line 1784 "guidoparse.c++"
    break;

  case 20: /* symbols: symbols music  */
#line 148 "guido.y"
                                                                                                        { debug("add music"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1790 "guidoparse.c++"
    break;

  case 21: /* symbols: symbols tag  */
#line 149 "guido.y"
                                                                                                        { debug("add tag"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1796 "guidoparse.c++"
    break;

  case 22: /* symbols: symbols chord  */
#line 150 "guido.y"
                                                                                                        { debug("add chord"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1802 "guidoparse.c++"
    break;

  case 23: /* symbols: symbols varname  */
#line 151 "guido.y"
                                                                                                        { debug("add varname"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1808 "guidoparse.c++"
    break;

  case 24: /* symbols: symbols comment  */
#line 152 "guido.y"
                                                                                                        { debug("add comment"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 1814 "guidoparse.c++"
    break;

  case 25: /* vardecl: varname EQUAL STRING ENDVAR  */
#line 155 "guido.y"
                                                                                { vdebug("vardecl string", *(yyvsp[-3].elt)); (yyval.elt) = (yyvsp[-3].elt); context->variableDecl (*(yyvsp[-3].elt), context->fText.c_str(), guidoparser::kString);  }
#line 1820 "guidoparse.c++"
    break;

  case 26: /* vardecl: varname EQUAL signednumber ENDVAR  */
#line 156 "guido.y"
                                                                                        { vdebug("vardecl int", *(yyvsp[-3].elt)); (yyval.elt) = (yyvsp[-3].elt); context->variableDecl (*(yyvsp[-3].elt), context->fText.c_str(), guidoparser::kInt);  }
#line 1826 "guidoparse.c++"
    break;

  case 27: /* vardecl: varname EQUAL floatn ENDVAR  */
#line 157 "guido.y"
                                                                                        { vdebug("vardecl float", *(yyvsp[-3].elt)); (yyval.elt) = (yyvsp[-3].elt); context->variableDecl (*(yyvsp[-3].elt), context->fText.c_str(), guidoparser::kFloat); }
#line 1832 "guidoparse.c++"
    break;

  case 28: /* varname: VARNAME  */
#line 160 "guido.y"
                                                                                                        { vdebug("varname", context->fText); (yyval.elt) =  context->newVariable(context->fText); }
#line 1838 "guidoparse.c++"
    break;

  case 29: /* tag: positiontag  */
#line 165 "guido.y"
                                                                                                        { debug("position tag "); (yyval.elt) = (yyvsp[0].elt); }
#line 1844 "guidoparse.c++"
    break;

  case 30: /* tag: rangetag  */
#line 166 "guido.y"
                                                                                                                { debug("range tag "); (yyval.elt) = (yyvsp[0].elt); }
#line 1850 "guidoparse.c++"
    break;

  case 31: /* positiontag: tagid  */
#line 169 "guido.y"
                                                                                                        { debug("new position tag "); (yyval.elt) = (yyvsp[0].elt); }
#line 1856 "guidoparse.c++"
    break;

  case 32: /* positiontag: tagid STARTPARAM tagparams ENDPARAM  */
#line 170 "guido.y"
                                                                                { debug("new tag + params"); (yyval.elt) = (yyvsp[-3].elt); (*(yyvsp[-3].elt))->add (*(yyvsp[-1].vattr)); delete (yyvsp[-1].vattr); }
#line 1862 "guidoparse.c++"
    break;

  case 33: /* rangetag: positiontag STARTRANGE symbols ENDRANGE  */
#line 173 "guido.y"
                                                                        { debug("new range tag "); (yyval.elt) = (yyvsp[-3].elt); (*(yyvsp[-3].elt))->push (*(yyvsp[-1].velt)); delete (yyvsp[-1].velt); }
#line 1868 "guidoparse.c++"
    break;

  case 34: /* tagname: TAGNAME  */
#line 176 "guido.y"
                                                                                                        { debug("tag name "); (yyval.str) = new string(context->fText); }
#line 1874 "guidoparse.c++"
    break;

  case 35: /* tagid: tagname  */
#line 179 "guido.y"
                                                                                                        { vdebug("new tag", *(yyvsp[0].str)); (yyval.elt) = context->newTag(*(yyvsp[0].str), 0); if (!(yyval.elt)) { guidotagerror(context, (yyvsp[0].str), (yylsp[0]).first_line, (yylsp[0]).first_column); YYERROR;} delete (yyvsp[0].str); }
#line 1880 "guidoparse.c++"
    break;

  case 36: /* tagid: tagname IDSEP NUMBER  */
#line 180 "guido.y"
                                                                                                { debug("new tag::id");  (yyval.elt) = context->newTag(*(yyvsp[-2].str), (yyvsp[-1].c)); if (!(yyval.elt)) { guidotagerror(context, (yyvsp[-2].str), (yylsp[-2]).first_line, (yylsp[-2]).first_column); YYERROR;} delete (yyvsp[-2].str); }
#line 1886 "guidoparse.c++"
    break;

  case 37: /* tagid: BAR  */
#line 181 "guido.y"
                                                                                                                { debug("new bar"); (yyval.elt) = context->newTag("\\bar", 0); }
#line 1892 "guidoparse.c++"
    break;

  case 38: /* tagarg: signednumber  */
#line 184 "guido.y"
                                                                                                { debug("new signednumber arg"); (yyval.attr) = context->newAttribute((yyvsp[0].num)); }
#line 1898 "guidoparse.c++"
    break;

  case 39: /* tagarg: floatn  */
#line 185 "guido.y"
                                                                                                                { debug("new FLOAT arg"); (yyval.attr) = context->newAttribute((yyvsp[0].real)); }
#line 1904 "guidoparse.c++"
    break;

  case 40: /* tagarg: signednumber UNIT  */
#line 186 "guido.y"
                                                                                                        { debug("new signednumber UNIT arg"); (yyval.attr) = context->newAttribute((yyvsp[-1].num)); (*(yyval.attr))->setUnit(context->fText); }
#line 1910 "guidoparse.c++"
    break;

  case 41: /* tagarg: floatn UNIT  */
#line 187 "guido.y"
                                                                                                        { debug("new FLOAT UNIT arg"); (yyval.attr) = context->newAttribute((yyvsp[-1].real)); (*(yyval.attr))->setUnit(context->fText); }
#line 1916 "guidoparse.c++"
    break;

  case 42: /* tagarg: STRING  */
#line 188 "guido.y"
                                                                                                                { debug("new STRING arg"); (yyval.attr) = context->newAttribute(context->fText, true); }
#line 1922 "guidoparse.c++"
    break;

  case 43: /* tagarg: id  */
#line 189 "guido.y"
                                                                                                                { debug("new ID arg"); (yyval.attr) = context->newAttribute(*(yyvsp[0].str), false); delete (yyvsp[0].str); }
#line 1928 "guidoparse.c++"
    break;

  case 44: /* tagarg: varname  */
#line 190 "guido.y"
                                                                                                                { debug("new var arg"); (yyval.attr) = context->newAttribute((*(yyvsp[0].elt))->getName(), false); delete (yyvsp[0].elt); }
#line 1934 "guidoparse.c++"
    break;

  case 45: /* tagparam: tagarg  */
#line 193 "guido.y"
                                                                                                        { debug("tagparam"); (yyval.attr) = (yyvsp[0].attr); }
#line 1940 "guidoparse.c++"
    break;

  case 46: /* tagparam: id EQUAL tagarg  */
#line 194 "guido.y"
                                                                                                        { debug("tagparam"); (yyval.attr) = (yyvsp[0].attr); (*(yyvsp[0].attr))->setName(*(yyvsp[-2].str)); delete (yyvsp[-2].str); }
#line 1946 "guidoparse.c++"
    break;

  case 47: /* tagparams: tagparam  */
#line 197 "guido.y"
                                                                                                        { (yyval.vattr) = new vector<Sguidoattribute>; (yyval.vattr)->push_back(*(yyvsp[0].attr)); delete (yyvsp[0].attr); }
#line 1952 "guidoparse.c++"
    break;

  case 48: /* tagparams: tagparams SEP tagparam  */
#line 198 "guido.y"
                                                                                                { (yyval.vattr) = (yyvsp[-2].vattr); (yyval.vattr)->push_back(*(yyvsp[0].attr)); delete (yyvsp[0].attr); }
#line 1958 "guidoparse.c++"
    break;

  case 49: /* chord: STARTCHORD chordsymbols ENDCHORD  */
#line 204 "guido.y"
                                                                                { debug("new chord"); (yyval.elt) = context->newChord(); (*(yyval.elt))->push(*(yyvsp[-1].velt)); delete (yyvsp[-1].velt); }
#line 1964 "guidoparse.c++"
    break;

  case 50: /* chordsymbols: tagchordsymbol  */
#line 207 "guido.y"
                                                                                        { (yyval.velt) = new vector<Sguidoelement>; vadd((yyval.velt), (yyvsp[0].velt)); delete (yyvsp[0].velt); }
#line 1970 "guidoparse.c++"
    break;

  case 51: /* chordsymbols: chordsymbols SEP tagchordsymbol  */
#line 208 "guido.y"
                                                                                        { (yyval.velt) = (yyvsp[-2].velt); vadd((yyval.velt), (yyvsp[0].velt)); delete (yyvsp[0].velt); }
#line 1976 "guidoparse.c++"
    break;

  case 52: /* tagchordsymbol: chordsymbol  */
#line 211 "guido.y"
                                                                                                { (yyval.velt) = (yyvsp[0].velt);}
#line 1982 "guidoparse.c++"
    break;

  case 53: /* tagchordsymbol: taglist chordsymbol  */
#line 212 "guido.y"
                                                                                                { (yyval.velt) = (yyvsp[-1].velt); vadd((yyval.velt), (yyvsp[0].velt)); delete (yyvsp[0].velt); }
#line 1988 "guidoparse.c++"
    break;

  case 54: /* tagchordsymbol: chordsymbol taglist  */
#line 213 "guido.y"
                                                                                                { (yyval.velt) = (yyvsp[-1].velt); vadd((yyval.velt), (yyvsp[0].velt)); delete (yyvsp[0].velt); }
#line 1994 "guidoparse.c++"
    break;

  case 55: /* tagchordsymbol: taglist chordsymbol taglist  */
#line 214 "guido.y"
                                                                                        { (yyval.velt) = (yyvsp[-2].velt); vadd((yyval.velt), (yyvsp[-1].velt)); delete (yyvsp[-1].velt); vadd((yyval.velt), (yyvsp[0].velt)); delete (yyvsp[0].velt); }
#line 2000 "guidoparse.c++"
    break;

  case 56: /* chordsymbol: music  */
#line 217 "guido.y"
                                                                                                        { (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2006 "guidoparse.c++"
    break;

  case 57: /* chordsymbol: rangechordtag  */
#line 218 "guido.y"
                                                                                                        { (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2012 "guidoparse.c++"
    break;

  case 58: /* chordsymbol: chordsymbol comment  */
#line 219 "guido.y"
                                                                                                { (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2018 "guidoparse.c++"
    break;

  case 59: /* chordsymbol: comment chordsymbol  */
#line 220 "guido.y"
                                                                                                { debug("comment chord"); (yyval.velt) = (yyvsp[0].velt); (yyval.velt)->push_back(*(yyvsp[-1].elt)); delete (yyvsp[-1].elt); }
#line 2024 "guidoparse.c++"
    break;

  case 60: /* rangechordtag: positiontag STARTRANGE tagchordsymbol ENDRANGE  */
#line 223 "guido.y"
                                                                { debug("range chord tag"); (yyval.elt) = (yyvsp[-3].elt); (*(yyval.elt))->push(*(yyvsp[-1].velt)); delete (yyvsp[-1].velt); }
#line 2030 "guidoparse.c++"
    break;

  case 61: /* taglist: positiontag  */
#line 226 "guido.y"
                                                                                                { debug("new taglist 1"); (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2036 "guidoparse.c++"
    break;

  case 62: /* taglist: taglist positiontag  */
#line 227 "guido.y"
                                                                                                { debug("new taglist 2"); (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2042 "guidoparse.c++"
    break;

  case 63: /* music: note  */
#line 233 "guido.y"
                                                                                                        { (yyval.elt) = (yyvsp[0].elt); }
#line 2048 "guidoparse.c++"
    break;

  case 64: /* music: rest  */
#line 234 "guido.y"
                                                                                                                { (yyval.elt) = (yyvsp[0].elt); }
#line 2054 "guidoparse.c++"
    break;

  case 65: /* rest: RESTT duration dots  */
#line 237 "guido.y"
                                                                                                { debug("new rest 1"); (yyval.elt) = context->newRest((yyvsp[-1].r), (yyvsp[0].num)); delete (yyvsp[-1].r); }
#line 2060 "guidoparse.c++"
    break;

  case 66: /* rest: RESTT STARTPARAM NUMBER ENDPARAM duration dots  */
#line 238 "guido.y"
                                                                                { debug("new rest 2"); (yyval.elt) = context->newRest((yyvsp[-1].r), (yyvsp[0].num)); delete (yyvsp[-1].r); }
#line 2066 "guidoparse.c++"
    break;

  case 67: /* note: noteid octave duration dots  */
#line 241 "guido.y"
                                                                        { debug("new note v1"); (yyval.elt) = context->newNote(*(yyvsp[-3].str), 0, (yyvsp[-2].num), (yyvsp[-1].r), (yyvsp[0].num)); delete (yyvsp[-3].str); delete (yyvsp[-1].r); }
#line 2072 "guidoparse.c++"
    break;

  case 68: /* note: noteid accidentals octave duration dots  */
#line 242 "guido.y"
                                                                        { debug("new note v2"); (yyval.elt) = context->newNote(*(yyvsp[-4].str), (yyvsp[-3].num), (yyvsp[-2].num), (yyvsp[-1].r), (yyvsp[0].num)); delete (yyvsp[-4].str); delete (yyvsp[-1].r); }
#line 2078 "guidoparse.c++"
    break;

  case 69: /* noteid: notename  */
#line 245 "guido.y"
                                                                                                { vdebug("notename", *(yyvsp[0].str)); (yyval.str) = (yyvsp[0].str); }
#line 2084 "guidoparse.c++"
    break;

  case 70: /* noteid: notename STARTPARAM NUMBER ENDPARAM  */
#line 246 "guido.y"
                                                                        { (yyval.str) = (yyvsp[-3].str); }
#line 2090 "guidoparse.c++"
    break;

  case 71: /* notename: DIATONIC  */
#line 249 "guido.y"
                                                                                        { debug("new diatonic note"); (yyval.str) = new string(context->fText); }
#line 2096 "guidoparse.c++"
    break;

  case 72: /* notename: CHROMATIC  */
#line 250 "guido.y"
                                                                                                { debug("new chromatic note"); (yyval.str) = new string(context->fText); }
#line 2102 "guidoparse.c++"
    break;

  case 73: /* notename: SOLFEGE  */
#line 251 "guido.y"
                                                                                                { debug("new solfege note"); (yyval.str) = new string(context->fText); }
#line 2108 "guidoparse.c++"
    break;

  case 74: /* notename: EMPTYT  */
#line 252 "guido.y"
                                                                                                { debug("new empty note"); (yyval.str) = new string(context->fText); }
#line 2114 "guidoparse.c++"
    break;

  case 75: /* accidentals: accidental  */
#line 255 "guido.y"
                                                                                { debug("accidental"); (yyval.num) = (yyvsp[0].num); }
#line 2120 "guidoparse.c++"
    break;

  case 76: /* accidentals: accidentals accidental  */
#line 256 "guido.y"
                                                                                { debug("accidentals"); (yyval.num) = (yyvsp[-1].num) + (yyvsp[0].num); }
#line 2126 "guidoparse.c++"
    break;

  case 77: /* accidental: SHARPT  */
#line 259 "guido.y"
                                                                                        { debug("sharp"); (yyval.num) = 1; }
#line 2132 "guidoparse.c++"
    break;

  case 78: /* accidental: FLATT  */
#line 260 "guido.y"
                                                                                                { debug("flat"); (yyval.num) = -1; }
#line 2138 "guidoparse.c++"
    break;

  case 79: /* octave: %empty  */
#line 263 "guido.y"
                                                                                                { debug("no octave"); (yyval.num) = -1000; }
#line 2144 "guidoparse.c++"
    break;

  case 80: /* octave: signednumber  */
#line 264 "guido.y"
                                                                                        { debug("octave"); (yyval.num) = (yyvsp[0].num); }
#line 2150 "guidoparse.c++"
    break;

  case 81: /* duration: %empty  */
#line 267 "guido.y"
                                                                                                { debug("implicit duration"); (yyval.r) = new rational(-1, 1); }
#line 2156 "guidoparse.c++"
    break;

  case 82: /* duration: MULT number DIV number  */
#line 268 "guido.y"
                                                                                { debug("duration ./."); (yyval.r) = new rational((yyvsp[-2].num), (yyvsp[0].num)); }
#line 2162 "guidoparse.c++"
    break;

  case 83: /* duration: MULT number  */
#line 269 "guido.y"
                                                                                        { debug("duration *"); (yyval.r) = new rational((yyvsp[0].num), 1); }
#line 2168 "guidoparse.c++"
    break;

  case 84: /* duration: DIV number  */
#line 270 "guido.y"
                                                                                        { debug("duration /"); (yyval.r) = new rational(1, (yyvsp[0].num)); }
#line 2174 "guidoparse.c++"
    break;

  case 85: /* dots: %empty  */
#line 273 "guido.y"
                                                                                                { debug("dots 0"); (yyval.num) = 0; }
#line 2180 "guidoparse.c++"
    break;

  case 86: /* dots: DOT  */
#line 274 "guido.y"
                                                                                                { debug("dots 1"); (yyval.num) = 1; }
#line 2186 "guidoparse.c++"
    break;

  case 87: /* dots: DDOT  */
#line 275 "guido.y"
                                                                                                { debug("dots 2"); (yyval.num) = 2; }
#line 2192 "guidoparse.c++"
    break;

  case 88: /* comment: COMMENT  */
#line 281 "guido.y"
                                                                                        { vdebug("comment", context->fText);  (yyval.elt) = context->newComment(context->fText); }
#line 2198 "guidoparse.c++"
    break;

  case 89: /* comments: comment  */
#line 284 "guido.y"
                                                                                        { vdebug("comments", context->fText);  (yyval.velt) = new vector<Sguidoelement>; (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2204 "guidoparse.c++"
    break;

  case 90: /* comments: comments comment  */
#line 285 "guido.y"
                                                                                        { vdebug("comments", context->fText);  (yyval.velt) = (yyvsp[-1].velt); (yyval.velt)->push_back(*(yyvsp[0].elt)); delete (yyvsp[0].elt); }
#line 2210 "guidoparse.c++"
    break;

  case 91: /* id: IDT  */
#line 288 "guido.y"
                                                                                                { (yyval.str) = new string(context->fText); }
#line 2216 "guidoparse.c++"
    break;

  case 92: /* number: NUMBER  */
#line 290 "guido.y"
                                                                                        { vdebug("NUMBER", context->fText); (yyval.num) = atol(context->fText.c_str()); }
#line 2222 "guidoparse.c++"
    break;

  case 93: /* pnumber: PNUMBER  */
#line 292 "guido.y"
                                                                                        { vdebug("PNUMBER", context->fText); (yyval.num) = atol(context->fText.c_str()); }
#line 2228 "guidoparse.c++"
    break;

  case 94: /* nnumber: NNUMBER  */
#line 294 "guido.y"
                                                                                        { vdebug("NNUMBER", context->fText); (yyval.num) = atol(context->fText.c_str()); }
#line 2234 "guidoparse.c++"
    break;

  case 95: /* floatn: FLOAT  */
#line 296 "guido.y"
                                                                                        { vdebug("FLOAT", context->fText); (yyval.real) = atof(context->fText.c_str()); }
#line 2240 "guidoparse.c++"
    break;

  case 96: /* signednumber: number  */
#line 298 "guido.y"
                                                                                { (yyval.num) = (yyvsp[0].num); }
#line 2246 "guidoparse.c++"
    break;

  case 97: /* signednumber: pnumber  */
#line 299 "guido.y"
                                                                                                { (yyval.num) = (yyvsp[0].num); }
#line 2252 "guidoparse.c++"
    break;

  case 98: /* signednumber: nnumber  */
#line 300 "guido.y"
                                                                                                { (yyval.num) = (yyvsp[0].num); }
#line 2258 "guidoparse.c++"
    break;


#line 2262 "guidoparse.c++"

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
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
        yyerror (&yylloc, context, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
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
                      yytoken, &yylval, &yylloc, context);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, context);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, context, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, context);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, context);
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

#line 302 "guido.y"


} // namespace

#ifdef TEST
int	gParseErrorLine = 0;
#else
extern int	gParseErrorLine;
#endif

extern YYLTYPE* yylloc;

static int _error(int line, int column, guido::guidoparser* p, const char* msg) {
	p->error (msg, line, column);
	return 0;
}

static void guidotagerror (guido::guidoparser* p, const std::string* tag, int line, int col) {
	std::string msg ("unknown tag ");
	msg += *tag;
	_error (line, col, p, msg.c_str());
}

static int guidoarerror(YYLTYPE* loc, guido::guidoparser* p, const char*s) {
	return _error (loc->last_line, loc->first_column, p, s);
}

int guido::guidoparser::_yyparse()		{ return yyparse (this); }
