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

//________________________________________________________________________
transposeOperation::transposeOperation ()
{
	initialize();
}

transposeOperation::~transposeOperation() {}

//_______________________________________________________________________________
Sguidoelement transposeOperation::operator() ( const Sguidoelement& score, int steps )
{
	fCurrentOctaveIn = fCurrentOctaveOut = 1;			// default current octave
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
}

//________________________________________________________________________
// transpose a pitch using the table of fifth cycle
void transposeOperation::transpose ( char& pitch, int& alter, int& octave, int tableshift ) const
{
	int pitch1 = ARNote::NormalizedName2Pitch(pitch);
	for (unsigned int i=0; i < fFifthCycle.size(); i++) {
		if ((fFifthCycle[i].second == alter) && (fFifthCycle[i].first == pitch)) {
			i += tableshift;
			if (i > fFifthCycle.size()) i -= 12;
			else if (i < 0) i += 12;
			
			pitch = fFifthCycle[i].first;
			alter = fFifthCycle[i].second;
	
			int pitch2 = ARNote::NormalizedName2Pitch(pitch);
			if ((pitch2 < pitch1) && (fChromaticSteps > 0)) octave++;
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
	if (octave != fCurrentOctaveOut) elt->SetOctave(octave);
	fCurrentOctaveOut = octave;
	elt->SetAccidental(alter);
//cerr << string(*elt) << " oct chge: " << fOctaveChange << endl;
}

//________________________________________________________________________
void transposeOperation::visitStart ( SARKey& elt )
{
	Sguidoattribute attr = elt->getAttribute(0);
	if (attr) {
		int key = int(*attr);
		int enharmonicChange;
		int newkey = transposeKey (key, fChromaticSteps, enharmonicChange);
		attr->setValue (long(newkey));
//cerr << "visit SARKey value " << key << " -> " << newkey << " enharmonic (" << enharmonicChange << ")" << endl;
	}
}

//________________________________________________________________________
void transposeOperation::visitStart ( SARVoice& elt ) {
	fCurrentOctaveIn = fCurrentOctaveOut = 1;				// default current octave
	fTableShift = getKey (getOctaveStep(fChromaticSteps));
}

}
