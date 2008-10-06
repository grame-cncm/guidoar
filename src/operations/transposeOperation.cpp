/*

  Copyright (C) 2007  Grame


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

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    research@grame.fr

*/

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <math.h>

#include "ARNote.h"
#include "ARFactory.h"
#include "AROthers.h"
#include "ARTag.h"
#include "clonevisitor.h"
#include "transposeOperation.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{


//______________________________________________________________________________
/*!
\brief	A visitor to retrive the pitch of the first note (fist voice, lowest note) 
*/
class firstnotevisitor :
	public tree_browser<guidoelement>,
	public visitor<SARChord>,
	public visitor<SARNote>
{
    public:
				 firstnotevisitor() { set(this); }
       	virtual ~firstnotevisitor() {}
		int		firstPitch (const Sguidoelement& score);

		bool 	done () const	{ return fDone; }
		
	protected:              
		virtual void visitStart( SARChord& elt );
		virtual void visitStart( SARNote& elt );
		virtual void visitEnd  ( SARChord& elt );
		int		fPitch, fCurrentOctave;
		bool	fInChord, fDone;
};

int	firstnotevisitor::firstPitch (const Sguidoelement& score) {
	fInChord = fDone = false;
	fPitch = 9999;								// set to a high value since the lowest pitch is collected
	fCurrentOctave = ARNote::kDefaultOctave;	// the default octave
	browse (*score);
	return done() ? fPitch : -1;
}
void firstnotevisitor::visitStart( SARChord& elt )	{ fInChord=true; }
void firstnotevisitor::visitEnd  ( SARChord& elt )	{ fInChord=false; fDone = true; }

void firstnotevisitor::visitStart( SARNote& elt )	
{
	int octave = elt->GetOctave();
	if (octave != ARNote::kUndefined) fCurrentOctave = octave;

	int alter; int midi = -1;
	ARNote::pitch pitch = elt->GetPitch (alter);
	if (pitch != ARNote::kNoPitch) {
		// offset in octave numeration between guido and midi is 3
		int midioctave = (fCurrentOctave + 3) * 12;
		midi = midioctave + (pitch*2) + alter;
		if (pitch > ARNote::E) midi--;
		if (midi < fPitch) fPitch = midi;
		if (!fInChord) fDone = true;
	}
}


//________________________________________________________________________
// transposeOperation implementation
//________________________________________________________________________
transposeOperation::transposeOperation ()
{
	initialize();
}

transposeOperation::~transposeOperation() {}

//_______________________________________________________________________________
SARMusic transposeOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	if (!score1 || !score2) return 0;

	firstnotevisitor fnv;
	int p1 = fnv.firstPitch (score1);
	int p2 = fnv.firstPitch (score2);
	int steps = ((p1 < 0) || (p2 < 0)) ? 0 : p2 - p1;

	Sguidoelement elt = (*this)(score1, steps);
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//_______________________________________________________________________________
Sguidoelement transposeOperation::operator() ( const Sguidoelement& score, int steps )
{
	fCurrentOctaveIn = fCurrentOctaveOut = ARNote::kDefaultOctave;			// default current octave
	fChromaticSteps = steps;
	fOctaveChange = getOctave(fChromaticSteps);
	fTableShift = getKey (getOctaveStep(fChromaticSteps));

	Sguidoelement transposed;
	if (score) {
		clonevisitor cv;
		transposed = cv.clone(score);
	}
	if (transposed) {
		tree_browser<guidoelement> tb(this);
		tb.browse (*transposed);
	}
	return transposed;
}

//________________________________________________________________________
/*
	The cycle of fifth is a special ordering of notes, beginning, say, with a F 
	double flat, and ending with a B double sharp, with an interval of a perfect 
	fifth between each note. This leads to the following list: 
	Fbb, Cbb, Gbb, Dbb, Abb, Ebb, Bbb, Fb, Cb, Gb, Db, Ab, Eb, Bb, F, C, G, D, 
	A, E, B, F#, C#, G#, D#, A#, E#, B#, F##, C##, G##, D##, A##, E##, B##. 
	To apply transposition, we first look in the table for the correct 
	shifting, and apply the same to every note to transpose.
*/
void transposeOperation::initialize ()
{
	fFifthCycle.clear();
	for (int i=-2; i<=2; i++) {
		fFifthCycle.push_back(make_pair('f', i));
		fFifthCycle.push_back(make_pair('c', i));
		fFifthCycle.push_back(make_pair('g', i));
		fFifthCycle.push_back(make_pair('d', i));
		fFifthCycle.push_back(make_pair('a', i));
		fFifthCycle.push_back(make_pair('e', i));
		fFifthCycle.push_back(make_pair('b', i));
	}
	fKeysMap["C&"] = fKeysMap["a&"] = -7;
	fKeysMap["C"]  = fKeysMap["a"]  = 0;
	fKeysMap["C#"] = fKeysMap["a#"] = 7;

	fKeysMap["D&"] = fKeysMap["b&"] = fKeysMap["h&"] = -5;
	fKeysMap["D"]  = fKeysMap["b"]  = fKeysMap["h"]  = 2;
	fKeysMap["D#"] = fKeysMap["b#"] = fKeysMap["h#"] = 9;

	fKeysMap["E&"] = fKeysMap["c"] = -3;
	fKeysMap["E"]  = fKeysMap["c#"] = 4;
	fKeysMap["E#"] = 11;			// double  sharp not supported in key sign

	fKeysMap["F&"] = fKeysMap["d&"] = -8;
	fKeysMap["F"]  = fKeysMap["d"]  = -1;
	fKeysMap["F#"] = fKeysMap["d#"] = 6;

	fKeysMap["G&"] = fKeysMap["e&"] = -6;
	fKeysMap["G"]  = fKeysMap["e"]  = 1;
	fKeysMap["G#"] = fKeysMap["e#"] = 8;

	fKeysMap["A&"] = fKeysMap["f"] = -4;
	fKeysMap["A"]  = fKeysMap["f#"] = 3;
	fKeysMap["A#"] = 10;			// double  sharp not supported in key sign

	fKeysMap["B&"] = fKeysMap["H&"] = fKeysMap["g"] = -2;
	fKeysMap["B"]  = fKeysMap["H"]  = fKeysMap["g#"] = 5;
	fKeysMap["B#"] = fKeysMap["H#"] = 12;	// double  sharp not supported in key sign
}

