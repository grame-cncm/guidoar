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

#ifndef __AROthers__
#define __AROthers__

#include "arexport.h"
#include "guidoelement.h"
#include "guidovariable.h"

namespace guido 
{

/*!
\addtogroup abstract
@{
*/

class basevisitor;
//______________________________________________________________________________
/*!
\brief The root element of a Guido tree
*/
class gar_export ARMusic : public guidoelement
{
	public:
		typedef std::vector<Sguidoelement> THeader;
		typedef std::vector<Sguidoelement> TFooter;
	
		static SMARTP<ARMusic> create();
        virtual void	acceptIn(basevisitor& v);
        virtual void	acceptOut(basevisitor& v);
		virtual void	setHeader (THeader& header)		{ fHeader = header; }
		virtual void	addHeader (Sguidoelement elt)	{ fHeader.push_back(elt); }
		virtual THeader	getHeader () const				{ return fHeader; }
		virtual void	addFooter (Sguidoelement elt)	{ fFooter.push_back(elt); }
		virtual TFooter	getFooter () const				{ return fFooter; }

    protected:
				 ARMusic() {}
		virtual ~ARMusic() {}
		THeader fHeader;
		TFooter fFooter;
};

//______________________________________________________________________________
/*!
\brief A Guido voice
*/
class gar_export ARVoice : public guidoelement
{ 
	public:
		typedef std::vector<Sguidoelement> TComments;

		static SMARTP<ARVoice> create();
        virtual void	acceptIn(basevisitor& v);
        virtual void	acceptOut(basevisitor& v);
		virtual void		addBefore(Sguidoelement elt){ fBefore.push_back(elt); }
		virtual TComments	getBefore () const			{ return fBefore; }
		virtual void		addAfter (Sguidoelement elt){ fAfter.push_back(elt); }
		virtual TComments	getAfter () const			{ return fAfter; }

    protected:	
				 ARVoice() {}
		virtual ~ARVoice() {}
		TComments fBefore;
		TComments fAfter;
};

/*! @} */

} // namespace

#endif
