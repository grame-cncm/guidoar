/*
  GUIDO Library
  Copyright (C) 2023 D.Fober

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
*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <algorithm>
#include <sstream>
#include <regex>

#include "ARChord.h"
#include "ARFactory.h"
#include "ARNote.h"
#include "ARChord.h"
#include "AROthers.h"
#include "ARTag.h"
#include "guidoelement.h"
#include "guidocomment.h"
#include "guidovariable.h"
#include "tree_browser.h"

#include "gmn2tabvisitor.h"

using namespace std;

namespace guido
{

// variables names and default values
static const char* InstrSize = "$INSTRSize";
static const char* TabSize   = "$TABSize";
static const char* PushDy    = "$PushDy";
static const char* PullDy    = "$PullDy";
static const char* TabStaffDist= "$TabStaffDist";

static const char* HarmMainDy= "$HarmMainDy";
static const char* HarmSubDy = "$HarmSubDy";
static const char* HarmMainSize = "$HarmMainSize";
static const char* HarmSubSize  = "$HarmSubSize";

static const char* defaultInstrSize = "2.0";
static const char* defaultTabSize 	= "1.6";
static const char* defaultPy 		= "3.5";
static const char* defaultTy 		= "1.6";
static const char* defaultTabStaffDist	= "4";

static const char* defaultHarmMainDy	= "-0.5";
static const char* defaultHarmSubDy 	= "-1.0";
static const char* defaultHarmMainSize 	= "2.5";
static const char* defaultHarmSubSize  	= "2.0";

//______________________________________________________________________________
AccordionKeyboard::AccordionKeyboard(KBDType type)
{
	initEnharmonics(fEnharmonics);
	initialize (type);
}

//______________________________________________________________________________
void AccordionKeyboard::initialize (KBDType type)
{
	switch (type) {
		case k3Rows:
			init3Rows(fKeysMap);
			fInitialised = true;
			break;
		case k3RowsH2:
			initHeim2(fKeysMap);
			fInitialised = true;
			break;
		case k2RowsCG:
		case k2RowsDA:
			cerr << "Keyboard type no yet supported" << endl;
			break;
		default:
			cerr << "Unknown keyboard type" << endl;
			break;
	}
}

//______________________________________________________________________________
void AccordionKeyboard::initEnharmonics(TEnharmonics& tbl)
{
	tbl["c&0"] = "b-1";
	tbl["a##-1"] = "b-1";

	tbl["g##0"] = "a0";
	tbl["b&&0"] = "a0";
	tbl["g##1"] = "a1";
	tbl["b&&1"] = "a1";
	tbl["g##2"] = "a2";
	tbl["b&&2"] = "a2";

	tbl["a#0"] = "b&0";
	tbl["a#1"] = "b&1";
	tbl["a#2"] = "b&2";

	tbl["c&1"] = "b0";
	tbl["a##0"] = "b0";
	tbl["c&2"] = "b1";
	tbl["a##1"] = "b1";
	tbl["c&3"] = "b2";
	tbl["a##1"] = "b2";

	tbl["d&1"] = "c#1";
	tbl["d&2"] = "c#2";
	tbl["d&3"] = "c#3";

	tbl["b#0"] = "c1";
	tbl["d&&1"] = "c1";
	tbl["b#1"] = "c2";
	tbl["d&&2"] = "c2";
	tbl["b#2"] = "c3";
	tbl["d&&3"] = "c3";

	tbl["c##0"] = "d0";
	tbl["e&&0"] = "d0";
	tbl["c##1"] = "d1";
	tbl["e&&1"] = "d1";
	tbl["c##2"] = "d2";
	tbl["e&&2"] = "d2";
	tbl["c##3"] = "d3";
	tbl["e&&3"] = "d3";

	tbl["d#1"] = "e&1";
	tbl["d#2"] = "e&2";
	tbl["d#3"] = "e&3";

	tbl["d##0"] = "e0";
	tbl["f&0"] = "e0";
	tbl["d##1"] = "e1";
	tbl["f&1"] = "e1";
	tbl["d##2"] = "e2";
	tbl["f&2"] = "e2";
	tbl["d##3"] = "e3";
	tbl["f&3"] = "e3";

	tbl["g&0"] = "f#0";
	tbl["g&1"] = "f#1";
	tbl["g&2"] = "f#2";

	tbl["e#1"] = "f1";
	tbl["g&&1"] = "f1";
	tbl["e#2"] = "f2";
	tbl["g&&2"] = "f2";

	tbl["a&0"] = "g#0";
	tbl["a&1"] = "g#1";
	tbl["a&2"] = "g#2";
	tbl["a&3"] = "g#3";

	tbl["f##0"] = "g0";
	tbl["a&&0"] = "g0";
	tbl["f##1"] = "g1";
	tbl["a&&1"] = "g1";
	tbl["f##2"] = "g2";
	tbl["a&&2"] = "g2";
	tbl["f##3"] = "g3";
	tbl["a&&3"] = "g3";
}

//______________________________________________________________________________
void AccordionKeyboard::initHeim2 (Keyboard& map)
{
// push mode
	map.push.first["b-1"]= "1";
	map.push.first["d0"] = "2"; 
	map.push.first["g0"] = "3"; 
	map.push.first["b0"] = "4"; 
	map.push.first["d1"] = "5"; 
	map.push.first["g1"] = "6"; 
	map.push.first["b1"] = "7"; 
	map.push.first["d2"] = "8"; 
	map.push.first["g2"] = "9"; 
	map.push.first["b2"] = "10"; 
	map.push.first["d3"] = "11"; 
	map.push.first["g3"] = "12"; 

	map.push.second["e0"] = "1'";
	map.push.second["a0"] = "2'";
	map.push.second["c1"] = "3'";
	map.push.second["e1"] = "4'";
	map.push.second["a1"] = "5'";
	map.push.second["c2"] = "6'";
	map.push.second["e2"] = "7'";
	map.push.second["a2"] = "8'";
	map.push.second["c3"] = "9'";
	map.push.second["e3"] = "10'";
	map.push.second["a3"] = "11'";

	map.push.third["f0"]  = "1''";
	map.push.third["g#0"] = "2''";
	map.push.third["e&1"] = "3''";
	map.push.third["f1"]  = "4''";
	map.push.third["g#1"] = "5''";
	map.push.third["e&2"] = "6''";
	map.push.third["f2"]  = "7''";
	map.push.third["g#2"] = "8''";
	map.push.third["e&3"] = "9''";
	map.push.third["f3"]  = "10''";

// pull mode
  	map.pull.first["e0"]  = "1";
	map.pull.first["f#0"] = "2"; 
	map.pull.first["a0"]  = "3"; 
	map.pull.first["c1"]  = "4"; 
	map.pull.first["e1"]  = "5"; 
	map.pull.first["f#1"] = "6"; 
	map.pull.first["a1"]  = "7"; 
	map.pull.first["c2"]  = "8"; 
	map.pull.first["e2"]  = "9"; 
	map.pull.first["f#2"] = "10"; 
	map.pull.first["a2"]  = "11"; 
	map.pull.first["c3"]  = "12"; 

	map.pull.second["g0"] = "1'";
	map.pull.second["b0"] = "2'";
	map.pull.second["d1"] = "3'";
	map.pull.second["f1"] = "4'";
	map.pull.second["g1"] = "5'";
	map.pull.second["b1"] = "6'";
	map.pull.second["d2"] = "7'";
	map.pull.second["f2"] = "8'";
	map.pull.second["g2"] = "9'";
	map.pull.second["b2"] = "10'";
	map.pull.second["d3"] = "11'";

	map.pull.third["b&0"] = "1''";
	map.pull.third["c#1"] = "2''";
	map.pull.third["e&1"] = "3''";
	map.pull.third["g#1"] = "4''";
	map.pull.third["b&1"] = "5''";
	map.pull.third["c#2"] = "6''";
	map.pull.third["e&2"] = "7''";
	map.pull.third["g#2"] = "8''";
	map.pull.third["b&2"] = "9''";
	map.pull.third["c#3"] = "10''";
}

//______________________________________________________________________________
void AccordionKeyboard::init3Rows (Keyboard& map)
{
// push mode
	map.push.first["b-1"]= "1";
	map.push.first["d0"] = "2"; 
	map.push.first["g0"] = "3"; 
	map.push.first["b0"] = "4"; 
	map.push.first["d1"] = "5"; 
	map.push.first["g1"] = "6"; 
	map.push.first["b1"] = "7"; 
	map.push.first["d2"] = "8"; 
	map.push.first["g2"] = "9"; 
	map.push.first["b2"] = "10"; 
	map.push.first["d3"] = "11"; 
	map.push.first["g3"] = "12"; 

	map.push.second["e0"] = "1'";
	map.push.second["g0"] = "2'";
	map.push.second["c1"] = "3'";
	map.push.second["e1"] = "4'";
	map.push.second["g1"] = "5'";
	map.push.second["c2"] = "6'";
	map.push.second["e2"] = "7'";
	map.push.second["g2"] = "8'";
	map.push.second["c3"] = "9'";
	map.push.second["e3"] = "10'";
	map.push.second["g3"] = "11'";

	map.push.third["g#0"] = "1''";
	map.push.third["a0"]  = "2''";
	map.push.third["e&1"] = "3''";
	map.push.third["g#1"] = "4''";
	map.push.third["a1"]  = "5''";
	map.push.third["e&2"] = "6''";
	map.push.third["g#2"] = "7''";
	map.push.third["a2"]  = "8''";
	map.push.third["e&3"] = "9''";
	map.push.third["g#3"] = "10''";

// pull mode
  	map.pull.first["e0"]  = "1";
	map.pull.first["f#0"] = "2"; 
	map.pull.first["a0"]  = "3"; 
	map.pull.first["c1"]  = "4"; 
	map.pull.first["e1"]  = "5"; 
	map.pull.first["f#1"] = "6"; 
	map.pull.first["a1"]  = "7"; 
	map.pull.first["c2"]  = "8"; 
	map.pull.first["e2"]  = "9"; 
	map.pull.first["f#2"] = "10"; 
	map.pull.first["a2"]  = "11"; 
	map.pull.first["c3"]  = "12"; 

	map.pull.second["g0"] = "1'";
	map.pull.second["b0"] = "2'";
	map.pull.second["d1"] = "3'";
	map.pull.second["f1"] = "4'";
	map.pull.second["a1"] = "5'";
	map.pull.second["b1"] = "6'";
	map.pull.second["d2"] = "7'";
	map.pull.second["f2"] = "8'";
	map.pull.second["a2"] = "9'";
	map.pull.second["b2"] = "10'";
	map.pull.second["d3"] = "11'";

	map.pull.third["b&0"] = "1''";
	map.pull.third["c#1"] = "2''";
	map.pull.third["g1"]  = "3''";
	map.pull.third["g#1"] = "4''";
	map.pull.third["b&1"] = "5''";
	map.pull.third["c#2"] = "6''";
	map.pull.third["g2"]  = "7''";
	map.pull.third["g#2"] = "8''";
	map.pull.third["b&2"] = "9''";
	map.pull.third["c#3"] = "10''";
}

//______________________________________________________________________________
const char * AccordionKeyboard::note2tab (const std::string& note, bool& push, int row, bool force) const
{

	const char * notfound = "x";
	if ((row > 2) || (row < 1)) return notfound;
	
	TEnharmonics::const_iterator e = fEnharmonics.find(note);
	string target = (e != fEnharmonics.end()) ? e->second : note;
//cerr << "AccordionKeyboard::note2tab " << target << (push ? " push" : " pull") << endl;
	
	if (push) {
		const char *kp = scanRows (target, fKeysMap.push, row);
		if (kp) return kp;
		if (force) return notfound;
		push = false;
		kp = note2tab(note, push, row, true);
		if (kp) return kp;
		else push = true;
	}
	else {
		const char *kp = scanRows (target, fKeysMap.pull, row);
		if (kp) return kp;
		if (force) return notfound;
		push = true;
		kp = note2tab(note, push, row, true);
		if (kp) return kp;
		else push = false;
	}
	return notfound;
}

//______________________________________________________________________________
const char * AccordionKeyboard::scanRows(const std::string& note, const TKeysMap& map, int row) const
{
	TRowMap::const_iterator i;
	switch (row) {
//		case 1:
//			k = map[0][nptr]; if (k) return k;
//			k = map[1][nptr]; if (k) return k;
//			k = map[2][nptr]; if (k) return k;
//			break;
		case 1:
			i = map.first.find(note);  if (i != map.first.end())  return i->second;
			i = map.second.find(note); if (i != map.second.end()) return i->second;
			i = map.third.find(note);  if (i != map.third.end())  return i->second;
			break;
		case 2:
			i = map.second.find(note); if (i != map.second.end()) return i->second;
			i = map.first.find(note);  if (i != map.first.end())  return i->second;
			i = map.third.find(note);  if (i != map.third.end())  return i->second;
			break;
	}
	return nullptr;
}

//______________________________________________________________________________
SARMusic gmn2tabvisitor::gmn2tab (const SARMusic ar, int targetvoice)
{
	if (ar->size() < targetvoice) {
		cerr << "Voice " << targetvoice << ": out of range. Score voice count is " << ar->size() << "." << endl;
		return nullptr;
	}
	if (!fKeyBoard.initialised()) {
		cerr << "Keyboard not initialised" << endl;
		return nullptr;
	}
	fTargetVoice = targetvoice;
	fVoiceNum = 0;
	fTabMode.push = false;
	fTabMode.row = 0;
	fInChord = false;
	fInTie = 0;
	fMeasureNum = 1;
	fHarmDur = rational ("1/4");
	fCurrentOctave = ARNote::getDefaultOctave();
	fTabVoice = ARFactory::instance().createVoice();
	initTabVoice(fTabVoice);

	Sguidoelement elt = clone (ar);
	SARMusic score = dynamic_cast<ARMusic*>((guidoelement*)elt);
	if (score)
		initVariables(score);
	return score;
}

//______________________________________________________________________________
Sguidoelement gmn2tabvisitor::newLine () const
{
	Sguidoelement nl = guidocomment::create();
	nl->setName("\n");
	return nl;
}

//______________________________________________________________________________
string	gmn2tabvisitor::noteName ( const SARNote& note) const
{
	stringstream sstr;
	sstr << note->getName();
	int accidentals = note->GetAccidental();
	while (accidentals > 0) { sstr << '#'; accidentals--; }
	while (accidentals < 0) { sstr << '&'; accidentals++; }
	sstr << (note->implicitOctave() ? fCurrentOctave : note->GetOctave());
	return sstr.str();
}

//______________________________________________________________________________
void gmn2tabvisitor::addToTabVoice ( Sguidoelement elt )
{
	if (fVoiceNum == fTargetVoice) fTabVoice->push (elt);
}

//______________________________________________________________________________
Sguidoattribute gmn2tabvisitor::makeAttribute ( const char* name, const char* value, bool quote ) const
{
	Sguidoattribute attr = guidoattribute::create();
	if (name) attr->setName(name);
	attr->setValue (value, quote);
	return attr;
}

//______________________________________________________________________________
Sguidoattribute gmn2tabvisitor::makeAttribute ( const char* name, float value ) const
{
	Sguidoattribute attr = guidoattribute::create();
	if (name) attr->setName(name);
	attr->setValue (value);
	return attr;
}

//______________________________________________________________________________
SARNote	gmn2tabvisitor::makeEmpty ( const rational& dur, int dots) const
{
	SARNote empty = ARFactory().instance().createNote("empty");
	if (dur.getNumerator() != 0) *empty = dur;
	empty->SetDots(dots);
	return empty;
}

//______________________________________________________________________________
Sguidotag gmn2tabvisitor::makeTab ( const std::string& content, bool push ) const
{
	Sguidotag lyric = ARFactory().instance().createTag("lyrics");
	lyric->add( makeAttribute(nullptr, content.c_str(), true) );
	lyric->add( makeAttribute("fsize", TabSize, false) );
	lyric->add( makeAttribute("dy", push ? PushDy : PullDy, false) );
	return lyric;
}

//______________________________________________________________________________
bool gmn2tabvisitor::existingVariables 	( const ARMusic::THeader& header, std::string varname) const
{
	for (auto elt: header) {
		const guidovariable* var = dynamic_cast<const guidovariable*>((const guidoelement*)elt);
		if (var && (var->getName() == varname)) return true;
	}
	return false;
}

//______________________________________________________________________________
Sguidovariable gmn2tabvisitor::createVariable (const char * name, const char * value) const
{
	Sguidovariable var = ARFactory().instance().createVariable(name);
	var->setValue(value, false);
	return var;
}

//______________________________________________________________________________
void gmn2tabvisitor::initVariables (SARMusic score)
{
	Sguidocomment c = guidocomment::create();
	c->setName("\n% start of auto variables");
	score->addHeader (c);

	const ARMusic::THeader& header = score->getHeader();
	if (!existingVariables(header, InstrSize)) 		score->addHeader (createVariable(InstrSize, defaultInstrSize));
	if (!existingVariables(header, TabSize)) 		score->addHeader (createVariable(TabSize, defaultTabSize));
	if (!existingVariables(header, PushDy)) 		score->addHeader (createVariable(PushDy, defaultPy));
	if (!existingVariables(header, PullDy)) 		score->addHeader (createVariable(PullDy, defaultTy));
	if (!existingVariables(header, TabStaffDist)) 	score->addHeader (createVariable(TabStaffDist, defaultTabStaffDist));

	score->addHeader(newLine());

	if (!existingVariables(header, HarmMainDy)) 	score->addHeader (createVariable(HarmMainDy, defaultHarmMainDy));
	if (!existingVariables(header, HarmSubDy)) 		score->addHeader (createVariable(HarmSubDy, defaultHarmSubDy));
	if (!existingVariables(header, HarmMainSize)) 	score->addHeader (createVariable(HarmMainSize, defaultHarmMainSize));
	if (!existingVariables(header, HarmSubSize)) 	score->addHeader (createVariable(HarmSubSize, defaultHarmSubSize));

	c = guidocomment::create();
	c->setName("\n% end of auto variables\n");
	score->addHeader (c);

}

//______________________________________________________________________________
SARVoice gmn2tabvisitor::initHarmVoice () const
{
	SARVoice voice = ARFactory().instance().createVoice();

	Sguidotag staff = ARFactory().instance().createTag("staff");
	staff->add( makeAttribute(nullptr, fTargetVoice+1 ));
	voice->push (staff);
	voice->push(newLine());

	Sguidotag set = ARFactory().instance().createTag("set");
	set->add( makeAttribute("autoEndBar", "off", true) );
	voice->push (set);
	voice->push(newLine());
	
	Sguidotag clef = ARFactory().instance().createTag("clef");
	clef->add( makeAttribute(nullptr, "none", true) );
	voice->push (clef);
	voice->push(newLine());

	return voice;
}

//______________________________________________________________________________
void gmn2tabvisitor::initTabVoice ( Sguidoelement elt )
{
	Sguidotag set = ARFactory().instance().createTag("set");
	set->add( makeAttribute("autoEndBar", "off", true) );
	elt->push (set);
	elt->push(newLine());

	Sguidotag clef = ARFactory().instance().createTag("clef");
	clef->add( makeAttribute(nullptr, "none", true) );
	elt->push (clef);
	elt->push(newLine());

	Sguidotag instr = ARFactory().instance().createTag("instr");
	instr->add( makeAttribute(nullptr, "P\\nT", true) );
	instr->add( makeAttribute("autopos", "on", true) );
	instr->add( makeAttribute("repeat", "on", true) );
	instr->add( makeAttribute("fsize", InstrSize, false) );
	instr->add( makeAttribute("dx", -4.0) );
	instr->add( makeAttribute("dy", 1) );
	elt->push (instr);
	elt->push(newLine());

	Sguidotag format = ARFactory().instance().createTag("staffFormat");
	format->add( makeAttribute("style", "3-lines", true) );
	format->add( makeAttribute("lineThickness", 0.05) );
	format->add( makeAttribute("size", 2) );
	format->add( makeAttribute("distance", TabStaffDist, false) );
	elt->push (format);
	elt->push(newLine());
}

//______________________________________________________________________________
static Sguidocomment makeMeasureNum (int num)
{
	stringstream mnum;
	mnum << "\n% ====== measure " << num << "\n";
	Sguidocomment c = guidocomment::create();
	c->setName(mnum.str());
	return c;
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( Sguidotag& tag ) 		{ clonevisitor::visitStart(tag); }
void gmn2tabvisitor::visitStart ( SARBar& bar )	{
	Sguidotag tag = bar;
	clonevisitor::visitStart( tag );
	addToTabVoice(bar);
	addToTabVoice(makeMeasureNum(++fMeasureNum));
}
void gmn2tabvisitor::visitStart ( SARRepeatBegin& bar )	{
	Sguidotag tag = bar;
	clonevisitor::visitStart( tag );
//	addToTabVoice(makeHidden("repeatBegin"));
	addToTabVoice(makeMeasureNum(++fMeasureNum));
}
void gmn2tabvisitor::visitStart ( SARRepeatEnd& bar ) {
	Sguidotag tag = bar;
	clonevisitor::visitStart( tag );
//	addToTabVoice(makeHidden("repeatEnd"));
	addToTabVoice(makeMeasureNum(++fMeasureNum));
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( SARNote& note )
{
	clonevisitor::visitStart(note);
	if (fVoiceNum != fTargetVoice) return;

//cerr << "gmn2tabvisitor::visitStart SARNote " << noteName(note) << " " << note->GetAccidental() << endl;
	if (!note->implicitOctave()) fCurrentOctave = note->GetOctave();
	if (fInChord) {
	 	if (fInTie < 2) fChordNotes.push_back(TPNote(note, note->midiPitch(fCurrentOctave)));
	}
	else {
		SARNote empty = makeEmpty(note->duration(), note->GetDots());
		if (note->isPitched() && (fInTie < 2)) {
//cerr << "gmn2tabvisitor::visitStart SARNote set tab to " << noteName(note) << " => " << string(*empty) << endl;
			bool push = fTabMode.push;
			string tab = fKeyBoard.note2tab(noteName(note), push, fTabMode.row, false);
			if (!fInChord) {
				Sguidotag lyric = makeTab (tab, push);
				lyric->push (empty);
				fTabVoice->push(newLine());
				fTabVoice->push(lyric);
			}
		}
		else fTabVoice->push(empty);
		if (fInTie) fInTie++;
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::handleTab (const std::string& str)
{
	size_t pos = str.find_first_of("PT");
	if (pos != string::npos) {
		fTabMode.push = (str[pos] == 'P');
		pos = str.find_first_of("GC", pos);
		if (pos != string::npos) {
			fTabMode.row = (str[pos] == 'G') ? 1 : 2;
		}
	}
}

//______________________________________________________________________________
Sguidotag gmn2tabvisitor::makeHidden ( const std::string& name) const
{
	Sguidotag tag = ARFactory().instance().createTag(name);
	tag->add (makeAttribute("hidden", "true", true));
	return tag;
}

//______________________________________________________________________________
void gmn2tabvisitor::makeHarmony( const string& h, const rational& dur)
{
	if (!fHarmVoice) fHarmVoice = initHarmVoice();
//	cerr << "gmn2tabvisitor::makeHarmony " << h << " " << dur << endl;
	
	if (h == "|") {
		Sguidotag bar = ARFactory().instance().createTag("bar");
		fHarmVoice->push (bar);
	}
	else if (h == "empty") {
		SARNote empty = ARFactory().instance().createNote("empty");
		*empty = dur;
		fHarmVoice->push (empty);
	}
//	else if (h == ":|") {
//		fHarmVoice->push (makeHidden("repeatEnd"));
//	}
	else {
		fHarmVoice->push (newLine());
		size_t dxpos = h.find("dx=");
		string dx ("0");
		string hh (h);
		if (dxpos != string::npos) {
			dx = h.substr(dxpos+3);
			hh = h.substr(0,dxpos);
		}
		const char * dy 	= isupper(h[0]) ? HarmMainDy : HarmSubDy;
		const char * size 	= isupper(h[0]) ? HarmMainSize : HarmSubSize;
		Sguidotag harm = ARFactory().instance().createTag("harmony");
		harm->add( makeAttribute(nullptr, hh.c_str(), true) );
		harm->add( makeAttribute("dy", dy, false) );
		harm->add( makeAttribute("dx", dx.c_str(), false) );
		harm->add( makeAttribute("fsize", size, false) );
		fHarmVoice->push (harm);

		SARNote empty = ARFactory().instance().createNote("empty");
		*empty = dur;
		fHarmVoice->push (empty);
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::handleHarm (const std::string& str)
{
	vector<string> parts;
	size_t pos = str.find_first_of("ABCDEFGabcdefg");
	while ( pos != string::npos ) {
		size_t n = str.find_first_of(" 	", pos);
		if (n != string::npos) {
			string p = str.substr( pos, n-pos);
			parts.push_back( p );
			pos = str.find_first_of("ABCDEFGabcdefg|", n+1);
		}
		else {
			string p = str.substr( pos);
			parts.push_back( p );
			break;
		}
	}
	for (auto elt: parts) {
		pos = elt.find_first_of("*/");
		string h = elt.substr(0, pos);
		if (pos != string::npos ) {
			string d = elt.substr(pos);
			if (d[0] == '*') d = d.substr(1);
			else d = '1' + d;
			fHarmDur = rational (d);
		}
		makeHarmony ( elt.substr(0,pos), fHarmDur );
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( Sguidocomment& c )
{
	clonevisitor::visitStart(c);
	if (fVoiceNum == fTargetVoice) {
		string str = c->trim();
		std::regex tab  ("%[ \t]*tab[ \t]*:..*");		// catch tab expressions
		std::regex harm ("%[ \t]*H[ \t]*:..*");			// catch harmony expressions
		if (std::regex_match (str, tab)) {
			handleTab(str);
		}
		else if (std::regex_match (str, harm)) {
			handleHarm(str);
		}
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( SARMusic& music )
{
	clonevisitor::visitStart (music);
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( SARChord& chord )
{
	clonevisitor::visitStart (chord);
	if (fVoiceNum == fTargetVoice) {
		fChordNotes.clear();
		fInChord = true;
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::visitEnd ( SARChord& chord )
{
	clonevisitor::visitEnd (chord);
	if (fVoiceNum != fTargetVoice) return;

	if (fInTie) fInTie++;
	rational dur = chord->duration();
	std::vector<const SARNote> vnotes = chord->notes();
	int dots = vnotes.size() ? vnotes[0]->GetDots() : 0;

	if (fChordNotes.size()) {
		std::sort (fChordNotes.begin(), fChordNotes.end(), [] (gmn2tabvisitor::TPNote n1, gmn2tabvisitor::TPNote n2) { return n1.pitch < n2.pitch; });
		const char* sep = "";
		string tabs;
		for (auto n: fChordNotes) {
			tabs += sep;
			tabs += fKeyBoard.note2tab (noteName (n.note), fTabMode.push, fTabMode.row, true);
			sep = ",";
		}
		Sguidotag lyric = makeTab (tabs, fTabMode.push);
		lyric->push (makeEmpty (dur, dots));
		fTabVoice->push(newLine());
		fTabVoice->push(lyric);
	}
	else {
		fTabVoice->push( makeEmpty (dur, dots ));
	}
	fInChord = false;
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( SARVoice& voice )	 {
	clonevisitor::visitStart(voice);
	fVoiceNum++;
}

//______________________________________________________________________________
void gmn2tabvisitor::visitEnd ( SARVoice& voice )
{
	clonevisitor::visitEnd(voice);
	if (fVoiceNum == fTargetVoice) {
		if (fTabMode.row) {
			Sguidoelement elt = fTabVoice;
			clonevisitor::push (elt, false);
		}
		if (fHarmVoice) {
			Sguidoelement elt = fHarmVoice;
			clonevisitor::push (elt, false);
		}
	}
}

//______________________________________________________________________________
void gmn2tabvisitor::visitStart ( SARTie& tie )
{
	Sguidotag tag = tie;
	clonevisitor::visitStart(tag);
	fInTie = 1;
}
void gmn2tabvisitor::visitEnd ( SARTie& tie )
{
	Sguidotag tag = tie;
	clonevisitor::visitEnd(tag);
	fInTie = 0;
}

} // namespace
