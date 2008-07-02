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

#ifndef __ARNote__
#define __ARNote__

#include "guidoelement.h"
#include "rational.h"
#include "export.h"

namespace guido 
{

/*!
\addtogroup abstract
@{
*/

class basevisitor;
//______________________________________________________________________________
/*!
\brief A Guido note description
*/
class export ARNote : public guidoelement
{ 
    protected:	
				ARNote();
		virtual ~ARNote() {}

	int fOctave, fAccidental, fDots;
	rational fDuration;

	public:
		enum { kUndefined = -1 };

		static SMARTP<ARNote> create();
        virtual void			acceptIn  (basevisitor& v);
        virtual void			acceptOut (basevisitor& v);

	void SetOctave		(int oct)	{ fOctave = oct; }
	void SetAccidental	(int acc)	{ fAccidental= acc; }
	void SetDots		(int dots)	{ fDots = dots; }

	int GetOctave		() const	{ return fOctave; }
	int GetAccidental	() const	{ return fAccidental; }
	int GetDots			() const	{ return fDots; }
	
	// duration operations
	rational&		duration()		{ return fDuration; }
	ARNote& operator =  (const rational&);
	ARNote& operator += (const rational&);
	ARNote& operator -= (const rational&);
	ARNote& operator *= (const rational&);
	ARNote& operator /= (const rational&);

	operator std::string () const;
	
};

}

/*! @} */

#endif
