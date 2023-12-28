/*
  GUIDO Library
  Copyright (C) 2006  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <locale.h>
#include <fstream>
#include <sstream>

#include "guidoparser.h"
#include "guidoelement.h"
#include "guidocomment.h"
#include "guidovariable.h"
#include "ARFactory.h"
#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "ARTag.h"

using namespace std;

namespace guido 
{

#if 0
#define debug(str,val)	cout << str << " - " << val << endl
#else
#define debug(str,val)
#endif

//--------------------------------------------------------------------------
guidoparser::guidoparser()
{
	setlocale(LC_NUMERIC, "C");
    initScanner();
}

//--------------------------------------------------------------------------
guidoparser::~guidoparser() 
{
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
}

//--------------------------------------------------------------------------
// return the next char in stream
bool guidoparser::get(char& c)
{
	fStream->get(c);
	return !fStream->eof();
}
//--------------------------------------------------------------------------
void guidoparser::setStream(std::istream *stream)
{
    if (stream)
        fStream = stream;
}

//______________________________________________________________________________
Sguidoelement* guidoparser::newComment(const string& comment)
{
	Sguidoelement* cptr = new Sguidoelement;
	Sguidocomment c = guidocomment::create();
	c->setName(comment);
	*cptr = c;
	return cptr;
}

//______________________________________________________________________________
void guidoparser::setHeader(std::vector<Sguidoelement>* header)
{
	if (fMusic) fMusic->setHeader(*header);
	else cerr << "guidoparser::setHeader called without fMusic" << endl;
}

//______________________________________________________________________________
void guidoparser::addFooter(Sguidoelement elt)
{
	if (fMusic) fMusic->addFooter(elt);
	else cerr << "guidoparser::setHeader called without fMusic" << endl;
}

//______________________________________________________________________________
void guidoparser::beforeVoice(Sguidoelement* voice, Sguidoelement elt)
{
	SARVoice v = dynamic_cast<ARVoice*>((guidoelement*)(*voice));
	if (v) v->addBefore (elt);
}

//______________________________________________________________________________
void guidoparser::afterVoice(Sguidoelement* voice, Sguidoelement elt)
{
	SARVoice v = dynamic_cast<ARVoice*>((guidoelement*)(*voice));
	if (v) v->addAfter (elt);
}

//______________________________________________________________________________
Sguidoelement* guidoparser::newScore()
{
//	cout << "create new score" << endl;
	Sguidoelement* score = new Sguidoelement;
	fMusic = ARFactory::instance().createMusic();
	*score = fMusic;
	return score;
}

Sguidoelement* guidoparser::newVoice()
{
//	cout << "create new voice" << endl;
	Sguidoelement* voice = new Sguidoelement;
	*voice = ARFactory::instance().createVoice();
	return voice;
}

Sguidoelement* guidoparser::newChord()
{
//	cout << "create new chord" << endl;
	Sguidoelement* chord = new Sguidoelement;
	*chord = ARFactory::instance().createChord();
	return chord;
}

Sguidoelement* guidoparser::newRest(const rational * r, long dots)
{
//	cout << "create new rest " << string(*r) << " dots: " << dots << endl;
	Sguidoelement* notep = new Sguidoelement;
	SARNote note = ARFactory::instance().createNote("_");
	if (r->getNumerator() >= 0)		(*note) = *r;
	if (dots > 0)					note->SetDots (int(dots));
	*notep = note;
	return notep;
}

Sguidoelement* guidoparser::newNote(const std::string& name, long accidentals, long octave, const rational * r, long dots)
{
//	cout << "create new note " << name << " acc: " << accidentals << " oct: " <<  octave << " - " << string(*r) << " dots: " << dots << endl;
	Sguidoelement* notep = new Sguidoelement;
	SARNote note = ARFactory::instance().createNote(name);
	if (accidentals)				note->SetAccidental (int(accidentals));
	if (octave != -1000)			note->SetOctave (int(octave));
	if (r->getNumerator() >= 0)		(*note) = *r;
	if (dots > 0)					note->SetDots (int(dots));
	*notep = note;
	return notep;
}

Sguidoelement* guidoparser::newTag(const std::string& name, long id)
{
//	cout << "create new tag " << name << " id: " << id << endl;
	Sguidoelement tag = ARFactory::instance().createTag(name.substr(1), id);
	if (!tag) return 0;
	Sguidoelement* tagp = new Sguidoelement;
	*tagp = tag;
	return tagp;
}

Sguidoelement* guidoparser::newVariable(const std::string& name)
{
	Sguidoelement var = ARFactory::instance().createVariable(name);
	if (!var) return 0;
	Sguidoelement* varp = new Sguidoelement;
	*varp = var;
	return varp;
}

Sguidoattribute* guidoparser::newAttribute(long value)
{
//	cout << "create new attribute with value " << value << endl;
	Sguidoattribute* attr = new Sguidoattribute;
	*attr = guidoattribute::create();
	(*attr)->setValue(value);
	return attr;
}

Sguidoattribute* guidoparser::newAttribute(float value)
{
//	cout << "create new attribute with value " << value << endl;
	Sguidoattribute* attr = new Sguidoattribute;
	*attr = guidoattribute::create();
	(*attr)->setValue(value);
	return attr;
}

Sguidoattribute* guidoparser::newAttribute(const std::string& value, bool quote)
{
//	cout << "create new attribute with value " << value << " - quote: " << quote << endl;
	Sguidoattribute* attr = new Sguidoattribute;
	*attr = guidoattribute::create();
	(*attr)->setValue(value, quote);
	return attr;
}

int guidoparser::error(const char * msg, int line, int col)
{
	fError.line = line;
	fError.col = col;
	fError.msg = msg;
	cerr << "line " << line << " col " << col << ": " << msg << endl;
	return 0;
}

//______________________________________________________________________________
void guidoparser::parse  (std::istream * stream)
{
	fStream = stream;
    destroyScanner();
    initScanner();
	setlocale(LC_NUMERIC, "C");
	_yyparse ();
	setlocale(LC_NUMERIC, 0);
	fStream = nullptr;
}

//______________________________________________________________________________
//SARMusic guidoparser::parseFile(FILE* fd)
//{
//	setlocale(LC_NUMERIC, "C");
//	readfile (fd, this);
//	setlocale(LC_NUMERIC, 0);
//	return fMusic;
//}

//______________________________________________________________________________
SARMusic guidoparser::parseFile(const char* file)
{
	ifstream * fileStream = new ifstream (file, std::ifstream::in);
	parse (fileStream);
	fileStream->close();
	delete fileStream;
	return fMusic;
}

//______________________________________________________________________________
SARMusic guidoparser::parseString(const char* str)
{
	stringstream* ss = new stringstream(str);
	parse (ss);
	return fMusic;
}

//--------------------------------------------------------------------------
void guidoparser::variableDecl (Sguidoelement var, const char* value, vartype type)
{
	Sguidovariable v = dynamic_cast<guidovariable*>((guidoelement*)var);
	if (v) {
		v->setValue (value, (type == kString));
	}
	else cerr << "Unexpected variable declaration " << var << endl;
}

} // namespace
