%{

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

%}

%define api.pure
%locations
%defines
%define parse.error verbose
%parse-param { guido::guidoparser* context }
%lex-param { void* scanner  }
%expect 2   /* 
				2 shift/reduce warnings expected: 
				comments after score and after voice 
				comments inside a chord
			*/

%start gmn

/*------------------------------ numbers ------------------------------*/
%token NUMBER PNUMBER NNUMBER FLOAT

/*------------------------------ markers ------------------------------*/
%token STARTCHORD ENDCHORD STARTSEQ ENDSEQ STARTPARAM ENDPARAM
%token STARTRANGE ENDRANGE SEP IDSEP

/*------------------------------   tags  ------------------------------*/
%token BAR TAGNAME IDT

/*------------------------------   notes ------------------------------*/
%token DIATONIC CHROMATIC SOLFEGE EMPTYT RESTT
%token DOT DDOT TDOT SHARPT FLATT TAB

/*------------------------------   misc  ------------------------------*/
%token MLS SEC UNIT MULT DIV EQUAL STRING EXTRA ENDVAR VARNAME FRETTE COMMENT

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

/*------------------------------   types  ------------------------------*/
%type <num> 	NUMBER PNUMBER NNUMBER
%type <real> 	FLOAT floatn
%type <token>	TAGNAME IDT MLS SEC STRING UNIT DIATONIC CHROMATIC SOLFEGE RESTT 
%type <token>	EMPTYT DOT DDOT EXTRA
%type <c>		STARTCHORD ENDCHORD STARTSEQ ENDSEQ STARTPARAM ENDPARAM STARTRANGE ENDRANGE SEP IDSEP BAR 
%type <c>		SHARPT FLATT MULT DIV EQUAL

%type <str>		notename noteid tagname id
%type <num>		dots accidentals accidental octave number pnumber nnumber signednumber
%type <r>		duration
%type <elt>		gmn score voice note rest music chord tag tagid positiontag rangetag rangechordtag varname vardecl comment
%type <attr>	tagarg tagparam
%type <velt>	symbols voicelist chordsymbol chordsymbols taglist tagchordsymbol header comments sep
%type <vattr>	tagparams

%% 

//_______________________________________________
gmn			: score
			| header score							        { debug("header score"); context->setHeader($1); delete $2; } 
			;

header      : comment							   	 		{ debug("header comment"); $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1;}
			| vardecl							  			{ debug("header variable"); $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1;}
			| header vardecl							  	{ debug("header + variable"); $$=$1; $1->push_back(*$2); delete $2; }
			| header comment							  	{ debug("header + comment"); $$=$1; $1->push_back(*$2); delete $2; }
			;

score		: STARTCHORD ENDCHORD							{ debug("new score"); $$ = context->newScore(); }
			| STARTCHORD voicelist ENDCHORD					{ debug("score voicelist"); $$ = context->newScore(); (*$$)->push( *$2); delete $2; }
			| voice											{ debug("score voice"); $$ = context->newScore(); (*$$)->push( *$1); delete $1; }
			| score comment									{ debug("score comment"); $$ = $1; context->addFooter(*$2); delete $2; } 
			;

voicelist	: voice											{ debug("new voicelist"); $$ = new vector<Sguidoelement>; $$->push_back (*$1); delete $1; }
			| comments voice							    { debug("add voicelist"); $$ = new vector<Sguidoelement>; if ($1) { for (auto c: *$1) context->beforeVoice($2, c); }; $$->push_back (*$2); delete $2; }
			| voicelist sep voice							{ debug("add voicelist"); $$ = $1; $$->push_back (*$3); delete $3; }
			;

sep			: SEP											{ debug("SEP"); $$=0; }
			| SEP comments 									{ debug("SEP comments"); $$=$2; }
			; 

voice		: STARTSEQ symbols ENDSEQ						{ debug("new voice"); $$ = context->newVoice(); (*$$)->push( *$2); delete $2; }
			| voice comment									{ debug("voice comment"); $$ = $1; context->afterVoice($$, *$2); delete $2; } 
			;

