/*

  MusicXML Library
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

#include <iostream>

#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "durationvisitor.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//______________________________________________________________________________
rational durationvisitor::duration(const Sguidoelement& elt)
{ 
	fDuration = fCurrentChordDuration = fCurrentVoiceDuration = rational(0,1);
	fInChord = false;
	if (elt) {
		tree_browser<guidoelement> tb(this);
		tb.browse (*elt);
	}
	return fDuration;
}

//______________________________________________________________________________
void durationvisitor::visitStart( SARVoice& elt )
{
	fInChord = false;
	fCurrentVoiceDuration = rational(0,1);
	fCurrentNoteDuration = rational(1,4);
}

//______________________________________________________________________________
void durationvisitor::visitStart( SARChord& elt )
{
	fCurrentChordDuration = rational(0,1);
	fInChord = true;
}

//______________________________________________________________________________
void durationvisitor::visitStart( SARNote& elt )
{
	rational duration = elt->duration();
	if (duration.getNumerator() == ARNote::kUndefined)
		duration = fCurrentNoteDuration;

	int den = 1, dots = elt->GetDots();
	rational mult = rational(0,1);
	while (dots--)
		mult += rational(1, den *= 2);
	duration += duration * mult;
	duration.rationalise();
	
	fCurrentNoteDuration = duration;
	if ( fInChord ) {
		if (fCurrentNoteDuration > fCurrentChordDuration)
			fCurrentChordDuration = fCurrentNoteDuration;
	}
	else {
		fCurrentVoiceDuration += fCurrentNoteDuration;
		fCurrentVoiceDuration.rationalise();
	}
}

//______________________________________________________________________________
void durationvisitor::visitEnd  ( SARVoice& elt )
{ 
	if (fCurrentVoiceDuration > fDuration) 
		fDuration = fCurrentVoiceDuration;
}

//______________________________________________________________________________
void durationvisitor::visitEnd  ( SARChord& elt )
{ 
	fCurrentVoiceDuration += fCurrentChordDuration;
	fInChord = false;
}


}
