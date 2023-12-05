%{

#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

#include "guidoelement.h"
#include "gmnreader.h"
#include "guidorational.h"

#include "guidoparse.h++"
#include "guidolex.c++"


#ifdef WIN32
# pragma warning (disable : 4267 4005)
#endif


#define YYERROR_VERBOSE
int guidoerror (YYLTYPE* locp, GuidoParser* context, const char*s);
int varerror (int line, int column, GuidoParser* p, const char* varname);
int yylex(YYSTYPE* lvalp, YYLTYPE* llocp, void* scanner);

#define scanner context->fScanner

using namespace std;

namespace guido
{

%}

%define api.pure
%locations
%defines
%define parse.error verbose
%parse-param { GuidoParser* context }
%lex-param { void* scanner  }

%start gmn

%union {         
	long int		num;
	float			real;
	const char*		token;
	std::string*	str;
	char			c;
	guido::Sguidoelement *		elt;
	guido::Sguidoattribute*		attr;
	std::vector<guido::Sguidoelement>*	 velt;
	std::vector<guido::Sguidoattribute>* vattr;
	guido::rational *		r;
}

/*------------------------------ numbers ------------------------------*/
%token NUMBER
%token PNUMBER
%token NNUMBER
%token FLOAT

/*------------------------------ markers ------------------------------*/
%token STARTCHORD
%token ENDCHORD
%token STARTSEQ
%token ENDSEQ
%token STARTPARAM
%token ENDPARAM
%token STARTRANGE
%token ENDRANGE
%token SEP
%token IDSEP

/*------------------------------   tags  ------------------------------*/
%token BAR
%token TAGNAME
%token IDT

/*------------------------------   notes ------------------------------*/
%token DIATONIC
%token CHROMATIC
%token SOLFEGE
%token EMPTYT
%token RESTT
%token DOT
%token DDOT
%token TDOT
%token SHARPT
%token FLATT
%token TAB

/*------------------------------   misc  ------------------------------*/
%token MLS
%token SEC
%token UNIT
%token MULT
%token DIV
%token EQUAL
%token STRING
%token EXTRA
%token ENDVAR
%token VARNAME
%token FRETTE


/*------------------------------   types  ------------------------------*/
%type <num> 	NUMBER PNUMBER NNUMBER
%type <real> 	FLOAT floatn
%type <token>	TAGNAME IDT MLS SEC STRING UNIT DIATONIC CHROMATIC SOLFEGE RESTT 
%type <token>	EMPTYT DOT DDOT EXTRA
%type <c>		STARTCHORD ENDCHORD STARTSEQ ENDSEQ STARTPARAM ENDPARAM STARTRANGE ENDRANGE SEP IDSEP BAR 
%type <c>		SHARPT FLATT MULT DIV EQUAL

%type <str>		notename noteid tagname id varname
%type <num>		dots accidentals accidental octave number pnumber nnumber signednumber
%type <r>		duration
%type <elt>		score voice note rest music chord  tag tagid positiontag rangetag rangechordtag 
%type <attr>	tagarg tagparam
%type <velt>	symbols voicelist chordsymbol chordsymbols taglist tagchordsymbol
%type <vattr>	tagparams

%%

//_______________________________________________
gmn			: score
			| variables score
			;

score		: STARTCHORD ENDCHORD							{ debug("new score"); $$ = gReader->newScore(); }
			| STARTCHORD voicelist ENDCHORD					{ debug("score voicelist"); $$ = gReader->newScore(); addElt(*$$, $2); }
			| voice											{ debug("score voice"); $$ = gReader->newScore(); addElt(*$$, $1); }
			;

voicelist	: voice											{ debug("new voicelist"); $$ = new vector<Sguidoelement>; $$->push_back (*$1); delete $1; }
			| voicelist SEP voice							{ debug("add voicelist"); $$ = $1; $$->push_back (*$3); delete $3; }
			;

voice		: STARTSEQ symbols ENDSEQ						{ debug("new voice"); $$ = gReader->newVoice(); addElt(*$$, $2); }
			;

symbols		:												{ debug("new symbols"); $$ = new vector<Sguidoelement>; }
			| symbols music									{ debug("add music"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols tag									{ debug("add tag"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols chord									{ debug("add chord"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols varname								{ debug("varname"); $$ = $1; $$->push_back(*$2); delete $2; }
			;

//_______________________________________________
// variables - introduced on sept. 15 2020 by DF
variables 	: vardecl
			| variables vardecl
			;

vardecl 	: varname EQUAL STRING ENDVAR					{ context->variableDecl ($1->c_str(), context->fText.c_str(), GuidoParser::kString); delete $1; }
			| varname EQUAL signednumber ENDVAR				{ context->variableDecl ($1->c_str(), context->fText.c_str(), GuidoParser::kInt); delete $1; }
			| varname EQUAL floatn ENDVAR					{ context->variableDecl ($1->c_str(), context->fText.c_str(), GuidoParser::kFloat); delete $1; }
			;

varname		: VARNAME										{ $$ = new string(context->fText); }
			;

//_______________________________________________
// tags description
tag			: positiontag									{ debug("position tag "); $$ = $1; }
			| rangetag										{ debug("range tag "); $$ = $1; }
			;

positiontag	: tagid											{ debug("new position tag "); $$ = $1; }
			| tagid STARTPARAM tagparams ENDPARAM			{ debug("new tag + params"); $$ = $1; (*$1)->add (*$3); delete $3; }
			;

rangetag	: positiontag  STARTRANGE symbols ENDRANGE		{ debug("new range tag "); $$ = $1; (*$1)->push (*$3); delete $3; }
			;

tagname		: TAGNAME										{ debug("tag name "); $$ = new string(guidoartext); }
			;

tagid		: tagname										{ vdebug("new tag", *$1); $$ = gReader->newTag(*$1, 0); delete $1; if (!$$) { guidoarerror("unknown tag"); YYERROR;} }
			| tagname IDSEP NUMBER							{ debug("new tag::id"); $$ = gReader->newTag(*$1, $2); delete $1; if (!$$) { guidoarerror("unknown tag"); YYERROR;} }
			| BAR											{ debug("new bar"); $$ = gReader->newTag("bar", 0); }
			;

tagarg		: signednumber									{ debug("new signednumber arg"); $$ = gReader->newAttribute($1); }
			| floatn										{ debug("new FLOAT arg"); $$ = gReader->newAttribute($1); }
			| signednumber UNIT								{ debug("new signednumber UNIT arg"); $$ = gReader->newAttribute($1); (*$$)->setUnit(guidoartext); }
			| floatn UNIT									{ debug("new FLOAT UNIT arg"); $$ = gReader->newAttribute($1); (*$$)->setUnit(guidoartext); }
			| STRING										{ debug("new STRING arg"); $$ = gReader->newAttribute(guidoartext, true); }
			| id											{ debug("new ID arg"); $$ = gReader->newAttribute(*$1, false); delete $1; }
			;

tagparam	: tagarg										{ $$ = $1; }
			| id EQUAL tagarg								{ $$ = $3; (*$3)->setName(*$1); delete $1; }
			;

tagparams	: tagparam										{ $$ = new vector<Sguidoattribute>; $$->push_back(*$1); delete $1; }
			| tagparams SEP tagparam						{ $$ = $1; $$->push_back(*$3); delete $3; }
			;

//_______________________________________________
// chord description

chord		: STARTCHORD chordsymbols ENDCHORD				{ debug("new chord"); $$ = gReader->newChord(); (*$$)->push(*$2); delete $2; }
			;

chordsymbols: tagchordsymbol								{ $$ = new vector<Sguidoelement>; vadd($$, $1); delete $1; }
			| chordsymbols SEP tagchordsymbol				{ $$ = $1; vadd($$, $3); delete $3; }
			;

tagchordsymbol: chordsymbol									{ $$ = $1;}
			| taglist chordsymbol							{ $$ = $1; vadd($$, $2); delete $2; }
			| chordsymbol taglist							{ $$ = $1; vadd($$, $2); delete $2; }
			| taglist chordsymbol taglist					{ $$ = $1; vadd($$, $2); delete $2; vadd($$, $3); delete $3; }
			;

chordsymbol	: music											{ $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1; }
			| rangechordtag									{ $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1; }
			;

rangechordtag : positiontag  STARTRANGE tagchordsymbol ENDRANGE	{ debug("range chord tag"); $$ = $1; (*$$)->push(*$3); delete $3; }
			;

taglist		: positiontag									{ debug("new taglist 1"); $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1; }
			| taglist positiontag							{ debug("new taglist 2"); $$ = $1; $$->push_back(*$2); delete $2; }
			;

//_______________________________________________
// notes description

music		: note											{ $$ = $1; }
			| rest											{ $$ = $1; }
			;

rest		: RESTT duration	dots							{ debug("new rest 1"); $$ = gReader->newRest($2, $3); delete $2; }
			| RESTT STARTPARAM NUMBER ENDPARAM duration dots	{ debug("new rest 2"); $$ = gReader->newRest($5, $6); delete $5; }
			;

note		: noteid octave duration dots				{ debug("new note v1"); $$ = gReader->newNote(*$1, 0, $2, $3, $4); delete $1; delete $3; }
			| noteid accidentals octave duration dots	{ debug("new note v2"); $$ = gReader->newNote(*$1, $2, $3, $4, $5); delete $1; delete $4; }
			;

noteid		: notename									{ vdebug("notename", *$1); $$ = $1; }
			| notename STARTPARAM NUMBER ENDPARAM		{ $$ = $1; }
			;
			
notename	: DIATONIC								{ debug("new diatonic note"); $$ = new string(guidoartext); }
			| CHROMATIC								{ debug("new chromatic note"); $$ = new string(guidoartext); }
			| SOLFEGE								{ debug("new solfege note"); $$ = new string(guidoartext); }
			| EMPTYT								{ debug("new empty note"); $$ = new string(guidoartext); }
			;		

accidentals	: accidental							{ debug("accidental"); $$ = $1; }
			| accidentals accidental				{ debug("accidentals"); $$ = $1 + $2; }
			;

accidental	: SHARPT								{ debug("sharp"); $$ = 1; }
			| FLATT									{ debug("flat"); $$ = -1; }
			;

octave		:										{ debug("no octave"); $$ = -1000; }					// implicit duration
			| signednumber							{ debug("octave"); $$ = $1; }
			;

duration	:										{ debug("implicit duration"); $$ = new rational(-1, 1); }	// implicit duration
			| MULT number DIV number				{ debug("duration ./."); $$ = new rational($2, $4); }
			| MULT number							{ debug("duration *"); $$ = new rational($2, 1); }
			| DIV number							{ debug("duration /"); $$ = new rational(1, $2); }
			;

dots		:										{ debug("dots 0"); $$ = 0; }
			| DOT									{ debug("dots 1"); $$ = 1; }
			| DDOT									{ debug("dots 2"); $$ = 2; }
			;

//_______________________________________________
// misc

id			: IDT									{ $$ = new string(guidoartext); }
			;
number		: NUMBER								{ vdebug("NUMBER", guidoartext); $$ = atol(guidoartext); }
			;
pnumber		: PNUMBER								{ vdebug("NUMBER", guidoartext); $$ = atol(guidoartext); }
			;
nnumber		: NNUMBER								{ vdebug("NUMBER", guidoartext); $$ = atol(guidoartext); }
			;
floatn		: FLOAT									{ $$ = atof(guidoartext); }
			;
signednumber: number								{ $$ = $1; }
			| pnumber								{ $$ = $1; } 
			| nnumber								{ $$ = $1; }
			;
%%

} // namespace

#ifdef TEST
int	gParseErrorLine = 0;
#else
extern int	gParseErrorLine;
#endif

static int _error(int line, int column, GuidoParser* p, const char* msg) {
	p->parseError (line, column, msg);
	return 0;
}

int varerror(int line, int column, GuidoParser* p, const char* varname) {
	string msg = "unknown variable ";
	msg += varname;
	return _error (line, column, p, msg.c_str());
}

int guidoerror(YYLTYPE* loc, GuidoParser* p, const char*s) {
	return _error (loc->last_line, loc->first_column, p, s);
}

int GuidoParser::_yyparse()		{ return yyparse (this); }
