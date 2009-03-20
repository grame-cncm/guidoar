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
#pragma warning (disable : 4786)
#endif

#include <stdlib.h>
#include <sstream>
#include "ARNote.h"
#include "visitor.h"

using namespace std;

namespace guido 
{

std::map<std::string, std::pair<char, int> > ARNote::fNormalizeMap;

//______________________________________________________________________________
ARNote::ARNote() 
	:	fOctave(kUndefined), fAccidental(0), 
		fDots(0), fDuration(kUndefined,4)
		
{
	if (!fNormalizeMap.size()) {
		fNormalizeMap["c"]   = make_pair('c', 0);
		fNormalizeMap["d"]   = make_pair('d', 0);
		fNormalizeMap["e"]   = make_pair('e', 0);
		fNormalizeMap["f"]   = make_pair('f', 0);
		fNormalizeMap["g"]   = make_pair('g', 0);
		fNormalizeMap["a"]   = make_pair('a', 0);
		fNormalizeMap["b"]   = make_pair('b', 0);
		fNormalizeMap["h"]   = make_pair('b', 0);

		fNormalizeMap["do"]  = make_pair('c', 0);
		fNormalizeMap["re"]  = make_pair('d', 0);
		fNormalizeMap["mi"]  = make_pair('e', 0);
		fNormalizeMap["fa"]  = make_pair('f', 0);
		fNormalizeMap["sol"] = make_pair('g', 0);
		fNormalizeMap["la"]  = make_pair('a', 0);
		fNormalizeMap["si"]  = make_pair('b', 0);
		fNormalizeMap["ti"]  = make_pair('b', 0);

		fNormalizeMap["cis"] = make_pair('c', 1);
		fNormalizeMap["dis"] = make_pair('d', 1);
		fNormalizeMap["fis"] = make_pair('f', 1);
		fNormalizeMap["gis"] = make_pair('g', 1);
		fNormalizeMap["ais"] = make_pair('a', 1);
	}
}

//______________________________________________________________________________
void ARNote::NormalizedPitchName (char& name, int& alter) const
{
	pair<map<string, pair<char, int> >::const_iterator, map<string, pair<char, int> >::const_iterator>
	erp = fNormalizeMap.equal_range( getName() );
	if (erp.first == erp.second) {
		name = 0;
		alter = 0;
	}
	else {
		name = (*erp.first).second.first;
		alter = (*erp.first).second.second;
	}
}

//______________________________________________________________________________
ARNote::pitch ARNote::NormalizedName2Pitch	(char note)
{
	switch (note) {
		case 'a':	return A;
		case 'b':	return B;
		case 'c':	return C;
		case 'd':	return D;
		case 'e':	return E;
		case 'f':	return F;
		case 'g':	return G;
	}
	return kNoPitch;
}

//______________________________________________________________________________
ARNote::pitch ARNote::GetPitch (int& alter) const
{
	char npitch;
	NormalizedPitchName (npitch, alter);
	alter += GetAccidental();
	return NormalizedName2Pitch(npitch);
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
	if ((getName() != "_") && (getName() != "empty")) {
		int n = GetAccidental();
		if (n) {
			char c = (n > 0) ? '#' : '&';
			n = abs(n);
			while (n--) str << c;
		}

		n = GetOctave();
		if ( n != ARNote::kUndefined) str << n;
	}

	int n = fDuration.getNumerator();
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
