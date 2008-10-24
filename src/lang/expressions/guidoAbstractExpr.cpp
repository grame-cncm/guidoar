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
#include "guidoAbstractExpr.h"
#include "guidoClosureValue.h"
#include "guidoEnv.h"
#include "visitor.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
// guidoAbstractExpr
//______________________________________________________________________________
guidoAbstractExpr::guidoAbstractExpr(Sguidoexpression& var, Sguidoexpression& exp)
{
	push(var);	
	push(exp);
}

//______________________________________________________________________________
Sguidovalue guidoAbstractExpr::eval(SguidoEnv env)
{
	evalPrint ("guidoAbstractExpr");
	Sguidoexpression id = getArg(0);
	Sguidoexpression body = getArg(1);
	if (!id || !body) throw (newException (kMissingArgument));

	SguidoEnv empty = guidoEnv::create();
	Sguidovalue valId = id->eval(empty);
	if (!valId) throw (newException (kNullValue));
	env->bind (id, valId);

	Sguidovalue valBody = body->eval(env);
	if (!valBody) throw (newException (kNullValue));
	
	unsigned int length = valBody->length();
	rational dur = valBody->duration();
	unsigned int voices = valBody->voices();
	return guidoClosureValue::create(id, body, env, length, dur, voices);
}

//______________________________________________________________________________
SguidoAbstractExpr guidoAbstractExpr::create(Sguidoexpression& var, Sguidoexpression& exp)		
	{ guidoAbstractExpr * o = new guidoAbstractExpr(var, exp); assert(o!=0); return o; }

//______________________________________________________________________________
void guidoAbstractExpr::acceptIn(basevisitor& v) {
	if (visitor<SguidoAbstractExpr>* p = dynamic_cast<visitor<SguidoAbstractExpr>*>(&v)) {
		SguidoAbstractExpr ge = this;
		p->visitStart (ge);
	}
}

//______________________________________________________________________________
void guidoAbstractExpr::acceptOut(basevisitor& v) {
	if (visitor<SguidoAbstractExpr>* p = dynamic_cast<visitor<SguidoAbstractExpr>*>(&v)) {
		SguidoAbstractExpr ge = this;
		p->visitEnd (ge);
	}
}

//______________________________________________________________________________
bool guidoAbstractExpr::operator ==(const Sguidoexpression& elt) const 
{ 
	if (!dynamic_cast<guidoAbstractExpr*>((guidoexpression*)elt)) return false;

	Sguidoexpression arg1 = getArg(0);
	Sguidoexpression arg2 = getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	Sguidoexpression elt1 = elt->getArg(0);
	Sguidoexpression elt2 = elt->getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	return (arg1 == elt1) && (arg2 == elt2);
}

} // namespace
