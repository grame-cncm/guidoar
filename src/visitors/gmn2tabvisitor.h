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

#include <stack>
#include <string>
#include <vector>
#include <map>

#include "arexport.h"
#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "ARTypes.h"
#include "clonevisitor.h"

namespace guido
{

//______________________________________________________________________________
/*!
\brief	Keyboard représentation
*/
class AccordionKeyboard
{
	public :
		typedef std::map<const std::string, const char*> TRowMap;
		typedef std::map<const std::string, const char*> TEnharmonics;
		typedef struct TKeysMap {
			TRowMap first;
			TRowMap second;
			TRowMap third;
		} TKeysMap;
		typedef struct {
			TKeysMap push;
			TKeysMap pull;
		} Keyboard;
		
		typedef enum { kUnknown, k3Rows, k3RowsH2, k2RowsCG, k2RowsDA, kDefault=k3Rows} KBDType;

			 AccordionKeyboard(KBDType type);
	virtual ~AccordionKeyboard() {}
	
		// gives a note tablature with best effort
		// push mode may be enforced with the force parameter
		// otherwise the effective push mode is returned by the push parameter
		const char* note2tab (const std::string& note, bool& push, int row, bool force=false) const;
		void 		initialize(KBDType type);
		bool 		initialised() const		{ return fInitialised; }

	private:
	
		void 		 init3Rows (Keyboard& k);
		void 		 initHeim2 (Keyboard& k);
		void 		 initEnharmonics(TEnharmonics& tbl);
		const char * scanRows(const std::string& note, const TKeysMap& map, int row) const;

		Keyboard  		fKeysMap;
		TEnharmonics	fEnharmonics;
		bool 			fInitialised = false;
};

//______________________________________________________________________________
/*!
\brief	A visitor to add accordion tablature to a score
*/
class gar_export gmn2tabvisitor :
	public clonevisitor,
	public visitor<SARTie>,
	public visitor<SARBar>,
	public visitor<SARRepeatBegin>,
	public visitor<SARRepeatEnd>
{
	private:
		AccordionKeyboard fKeyBoard;    ///< the keyboard description
		SARVoice fTabVoice;				///< the tablature voice
		SARVoice fHarmVoice;			///< the harmony voice
		int	 	 fInTie;				///< use to prevent tablature for tied notes
		bool	 fInChord;
		int		 fVoiceNum;				///< the current voice number
		int		 fTargetVoice;			///< the target voice for tablature
		int		 fCurrentOctave;		///<  the current octave, required to sort chord notes
		int 	 fMeasureNum;
		rational fHarmDur;				///< the last harmony duration

		typedef struct TabMode {
			bool push;
			int  row;
			TabMode (bool p=false, int r=0) : push(p), row(r) {}
			TabMode (TabMode& m) 			: push(m.push), row(m.row) {}
		} TabMode;
		TabMode  fTabMode;

		typedef struct TPNote {
			SARNote note;
			int 	pitch;
					TPNote (SARNote n, int p) { note = n; pitch = p; }
		} TPNote;
		std::vector<TPNote> fChordNotes;	// list of chord notes with associated midi pitch

		void 	addToTabVoice 		( Sguidoelement elt );
		void 	initTabVoice 		( Sguidoelement elt );
		SARVoice initHarmVoice 		() const;
		void 	initVariables 		( SARMusic score);
		bool 	existingVariables 	( const ARMusic::THeader& header, std::string varname) const;
		Sguidovariable createVariable (const char * name, const char * value) const;

		Sguidoattribute makeAttribute ( const char* name, const char* value, bool quote ) const;
		Sguidoattribute makeAttribute ( const char* name, float value ) const;
		Sguidotag 		makeHidden 	  ( const std::string& name) const;
		Sguidotag 		makeTab 	  ( const std::string& content, bool push ) const;
		void 			makeHarmony   ( const std::string& h, const rational& dur );
		std::string		noteName 	  ( const SARNote& note) const;   // note name + octave
		Sguidoelement 	newLine 	  () const;
		SARNote			makeEmpty	  ( const rational& dur, int dots) const;
		void 			handleTab 	  (const std::string&);  // handle tab expressions
		void 			handleHarm 	  (const std::string&);  // handle harmony expressions

    public:
		typedef enum { kUnknown, k3Rows, k3RowsH2, k2RowsCG, k2RowsDA, kDefault = k3Rows } kbType;
		
				 gmn2tabvisitor(AccordionKeyboard::KBDType type = AccordionKeyboard::k3Rows) : fKeyBoard(type) {}
		virtual ~gmn2tabvisitor() {}
		
		SARMusic gmn2tab (const SARMusic ar, int targetvoice);

		virtual void visitStart ( Sguidocomment& comment );
		virtual void visitStart ( Sguidotag& tag );
		virtual void visitStart ( SARNote& elt );
		virtual void visitStart ( SARMusic& elt );
		virtual void visitStart ( SARChord& elt );
		virtual void visitStart ( SARVoice& elt );
		virtual void visitStart ( SARBar& elt );
		virtual void visitStart ( SARRepeatBegin& elt );
		virtual void visitStart ( SARRepeatEnd& elt );
		virtual void visitStart ( SARTie& tie );

		virtual void visitEnd ( SARChord& elt );
		virtual void visitEnd ( SARVoice& elt );
		virtual void visitEnd ( SARTie& tie );
};

} // namespace
