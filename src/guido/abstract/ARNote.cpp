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

#include <sstream>
#include "ARNote.h"
#include "visitor.h"

using namespace std;

namespace guido 
{

//______________________________________________________________________________
ARNote::ARNote() 
	:	fOctave(kUndefined), fAccidental(0), 
		fDuration(kUndefined,4),
		fDots(0)
{
}

//______________________________________________________________________________
ARNote::pitch ARNote::GetPitch (bool& sharp) const
{
	string name = getName();
	sharp = false;
	if (name == "cis") { sharp = true; return C; }
	if (name == "dis") { sharp = true; return D; }
	if (name == "fis") { sharp = true; return F; }
	if (name == "gis") { sharp = true; return G; }
	if (name == "ais") { sharp = true; return A; }

	if (name == "do" || name == "c") return C;
	if (name == "re" || name == "d") return D;
	if (name == "mi" || name == "e") return E;
	if (name == "fa" || name == "f") return F;
	if (name == "sol" || name == "g") return G;
	if (name == "la" || name == "a") return A;
	if (name == "si" || name == "ti" || name == "b" || name == "h") return B;
	return kNoPitch;
}

//______________________________________________________________________________
ARNote& ARNote::operator =  (const rational& d)	{ fDuration  = d; fDuration.rationalise(); return *this; }
ARNote& ARNote::operator += (const rational& d)	{ fDuration += d; fDuration.rationalise(); return *this; }
ARNote& ARNote::operator *= (const rational& d)	{ fDuration *= d; fDuration.rationalise(); return *this; }
ARNote& ARNote::operator /= (const rational& d)	{ fDuration /= d; fDuration.rationalise(); return *this; }
ARNote& ARNote::operator -= (const rational& d)	{ fDuration -= d; fDuration.rationalise(); return *this; }

//______________________________________________________________________________
void ARNote::acceptIn(basevisitor& v) {
	if (visitor<SMARTP<ARNote> >* p = dynamic_cast<visitor<SMARTP<ARNote> >*>(&v)) {
		SMARTP<ARNote> sptr = this;
		p->visitStart(sptr);
	}
	else guidoelement::acceptIn(v);
}

//______________________________________________________________________________
void ARNote::acceptOut(basevisitor& v) {
	if (visitor<SMARTP<ARNote> >* p = dynamic_cast<visitor<SMARTP<ARNote> >*>(&v)) {
		SMARTP<ARNote> sptr = this;
		p->visitEnd(sptr);
	}
	else guidoelement::acceptOut(v);
}

//______________________________________________________________________________
ARNote::operator string() const {
    ostringstream str;

	str << getName();
	int n = GetAccidental();
	if (n) {
		char c = (n > 0) ? '#' : '&';
		n = abs(n);
		while (n--) str << c;
	}

	n = GetOctave();
	if (n != ARNote::kUndefined) str << n;

	n = fDuration.getNumerator();
	if (n != kUndefined) {
		if (n != 1)  str << '*' << n;
		n = fDuration.getDenominator();
		if (n > 0) str << '/' << n;
	}

	n = GetDots();
	while (n--) str << '.';

	return  str.str();
}

//______________________________________________________________________________
SMARTP<ARNote> ARNote::create()
    { ARNote* o = new ARNote(); assert(o!=0); return o; }

}
