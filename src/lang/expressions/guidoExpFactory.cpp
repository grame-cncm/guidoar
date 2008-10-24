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

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>

#include "guidoExpFactory.h"

#include "guidoexpression.h"
#include "guidoApplyExpr.h"
#include "guidoAbstractExpr.h"
#include "guidoCompExpr.h"
#include "guidoScoreExpr.h"

using namespace std; 
using namespace guido; 

namespace guidolang
{

//______________________________________________________________________________
template<int elt>
class newNodeFunctor : public rfunctor<Sguidoexpression> {
	public:
		Sguidoexpression operator ()() { return guidolnode<elt>::create(); }
};

//______________________________________________________________________________
guidoExpFactory::guidoExpFactory()
{
	fMap["lambda"]		= new newNodeFunctor<guidoexpression::kTAbstract>;
	fMap["apply"]		= new newNodeFunctor<guidoexpression::kTApply>;
	fMap["transp"]		= new newNodeFunctor<guidoexpression::kTTransp>;
	fMap["stretch"]		= new newNodeFunctor<guidoexpression::kTStretch>;
	fMap["compose"]		= new newNodeFunctor<guidoexpression::kTCompOp>;
	fMap["ident"]		= new newNodeFunctor<guidoexpression::kTIdent>;
}

//______________________________________________________________________________
Sguidoexpression guidoExpFactory::create(const string& name) const
{
	map<std::string, NewNodeFunctor*>::const_iterator i = fMap.find( name );
	if (i != fMap.end()) {
		NewNodeFunctor* f= i->second;
		if (f) {
			Sguidoexpression elt = (*f)();
			return elt;
		}
	}
	cerr << "Sguidoexpression factory::create called with unknown expression name \"" << name << "\"" << endl;
	return 0;
}

//______________________________________________________________________________
SguidoScoreExpr guidoExpFactory::create(guido::Sguidoelement& score) const
{
	SguidoScoreExpr expr = guidoScoreExpr::create(score);
	return expr;
}

/*
//______________________________________________________________________________
SguidoApplyExpr guidoExpFactory::createApplication(Sguidoexpression& e1, Sguidoexpression& e2) const
{
	SguidoApplyExpr expr = guidoApplyExpr::create(e1, e2);
	return expr;
}

//______________________________________________________________________________
SguidoAbstractExpr guidoExpFactory::createAbstraction(Sguidoexpression& e1, Sguidoexpression& e2) const
{
	SguidoAbstractExpr expr = guidoAbstractExpr::create(e1, e2);
	return expr;
}

//______________________________________________________________________________
SguidoCompExpr guidoExpFactory::createComposition(guidoCompExpr::composition op, Sguidoexpression& e1, Sguidoexpression& e2) const
{
	SguidoCompExpr expr = guidoCompExpr::create(op, e1, e2);
	return expr;
}

//______________________________________________________________________________
SguidoScoreExpr guidoExpFactory::createScore(guido::Sguidoelement& score) const
{
	SguidoScoreExpr expr = guidoScoreExpr::create(score);
	return expr;
}
*/

} // namespace
