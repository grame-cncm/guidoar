/*
  Copyright © Grame 2003,2007

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

#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "ARTag.h"
#include "midicontextvisitor.h"
#include "unrolled_guido_browser.h"

using namespace std;
namespace guido {

//________________________________________________________________________
// midicontextvisitor 
//________________________________________________________________________
midicontextvisitor::~midicontextvisitor() {}

//________________________________________________________________________
midicontextvisitor::midicontextvisitor(long tpq, midiwriter* writer) 
{ 
	fTPQ = tpq;
	fMidiWriter = writer;
	reset ();
}

//________________________________________________________________________
void midicontextvisitor::visit(Sguidoelement& elt) 
{ 
	reset();
	unrolled_guido_browser tb(this);
	tb.browse (elt);
}

//________________________________________________________________________
void midicontextvisitor::reset() 
{ 
	fInChord =  fInSlur = fInStaccato = fInGrace = false;
	fTieState = kNoTie;
	// reset to the default guido implicit values
    fCurrentDate = fChordDuration = 0;
	fCurrentDuration = rational (1,4);
    fTranspose = fCurrentDots = 0;
	fCurrentOctave = 1;
	fCurrentVel = 90;
}

//________________________________________________________________________
int midicontextvisitor::moveTime(int dur) 
{
	if (!fInChord) return dur;
	if (dur > fChordDuration) fChordDuration = dur;
	return 0;
}

//________________________________________________________________________
int midicontextvisitor::rational2ticks(const rational& dur) 
{
	// dur is expressed in whole note fraction
	float fdur = float(dur * 4);
	return int(fdur * fTPQ); 
}

//________________________________________________________________________
int midicontextvisitor::midiPitch (SARNote& elt) 
{
	bool sharp; int midi = -1;
	ARNote::pitch pitch = elt->GetPitch (sharp);
	if (pitch != ARNote::kNoPitch) {
		// offset in octave numeration between guido and midi is 3
		int midioctave = (fCurrentOctave + 3) * 12;
		midi = midioctave + (pitch*2) + elt->GetAccidental();
		if (pitch > ARNote::E) midi--;
		if (sharp) midi++;
	}
	return midi;
}
//________________________________________________________________________
rational midicontextvisitor::noteduration (SARNote& elt )
{
	rational dur = elt->duration();
	if (dur.getNumerator() != ARNote::kUndefined) {
		fCurrentDuration = dur;
		fCurrentDots = 0;
	}
	int dots = elt->GetDots();
	if (dots) fCurrentDots = dots;
	dur = fCurrentDuration;
	dots = fCurrentDots;
	rational dotmult (1,1);
	while (dots) {
		dotmult /= 2;
		dotmult.rationalise();
		dur *= dotmult;
		dur.rationalise();
	}
	return dur;
}

//________________________________________________________________________
// the various play methods
//________________________________________________________________________
void midicontextvisitor::playTempoChange (long bpm)
{
	if (fMidiWriter && bpm)
		fMidiWriter->tempoChange (fCurrentDate, bpm);
}

void midicontextvisitor::playProgChange (long prog)
{
	if (fMidiWriter)
		fMidiWriter->progChange (fCurrentDate, prog);
}

//________________________________________________________________________
void midicontextvisitor::playNote (long date, int pitch, int duration)
{
	if (fMidiWriter) {
		int articulation = midiwriter::kNone;
		if (fInSlur) articulation += midiwriter::kSlur;
		if (fInStaccato) articulation += midiwriter::kStaccato;
		fMidiWriter->newNote (date, pitch + fTranspose, fCurrentVel, duration, articulation);
	}	
}

//________________________________________________________________________
void midicontextvisitor::playMidiInstrument (int progChange)
{
	if (fMidiWriter) {
		fMidiWriter->progChange (fCurrentDate, progChange);
	}
}

//________________________________________________________________________
void midicontextvisitor::startTie(Sguidoelement tie, Sguidoelement context)	
{ 
	fTieState = kInTie;
/*
	ctree<guidoelement>::iterator i;
	if (context) {
		i = context->begin();
	}
	else if (fCurrentVoice) {
		context = fCurrentVoice;
		i = find(context->begin(), context->end(), tie);
	}

	while (i != context->end()) {
		SARNote note = dynamic_cast<ARNote*>((guidoelement*)(*i));
		SARChord chord = dynamic_cast<ARChord*>((guidoelement*)(*i));
		SARTieEnd tieEnd = dynamic_cast<ARTag<kTTieEnd>*>((guidoelement*)(*i));
		
		i++;
	}
*/
}

