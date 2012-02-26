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
#include "AROthers.h"
#include "ARTag.h"
#include "clonevisitor.h"
#include "headOperation.h"
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
	map<std::string,int>::iterator i;
	for (i = fOpenedTagsMap.begin(); i != fOpenedTagsMap.end(); i++) {
		if (i->second) {
			string name = i->first;
			size_t n = name.find("Begin", 0);
			if (n !=string::npos) {
				name.replace (n, name.length(), "End");
				Sguidoelement tag = ARFactory::instance().createTag(name);
				if (tag) push (tag, false);
			}
			i->second = 0;
		}
	}
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void headOperation::visitStart ( SARVoice& elt )
{
	fOpenedTagsMap.clear();
	fCopy = (float(fCutPoint) > 0.001) ? true: false;
	clonevisitor::visitStart (elt);
	if (fCopy) fDuration.visitStart (elt);
}

//________________________________________________________________________
void headOperation::visitStart ( SARChord& elt )
{
	if (fCopy) {
		clonevisitor::visitStart (elt);
		fDuration.visitStart (elt);
	}
}

//________________________________________________________________________
void headOperation::visitStart ( SARNote& elt )
{
	rational remain = fCutPoint - fDuration.currentVoiceDate();
	if (float(remain) > 0) {
		rational dur = elt->duration();
		if (ARNote::implicitDuration (dur)) {
			dur = fDuration.currentNoteDuration();
			*elt = remain;		
		}
		else {
			rational excess = remain - dur;
			excess.rationalise();
			if (float(excess) < 0) {
				*elt += excess;
			}
		}
		clonevisitor::visitStart (elt);
		fDuration.visitStart (elt);
	}
	else fBrowser.stop();
//	if (fCopy) {
//		clonevisitor::visitStart (elt);
//		fDuration.visitStart (elt);
//	}
}

//________________________________________________________________________
void headOperation::visitStart ( Sguidotag& elt )
{
	if (fCopy) {
		clonevisitor::visitStart (elt);

		string name = elt->getName();
		if (elt->beginTag())
			fOpenedTagsMap[name] += 1;
		else if (elt->endTag()) {
			fOpenedTagsMap[elt->matchTag()] -= 1;
		}
	}
}

//________________________________________________________________________
void headOperation::visitEnd ( SARNote& elt )
{
	if (fCopy && (fDuration.currentVoiceDate() >= fCutPoint)) {
		rational remain = fCutPoint - fDuration.currentVoiceDate();
		fCopy = false;
		checkOpenedTags();
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

//________________________________________________________________________
void headOperation::visitEnd ( Sguidotag& elt )
{
	if (fCopy) {
		clonevisitor::visitEnd (elt);
	}
}

}
