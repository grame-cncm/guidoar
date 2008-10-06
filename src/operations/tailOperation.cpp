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

#include "ARNote.h"
#include "AROthers.h"
#include "ARTag.h"
#include "clonevisitor.h"
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
	fPendingTagsMap.clear();
	fCurrentOctave = ARNote::kDefaultOctave;
	fCurrentNoteDots = 0;
	fCurrentNoteDuration.set(1,4);
	fStartPoint = duration;

	Sguidoelement outscore;
	if (score) {
		tree_browser<guidoelement> tb(this);
		tb.browse (*score);
		outscore = fStack.top();
		fStack.pop();
	}
	return outscore;
}

//________________________________________________________________________
void tailOperation::checkStart()
{
	if ((fState == kSkip) && (fDuration.currentVoiceDate() >= fStartPoint)) {
		fState = kStartPending;
		checkPendingHead();
		checkPendingTags();
	}
}

//________________________________________________________________________
void tailOperation::checkPendingHead()
{
	if (!fHeaderFlushed) {
		if (fCurrentStaff)	clonevisitor::visitStart (fCurrentStaff);
		if (fCurrentClef)	clonevisitor::visitStart (fCurrentClef);
		if (fCurrentKey)	clonevisitor::visitStart (fCurrentKey);
		if (fCurrentMeter)	clonevisitor::visitStart (fCurrentMeter);
		fCurrentClef = fCurrentKey = fCurrentMeter = fCurrentStaff = 0;
		fHeaderFlushed = true;
	}
}

//________________________________________________________________________
void tailOperation::checkPendingTags()
{
	map<Sguidotag,int>::iterator i;
	for (i = fPendingTagsMap.begin(); i != fPendingTagsMap.end(); i++) {
		if (i->second) {
			Sguidotag tag = i->first;
			clonevisitor::visitStart (tag);
			i->second = 0;
		}
	}
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void tailOperation::visitStart ( SARVoice& elt )
{
	fPendingTagsMap.clear();
	fState = (float(fStartPoint) > 0.001) ? kSkip : kStartPending;
	fHeaderFlushed = false;
	fCurrentOctave = ARNote::kDefaultOctave;
	fCurrentNoteDots = 0;
	fCurrentNoteDuration.set(1,4);
	clonevisitor::visitStart (elt);
	fDuration.visitStart (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARChord& elt )
{
	fDuration.visitStart (elt);
	if (fState) clonevisitor::visitStart (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARNote& elt )
{
	fDuration.visitStart (elt);

	int octave = elt->GetOctave();
	if (octave != ARNote::kUndefined) fCurrentOctave = octave;

	rational duration = elt->duration();
	if (duration.getNumerator() != ARNote::kUndefined) fCurrentNoteDuration = duration;
	if (fState) {
		if (fState == kStartPending) {
			if (!elt->isRest() && !elt->isEmpty()) {
				if ((elt->GetOctave() == ARNote::kUndefined) && (fCurrentOctave != ARNote::kDefaultOctave)) {
					elt->SetOctave(fCurrentOctave);
				}
				fState = kCopy;
			}
			if (duration.getNumerator() == ARNote::kUndefined) (*elt) = fCurrentNoteDuration;
			
		}
		clonevisitor::visitStart (elt);
	}
}

//________________________________________________________________________
void tailOperation::visitStart ( Sguidotag& elt )
{
	if (fState) {
		clonevisitor::visitStart (elt);
	}
	else {
		if (elt->size()) fPendingTagsMap[elt] = 1;

		switch (elt->getType()) {
			case kTComposer:
			case kTNewLine:
			case kTNewPage:
			case kTNewSystem:
			case kTPageFormat:
			case kTSystemFormat:
			case kTTitle:
				break;
			case kTStaffFormat:
			case kTBarFormat:
			case kTInstr:
				clonevisitor::visitStart (elt);
				break;
			default:
				checkPendingHead();
				
		}
	}
}

//________________________________________________________________________
void tailOperation::visitStart ( SARKey& elt )
{
	if (fState == kSkip)	fCurrentKey = Sguidotag(elt);
	else					cloneTag (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARMeter& elt )
{
	if (fState == kSkip)	fCurrentMeter = Sguidotag(elt);
	else					cloneTag (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARClef& elt )
{
	if (fState == kSkip)	fCurrentClef = Sguidotag(elt);
	else					cloneTag (elt);
}

//________________________________________________________________________
void tailOperation::visitStart ( SARStaff& elt )
{
	if (fState == kSkip)	fCurrentStaff = Sguidotag(elt);
	else					cloneTag (elt);
}

//________________________________________________________________________
void tailOperation::visitEnd ( SARNote& elt )
{
	checkStart();
}

//________________________________________________________________________
void tailOperation::visitEnd ( SARChord& elt )
{
	fDuration.visitEnd (elt);
	if (fState)	clonevisitor::visitEnd (elt);
	else		checkStart();
}

//________________________________________________________________________
void tailOperation::visitEnd ( SARVoice& elt )
{
	clonevisitor::visitEnd (elt);
	// adjusts the stack
	// may be necessary due to potential end inside range tags
	while (fStack.size() > 1)
		fStack.pop();
}

//________________________________________________________________________
void tailOperation::visitEnd ( Sguidotag& elt )
{
	if (fState) clonevisitor::visitEnd (elt);
	else if (elt->size()) {
		fPendingTagsMap[elt] = 0;
	}
}

}
