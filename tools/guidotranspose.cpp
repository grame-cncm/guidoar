
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <string>
#include <stdio.h>
//#include <inttypes.h>

#include "AROthers.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "transposeOperation.h"

using namespace std;
using namespace guido;

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " <file> <interval>"  << endl;
	cerr << "       transpose the input gmn files"  << endl;
	cerr << "       file    : the file to be transposed"  << endl;
	cerr << "                 use '-' for stdin input"  << endl;
	cerr << "       interval: the transposing interval"  << endl;
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
	char * args[] = {"../test.gmn", "-1", 0};
	char ** argsPtr = args;
#else
	if (argc != 3) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	string file (*argsPtr++);
	guidoparser r;
	SARMusic gmn = (file == "-") ?  r.parseFile( stdin ) : r.parseFile( file.c_str() );
	if (!gmn) readErr(file.c_str() );

	int interval = strtol(*argsPtr, 0, 10);
	Sguidoelement result = gmn;
	if (interval) {
		transposeOperation trsp;
		result = trsp(gmn, interval);
	}
	cout << result << endl;
	return 0;
}
