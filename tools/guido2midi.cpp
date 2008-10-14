/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/

#ifdef WIN32
# pragma warning (disable : 4786)
# define basename(name)	(name)
# define _CRT_SECURE_NO_DEPRECATE
#else 
# include <libgen.h>
#endif

#include <stdlib.h>
#include <iostream>

#define USEMidiShare
#include "guidoparser.h"
#include "midicontextvisitor.h"
#include "midiconverter.h"

//#define debug

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
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> [outfile]"  << endl;
	cerr << "       convert a guido score to midifile"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       outfile: optional outfile (defaults to <score>.mid"  << endl;
	exit (1);
}


//_______________________________________________________________________________
static SARMusic read (const char* file) 
{
	guidoparser r;
	SARMusic score;
	if (!strcmp(file, "-"))
		score = r.parseFile(stdin);
	else
		score = r.parseFile(file);
	if (!score) {
		cerr << file << ": read failed"  << endl;
		exit (1);
	}
	return score;
}

//_______________________________________________________________________________
static char* gmn2mid (const char* file) 
{
	static char outname[512];

	strncpy (outname, file, 500);
	char * dot = strrchr (outname, '.');	
	if (dot)	strcpy (dot, ".mid");
	else		strcat (outname, ".mid");
	return outname;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
#ifdef debug
	char * file = "test.gmn";
	char * outfile = gmn2mid(file);
#else
	if (argc < 2) usage(argv[0]);
	const char * file = argv[1];
	char * outfile = (argc == 3) ? argv[2] : gmn2mid(file);
#endif

	Sguidoelement score = read (file);
	if (score) {
#if 0
		mymidiwriter writer;
		midicontextvisitor mcv(100, &writer);
		mcv.visit (score);
#else
		midiconverter mc;
		if (!mc.score2midifile(score, outfile))
			cerr << "error while convertir " << file << " to midifile " << outfile << endl;
#endif
	}
	return 0;
}
