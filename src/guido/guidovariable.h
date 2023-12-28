/*
  GUIDO Library
  Copyright (C) 2023 D.Fober

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
*/

#pragma once

#include "guidoelement.h"

namespace guido 
{

class guidovariable;

typedef SMARTP<guidovariable> 	Sguidovariable;

/*
\brief A guido variable representation.
*/
class gar_export guidovariable : public guidoelement
{
    protected:
				 guidovariable() {}
		virtual ~guidovariable() {}

	public:
        static Sguidovariable create();
		operator std::string () const;

		virtual void		acceptIn(basevisitor& visitor);
		virtual void		acceptOut(basevisitor& visitor);
		virtual	void		print(std::ostream& os);

		void				setValue (const std::string& value, bool quote);
		const std::string	getValue () const;

};

} // namespace
