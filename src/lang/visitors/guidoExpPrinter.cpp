/*
  GUIDO Library
  Copyright (C) 2008  Grame

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

#ifndef __guidoExpPrinter__
#define __guidoExpPrinter__

#include <iostream>

#include "guidoExpPrinter.h"
#include "guidoApplyExpr.h"
#include "guidoAbstractExpr.h"
#include "guidoCompExpr.h"
#include "guidoScoreExpr.h"
#include "tree_browser.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
// the visit methods
//______________________________________________________________________________
void guidoExpPrinter::visitStart (Sguidoexpression& exp) 
{
}

void guidoExpPrinter::visitStart (SguidoScoreExpr& exp) 
{
	if (fPendingOp && fPos) {
		fOut << fPendingOp << " "; 
		fPendingOp = 0;
	}
	else fPos++;
	fOut << exp->getScore() << endl;
}

void guidoExpPrinter::visitStart (SguidoCompExpr& exp) 
{
	fPendingOp = exp->getOpString();
	fPos = 0;
}

void guidoExpPrinter::visitStart (SguidoAbstractExpr& exp) 
{
	fPendingOp = ".";
	fPos = 0;
	fOut << "#";
}

void guidoExpPrinter::visitStart (SguidoApplExpr& exp) 
{
	fPendingOp = "@";
	fPos = 0;
}

} // namespace

#endif
