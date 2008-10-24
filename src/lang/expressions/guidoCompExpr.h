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

#ifndef __guidoCompExpr__
#define __guidoCompExpr__

#include "guidoexpression.h"

namespace guidolang 
{

class guidoCompExpr;
typedef guido::SMARTP<guidoCompExpr> 	SguidoCompExpr;

/*!
\brief abstraction expression.
*/
class export guidoCompExpr : public guidoexpression
{
	public:
		enum composition { kSeqOp, kParOp, kHeadOp, kTailOp, kTopOp, kBottomOp };

    protected:
		static char*	fOpStrings[];		/// operations strings; must be in 'composition' order
		composition		fOperation;
		
				 guidoCompExpr(composition op, Sguidoexpression& e1, Sguidoexpression& e2);
		virtual ~guidoCompExpr() {}

	public:		
        static SguidoCompExpr create(composition op, Sguidoexpression& e1, Sguidoexpression& e2);
		
		virtual Sguidovalue eval(SguidoEnv env);

		virtual composition	getOperation() const		{ return fOperation; }
		virtual const char*	getOpString() const			{ return fOpStrings[fOperation]; }

		virtual void		acceptIn(guido::basevisitor& visitor);
		virtual void		acceptOut(guido::basevisitor& visitor);

		virtual bool operator ==(const Sguidoexpression& i) const;
};

} // namespace

#endif
