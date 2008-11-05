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
#include "guidoexpression.h"
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
	fPos = checkOp (fPos);
	fPendingOp.push(exp->getName().c_str());
//cout << "guidoExpPrinter::visitStart Sguidoexpression " << fPendingOp.top() << endl;
	fPos = 1;
}

//______________________________________________________________________________
void guidoExpPrinter::visitEnd (Sguidoexpression& exp)
{ 
//cout << "guidoExpPrinter::visitEnd Sguidoexpression " << fPendingOp.top() << " (" << exp->getType() << ")" << endl;
	fPendingOp.pop();
}

//______________________________________________________________________________
void guidoExpPrinter::visitStart( SguidoAbstractExpr& exp)
{
//cout << "guidoExpPrinter::visitStart SguidoAbstractExpr " << endl;
	fPos = checkOp (fPos);
	fOut << "#";
	fPendingOp.push(exp->getName().c_str());
	fPos = 1;
}


//______________________________________________________________________________
void guidoExpPrinter::visitEnd (SguidoAbstractExpr& exp)
{ 
//cout << "guidoExpPrinter::visitEnd SguidoAbstractExpr " << fPendingOp.top() << endl;
	fPendingOp.pop();
}


//______________________________________________________________________________
int guidoExpPrinter::checkOp (int pos) 
{
	if (fPendingOp.size() && !pos) {
		fOut << fPendingOp.top() << " "; 
	}
	return --pos;
}

//______________________________________________________________________________
void guidoExpPrinter::visitStart (SguidoScoreExpr& exp) 
{
//cout << "guidoExpPrinter::visitStart SguidoScoreExpr " << endl;
	fPos = checkOp (fPos);
	fOut << exp->getScore() << endl;
}


} // namespace

#endif
