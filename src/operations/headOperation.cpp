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
#include "ARFactory.h"
#include "ARChord.h"
#include "AROthers.h"
#include "ARTag.h"
#include "clonevisitor.h"
#include "headOperation.h"
#include "markers.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//_______________________________________________________________________________
SARMusic headOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	if (!score2) return 0;
	Sguidoelement elt = (*this)(score1, fDuration.duration(score2));
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//_______________________________________________________________________________
Sguidoelement headOperation::operator() ( const Sguidoelement& score, const rational& duration )
{
	fOpenedTagsMap.clear();
	fCutPoint = duration;
	Sguidoelement outscore;
	if (score) {
		fBrowser.browse (*score);
		outscore = fStack.top();
		fStack.pop();
	}
	return outscore;
}

//________________________________________________________________________
void headOperation::checkOpenedTags()
{
	for (map<std::string,Sguidotag>::iterator i = fOpenedTagsMap.begin(); i != fOpenedTagsMap.end(); i++) {
		Sguidotag tag = i->second;
		if (tag) {
			string name = i->first;
			size_t n = name.find("Begin", 0);
			if (n !=string::npos) {
				name.replace (n, name.length(), "End");
				Sguidotag endtag = ARFactory::instance().createTag(name);
				markers::markOpened (endtag);
				Sguidoelement endelt(endtag);
				if (endtag) push (endelt, false);
			}
			i->second = 0;
		}
	}
	fOpenedTagsMap.clear();

	for (map<std::string,Sguidotag>::iterator i = fRangeTagsMap.begin(); i != fRangeTagsMap.end(); i++) {
		Sguidotag tag = i->second;
		if (tag) markers::markOpened (tag, true);
	}
	fRangeTagsMap.clear();
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void headOperation::visitStart ( SARVoice& elt )
{
	fOpenedTagsMap.clear();
	fCurrentOctave = ARNote::kDefaultOctave;
	fCopy = (float(fCutPoint) > 0.001) ? true: false;
	fPopTie = false;
	clonevisitor::visitStart (elt);
	fDuration.visitStart (elt);
}

//________________________________________________________________________
void headOperation::visitStart ( SARChord& elt )
{
	rational remain = fCutPoint - fDuration.currentVoiceDate();
	rational dur = elt->totalduration(fDuration.currentNoteDuration(), fDuration.currentDots());
	if (float(remain) > 0) {
		if (remain < dur) {
			Sguidotag tag = ARTag<kTTie>::create();
			tag->setName ("tie");				// create a tie
			markers::markOpened (tag, true);	// mark the tie begin opened 
			Sguidoelement etag(tag);
			push(etag, true);					// push the tag to the current copy
			fPopTie = true;						// intended to pop the tie at the chord end
		}
		clonevisitor::visitStart (elt);
		fDuration.visitStart (elt);
	}
	else {
		fCopy = false;
		checkOpenedTags();		// and close any opened tag
	}
}

//________________________________________________________________________
void headOperation::visitStart ( SARNote& elt )
{
	rational remain = fCutPoint - fDuration.currentVoiceDate();
	bool tie = false;
	if (float(remain) > 0) {
		if (!elt->implicitOctave())
			fCurrentOctave = elt->GetOctave();
		rational currentDur = fDuration.currentNoteDuration();
		int currentDots = fDuration.currentDots();
		rational dur = elt->totalduration(currentDur, currentDots);
		if (dur > remain) {
			*elt = remain;
			elt->SetDots(0);
			tie = !fDuration.inChord();
		}

		if (tie) {		// notes splitted by the operation are marked using an opened tie
			Sguidotag tag = ARTag<kTTie>::create();
			tag->setName ("tie");
			markers::markOpened (tag, true);
			Sguidoelement etag(tag);
			if (elt->implicitOctave()) elt->SetOctave (fCurrentOctave);
			push(etag, true);
		}
		clonevisitor::visitStart (elt);
		fDuration.visitStart (elt);
	}
	else {
		fCopy = false;
		checkOpenedTags();		// and close any opened tag
	}
}

//________________________________________________________________________
void headOperation::visitStart ( Sguidotag& elt )
{
	rational remain = fCutPoint - fDuration.currentVoiceDate();
	if (float(remain) > 0) {
		clonevisitor::visitStart (elt);

		string name = elt->getName();
		if (elt->beginTag())
			fOpenedTagsMap[name] = elt;
		else if (elt->endTag())
			fOpenedTagsMap[elt->matchTag()] = 0;
		else if (elt->size()) {
			fRangeTagsMap[name] = dynamic_cast<guidotag*>((guidoelement*)fStack.top());
		}
	}
	else {
		fCopy = false;
		checkOpenedTags();		// and close any opened tag
	}
}

//________________________________________________________________________
void headOperation::visitEnd ( Sguidotag& elt )
{
	if (fCopy) {
		clonevisitor::visitEnd (elt);
		if (fPopTie) {
			fStack.pop();
			fPopTie = false;
		}
		if (elt->size())
			fRangeTagsMap[elt->getName()] = 0;
	}
}

//________________________________________________________________________
void headOperation::visitEnd ( SARChord& elt )
{
	if (fCopy) {
		clonevisitor::visitEnd (elt);
		fDuration.visitEnd (elt);
		if (fDuration.currentVoiceDate() >= fCutPoint) {
			fCopy = false;
			checkOpenedTags();
		}
	}
}

//________________________________________________________________________
void headOperation::visitEnd ( SARVoice& elt )
{
	clonevisitor::visitEnd (elt);
	// adjusts the stack
	// may be necessary due to potential end inside range tags
	while (fStack.size() > 1)
		fStack.pop();
}

}
