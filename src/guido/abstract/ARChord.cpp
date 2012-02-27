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

#include "ARChord.h"
#include "ARNote.h"
#include "ARTypes.h"
#include "functor.h"
#include "tree_browser.h"
#include "visitor.h"

using namespace std;

namespace guido 
{

//______________________________________________________________________________
// a class chord duration transformation
//______________________________________________________________________________
class chorddurationchange : public visitor<SARNote>
{
	public:
				 chorddurationchange() : fBrowser(this) {}
		virtual ~chorddurationchange() {}
		
		virtual void operator ()(const ARChord* chord, const rational& d) {
			fDuration = d;
			fBrowser.browse (*(guidoelement*)chord);
		}
	
	protected:
		rational fDuration;
		tree_browser<guidoelement> fBrowser;
};

class chordequal : public chorddurationchange		{ protected: inline void visitStart ( SARNote& elt ) { *elt  = fDuration; } };
class chordplusequal : public chorddurationchange	{ protected: inline void visitStart ( SARNote& elt ) { *elt += fDuration; } };
class chordminusequal : public chorddurationchange	{ protected: inline void visitStart ( SARNote& elt ) { *elt -= fDuration; } };
class chordmultequal : public chorddurationchange	{ protected: inline void visitStart ( SARNote& elt ) { *elt *= fDuration; } };
class chorddivequal : public chorddurationchange	{ protected: inline void visitStart ( SARNote& elt ) { *elt /= fDuration; } };


//______________________________________________________________________________
// a class to collect a chord notes durations
//______________________________________________________________________________
class chorddurationvisitor : public visitor<SARNote>
{
	public:
				 chorddurationvisitor() : fBrowser(this) {}
		virtual ~chorddurationvisitor() {}
		
		void	durations (const ARChord* chord, rationals& dlist);
	
	protected:		 
		virtual void visitStart( SARNote& elt )		{ fDurations.push_back (elt->duration()); }

		rationals	fDurations;
		tree_browser<guidoelement> fBrowser;
};

//______________________________________________________________________________
void chorddurationvisitor::durations (const ARChord* chord, rationals& dlist)
{
	fDurations.clear();
	fBrowser.browse (*(guidoelement*)chord);
	dlist = fDurations;
}


//______________________________________________________________________________
//
//   ARChord
//______________________________________________________________________________
void ARChord::duration (rationals& dur) const {
	chorddurationvisitor v;
	v.durations (this, dur);
}

//______________________________________________________________________________
void ARChord::acceptIn(basevisitor& v) {
	if (visitor<SMARTP<ARChord> >* p = dynamic_cast<visitor<SMARTP<ARChord> >*>(&v)) {
		SMARTP<ARChord> sptr = this;
		p->visitStart(sptr);
	}
	else guidoelement::acceptIn(v);
}

//______________________________________________________________________________
void ARChord::acceptOut(basevisitor& v) {
	if (visitor<SMARTP<ARChord> >* p = dynamic_cast<visitor<SMARTP<ARChord> >*>(&v)) {
		SMARTP<ARChord> sptr = this;
		p->visitEnd(sptr);
	}
	else guidoelement::acceptOut(v);
}

//______________________________________________________________________________
SMARTP<ARChord> ARChord::create()
    { ARChord* o = new ARChord; assert(o!=0); return o; }


//______________________________________________________________________________
rational ARChord::duration() const
{
	rationals dlist;
	duration (dlist);
	rational maxd (0,1);
	bool implicit = false;
	for (unsigned int i=0; i<dlist.size(); i++) {
		if (ARNote::implicitDuration (dlist[i])) implicit = true;
		if (dlist[i] > maxd) maxd = dlist[i];
	}
	if (implicit && maxd.getNumerator())
		maxd.setNumerator (-maxd.getNumerator());
	return maxd;
}

ARChord& ARChord::operator  =  (const rational& d)	{ chordequal dc; dc(this, d); return *this;  }
ARChord& ARChord::operator +=  (const rational& d)	{ chordplusequal dc; dc(this, d); return *this;  }
ARChord& ARChord::operator -=  (const rational& d)	{ chordminusequal dc; dc(this, d); return *this;  }
ARChord& ARChord::operator *=  (const rational& d)	{ chordmultequal dc; dc(this, d); return *this;  }
ARChord& ARChord::operator /=  (const rational& d)	{ chorddivequal dc; dc(this, d); return *this;  }

} // namespace
