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
#include "markers.h"
#include "tree_browser.h"

#include "ARTag.h"

using namespace std;

namespace guido 
{


//______________________________________________________________________________
/*!
\brief	A visitor to clean opened tags
*/
class export seqCleaner : public clonevisitor
{
	protected:
		SARNote	fFirstTied;
		bool	fInTie;		

		void visitStart ( SARNote& elt );
		void visitStart ( Sguidotag& elt );
		void visitEnd	( Sguidotag& elt );

    public:
				 seqCleaner() : fInTie(false) {}
		virtual ~seqCleaner() {}
};

//_______________________________________________________________________________
void seqCleaner::visitStart ( Sguidotag& elt )
{
cerr << "visitStart " << string(*elt) << endl;
	if (markers::opened (elt) == markers::kClosed) {
		if (elt->getType() == kTTie) fInTie = true;
cerr << "clean tag " << string(*elt) << endl;
		markers::delMark (elt);
	}
	if (!fInTie) {
cerr << "clone tag " << string(*elt)  << endl;
		clonevisitor::visitStart (elt);
	}
}

void seqCleaner::visitEnd ( Sguidotag& elt )
{
	if (fInTie) {
		fInTie = false;
		fFirstTied = 0;
	}
	else {
cerr << "end clone tag " << string(*elt) << endl;
		clonevisitor::visitStart (elt);
	}
}

void seqCleaner::visitStart	( SARNote& elt )
{
	if (fInTie) {
		if (fFirstTied) {
			*fFirstTied += elt->duration();
cerr << "add note dur" << endl;
		}
		else {
			fFirstTied = copy(elt);
			clonevisitor::push(fFirstTied);
		}
	}
	else clonevisitor::visitStart (elt);
}

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

		fFirstInScore = true;
		tree_browser<guidoelement> browser(this);
		// browse voice by voice in parallel
		while ((s1i != sc1->lend()) && (s2i != sc2->lend())) {
			fRangeTags.clear();
			fPosTags.clear();
			fOpenedTags.clear();
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
		
//		seqCleaner	cleanTags;
//		tree_browser<guidoelement> clean(&cleanTags);
//		clean.browse (*outscore);
//		outscore = dynamic_cast<ARMusic*>((guidoelement*)cleanTags.result());
	}
	return outscore;
}

//________________________________________________________________________
void seqOperation::storeTag(Sguidotag tag)
{
	const string& name = tag->getName();
	if (tag->beginTag())
		fRangeTags[name] = tag;
	else if (tag->endTag())
		fRangeTags[tag->matchTag()] = 0;
	else if (tag->size())
		fRangeTags[name] = tag;
	else {
		switch (tag->getType()) {
			case kTClef:
			case kTColor:
			case kTInstr:
			case kTIntens:
			case kTKey:
			case kTMeter:
				fPosTags[name] = tag;
				break;
		}
	}
}

//________________________________________________________________________
void seqOperation::endTag(Sguidotag tag)
{
	const string& name = tag->getName();
	if (tag->size()) {
		fRangeTags[name] = 0;
		if (markers::opened (tag) > 1) {
			Sguidotag copy = dynamic_cast<guidotag*>((guidoelement*)fStack.top());
			fOpenedTags[name] = copy;
		}
	}
}

//________________________________________________________________________
bool seqOperation::currentTag(Sguidotag tag, bool end)
{
	bool ret = false;
	const string& name = tag->getName();
	if (!tag->size()) {
		Sguidotag cur = fPosTags[name];
		if (cur) {
			ret = (*cur == tag);
			if (end) fPosTags[name] = 0;
		}
	}
	return ret;
}

