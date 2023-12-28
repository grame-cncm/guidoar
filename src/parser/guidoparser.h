/*
  GUIDO Library
  Copyright (C) 2006 Grame - 2023 D.Fober

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

#pragma once

#include <stdio.h>
#include <istream>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <locale.h>

#include "arexport.h"
#include "gmnreader.h"
#include "ARTypes.h"
#include "guidorational.h"

namespace guido 
{

class gar_export guidoparser : public gmnreader
{ 
	SARMusic 		fMusic;
	std::istream * 	fStream = nullptr;     // input stream
    
	void initScanner();
	void destroyScanner();
	int 	_yyparse();
	void 	parse  (std::istream * stream);
	
	public:
				 guidoparser();
		virtual ~guidoparser();

		void *	fScanner;   // the flex scanner
		errInfo fError;
		std::string fText;
		
		virtual const errInfo& getError() const  { return fError; }
		virtual bool get(char& c);  // return the next char in stream
        virtual void setStream(std::istream *stream);

//		SARMusic parseFile  (FILE* fd);
		SARMusic parseFile  (const char* file);
		SARMusic parseString(const char* string);

		virtual void	 	   setHeader(std::vector<Sguidoelement>*);
		virtual void	 	   addFooter(Sguidoelement);
		virtual void	 	   beforeVoice(Sguidoelement* voice, Sguidoelement);
		virtual void	 	   afterVoice(Sguidoelement* voice, Sguidoelement);
		virtual Sguidoelement* newComment(const std::string&);
		virtual Sguidoelement* newScore();
		virtual Sguidoelement* newVoice();
		virtual Sguidoelement* newChord();
		virtual Sguidoelement* newRest(const rational * r, long dots);
		virtual Sguidoelement* newNote(const std::string& name, long accidentals, long octave, const rational * r, long dots);
		virtual Sguidoelement* newTag(const std::string&, long id);
		virtual Sguidoelement* newVariable(const std::string& value);
		virtual Sguidoattribute* newAttribute(long value);
		virtual Sguidoattribute* newAttribute(float value);
		virtual Sguidoattribute* newAttribute(const std::string& value, bool quote);

		virtual void variableDecl (Sguidoelement var, const char* value, vartype type);

		virtual int error(const char * msg, int line, int col);
};

} // namespace
