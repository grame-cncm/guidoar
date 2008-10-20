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

#ifndef __guidoexpression__
#define __guidoexpression__

#include "export.h"
#include "visitable.h"
#include "ctree.h"
#include "smartpointer.h"

namespace guidolang 
{

class guidoexpression;
typedef guido::SMARTP<guidoexpression> 	Sguidoexpression;


/*!
\brief The base class for guido language expressions.
*/
class export guidoexpression : public guido::ctree<guidoexpression>, public guido::visitable
{
    protected:
				 guidoexpression() {}
		virtual ~guidoexpression() {}

	public:
        static Sguidoexpression create();

		virtual void		acceptIn(guido::basevisitor& visitor);
		virtual void		acceptOut(guido::basevisitor& visitor);
		virtual	void		print(std::ostream& os);

		//________________________________________________________________________
		virtual bool operator ==(const Sguidoexpression& i) const;
		virtual bool operator !=(const Sguidoexpression& i) const		{ return !(*this == i); }
};

export std::ostream& operator << (std::ostream& os, const Sguidoexpression& elt);

} // namespace

#endif
