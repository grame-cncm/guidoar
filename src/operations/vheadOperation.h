/*
  Copyright © Grame 2008

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

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    research@grame.fr

*/

#ifndef __vheadOperation__
#define __vheadOperation__

#include "export.h"
#include "AROthers.h"
#include "clonevisitor.h"


namespace guido 
{

/*!
\addtogroup visitors
@{
*/

/*!
\brief A visitor that cuts the tail of a score voices.
*/
class export vheadOperation : 
	public clonevisitor,
	public visitor<SARStaff>
{		
    public:
 				 vheadOperation()	{}
		virtual ~vheadOperation()	{}

		/*! cuts the tail of the score voices after a given voice
			\param voicenum the score voices to preserve
			\return a new score
		*/
		Sguidoelement operator() ( const Sguidoelement& score, int voicenum );
 
     protected:
		int			fVoiceNum, fCurrentVoice;

		virtual bool copy  ();

		virtual void visitStart( SARStaff& elt );
		virtual void visitStart( SARVoice& elt );
};

/*! @} */

} // namespace MusicXML


#endif
