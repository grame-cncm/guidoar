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

#include <iostream>

#include "clonevisitor.h"
#include "seqOperation.h"
#include "ARFactory.h"
#include "ARNote.h"
#include "AROthers.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//_______________________________________________________________________________
SARMusic seqOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	fCurrentDuration = rational(1,4);
	SARMusic outscore = ARFactory::instance().createMusic();
	if (outscore) {
		push (Sguidoelement(outscore));
		
		Sguidoelement sc1 = score1 ? score1 : outscore;
		Sguidoelement sc2 = score2 ? score2 : outscore;

		ctree<guidoelement>::literator s1i = sc1->lbegin();
		ctree<guidoelement>::literator s2i = sc2->lbegin();

		tree_browser<guidoelement> browser(this);
		while ((s1i != sc1->lend()) && (s2i != sc2->lend())) {
			fCurrentKey = fCurrentMeter = fCurrentClef = 0;
			if (s1i != sc1->lend()) {
				fState = kInFirstScore;
				browser.browse(*(*s1i));
				s1i++;
			}
			if (s2i != sc2->lend()) {
				fState = kInSecondScore;
				browser.browse(*(*s2i));
				s2i++;
			}
		}
		fState = kRemainVoice;
		for (; s1i != sc1->lend(); s1i++)	{ browser.browse(*(*s1i)); }
		for (; s2i != sc2->lend(); s2i++)	{ browser.browse(*(*s2i)); }		
	}
	return outscore;
}

void seqOperation::checkHeader(Sguidotag tag, Sguidotag& target)
{
	switch (fState) {
		case kInFirstScore:			
			target = tag;
		case kRemainVoice:			
			clonevisitor::visitStart (tag);
			break;
		case kInSecondScore:
			if (!target || (*tag != target)) 
				clonevisitor::visitStart (tag);
			fCurrentClef = 0;
			break;
	}
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void seqOperation::visitStart ( SARClef& elt )		{ checkHeader (elt, fCurrentClef); }
void seqOperation::visitStart ( SARKey& elt )		{ checkHeader (elt, fCurrentKey); }
void seqOperation::visitStart ( SARMeter& elt )		{ checkHeader (elt, fCurrentMeter); }

// notes are visited only for correct duration link
void seqOperation::visitStart ( SARNote& elt ) 
{ 
	bool done = false;
	rational duration = elt->duration();

	if (fState == kInFirstScore) {
		// maintain the current duration status while in the first score
		if (duration.getNumerator() != ARNote::kUndefined)
			fCurrentDuration = duration;
	}
	else if (fState = kInSecondScore) {
		if (fCurrentDuration.getNumerator() != ARNote::kUndefined) {
			if ((duration.getNumerator() == ARNote::kUndefined) && (fCurrentDuration != rational(1,4))) {
				// here we need to force implicit duration
				SARNote	note = copy (elt);
				*note = rational(1,4);
				push( note );
				fCurrentDuration = ARNote::getImplicitDuration();
				done = true;
			}
		}
	}
	if (!done) clonevisitor::visitStart (elt);
}

// end bars are skipped for the first score
void seqOperation::visitStart ( SAREndBar& elt ) 
{ 
	Sguidotag tag = elt;
	switch (fState) {
		case kRemainVoice:			
		case kInSecondScore:			
			clonevisitor::visitStart (tag);
			break;
	}
}

// a voice is created only for the first score
void seqOperation::visitStart ( SARVoice& elt ) 
{ 
	switch (fState) {
		case kInFirstScore:			
		case kRemainVoice:			
			clonevisitor::visitStart (elt);
			break;
	}
}

// a voice is created only for the first score
void seqOperation::visitEnd   ( SARVoice& elt )
{ 
	switch (fState) {
		case kInSecondScore:			
		case kRemainVoice:			
			clonevisitor::visitEnd (elt);
			break;
	}
}



} // namespace
