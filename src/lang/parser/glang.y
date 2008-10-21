%{

#include <iostream>
#include <string>
#include "glangreader.h"

#include "glangparse.hpp"
#include "glanglex.cpp"

int glangerror(const char*s);

//#define parseDebug
#ifdef parseDebug
#define debug(msg)		std::cout << msg << " -" << glangtext << "-" << std::endl;
#else
#define debug(msg)
#endif

#define clean(a,b)	delete a; delete b

extern guidolang::glangreader* gGLReader;
using namespace guidolang;

%}

//%pure_parser		/* reentrancy support (but generates incorrect code) */

%start program

%union {         
	SGLExpr*  exprPtr;
	std::string * strPtr;
}

%type <exprPtr> 	expr group 
%type <strPtr>		name 


/*------------------------- tokens  and precedence -----------------------*/
%token GMN 
%token GROUPSTART 
%token GROUPEND 
%token ASEP 
%token EQ IDENT 

%left  BOTTOM
%left TOP
%left TAIL
%left HEAD
%left PAR
%left SEQ
%left APPLY
%right ABSTRACT

/*
	there are actually 7 shift/reduce
*/
%expect 7

%%

//__________________________________________________________________________
program		: deflist						{ }

deflist		: name EQ expr					{ debug("ident expr");		gGLReader->newIDExpr($1->c_str(), $3); delete $1; delete $3; }
			| deflist name EQ expr			{ debug("deflist...");		gGLReader->newIDExpr($2->c_str(), $4); delete $2; delete $4; }


expr		: GMN							{ debug("score expr");		$$ = gGLReader->newScoreExpr(glangtext); 
																			 if (!$$) { glangerror("Error while parsing gmn code"); YYERROR; } }
			| expr SEQ expr					{ debug("seq expr");		$$ = gGLReader->newComposedExpr(glangreader::kSeqOp,$1,$3); clean($1, $3); }
			| expr PAR expr					{ debug("par expr");		$$ = gGLReader->newComposedExpr(glangreader::kParOp,$1,$3); clean($1, $3); }
			| expr HEAD expr				{ debug("head expr");		$$ = gGLReader->newComposedExpr(glangreader::kHeadOp,$1,$3); clean($1, $3); }
			| expr TAIL expr				{ debug("tail expr");		$$ = gGLReader->newComposedExpr(glangreader::kTailOp,$1,$3); clean($1, $3); }
			| expr TOP expr					{ debug("top expr");		$$ = gGLReader->newComposedExpr(glangreader::kTopOp,$1,$3); clean($1, $3); }
			| expr BOTTOM expr				{ debug("bottom expr");		$$ = gGLReader->newComposedExpr(glangreader::kBottomOp,$1,$3); clean($1, $3); }
			| ABSTRACT expr ASEP expr		{ debug("abstract expr");	$$ = gGLReader->newAbstractExpr($2,$4); clean($2, $4);}
			| expr APPLY expr				{ debug("apply expr");		$$ = gGLReader->newApplyExpr($1,$3); clean($1, $3);}
			| group							{ debug("group expr");		$$ = $1; }
			;

group		: GROUPSTART expr GROUPEND		{ debug("group expr"); $$ = $2; }

name		: IDENT							{ debug("name"); $$ = new std::string (glangtext); }

%%

int	glangwrap()		{ return(1); }

int glangerror(const char* s) {
	YY_FLUSH_BUFFER;
	return gGLReader->error(s, glanglineno);
	return 0;
}

