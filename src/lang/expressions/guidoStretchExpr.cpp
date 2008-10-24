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
#include "guidoStretchExpr.h"
#include "guidoApplyValue.h"
#include "guidoEnv.h"
#include "visitor.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
// guidoStretchExpr
//______________________________________________________________________________
guidoStretchExpr::guidoStretchExpr(Sguidoexpression& exp1, Sguidoexpression& exp2)
{
	push(exp1);
	push(exp2);
}

//______________________________________________________________________________
SguidoStretchExpr guidoStretchExpr::create(Sguidoexpression& exp1, Sguidoexpression& exp2)		
	{ guidoStretchExpr * o = new guidoStretchExpr(exp1, exp2); assert(o!=0); return o; }

//______________________________________________________________________________
Sguidovalue guidoStretchExpr::eval(SguidoEnv env)
{
	evalPrint ("guidoStretchExpr");
	Sguidoexpression arg1 = getArg(0);
	Sguidoexpression arg2 = getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	Sguidovalue earg1 = arg1->eval(env);
	Sguidovalue earg2 = arg2->eval(env);
	if (!earg1 || earg2) throw (newException (kNullValue));
	
	rational dur = earg2->duration() - earg1->duration();
	return earg1->stretch(dur.rationalise());
}

//______________________________________________________________________________
void guidoStretchExpr::acceptIn(basevisitor& v) {
	if (visitor<SguidoStretchExpr>* p = dynamic_cast<visitor<SguidoStretchExpr>*>(&v)) {
		SguidoStretchExpr ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidoStretchExpr::acceptOut(basevisitor& v) {
	if (visitor<SguidoStretchExpr>* p = dynamic_cast<visitor<SguidoStretchExpr>*>(&v)) {
		SguidoStretchExpr ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
bool guidoStretchExpr::operator ==(const Sguidoexpression& elt) const 
{ 
	if (!dynamic_cast<guidoStretchExpr*>((guidoexpression*)elt)) return false;

	Sguidoexpression arg1 = getArg(0);
	Sguidoexpression arg2 = getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	Sguidoexpression elt1 = elt->getArg(0);
	Sguidoexpression elt2 = elt->getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	return (arg1 == elt1) && (arg2 == elt2);
}

} // namespace
