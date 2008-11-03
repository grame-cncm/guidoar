/*

  MusicXML Library
  Copyright (C) 2006,2007  Grame

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

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <iostream>

#include "guidoExpFactory.h"
#include "guidoexpression.h"
#include "guidoScoreExpr.h"
#include "clonevisitor.h"
#include "tree_browser.h"

using namespace std;
using namespace guido;

namespace guidolang 
{

//______________________________________________________________________________
Sguidoexpression clonevisitor::clone(const Sguidoexpression& exp)
{ 
	if (exp) {
		tree_browser<guidoexpression> tb(this);
		tb.browse (*exp);
		Sguidoexpression copy = fStack.top();
		fStack.pop();
		return copy;
	}
	return 0;
}

//______________________________________________________________________________
void clonevisitor::push( const Sguidoexpression& exp, bool stack )
{
	if (fStack.empty())
		fStack.push(exp);
	else fStack.top()->push(exp);
	if (stack) fStack.push (exp);	
}

//______________________________________________________________________________
// the visit methods
//______________________________________________________________________________
void clonevisitor::visitStart( Sguidoexpression& exp )
{
	if (copy()) push (guidoExpFactory::instance().create(exp->getName()));
}

//______________________________________________________________________________
void clonevisitor::visitStart( SguidoScoreExpr& exp )
{
	Sguidoelement score = exp->getScore();
	if (copy()) push ( guidoExpFactory::instance().create( score ));
}

//______________________________________________________________________________
void clonevisitor::visitEnd  ( Sguidoexpression& exp )
{ 
	if (copy()) fStack.pop(); 
}


}
