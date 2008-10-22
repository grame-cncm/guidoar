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
#include "guidoMixValue.h"
#include "guidoValFactory.h"

using namespace std;

namespace guidolang 
{

//______________________________________________________________________________
// guidoMixValue
//______________________________________________________________________________
Sguidovalue	guidoMixValue::create (Sguidovalue v1, Sguidovalue v2)
	{ guidoMixValue * o = new guidoMixValue(v1, v2); assert(o!=0); return o; }

//______________________________________________________________________________
Sguidovalue	guidoMixValue::head	(unsigned int length)
{
	return guidoValFactory.instance().createMix(head(fArg1,length), head(fArg2,length));
}

Sguidovalue	guidoMixValue::head	(const rational& length)
{
	return guidoValFactory.instance().createMix(head(fArg1,length), head(fArg2,length));
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::tail	(unsigned int length)
{
	return guidoValFactory.instance().createMix(tail(fArg1,length), tail(fArg2,length));
}

Sguidovalue	guidoMixValue::tail	(const rational& length)
{
	return guidoValFactory.instance().createMix(tail(fArg1,length), tail(fArg2,length));
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::top (unsigned int vnum)
{
	unsigned int vcount = fArg1.voices();
	if (vnum > vcount)
		return guidoValFactory.instance().createMix(fArg1, top(fArg2,vnum - vcount));
	return top(fArg1, vnum);
}

Sguidovalue	guidoMixValue::bottom (unsigned int vnum)
{
	unsigned int vcount = fArg1.voices();
	if (vnum < vcount)
		return guidoValFactory.instance().createMix(bottom(fArg1,vnum), fArg2);
	return bottom(fArg2, vnum - vcount);
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::transpose(int interval)
{
	return guidoValFactory.instance().createMix(transpose(fArg1, interval), transpose(fArg2, interval));
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::stretch (rational ratio)
{
	return guidoValFactory.instance().createMix(stretch(fArg1, ratio), stretch(fArg2, ratio));
}

Sguidovalue	guidoMixValue::stretch (float ratio)
{
	return guidoValFactory.instance().createMix(stretch(fArg1, ratio), stretch(fArg2, ratio));
}

//______________________________________________________________________________
unsigned int guidoMixValue::length () const
{
	unsigned int l1 = fArg1->length();
	if (l1 == kInfinite) return kInfinite;

	unsigned int l2 = fArg2->length();
	if (l2 == kInfinite) return kInfinite;

	return (l1 > l2) ? l1 : l2;
}

rational guidoMixValue::duration() const
{
	rational d1 = fArg1->duration();
	if (infinite(d1)) return d1;
	rational d2 = fArg2->duration();
	if (infinite(d2)) return d2;
	return (d1 > d2) ? d1 : d2;
}

unsigned int guidoMixValue::voices () const
{
	unsigned int v1 = fArg1->voices();
	if (v1 == kInfinite) return kInfinite;
	
	unsigned int v2 = fArg2->voices();
	if (v2 == kInfinite) return kInfinite;

	return v1 + v2;
}

unsigned int guidoMixValue::pitch () const
{
	return pitch(fArg1);
}

//______________________________________________________________________________
void guidoMixValue::acceptIn(basevisitor& v) {
	if (visitor<SguidoMixValue>* p = dynamic_cast<visitor<SguidoMixValue>*>(&v)) {
		SguidoMixValue ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidoMixValue::acceptOut(basevisitor& v) {
	if (visitor<SguidoMixValue>* p = dynamic_cast<visitor<SguidoMixValue>*>(&v)) {
		SguidoMixValue ge = this;
		p->visitEnd (ge);
	}
}

} // namespace
