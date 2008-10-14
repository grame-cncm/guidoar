
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <stdlib.h>


#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "parOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " files..."  << endl;
	cerr << "       put the input gmn files in parrallel with right alignment"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static void readErr(const char * name)
{
	cerr << name << ": read failed"  << endl;
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
	SARMusic g1 = r.parseFile( *argsPtr );
	if (!g1) readErr(*argsPtr);
	argsPtr++;
	for (int i=2; i<argc; i++, argsPtr++) {
		SARMusic g2 = r.parseFile(  *argsPtr );
		if (!g2) readErr(*argsPtr);
		parOperation par(parOperation::kRight);
		g1 = par(g1, g2);
	}
	if (g1) {
		Sguidoelement result = g1;
		cout << result << endl;
	}
	return 0;
}
