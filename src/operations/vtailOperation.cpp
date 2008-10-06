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
#include "AROthers.h"
#include "ARTag.h"
#include "vtailOperation.h"

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
		fBrowser.stop(false);
		fBrowser.browse (*score);
		outscore = fStack.top();
		fStack.pop();
	}
	return outscore;
}

//_______________________________________________________________________________
SARMusic vtailOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	Sguidoelement elt = (*this)(score1, score2->size());
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//________________________________________________________________________
bool vtailOperation::copy  ()	{ return fCurrentVoice > fVoiceNum; }

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void vtailOperation::visitStart ( SARVoice& elt )
{
	fCurrentVoice++;
	if (copy())
		clonevisitor::visitStart (elt);
	else fBrowser.stop();
}

//________________________________________________________________________
void vtailOperation::visitEnd ( SARVoice& elt )
{
	fBrowser.stop(false);
	if (copy())
		clonevisitor::visitEnd (elt);
}

//________________________________________________________________________
void vtailOperation::visitStart ( SARStaff& elt )
{
// don't copy staff assignments
}

}
