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

#include <Player.h>

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
	cerr << "usage: " << basename(name) << " <score> [outfile | --play]"  << endl;
	cerr << "       convert a guido score to midifile"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       outfile: optional outfile (defaults to <score>.mid"  << endl;
	cerr << "       --play: play the score but don't generates a midifile"  << endl;
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
	if (!strcmp(file, "-")) return "guido2midi.mid";

	strncpy (outname, file, 500);
	char * dot = strrchr (outname, '.');	
	if (dot)	strcpy (dot, ".mid");
	else		strcat (outname, ".mid");
	return outname;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) {
#ifdef debug
	char * file = "Dichter.gmn";
	char * outfile = gmn2mid(file);
	bool play = true;
#else
	if (argc < 2) usage(argv[0]);
	char * file = argv[1];
	bool play = false;
	char * outfile = 0;
	if (argc == 3) {
		play = (strcmp (argv[2], "--play") == 0);
		if (!play) outfile = argv[2];
	}
	else outfile = gmn2mid(file);
#endif

	Sguidoelement score = read (file);
	if (score) {
#ifdef USEMidiShare
		midiconverter mc;
		if (play) {
			short ref = mc.score2player(score, file);
			if (ref > 0) {
				cout << "Playing with Player library version " << Version() << endl;
				MidiConnect (ref, 0, true);
				StartPlayer(ref);
				PlayerState info;
				do { GetStatePlayer(ref, &info); } while (info.state != kIdle);
				StopPlayer(ref);
				ClosePlayer (ref);
			}
			else cerr << "error while convertir " << file << endl;
		}
		else {
			int err = mc.score2midifile(score, outfile);
			if (err != noErr)
				cerr << "error " << err << " while converting " << file << " to midifile " << outfile << endl;
		}
#else
		mymidiwriter writer;
		midicontextvisitor mcv(100, &writer);
		mcv.visit (score);
#endif
	}
	return 0;
}
