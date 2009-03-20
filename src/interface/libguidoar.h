/*

  guidoar Library
  Copyright (C) 2008-2009  Grame

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

#ifdef VC6
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <string>
#include <stdio.h>
#include "rational.h"
#include "export.h"

namespace guido 
{
enum garErr { kNoErr, kInvalidFile, kInvalidArgument, kOperationFailed };

export int				guidoarVersion();
export const char*		guidoarVersionStr();

//--------------------------------------------------------------------------------
// operations on scores
//--------------------------------------------------------------------------------
export garErr			guido2unrolled	(const char* gmn, std::ostream& out);

export garErr			guidoTranpose	(const char* gmn, int interval, std::ostream& out);
export garErr			guidoTranpose	(const char* gmn, const char* gmnSpec, std::ostream& out);

export garErr			guidoBottom		(const char* gmn, int nvoices, std::ostream& out);
export garErr			guidoBottom		(const char* gmn, const char* gmnSpec, std::ostream& out);

export garErr			guidoSetDuration(const char* gmn, const char* gmnSpec, std::ostream& out);
export garErr			guidoSetDuration(const char* gmn, const rational& duration, std::ostream& out);
export garErr			guidoMultDuration(const char* gmn, float duration, std::ostream& out);

export rational			guidoEv2Time(const char* gmn, unsigned int index, unsigned int voice);

//--------------------------------------------------------------------------------
// tools
//--------------------------------------------------------------------------------
export char *			guidoread	    (const char* file);
export char *			guidoread	    (FILE* fd);

}
