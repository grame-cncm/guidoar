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

#include "guidocomment.h"
#include "visitor.h"

using namespace std;

namespace guido
{

//______________________________________________________________________________
Sguidocomment guidocomment::create()
	{ guidocomment * o = new guidocomment; assert(o!=0); return o; }

//______________________________________________________________________________
void guidocomment::acceptIn(basevisitor& v) {
	if (visitor<Sguidocomment>* p = dynamic_cast<visitor<Sguidocomment>*>(&v)) {
		Sguidocomment ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidocomment::acceptOut(basevisitor& v) {
	if (visitor<Sguidocomment>* p = dynamic_cast<visitor<Sguidocomment>*>(&v)) {
		Sguidocomment ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
void guidocomment::print(std::ostream& os)
	{ os << getName(); }

//______________________________________________________________________________
const std::string guidocomment::trim () const {
	string str = getName();
    const char* WhiteSpace = " \t\v\r\n";
    std::size_t start = str.find_first_not_of(WhiteSpace);
    std::size_t end = str.find_last_not_of(WhiteSpace);
    return start == end ? std::string() : str.substr(start, end - start + 1);
}

} // namespace
