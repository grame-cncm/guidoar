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
#include "durationvisitor.h"
#include "parOperation.h"
#include "ARFactory.h"
#include "ARNote.h"
#include "AROthers.h"
#include "tree_browser.h"


using namespace std;

namespace guido 
{

//_______________________________________________________________________________
class firstnotechecker : public visitor<SARNote>
{
    public: firstnotechecker() {}
		void check(const Sguidoelement&);
	protected:
		void visitStart( SARNote& elt );
		bool fDone;
};
void firstnotechecker::check(const Sguidoelement& elt)
{
	fDone = false;
	if (elt) {
		tree_browser<guidoelement> tb(this);
		tb.browse (*elt);
	}
}

void firstnotechecker::visitStart(SARNote& elt)
{
	if (!fDone) {
		rational d = elt->duration();
		if (d.getNumerator() == ARNote::kUndefined)
			*elt = rational(1,4);
		fDone = true;
	}
}

//_______________________________________________________________________________
void parOperation::staffOffset(Sguidoelement elt, unsigned int offset)
{
	if (!offset) return;

	SARVoice v = dynamic_cast<ARVoice*>((guidoelement*)elt);
	if (v) {
		for (ctree<guidoelement>::literator i = v->lbegin(); i != v->lend(); i++) {
			if ((*i)->getName() == "staff") {
				Sguidoattributes attrs = (*i)->attributes();
				long int val = (int)(*attrs.front()) + offset;
				attrs.front()->setValue(val);				
			}
		}
	}	
}

//_______________________________________________________________________________
SARMusic parOperation::extend ( SARMusic& score, const rational& duration )
{
	durationvisitor dv;
	rational total = dv.duration (score);
	for (ctree<guidoelement>::literator i = score->lbegin(); i != score->lend(); i++) {		
		firstnotechecker fnc; 
		fnc.check(*i);			// check for first note implicit duration and force to default

		rational vdur = dv.duration(*i);
		SARNote note = ARFactory::instance().createNote("_");
		*note = duration + total - vdur;
		(*i)->elements().insert((*i)->elements().begin(), note);
	}
	return score;
}

//_______________________________________________________________________________
SARMusic parOperation::parallel ( const SARMusic& score1, const SARMusic& score2 )
{
	SARMusic elt = ARFactory::instance().createMusic();
	if (elt) {
		unsigned int offset = 0;
		if (score1) {
			elt->push (score1->elements());
			offset = score1->elements().size();
		}
		if (score2) {
			for (ctree<guidoelement>::literator i = score2->lbegin(); i != score2->lend(); i++) {
				elt->push (*i);
				staffOffset (*i, offset);
			}
		}
	}
	return elt;
}

//_______________________________________________________________________________
SARMusic parOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	clonevisitor cv;
	SARMusic cs1 = dynamic_cast<ARMusic*>((guidoelement*)cv.clone(score1));
	SARMusic cs2 = dynamic_cast<ARMusic*>((guidoelement*)cv.clone(score2));
	if (fMode == kLeft) 
		return parallel (cs1, cs2);
	else {
		durationvisitor dv;
		rational d1 = dv.duration(cs1);
		rational d2 = dv.duration(cs2);
		if (d1 > d2)
			cs2 = extend (cs2, d1-d2);
		else if (d1 < d2)
			cs1 = extend (cs1, d2-d1);
		return parallel (cs1, cs2);
	}
}


} // namespace