//________________________________________________________________________
// transpose a pitch using the table of fifth cycle
void transposeOperation::transpose ( char& pitch, int& alter, int& octave, int tableshift ) const
{
	// retrieve first the normaized pitch integer class
	int pitch1 = ARNote::NormalizedName2Pitch(pitch);
	// then browse the fifth cycle table
	for (unsigned int i=0; i < fFifthCycle.size(); i++) {
		// until we find the same pitch spelling (ie including name and accident)
		if ((fFifthCycle[i].second == alter) && (fFifthCycle[i].first == pitch)) {
			// then we shift into the table
			i += tableshift;
			// make possible adjustments
			if (i > fFifthCycle.size()) i -= 12;
			else if (i < 0) i += 12;
			// and retrieve the resulting transposed pitch
			pitch = fFifthCycle[i].first;
			alter = fFifthCycle[i].second;
			// check now fro octave changes
			int pitch2 = ARNote::NormalizedName2Pitch(pitch);
			// if pitch is lower but transposition is up: then increase octave
			if ((pitch2 < pitch1) && (fChromaticSteps > 0)) octave++;
			// if pitch is higher but transposition is down: then decrease octave
			else if ((pitch2 > pitch1) && (fChromaticSteps < 0)) octave--;

			return;
		}
	}
	cerr << "transpose: pitch out of fifth cycle table (" << pitch << " " << alter << ")" << endl;
}

//________________________________________________________________________
int transposeOperation::transposeKey (int key, Chromatic steps, int& enharmonicChange)
{
	int newkey = key + getKey(steps);
	if (newkey >= 6) {
		newkey -= 12;
		enharmonicChange = 1;
	}
	else if (newkey < -6) {
		newkey += 12;
		enharmonicChange = -1;
	}
	else enharmonicChange = 0;
	return newkey;
}

//________________________________________________________________________
int transposeOperation::getKey (  Chromatic steps ) 
{
	// the method looks for the key signature corresponding to a chromatic degree
	// the key signature is the simplest between flats and sharps alternatives
	// sharps are positive values and flats are negative
	steps = getOctaveStep(steps);		// first converts into a value modulo 12
	if (steps < 0) steps = 12 + steps;	// works only on positive values

	int sharps = 0;
	int curstep = 0;
	while (curstep != steps) {
		curstep += 7;		 	// add a fifth
		curstep %= 12;			// modulus an octave
		sharps++;
	}
	return (sharps >= 6 ? sharps - 12 : sharps);	// simplest key is chosen here
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void transposeOperation::visitStart ( SARNote& elt ) 
{
	if (elt->isRest() || elt->isEmpty()) return;

	char npitch; int alter;
	elt->NormalizedPitchName (npitch, alter);
	alter += elt->GetAccidental();
	int octaveChge = 0;
	transpose ( npitch, alter, octaveChge, fTableShift );
	int octave = elt->GetOctave();
	if (octave == ARNote::kUndefined) octave = fCurrentOctaveIn;
	else fCurrentOctaveIn = octave;
	octave += octaveChge + fOctaveChange;

//cerr << string(*elt) << " -> ";
	string npname; 
	npname += npitch;
	elt->setName(npname);
	if ((octave != fCurrentOctaveOut) || (elt->GetOctave() != ARNote::kUndefined))
		elt->SetOctave(octave);
	fCurrentOctaveOut = octave;
	elt->SetAccidental(alter);
//cerr << string(*elt) << " oct chge: " << fOctaveChange << endl;
}

//________________________________________________________________________
void transposeOperation::visitStart ( SARKey& elt )
{
	Sguidoattribute attr = elt->getAttribute(0);
	if (attr) {
		int key = 0;
		map<string,int>::const_iterator i = fKeysMap.lower_bound(attr->getValue());
		if (i != fKeysMap.end())
			key = i->second;
		else 
			key = int(*attr);
		int enharmonicChange;
		int newkey = transposeKey (key, fChromaticSteps, enharmonicChange);
		attr->setValue (long(newkey));
		attr->setQuoteVal(false);
//cerr << "visit SARKey value " << key << " -> " << newkey << " enharmonic (" << enharmonicChange << ")" << endl;
	}
}

//________________________________________________________________________
void transposeOperation::visitStart ( SARVoice& elt ) {
	fCurrentOctaveIn = fCurrentOctaveOut = ARNote::kDefaultOctave;				// default current octave
	fTableShift = getKey (getOctaveStep(fChromaticSteps));
}

}
