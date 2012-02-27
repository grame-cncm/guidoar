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

#include <map>
#include <string>

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

	static std::map<std::string, std::pair<char, int> >	fNormalizeMap;

	public:
		enum { kUndefinedOctave = -999, kUndefinedDuration = 0, kDefaultOctave=1 };
		enum pitch { kNoPitch = -1, C, D, E, F, G, A, B };

		static SMARTP<ARNote> create();
        virtual void			acceptIn  (basevisitor& v);
        virtual void			acceptOut (basevisitor& v);

	void SetOctave		(int oct)	{ fOctave = oct; }
	void SetAccidental	(int acc)	{ fAccidental= acc; }
	void SetDots		(int dots)	{ fDots = dots; }

	//! normalizes pitch names to 'a b c d...' notation, alter is to catch 'cis, dis...' notation
	char NormalizedPitchName (int* alter = 0) const;		

	int GetOctave		() const	{ return fOctave; }
	int GetAccidental	() const	{ return fAccidental; }
	int GetDots			() const	{ return fDots; }
	bool isRest ()	const			{ return getName() == "_"; }
	bool isEmpty ()	const			{ return getName() == "empty"; }
	bool isPitched () const			{ return !isRest() && !isEmpty(); }
	
	pitch	GetPitch	(int& alter) const;
	int		midiPitch	(int& currentOctave) const;
	
	// duration operations
	const rational&	duration() const		{ return fDuration; }
	rational		totalduration(rational& current, int& currentdots)	const;
	ARNote& operator =  (const rational&);
	ARNote& operator += (const rational&);
	ARNote& operator -= (const rational&);
	ARNote& operator *= (const rational&);
	ARNote& operator /= (const rational&);
	bool	implicitDuration() const					{ return fDuration == getImplicitDuration(); }
	bool	implicitOctave() const						{ return fOctave == getImplicitOctave(); }
	void	setImplicitDuration()						{ fDuration.set(kUndefinedDuration,4); }

	static rational getImplicitDuration()				{ return rational(kUndefinedDuration,4); }
	static bool		implicitDuration(const rational& d)	{ return d.getNumerator() == kUndefinedDuration; }
	static rational getDefaultDuration()				{ return rational(1,4); }
	static int		getDefaultOctave()					{ return 1; }
	static int		getImplicitOctave()					{ return kUndefinedOctave; }
	static bool		implicitOctave(int o)				{ return o == kUndefinedOctave; }
	
	static pitch OffsetPitch			(pitch p, int offset, int& octave, int& alter, int targetinterval);
	static pitch NormalizedName2Pitch	(char note);
	static char  NormalizedPitch2Name	(pitch p);
	static char  NormalizedPitchName	(const std::string& name, int* outalter=0);		

	operator std::string () const;
};

}

/*! @} */

#endif
