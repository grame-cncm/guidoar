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
#include "exceptions.h"
#include "guidoIdentExpr.h"
#include "guidoEnv.h"
#include "guidovalue.h"

#include "visitor.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
// guidoIdentExpr
//______________________________________________________________________________
Sguidovalue guidoIdentExpr::eval(SguidoEnv env)
{
	if (!env) throw (newException (kNullEnvironment));
	Sguidovalue result = env->value(fExp);
	return result;
}

//______________________________________________________________________________
SguidoIdentExpr guidoIdentExpr::create(Sguidoexpression e)		
	{ guidoIdentExpr * o = new guidoIdentExpr(e); assert(o!=0); return o; }

//______________________________________________________________________________
void guidoIdentExpr::acceptIn(basevisitor& v) {
	if (visitor<SguidoIdentExpr>* p = dynamic_cast<visitor<SguidoIdentExpr>*>(&v)) {
		SguidoIdentExpr ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidoIdentExpr::acceptOut(basevisitor& v) {
	if (visitor<SguidoIdentExpr>* p = dynamic_cast<visitor<SguidoIdentExpr>*>(&v)) {
		SguidoIdentExpr ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
bool guidoIdentExpr::operator ==(const SguidoIdentExpr& elt) const { 
	return true;
}

} // namespace
