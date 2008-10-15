#ifdef USEMidiShare
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

#define __Types__		// this is for midishare types only
#include <Player.h>
#include "midiconverter.h"
#include "tree_browser.h"

using namespace std;
namespace guido {

//________________________________________________________________________
midiconverter::~midiconverter()
{
	if (fSeq) MidiFreeSeq (fSeq);
}

//________________________________________________________________________
// midiconverter 
//________________________________________________________________________
int  midiconverter::score2midifile (Sguidoelement& score, char* fileName)
{
	MidiName tmpName = "guido2midi";
	short ref = MidiOpen (tmpName);
	if (ref < 0) return ref;

	int err = noErr;
	if (getMidi(score)) {
		MidiFileInfos infos;
		infos.format = midifile1;
		infos.timedef = TicksPerQuarterNote; 
		infos.clicks = fTPQ;
		err = MidiFileSave (fileName, fSeq, &infos);
		MidiFreeSeq (fSeq);
		fSeq = 0;
	}
	MidiClose (ref);
	return err;
}

//________________________________________________________________________
short midiconverter::score2player (Sguidoelement& score, const MidiName playerName)
{
	short ref = OpenPlayer (playerName);
	if (ref > 0) {
		 if (getMidi(score)) {
			SetAllTrackPlayer (ref, fSeq, fTPQ);
			fSeq = 0;		// the sequence is now owned by the player
		 }
		 else {
			ClosePlayer (ref);
			ref = -1;
		}
	}
	return ref;
}

//________________________________________________________________________
bool midiconverter::getMidi (Sguidoelement& score)
{
	if (!score) return false;

	if (fSeq) MidiClearSeq (fSeq);
	else fSeq = MidiNewSeq();
	if (fSeq) {
		midicontextvisitor midivisitor (fTPQ, this);
		midivisitor.visit (score);
		return true;
	}
	return false;
}

//________________________________________________________________________
void midiconverter::setCommon (MidiEvPtr ev, long date) const
{
	Date(ev)	= date;
	RefNum(ev)	= fVoiceNumber;
	Chan(ev)	= fVoiceNumber - 1;
}

//________________________________________________________________________
// midiwriter interface support
//________________________________________________________________________
void midiconverter::startVoice ()
{
	fVoiceNumber++;
}

void midiconverter::endVoice (long date)
{
	MidiEvPtr ev = MidiNewEv(typeEndTrack);
	if (ev) {
		setCommon(ev, date);
		MidiAddSeq (fSeq, ev);
	}	
}

void midiconverter::newNote (long date, int pitch, int vel, int duration, int art)
{
	MidiEvPtr ev = MidiNewEv(typeNote);
	if (ev) {
		setCommon(ev, date);
		Pitch(ev)	= pitch;
		Vel(ev)		= vel;
		if (art == midiwriter::kStaccato)
			duration *= 0.5f;
		else if (art == midiwriter::kSlur)
			duration *= 1.01f;
		else 
			duration *= 0.90f;
		Dur(ev)		= duration;
		MidiAddSeq (fSeq, ev);
	}	
}

void midiconverter::tempoChange (long date, int bpm)
{
	MidiEvPtr ev = MidiNewEv(typeTempo);
	if (ev) {
		setCommon(ev, date);
		Tempo(ev)	= 60000000 / bpm;
		MidiAddSeq (fSeq, ev);
	}	
}

void midiconverter::progChange (long date, int prog)
{
	MidiEvPtr ev = MidiNewEv(typeProgChange);
	if (ev) {
		setCommon(ev, date);
		Data(ev)[0]	= prog;
		MidiAddSeq (fSeq, ev);
	}	
}

void midiconverter::timeSignChange (long date, unsigned int num, unsigned int denom)
{
	MidiEvPtr ev = MidiNewEv(typeTimeSign);
	if (ev) {
		setCommon(ev, date);
		TSNum(ev)	= num;
		TSDenom(ev)	= denom;

		int clocksDiv = 1;
		while (denom > 1) {
			denom--;
			clocksDiv *= 2;
		}
		TSClocks(ev)= 96 / clocksDiv;	
		TS32nd(ev)	= 8;		// number of 32th note in a quarter note
		MidiAddSeq (fSeq, ev);
	}	
}

void midiconverter::keySignChange (long date, int signature, bool major)
{
	MidiEvPtr ev = MidiNewEv(typeKeySign);
	if (ev) {
		setCommon(ev, date);
		KSTon(ev)	= signature;
		KSMode(ev)	= major ? 0 : 1;
		MidiAddSeq (fSeq, ev);
	}	
}


} // end namespace

#endif // USEMidiShare
