/*
  GUIDO Library
  Copyright (C) 2023 D.Fober

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
*/

#include <sstream>

#include "guidovariable.h"
#include "visitor.h"

using namespace std;

namespace guido
{

//______________________________________________________________________________
Sguidovariable guidovariable::create()
	{ guidovariable * o = new guidovariable; assert(o!=0); return o; }

//______________________________________________________________________________
void guidovariable::acceptIn(basevisitor& v) {
	if (visitor<Sguidovariable>* p = dynamic_cast<visitor<Sguidovariable>*>(&v)) {
		Sguidovariable ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidovariable::acceptOut(basevisitor& v) {
	if (visitor<Sguidovariable>* p = dynamic_cast<visitor<Sguidovariable>*>(&v)) {
		Sguidovariable ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
guidovariable::operator string() const {
    ostringstream str;
	str << getName();
	Sguidoattribute a = getAttribute(0);
	if (a) {
		const string quote = a->quoteVal() ? "\"" : "";
		str << "=" << quote << a->getValue() << quote << ";";
	}
	return str.str();
}

//______________________________________________________________________________
void guidovariable::print(std::ostream& os)
	{ os << string(*this); }

//______________________________________________________________________________
void guidovariable::setValue (const std::string& value, bool quote) {
	Sguidoattribute a = guidoattribute::create();
	a->setValue (value, quote);
	add (a);
}

//______________________________________________________________________________
const std::string guidovariable::getValue () const {
	Sguidoattribute a = getAttribute(0);
	if (a) return a->getValue();
	else cerr << "guidovariable::getValue: missing value" << endl;
	return "";
}

} // namespace
