/*
  GUIDO Library
  Copyright (C) 2006-2008  Grame

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
#include "guidoEval.h"
#include "guidoexpression.h"
#include "guidoApplyValue.h"
#include "guidoClosureValue.h"
#include "guidoMixValue.h"
#include "guidoScoreExpr.h"
#include "guidoScoreValue.h"
#include "guidoSeqValue.h"

using namespace std;

#ifdef evalDebug
#define evalPrint(expr)	cout << "eval \"" << expr << "\"" << endl
#else
#define evalPrint(expr)
#endif

namespace guidolang 
{

//______________________________________________________________________________
Sguidovalue guidoEval::eval(Sguidoexpression e, SguidoEnv env) 
{
	fEnv = env;
	fValue = 0;
	e->acceptIn(*this);
	return fValue;
}

//______________________________________________________________________________
void guidoEval::evalBinary( Sguidoexpression exp, Sguidovalue& v1, Sguidovalue& v2)
{
	evalPrint (exp->getName());
	Sguidoexpression arg1 = exp->getArg(0);
	Sguidoexpression arg2 = exp->getArg(1);
	if (!arg1 || !arg2) throw (newException (kMissingArgument));

	guidoEval earg;
	v1 = earg.eval(arg1, fEnv);
	v2 = earg.eval(arg2, fEnv);
	if (!v1 || !v2) throw (newException (kNullValue));
}

//______________________________________________________________________________
// the visit methods
//______________________________________________________________________________
void guidoEval::visitStart( Sguidoexpression)
{
	cerr << __FILE__ << ": unexpected Sguidoexpression received for evaluation" << endl;
}

void guidoEval::visitStart( SguidoAbstractExpr exp)
{
	evalPrint (exp->getName());
	Sguidoexpression id = exp->getArg(0);
	Sguidoexpression body = exp->getArg(1);
	if (!id || !body) throw (newException (kMissingArgument));

	SguidoEnv empty = guidoEnv::create();
	guidoEval eval;
	Sguidovalue valId = eval.eval(id, empty);
	if (!valId) throw (newException (kNullValue));
	fEnv->bind (id, valId);

	Sguidovalue valBody = eval.eval(body, fEnv);
	if (!valBody) throw (newException (kNullValue));
	
	unsigned int length = valBody->length();
	rational dur = valBody->duration();
	unsigned int voices = valBody->voices();
	fValue = guidoClosureValue::create(id, body, fEnv, length, dur, voices);
}

void guidoEval::visitStart( SguidoApplyExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = guidoApplyValue::create(earg1, earg2);
}

void guidoEval::visitStart( SguidoTranspExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	int interval = earg2->pitch() - earg1->pitch();
	fValue = earg1->transpose(interval);
}

void guidoEval::visitStart( SguidoStretchExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	rational dur = earg2->duration() - earg1->duration();
	fValue = earg1->stretch(dur.rationalise());
}

void guidoEval::visitStart( SguidoSeqExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = guidoSeqValue::create(earg1, earg2);
}

void guidoEval::visitStart( SguidoParExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = guidoMixValue::create(earg1, earg2);
}

void guidoEval::visitStart( SguidoHeadExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = earg1->head(earg2->length());
}

void guidoEval::visitStart( SguidoTailExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = earg1->tail(earg2->length());
}

void guidoEval::visitStart( SguidoTopExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = earg1->top(earg2->length());
}

void guidoEval::visitStart( SguidoBottomExpr exp)
{
	evalPrint (exp->getName());
	Sguidovalue earg1, earg2;
	evalBinary (exp, earg1, earg2);
	fValue = earg1->bottom(earg2->length());
}

void guidoEval::visitStart( SguidoIdentExpr exp)
{
	evalPrint (exp->getName());
	Sguidoexpression e = exp->getArg(0);
	if (!e) throw (newException (kMissingArgument));
	if (!fEnv) throw (newException (kNullEnvironment));
	fValue = fEnv->value(e);
}

void guidoEval::visitStart( SguidoScoreExpr exp)
{
	evalPrint (exp->getName());
	fValue = guidoScoreValue::create (exp->getScore());
}

} // namespace

