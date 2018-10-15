/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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

#ifndef YY_GUIDOAR_GUIDOPARSE_H__INCLUDED
# define YY_GUIDOAR_GUIDOPARSE_H__INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int guidoardebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    PNUMBER = 259,
    NNUMBER = 260,
    FLOAT = 261,
    STARTCHORD = 262,
    ENDCHORD = 263,
    STARTSEQ = 264,
    ENDSEQ = 265,
    STARTPARAM = 266,
    ENDPARAM = 267,
    STARTRANGE = 268,
    ENDRANGE = 269,
    SEP = 270,
    IDSEP = 271,
    BAR = 272,
    TAGNAME = 273,
    ID = 274,
    DIATONIC = 275,
    CHROMATIC = 276,
    SOLFEGE = 277,
    EMPTY = 278,
    REST = 279,
    DOT = 280,
    DDOT = 281,
    SHARP = 282,
    FLAT = 283,
    MLS = 284,
    SEC = 285,
    UNIT = 286,
    MULT = 287,
    DIV = 288,
    EQUAL = 289,
    STRING = 290,
    EXTRA = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 48 "guido.y" /* yacc.c:1919  */
         
	long int		num;
	float			real;
	const char*		token;
	std::string*	str;
	char			c;
	guido::Sguidoelement *		elt;
	guido::Sguidoattribute*		attr;
	std::vector<guido::Sguidoelement>*	 velt;
	std::vector<guido::Sguidoattribute>* vattr;
	rational *		r;

#line 104 "guidoparse.h++" /* yacc.c:1919  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE guidoarlval;

int guidoarparse (void);

#endif /* !YY_GUIDOAR_GUIDOPARSE_H__INCLUDED  */