symbols		:												{ debug("new symbols"); $$ = new vector<Sguidoelement>; }
			| symbols music									{ debug("add music"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols tag									{ debug("add tag"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols chord									{ debug("add chord"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols varname								{ debug("add varname"); $$ = $1; $$->push_back(*$2); delete $2; }
			| symbols comment								{ debug("add comment"); $$ = $1; $$->push_back(*$2); delete $2; }
			;

vardecl 	: varname EQUAL STRING ENDVAR					{ vdebug("vardecl string", *$1); $$ = $1; context->variableDecl (*$1, context->fText.c_str(), guidoparser::kString);  }
			| varname EQUAL signednumber ENDVAR				{ vdebug("vardecl int", *$1); $$ = $1; context->variableDecl (*$1, context->fText.c_str(), guidoparser::kInt);  }
			| varname EQUAL floatn ENDVAR					{ vdebug("vardecl float", *$1); $$ = $1; context->variableDecl (*$1, context->fText.c_str(), guidoparser::kFloat); }
			;

varname		: VARNAME										{ vdebug("varname", context->fText); $$ =  context->newVariable(context->fText); }
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

tagname		: TAGNAME										{ debug("tag name "); $$ = new string(context->fText); }
			;

tagid		: tagname										{ vdebug("new tag", *$1); $$ = context->newTag(*$1, 0); if (!$$) { guidotagerror(context, $1, @1.first_line, @1.first_column); YYERROR;} delete $1; }
			| tagname IDSEP NUMBER							{ debug("new tag::id");  $$ = context->newTag(*$1, $2); if (!$$) { guidotagerror(context, $1, @1.first_line, @1.first_column); YYERROR;} delete $1; }
			| BAR											{ debug("new bar"); $$ = context->newTag("\\bar", 0); }
			;

tagarg		: signednumber									{ debug("new signednumber arg"); $$ = context->newAttribute($1); }
			| floatn										{ debug("new FLOAT arg"); $$ = context->newAttribute($1); }
			| signednumber UNIT								{ debug("new signednumber UNIT arg"); $$ = context->newAttribute($1); (*$$)->setUnit(context->fText); }
			| floatn UNIT									{ debug("new FLOAT UNIT arg"); $$ = context->newAttribute($1); (*$$)->setUnit(context->fText); }
			| STRING										{ debug("new STRING arg"); $$ = context->newAttribute(context->fText, true); }
			| id											{ debug("new ID arg"); $$ = context->newAttribute(*$1, false); delete $1; }
			| varname										{ debug("new var arg"); $$ = context->newAttribute((*$1)->getName(), false); delete $1; }; 
			;

tagparam	: tagarg										{ debug("tagparam"); $$ = $1; }
			| id EQUAL tagarg								{ debug("tagparam"); $$ = $3; (*$3)->setName(*$1); delete $1; }
			;

tagparams	: tagparam										{ $$ = new vector<Sguidoattribute>; $$->push_back(*$1); delete $1; }
			| tagparams SEP tagparam						{ $$ = $1; $$->push_back(*$3); delete $3; }
			;

//_______________________________________________
// chord description

chord		: STARTCHORD chordsymbols ENDCHORD				{ debug("new chord"); $$ = context->newChord(); (*$$)->push(*$2); delete $2; }
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
			| chordsymbol comment							{ $$ = $1; $$->push_back(*$2); delete $2; }
			| comment chordsymbol							{ debug("comment chord"); $$ = $2; $$->push_back(*$1); delete $1; }
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

rest		: RESTT duration	dots							{ debug("new rest 1"); $$ = context->newRest($2, $3); delete $2; }
			| RESTT STARTPARAM NUMBER ENDPARAM duration dots	{ debug("new rest 2"); $$ = context->newRest($5, $6); delete $5; }
			;

note		: noteid octave duration dots				{ debug("new note v1"); $$ = context->newNote(*$1, 0, $2, $3, $4); delete $1; delete $3; }
			| noteid accidentals octave duration dots	{ debug("new note v2"); $$ = context->newNote(*$1, $2, $3, $4, $5); delete $1; delete $4; }
			;

noteid		: notename									{ vdebug("notename", *$1); $$ = $1; }
			| notename STARTPARAM NUMBER ENDPARAM		{ $$ = $1; }
			;
			
notename	: DIATONIC								{ debug("new diatonic note"); $$ = new string(context->fText); }
			| CHROMATIC								{ debug("new chromatic note"); $$ = new string(context->fText); }
			| SOLFEGE								{ debug("new solfege note"); $$ = new string(context->fText); }
			| EMPTYT								{ debug("new empty note"); $$ = new string(context->fText); }
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

comment		: COMMENT								{ vdebug("comment", context->fText);  $$ = context->newComment(context->fText); }
			;

comments	: comment								{ vdebug("comments", context->fText);  $$ = new vector<Sguidoelement>; $$->push_back(*$1); delete $1; }
			| comments comment						{ vdebug("comments", context->fText);  $$ = $1; $$->push_back(*$2); delete $2; }
			;

id			: IDT									{ $$ = new string(context->fText); }
			;
number		: NUMBER								{ vdebug("NUMBER", context->fText); $$ = atol(context->fText.c_str()); }
			;
pnumber		: PNUMBER								{ vdebug("PNUMBER", context->fText); $$ = atol(context->fText.c_str()); }
			;
nnumber		: NNUMBER								{ vdebug("NNUMBER", context->fText); $$ = atol(context->fText.c_str()); }
			;
floatn		: FLOAT									{ vdebug("FLOAT", context->fText); $$ = atof(context->fText.c_str()); }
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