//________________________________________________________________________
void midicontextvisitor::stopTie()	
{ 
	fTiedNotes.clear();
	fTieState = kNoTie;
}

//________________________________________________________________________
void midicontextvisitor::storeTied( SARChord& elt )	
{
	fTiedNotes.clear();
	ctree<guidoelement>::iterator i;
	for (i = elt->begin(); i != elt->end(); i++) {
		SARNote note = dynamic_cast<ARNote*>((guidoelement*)(*i));
		if (note) fTiedNotes.push_back(note); 
	}
}

//________________________________________________________________________
// the visitxxx methods
//________________________________________________________________________
void midicontextvisitor::visitStart ( SARVoice& elt )
{
	reset ();
	fCurrentVoice = elt;
	if (fMidiWriter) fMidiWriter->startVoice();
}
void midicontextvisitor::visitEnd ( SARVoice& elt )		{ if (fMidiWriter) fMidiWriter->endVoice (fCurrentDate); }

//________________________________________________________________________
void midicontextvisitor::visitStart( SARNote& elt )
{
	if (fTieState == kInTie) {
		fTieState = kTiedNote;
		fTiedNotes.push_back(elt);
	}
	else if (fTieState == kTiedNote) {
	}

	int octave = elt->GetOctave();
	if (octave != ARNote::kUndefined) fCurrentOctave = octave;

	int dur = rational2ticks (noteduration(elt));
	int pitch = midiPitch(elt);
	if (pitch >= 0)	playNote (fCurrentDate, pitch, dur);
	fCurrentDate += moveTime (dur);
}

//________________________________________________________________________
void midicontextvisitor::visitStart( SARTie& elt )			{ startTie(elt, elt); }
void midicontextvisitor::visitEnd  ( SARTie& elt )			{ stopTie(); }
void midicontextvisitor::visitStart( SARTieBegin& elt )		{ startTie(elt); }
void midicontextvisitor::visitStart( SARTieEnd& elt )		{ stopTie(); }

//________________________________________________________________________
void midicontextvisitor::visitStart( SARChord& elt )	{ 
	fChordDuration = 0; 
	fInChord = true; 
	if (fTieState == kInTie) {
		fTieState = kTiedChord;
		storeTied (elt);
	}
}
void midicontextvisitor::visitEnd  ( SARChord& elt )	{ fInChord = false; fCurrentDate += moveTime (fChordDuration); }

//________________________________________________________________________
void midicontextvisitor::visitStart( SARTempo& elt )
{
	string val = elt->getAttributeValue("bpm");
	int num, denum, tempo;
	if (sscanf ( val.c_str(), "%d/%d=%d", &num, &denum, &tempo) == 3) {
		rational beat(num, denum);
		rational quarter(1,4);
		rational mult = beat / quarter;
		tempo *= mult.getNumerator();
		tempo /= mult.getDenominator();
		playTempoChange (tempo);
	}
}

//________________________________________________________________________
void midicontextvisitor::visitStart( SARIntens& elt )
{
	float intens = elt->getAttributeFloatValue (1, 0.);
	if (intens) fCurrentVel = int(127 * intens);
}

//________________________________________________________________________
void midicontextvisitor::visitStart( SAROct& elt )
{
	fTranspose = elt->getAttributeFloatValue (0, 0) * 12;
}
void midicontextvisitor::visitEnd( SAROct& elt )
{
	if (elt->size()) fTranspose = 0;
}

//________________________________________________________________________
void midicontextvisitor::visitStart( SARInstr& elt )
{
	string midi = elt->getAttributeValue (1);
	int prog;
	if (sscanf ( midi.c_str(), "MIDI %d", &prog) == 1)
		playProgChange (prog);
}

} // end namespace

