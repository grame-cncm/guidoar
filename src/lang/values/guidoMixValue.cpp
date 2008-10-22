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
#include "visitor.h"

using namespace std;
using namespace guido;

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
	Sguidovalue v1 = fArg1->head(length);
	Sguidovalue v2 = fArg2->head(length);
	return guidoValFactory::instance().createMix(v1, v2);
}

Sguidovalue	guidoMixValue::head	(const rational& length)
{
	Sguidovalue v1 = fArg1->head(length);
	Sguidovalue v2 = fArg2->head(length);
	return guidoValFactory::instance().createMix(v1, v2);
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::tail	(unsigned int length)
{
	Sguidovalue v1 = fArg1->tail(length);
	Sguidovalue v2 = fArg2->tail(length);
	return guidoValFactory::instance().createMix(v1, v2);
}

Sguidovalue	guidoMixValue::tail	(const rational& length)
{
	Sguidovalue v1 = fArg1->tail(length);
	Sguidovalue v2 = fArg2->tail(length);
	return guidoValFactory::instance().createMix(v1, v2);
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::top (unsigned int vnum)
{
	unsigned int vcount = fArg1->voices();
	if (vnum > vcount) {
		Sguidovalue v2 = fArg2->top(vnum - vcount);
		return guidoValFactory::instance().createMix(fArg1, v2);
	}
	return fArg1->top(vnum);
}

Sguidovalue	guidoMixValue::bottom (unsigned int vnum)
{
	unsigned int vcount = fArg1->voices();
	if (vnum < vcount) {
		Sguidovalue v1 = fArg1->bottom(vnum);
		return guidoValFactory::instance().createMix(v1, fArg2);
	}
	return fArg2->bottom(vnum - vcount);
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::transpose(int interval)
{
	Sguidovalue v1 = fArg1->transpose(interval);
	Sguidovalue v2 = fArg2->transpose(interval);
	return guidoValFactory::instance().createMix(v1, v2);
}

//______________________________________________________________________________
Sguidovalue	guidoMixValue::stretch (rational ratio)
{
	Sguidovalue v1 = fArg1->stretch(ratio);
	Sguidovalue v2 = fArg2->stretch(ratio);
	return guidoValFactory::instance().createMix(v1, v2);
}

Sguidovalue	guidoMixValue::stretch (float ratio)
{
	Sguidovalue v1 = fArg1->stretch(ratio);
	Sguidovalue v2 = fArg2->stretch(ratio);
	return guidoValFactory::instance().createMix(v1, v2);
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
	return fArg1->pitch();
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
