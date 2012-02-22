
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdlib.h>


#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "interleaveOperation.h"

#include "common.cxx"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " files..."  << endl;
	cerr << "       interleaves the input gmn files"  << endl;
	cerr << "       use '-' for standard input"  << endl;
	exit (1);
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 3;
	char * args[] = {"a.gmn", "a.gmn", 0};
	char ** argsPtr = args;
#else
	if (argc == 1) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	guidoparser r;
	char *buff = readgmn(*argsPtr);
	SARMusic g1 = r.parseString( buff );
	delete[] buff;
	if (!g1) readErr(*argsPtr);

	argsPtr++;
	for (int i=2; i<argc; i++, argsPtr++) {
		char *buff = readgmn(*argsPtr);
		SARMusic g2 = r.parseString( buff );
		delete[] buff;
		if (!g2) readErr(*argsPtr);
		interleaveOperation inter;
		g1 = inter(g1, g2);
	}
	if (g1) {
		Sguidoelement result = g1;
		cout << result << endl;
	}
	return 0;
}
