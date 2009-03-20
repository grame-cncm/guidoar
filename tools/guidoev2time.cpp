/*

  Copyright (C) 2003-2008  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
*/

#include "common.cxx"

//#define guidodebug

//_______________________________________________________________________________
static void usage(char * name)
{
	cerr << "usage: " << basename(name) << " <score> <evIndex> [voiceIndex]"  << endl;
	cerr << "       converts an event index to a time position"  << endl;
	cerr << "       score: the input file or '-' to read stdin"  << endl;
	cerr << "       evIndex: the index of the target event (1 based)"  << endl;
	cerr << "       voiceIndex: optional voice index (defaults to the first voice)"  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
	char *name = argv[0];
#ifdef guidodebug
	argc = 4;
	char * args[] = {"a.gmn", "2", "1", 0};
	char ** argsPtr = args;
#else
	if ((argc != 3) && (argc != 4)) usage(name);
	char ** argsPtr = &argv[1];
#endif

	const char *file = argsPtr[0];
	char *buff = readgmn(file);

	int eventIndex = intArg (argsPtr[1], -1);		// get the event index argument
	if (eventIndex <= 0) usage(name);
	
	int voiceIndex = 1;									// default voice is 1
	if (argc == 4) voiceIndex = intArg (argsPtr[2], -1);// get the voice index argument
	if (voiceIndex <= 0) usage(name);
		
	cout << file << ": voice " << voiceIndex << " event " << eventIndex
		 << ": time " << string(guidoEv2Time(buff, eventIndex-1, voiceIndex-1)) << endl;
	delete[] buff;
	return 0;
}
