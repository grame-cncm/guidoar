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

#include <iostream>

#include "clonevisitor.h"
#include "seqOperation.h"
#include "ARFactory.h"
#include "AROthers.h"


using namespace std;

namespace guido 
{

//_______________________________________________________________________________
void seqOperation::delEndBar(Sguidoelement elt)
{
	SARVoice v = dynamic_cast<ARVoice*>((guidoelement*)elt);
	if (v) {
		Sguidoelement& back = v->elements().back();
		if (back && (back->getName() == "endBar")) {
			v->elements().pop_back();
		}
	}
}

//_______________________________________________________________________________
SARMusic seqOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	SARMusic elt = ARFactory::instance().createMusic();
	if (elt) {
		clonevisitor cv;
		if (score1) {
			elt->push (cv.clone(score1)->elements());
		}
		if (score2) {
			Sguidoelement copy = cv.clone (score2);

			ctree<guidoelement>::const_literator i1 = elt->lbegin();
			ctree<guidoelement>::const_literator i2 = copy->lbegin();
			
			while ((i1 != elt->lend()) && (i2 != copy->lend())) {
				delEndBar(*i1);
				(*i1)->push((*i2)->elements());
				i1++;
				i2++;
			}
			while (i1 != elt->lend()) {
				delEndBar(*i1);
				i1++;
			}
			while (i2 != copy->lend()) {
				// score 2 has more voices than score 1: push the remaining voices
				elt->push (*i2);
				i2++;
			}
			
		}
	}
	return elt;
}


} // namespace
