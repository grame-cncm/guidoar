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
#include "guidoApplyExpr.h"
#include "guidoApplyValue.h"
#include "guidoEnv.h"
#include "visitor.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
// guidoApplyExpr
//______________________________________________________________________________
guidoApplyExpr::guidoApplyExpr(Sguidoexpression& exp, Sguidoexpression& arg)
{
	push(exp);
	push(arg);	
}

//______________________________________________________________________________
Sguidovalue guidoApplyExpr::eval(SguidoEnv env)
{
	Sguidoexpression arg1 = getArg(0);
	Sguidoexpression arg2 = getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	Sguidovalue earg1 = arg1->eval(env);
	Sguidovalue earg2 = arg2->eval(env);
	if (!earg1 || !earg2) throw (newException (kNullValue));

	return guidoApplyValue::create(earg1, earg2);
}

//______________________________________________________________________________
SguidoApplyExpr guidoApplyExpr::create(Sguidoexpression& exp, Sguidoexpression& arg)		
	{ guidoApplyExpr * o = new guidoApplyExpr(exp, arg); assert(o!=0); return o; }

//______________________________________________________________________________
void guidoApplyExpr::acceptIn(basevisitor& v) {
	if (visitor<SguidoApplyExpr>* p = dynamic_cast<visitor<SguidoApplyExpr>*>(&v)) {
		SguidoApplyExpr ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidoApplyExpr::acceptOut(basevisitor& v) {
	if (visitor<SguidoApplyExpr>* p = dynamic_cast<visitor<SguidoApplyExpr>*>(&v)) {
		SguidoApplyExpr ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
bool guidoApplyExpr::operator ==(const SguidoApplyExpr& elt) const { 
	return true;
}

} // namespace
