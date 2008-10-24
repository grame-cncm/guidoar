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

#ifndef __guidoExpReader__
#define __guidoExpReader__

#include <ostream>

#include "guidoexpression.h"
#include "smartpointer.h"
#include "visitor.h"

namespace guidolang 
{

class guidoexpression;
class guidoScoreExpr;
class guidoCompExpr;
class guidoAbstractExpr;
class guidoApplExpr;

typedef guido::SMARTP<guidoexpression>		Sguidoexpression;
typedef guido::SMARTP<guidoScoreExpr>		SguidoScoreExpr;
typedef guido::SMARTP<guidoCompExpr>		SguidoCompExpr;
typedef guido::SMARTP<guidoAbstractExpr>	SguidoAbstractExpr;
typedef guido::SMARTP<guidoApplExpr>		SguidoApplExpr;

//______________________________________________________________________________
/*!
\brief	An concrete class supporting the glang parser interface.
*/
class export guidoExpPrinter : 
	public guido::visitor<Sguidoexpression>,
	public guido::visitor<SguidoScoreExpr>,
	public guido::visitor<SguidoCompExpr>,
	public guido::visitor<SguidoAbstractExpr>,
	public guido::visitor<SguidoApplExpr>
{ 
	private:
		std::ostream& fOut;		///< the output stream 
		int			 fPos;		///< position inside a node
		const char * fPendingOp;

	public:
				 guidoExpPrinter(std::ostream& out) : fOut(out), fPendingOp(0) {}
		virtual ~guidoExpPrinter() {}

	protected:
		virtual void visitStart ( Sguidoexpression& tag );
		virtual void visitStart ( SguidoScoreExpr& tag );
		virtual void visitStart ( SguidoCompExpr& tag );
		virtual void visitStart ( SguidoAbstractExpr& tag );
		virtual void visitStart ( SguidoApplExpr& tag );
};

} // namespace

#endif