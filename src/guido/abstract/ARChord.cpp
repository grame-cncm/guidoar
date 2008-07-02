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

#include "ARChord.h"
//#include "durationvisitor.h"
//#include "targetvisitor.h"
#include "ARNote.h"
#include "ARTypes.h"
#include "functor.h"
#include "visitor.h"

using namespace std;

namespace guido 
{

//______________________________________________________________________________
/*
class durationfunctor : public functor<void, SARNote> {
	protected:
		rational fDuration;
	public:
		durationfunctor(const rational& d) : fDuration(d) {}
};

#define opclass(name,op) class name : public durationfunctor { \
	public: \
		name(const rational& d) : durationfunctor(d) {} \
		void operator ()(SARNote note) { (*note) op fDuration; } }

opclass (equal, =);
opclass (plusequal,  +=);
opclass (minusequal, -=);
opclass (multequal,  *=);
opclass (divequal,   /=);
*/

//______________________________________________________________________________
//
//   ARChord
//______________________________________________________________________________
void ARChord::duration(rationals& dur) {
//	chorddurationvisitor v(dur);
//	SARChord c(this);
//	v.startvisit(c);
}

//______________________________________________________________________________
void ARChord::acceptIn(basevisitor& v) {
	if (visitor<SMARTP<ARChord> >* p = dynamic_cast<visitor<SMARTP<ARChord> >*>(&v)) {
		SMARTP<ARChord> sptr = this;
		p->visitStart(sptr);
	}
	else guidoelement::acceptIn(v);
}

//______________________________________________________________________________
void ARChord::acceptOut(basevisitor& v) {
	if (visitor<SMARTP<ARChord> >* p = dynamic_cast<visitor<SMARTP<ARChord> >*>(&v)) {
		SMARTP<ARChord> sptr = this;
		p->visitEnd(sptr);
	}
	else guidoelement::acceptOut(v);
}

//______________________________________________________________________________
SMARTP<ARChord> ARChord::create()
    { ARChord* o = new ARChord; assert(o!=0); return o; }

/*
#define apply(op,d)  \
	op f(d); \
	TargetVisitor<SARNote> v(f); \
	Sguidoelement g(this); \
	v.startvisit(g)

ARChord& ARChord::operator =  (const rational& d)	{ apply(equal, d); return *this;  }
ARChord& ARChord::operator +=  (const rational& d)	{ apply(plusequal, d); return *this;  }
ARChord& ARChord::operator -=  (const rational& d)	{ apply(minusequal, d); return *this;  }
ARChord& ARChord::operator *=  (const rational& d)	{ apply(multequal, d); return *this;  }
ARChord& ARChord::operator /=  (const rational& d)	{ apply(divequal, d); return *this;  }
*/

} // namespace