//________________________________________________________________________
bool seqOperation::checkmatch(Sguidotag tag1, Sguidotag tag2)
{
	if (markers::opened (tag2) & markers::kOpenedEnd) {
		if (tag2->getType() == kTTie) {
			if (fCurrentMatch == tag1) return true;

			ctree<guidoelement>::iterator i1 = tag1->begin();
			ctree<guidoelement>::iterator i2 = tag2->begin();
			SARNote n1, n2;
			while ((i1 != tag1->end()) && !n1)
				n1 = dynamic_cast<ARNote*>((guidoelement*)*i1);
			while ((i2 != tag2->end()) && !n2)
				n2 = dynamic_cast<ARNote*>((guidoelement*)*i2);
			if (n1 && n2) {
				int octave = fCurrentOctave;
				int p1 = n1->midiPitch(octave);
				int p2 = n2->midiPitch(octave);
				return p1 == p2;
			}
		}
		else return true;
	}
	return false;
}

//________________________________________________________________________
bool seqOperation::matchOpenedTag(Sguidotag tag, bool end)
{
	int type = markers::opened (tag);
	if (type & markers::kOpenedBegin) {
		Sguidotag match = fOpenedTags[tag->getName()];
		if (match) {
			if (checkmatch (tag, match)) {
				if (end) {		// done with the current match
					markers::setMark (match, (markers::opened (match)==markers::kOpenedEnd) ? markers::kClosed : markers::kOpenedBegin);
					fOpenedTags[tag->getName()] = 0;
					fCurrentMatch = 0;
				}
				else {
					fCurrentMatch = tag;
					match->push (tag->elements());		// transfer elements to matched tag
					tag->clear();						// clears the current tag
				}
				return true;
			}
		}
	}
	return false;
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void seqOperation::visitStart ( Sguidotag& elt )
{
	switch (fState) {
		case kInFirstScore:
			clonevisitor::visitStart (elt);
			storeTag (elt);
			break;
		case kRemainVoice:			
		case kInSecondScore:			
			if (!matchOpenedTag (elt) && !currentTag(elt))
				clonevisitor::visitStart (elt);
			break;
	}
}

//________________________________________________________________________
void seqOperation::visitEnd	( Sguidotag& elt )
{
	switch (fState) {
		case kInFirstScore:			
			endTag (elt);
			clonevisitor::visitEnd (elt);
			break;
		case kRemainVoice:			
		case kInSecondScore:			
			if (!matchOpenedTag (elt, true) && !currentTag(elt))
				clonevisitor::visitEnd (elt);
			break;
	}
}


// notes are visited only for correct duration link
void seqOperation::visitStart ( SARNote& elt ) 
{ 
	bool done = false;
	rational duration = elt->duration();
	int octave = elt->GetOctave();

	if (fState == kInFirstScore) {
		// clear opened tags since only the last note is concerned
		fOpenedTags.clear();
		// maintain the current duration status while in the first score
		if (!ARNote::implicitDuration (duration))
			fCurrentDuration = duration;
		// maintain the current octave number while in the first score
		if (!ARNote::implicitOctave (octave))
			fCurrentOctave = octave;
	}
	else if (fState == kInSecondScore) {
		SARNote	note = copy (elt);
		push( note );
		done = true;

		if (fFirstInScore) {		// force implicit values in second score when unspecified
			 if (ARNote::implicitOctave (octave)) {
				note->SetOctave(ARNote::kDefaultOctave);
			}
			if ( ARNote::implicitDuration (duration) && (fCurrentDuration != ARNote::getDefaultDuration()) ) {
				*note = ARNote::getDefaultDuration();		// force explicit default duration
			}
			fFirstInScore = false;
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
		default:
			break;
	}
}

// a voice is created only for the first score
void seqOperation::visitStart ( SARVoice& elt ) 
{ 
	fCurrentOctave = ARNote::kDefaultOctave;
	switch (fState) {
		case kInFirstScore:	
		case kRemainVoice:			
			clonevisitor::visitStart (elt);
			break;
		default:
			break;
	}
}

// a voice is close only for the second score
void seqOperation::visitEnd   ( SARVoice& elt )
{ 
	switch (fState) {
		case kInSecondScore:			
		case kRemainVoice:			
			clonevisitor::visitEnd (elt);
			break;
		default:
			break;
	}
}



} // namespace
