/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/
	
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>

#include "guidoparser.h"
#include "midicontextvisitor.h"

using namespace std;
using namespace guido;

//_______________________________________________________________________________
class mymidiwriter : public midiwriter {
	public:
				 mymidiwriter() {}
		virtual ~mymidiwriter() {}
		
		virtual void startVoice () 
			{ cout << "startVoice " << endl; }
		virtual void endVoice (long date)
			{ cout << date << " endVoice" << endl; }

		virtual void newNote (long date, int pitch, int vel, int duration, int articulation)
			{ cout << date << " newNote [" << pitch << ", " << vel << ", " << duration <<  ", art: " << articulation << "]" << endl; }
		virtual void tempoChange (long date, int bpm)
			{ cout << date << " tempoChange " << bpm << endl; }
		virtual void progChange (long date, int prog)
			{ cout << date << " progChange " << prog << endl; }
};

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
	if (argc == 1) {
		guidoparser r;
		Sguidoelement g = r.parseFile( stdin );
		if (g) {
			mymidiwriter writer;
			midicontextvisitor mcv(480, &writer);
			mcv.visit (g);
		}
	}
	else for (int i=1; i< argc; i++) {
		guidoparser r;
		Sguidoelement g = r.parseFile( argv[i] );
		if (g) {
			mymidiwriter writer;
			midicontextvisitor mcv(100, &writer);
			mcv.visit (g);
		}
		else {
			cerr << argv[i] << ": read failed!" << endl;
			return 1;
		}
	}
	return 0;
}
