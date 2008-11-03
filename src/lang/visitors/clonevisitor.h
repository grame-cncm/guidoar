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

#ifndef __cloneVisitor__
#define __cloneVisitor__

#include <ostream>

#include "guidoExprTypes.h"
#include "visitor.h"

namespace guidolang
{

/*!
\addtogroup visitors
@{
*/

//______________________________________________________________________________
/*!
\brief	A visitor to print the gmn description
*/
class export clonevisitor :
	public guido::visitor<Sguidoexpression>,
	public guido::visitor<SguidoAbstractExpr>,
	public guido::visitor<SguidoScoreExpr>
{
    public:
				 clonevisitor() {}
       	virtual ~clonevisitor() {}
              
		virtual Sguidoexpression clone(const Sguidoexpression&);

	protected:		
		// the copy method may be used by derived classes to filter the elements
		virtual bool copy  () const	{ return true; }
		virtual void push	(const Sguidoexpression& exp, bool stack=true);

		virtual void visitStart ( Sguidoexpression&);
		virtual void visitEnd	( Sguidoexpression&);
		virtual void visitStart ( SguidoScoreExpr&);

		std::stack<Sguidoexpression> fStack;
};

/*! @} */

} // namespace

#endif
