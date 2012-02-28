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
#include <string>

#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "ARTag.h"
#include "clonevisitor.h"
#include "markers.h"
#include "tailOperation.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//_______________________________________________________________________________
tailOperation::tailOperation()	{}
tailOperation::~tailOperation()	{}

//_______________________________________________________________________________
SARMusic tailOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	if (!score2) return 0;
	Sguidoelement elt = (*this)(score1, fDuration.duration(score2));
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//_______________________________________________________________________________
Sguidoelement tailOperation::operator() ( const Sguidoelement& score, const rational& duration )
{
	fCurrentOctave = ARNote::kDefaultOctave;
	fCurrentNoteDots = 0;
	fStartPoint = duration;

	Sguidoelement outscore;
	if (score) {
		tree_browser<guidoelement> tb(this);
		tb.browse (*score);
		if (fStack.size()) {
			outscore = fStack.top();
			fStack.pop();
		}
	}
	return outscore;
}

//________________________________________________________________________

//________________________________________________________________________
void tailOperation::flushTags()
{
	for (unsigned int i = 0; i < fCurrentTags.size(); i++) {
		Sguidotag tag = fCurrentTags[i];
		if (tag) {
			if (tag->size()) markers::markOpened (tag, false);
			else if (ornament(tag)) continue;		// don't flush empty ornaments
			clonevisitor::visitStart (tag);
		}
	}
	fCurrentTags.clear();
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void tailOperation::visitStart ( SARVoice& elt )
{
//cerr << "start voice --------------" << endl;
	fCurrentTags.clear();
	fCopy = false;
	fCurrentOctave = ARNote::kDefaultOctave;
	fCurrentNoteDots = 0;
	clonevisitor::visitStart (elt);
	fDuration.visitStart (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARChord& elt )
{
	if (fCopy) clonevisitor::visitStart (elt);
	else {						// check if startpoint is reached
		rational remain = fStartPoint - fDuration.currentVoiceDate();
		rational dur = elt->duration();
		if (elt->implicitDuration(dur)) {
			if (!dur.getNumerator()) dur = fDuration.currentNoteDuration();
			else dur.set (-dur.getNumerator(), dur.getDenominator());
			dur = max(fDuration.currentNoteDuration(), dur);
		}

		if (remain < dur) {
//			fCopy = true;
			flushTags();
			clonevisitor::visitStart (elt);
		}
		fDuration.visitStart (elt);
	}
}

//________________________________________________________________________
void tailOperation::visitStart ( SARNote& elt )
{
	if (fStartPoint < fDuration.currentVoiceDate()) {
		if (!elt->isRest()) {
			if (fForceOctave && elt->implicitOctave())
				elt->SetOctave (fCurrentOctave);
			fForceOctave = false;
		}
		if (fForceDuration && elt->implicitDuration())
			*elt = fDuration.currentNoteDuration();
		fForceDuration = false;
		clonevisitor::visitStart (elt);
	}
	else {												// check if startpoint will be reached
		rational remain = fStartPoint - fDuration.currentVoiceDate();
		rational dur = elt->implicitDuration() ? fDuration.currentNoteDuration() : elt->duration();
		if (remain >= dur) {							// not yet
			// maintains the current state
			int octave = elt->GetOctave();
			if (elt->isPitched() && !ARNote::implicitOctave(octave))
				fCurrentOctave = octave;
			fDuration.visitStart (elt);
		}
		else {
			fDuration.visitStart (elt);
			fCopy = true;
			*elt = dur - remain;
			fForceDuration = (elt->duration() != fDuration.currentNoteDuration());
			fForceOctave = false;
			if (elt->implicitOctave()) {
				if (!elt->isRest()) elt->SetOctave (fCurrentOctave);
				else fForceOctave = true;
			}

			flushTags();
			clonevisitor::visitStart (elt);
//			if (tie) {		// notes splitted by the operation are marked using an opened tie
//				Sguidoelement tag = ARTag<kTTie>::create();
//				tag->setName ("tie");
//				markers::markOpened (tag, true);
//				push(tag, true);
//			}
		}
	}
}

//________________________________________________________________________
void tailOperation::pushTag ( Sguidotag& elt )
{
	for (unsigned int i=0; i < fCurrentTags.size(); i++) {
		if (fCurrentTags[i] && (fCurrentTags[i]->getName() == elt->getName())) {
			fCurrentTags[i] = elt;
			return;
		}
	}
	fCurrentTags.push_back(elt);
}

//________________________________________________________________________
bool tailOperation::ornament ( Sguidotag& elt )
{
	switch (elt->getType() == kTAccent) {
		case kTMord:
		case kTTurn:
		case kTTrill:
		case kTStacc:
		case kTPizz:
		case kTHarmonic:
		case kTFermata:
			return true;
	}
	return false;
}

//________________________________________________________________________
void tailOperation::popTag ( Sguidotag& elt )
{
	if (elt->endTag() || elt->size()) {
		for (unsigned int i=0; i < fCurrentTags.size(); i++) {
			if (fCurrentTags[i]) {
				if (fCurrentTags[i]->getName() == elt->getName()) {
					fCurrentTags[i] = 0;
					return;
				}
				if (fCurrentTags[i]->getName() == elt->matchTag()) {
					fCurrentTags[i] = 0;
					return;
				}
			}
		}
	}
}

//________________________________________________________________________
void tailOperation::visitStart ( Sguidotag& elt )
{
	if (fCopy) {
		clonevisitor::visitStart (elt);
	}
	else {
		pushTag (elt);
	}
}

//________________________________________________________________________
void tailOperation::visitEnd ( SARChord& elt )
{
	fDuration.visitEnd (elt);
	if (fCopy) clonevisitor::visitEnd (elt);
}

//________________________________________________________________________
void tailOperation::visitEnd ( SARVoice& elt )
{
	flushTags();
	clonevisitor::visitEnd (elt);
	// adjusts the stack
	// may be necessary due to potential end inside range tags
	while (fStack.size() > 1)
		fStack.pop();
}

//________________________________________________________________________
void tailOperation::visitEnd ( Sguidotag& elt )
{
	if (fCopy) clonevisitor::visitEnd (elt);
	else {
		popTag (elt);
	}
}

}
