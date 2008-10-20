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

#ifndef __guidoExpFactory__
#define __guidoExpFactory__

#include "guidoApplExpr.h"
#include "guidoAbstractExpr.h"
#include "guidoCompExpr.h"
#include "guidoScoreExpr.h"
#include "singleton.h"

namespace guidolang 
{

/*!
\brief A guido language expressions factory.
*/
class export guidoExpFactory : public singleton<guidoExpFactory>
{
    protected:
				 guidoExpFactory() {}
		virtual ~guidoExpFactory() {}

	public:
		SguidoApplExpr		createApplication(Sguidoexpression& e1, Sguidoexpression& e2) const;	
		SguidoAbstractExpr	createAbstraction(Sguidoexpression& e1, Sguidoexpression& e2) const;	
		SguidoCompExpr		createComposition(guidoCompExpr::composition op, Sguidoexpression& e1, Sguidoexpression& e2) const;	
		SguidoScoreExpr		createScore(guido::Sguidoelement& score) const;	
};

} // namespace

#endif
