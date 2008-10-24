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

#ifndef __guidoIdentExpr__
#define __guidoIdentExpr__

#include "guidoexpression.h"

namespace guidolang 
{

class guidoIdentExpr;
typedef guido::SMARTP<guidoIdentExpr> 	SguidoIdentExpr;

/*!
\brief abstraction expression.
*/
class export guidoIdentExpr : public guidoexpression
{
    protected:
		Sguidoexpression fExp;
		
				 guidoIdentExpr(Sguidoexpression e) : fExp(e) {}
		virtual ~guidoIdentExpr() {}

	public:		
        static SguidoIdentExpr create(Sguidoexpression e);
		
		virtual Sguidovalue eval(SguidoEnv env);
		virtual Sguidoexpression getIdent() const	{ return fExp; }

		virtual void		acceptIn(guido::basevisitor& visitor);
		virtual void		acceptOut(guido::basevisitor& visitor);

		virtual bool operator ==(const Sguidoexpression& i) const;
};

} // namespace

#endif
