#ifdef USEMidiShare

/*

  guidoar Library
  Copyright (C) 2006,2007  Grame

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

#ifndef __midiConverter__
#define __midiConverter__

#include "export.h"
#include "guidoelement.h"
#include "midicontextvisitor.h"

#define __Types__		// this is for midishare types only
#include <MidiShare.h>

struct TMidiSeq;

namespace guido 
{


/*!
\brief a midi converter

	It is based on MidiShare and on the Player libraries.
	It supports MIDIfile export as well as MidiShare player interface.
*/
class midiconverter : public midiwriter {
	public:
				 midiconverter(long tpq=480) : fTPQ(tpq), fSeq(0), fVoiceNumber(0) {}
		virtual ~midiconverter();
		
		// main services are provided under the form of a midifile export or a midishare player
		virtual bool  score2midifile (Sguidoelement& score, char* fileName);
		virtual short score2player   (Sguidoelement& score, const MidiName playerName);

	protected:
		// midiwriter interface support
		virtual void startVoice ();
		virtual void endVoice (long date);

		virtual void newNote (long date, int pitch, int vel, int duration, int art);
		virtual void tempoChange (long date, int bpm);
		virtual void progChange (long date, int prog);

		virtual bool getMidi (Sguidoelement& score);
		virtual void setCommon (MidiEvPtr ev, long date) const;
		
		long		fTPQ;
		TMidiSeq *	fSeq;
		short		fVoiceNumber;
};

}


#endif // USEMidiShare
#endif // __midiConverter__
