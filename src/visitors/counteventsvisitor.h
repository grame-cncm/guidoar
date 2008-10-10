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

#ifndef __countEventsVisitor__
#define __countEventsVisitor__

#include <vector>

#include "export.h"
#include "guidoelement.h"
#include "ARTypes.h"
#include "visitor.h"

namespace guido 
{

/*!
\addtogroup visitors
@{
*/

//_______________________________________________________________________________
/*!
\brief  a visitor to count the number of notes and chords.
		A chord counts for 1 and notes inside a chord are ignored.
*/
class export counteventsvisitor :
	public visitor<SARNote>,
	public visitor<SARChord>
{
    public: 
				 counteventsvisitor() {}
		virtual ~counteventsvisitor() {}

		int count (const Sguidoelement&);
		int currentCount () const		{ return fCount; }

		virtual void reset()	{ fCount=0; fInChord=false; }

		virtual void visitStart( SARNote& elt );
		virtual void visitStart( SARChord& elt );
		virtual void visitEnd  ( SARChord& elt );

	protected:
		bool	fInChord;
		int		fCount;
};

//_______________________________________________________________________________
/*!
\brief  a visitor to count the number of notes and chords per voice.
*/
class export countvoiceseventsvisitor : 
	public counteventsvisitor,
	public visitor<SARVoice>
{
    public: 
				 countvoiceseventsvisitor() {}
		virtual ~countvoiceseventsvisitor() {}

		std::vector<int> count (const Sguidoelement&);

		virtual void reset()	{ fVoicesCount.clear(); counteventsvisitor::reset(); }

	protected:
		void visitStart ( SARVoice& elt );
		void visitEnd	( SARVoice& elt );

		std::vector<int>	fVoicesCount;
};

/*! @} */

} // namespace

#endif
