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

#include "ARFactory.h"
#include "ARTag.h"
#include "vtailOperation.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//_______________________________________________________________________________
Sguidoelement vtailOperation::operator() ( const Sguidoelement& score, int voicenum )
{
	fVoiceNum = voicenum;
	fCurrentVoice = 0;
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
// The visit methods
//________________________________________________________________________
void vtailOperation::visitStart ( SARVoice& elt )
{
	fCurrentVoice++;
	if (fCurrentVoice > fVoiceNum)
		clonevisitor::visitStart (elt);
}

//________________________________________________________________________
void vtailOperation::visitStart ( SARStaff& elt )
{
// don't copy staff assignments
/*
	if (fCurrentVoice > fVoiceNum) {
		long staffNum = elt->getAttributeLongValue(0,9999);
		Sguidoelement copy = ARFactory::instance().createTag(elt->getName());
		Sguidoattribute attr = guidoattribute::create();
		attr->setValue( (staffNum > fCurrentVoice) ? fCurrentVoice : staffNum);
		copy->add(attr);
		push( copy, false );
	}
*/
}

//________________________________________________________________________
void vtailOperation::visitStart ( SARChord& elt )
{
	if (fCurrentVoice > fVoiceNum)
		clonevisitor::visitStart (elt);
}

//________________________________________________________________________
void vtailOperation::visitStart ( SARNote& elt )
{
	if (fCurrentVoice > fVoiceNum)
		clonevisitor::visitStart (elt);
}

//________________________________________________________________________
void vtailOperation::visitStart ( Sguidotag& elt )
{
	if (fCurrentVoice > fVoiceNum)
		clonevisitor::visitStart (elt);
}

//________________________________________________________________________
void vtailOperation::visitEnd ( SARVoice& elt )
{
	if (fCurrentVoice > fVoiceNum) clonevisitor::visitEnd (elt);
}

//________________________________________________________________________
void vtailOperation::visitEnd ( SARChord& elt )
{
	if (fCurrentVoice > fVoiceNum) clonevisitor::visitEnd (elt);
}

//________________________________________________________________________
void vtailOperation::visitEnd ( Sguidotag& elt )
{
	if (fCurrentVoice > fVoiceNum) clonevisitor::visitEnd (elt);
}

}
