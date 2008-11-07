
#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "guidoEnv.h"
#include "guidoExpReader.h"
#include "guidoScoreValue.h"
#include "replaceVisitor.h"
#include "valueRenderer.h"

using namespace std;
using namespace guido;
using namespace guidolang;


guidoExpReader gReader;

//#define debug

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " [file]"  << endl;
	cerr << "       launch the guido scores programming language interpreter"  << endl;
	cerr << "       file    : an optionnal file containing language expressions"  << endl;
	cerr << "                 use '-' for stdin input"  << endl;
	cerr << "       when launched without arguemtns, the interpreter takes its language expressions"  << endl;
	cerr << "       from the command line."  << endl;
	cerr << "       Special commands are: "  << endl;
	cerr << "        - 'quit', 'exit' or 'bye' to close the interpreter."  << endl;
	exit (1);
}

//_______________________________________________________________________________
static void help()
{
	cout << "Guido Scores Programming Language version "  << gReader.versionStr() << endl;
	cout << "Available commands are: "  << endl;
	cout << " 'quit', 'exit' or 'bye' to quit the interpreter"  << endl;
	cout << " 'env' to show the expressions in the current environment"  << endl;
	cout << " 'eval id' to evaluate an expression identified by 'id' from current environment"  << endl;
	cout << " '?' or 'help' to display this message"  << endl;
}

//_______________________________________________________________________________
#define kBlocksize	4096
static char* read(FILE * fd, bool eol) 
{
	int size = kBlocksize;
	char* memblock = (char*)malloc(size);
	if (!memblock) return 0;
	
	int i=0;
	while (true) {
		if (i >= (size-1)) {
			size += kBlocksize;
			memblock = (char*)realloc(memblock, size);
			if (!memblock) return 0;
		}
		int c = getc(fd);
		if (feof(fd) || (eol && (c == '\n'))) {
			break;
		}
		else memblock[i++] = c;
	}
	memblock[i] = 0;
	return memblock;
}

//_______________________________________________________________________________
static char* readfile(const char * filename) 
{
	char* memblock = 0;
	if (!strcmp(filename, "-")) 
		memblock = read(stdin, false);
	else {
		FILE * fd = fopen(filename, "r");
		if (fd) {
			memblock = read(fd, false);
			fclose(fd);
		}
		else {
			cerr << filename << ": read failed"  << endl;
			exit(1);
		}
	}	
	return memblock;
}

//_______________________________________________________________________________
static void env()
{
	guidoExpReader::ExpList expmap = gReader.getEnv();
	guidoExpReader::ExpList::const_iterator i;
	cout << expmap.size() << " expresssions in the current environment: " << endl;
	for (i=expmap.begin(); i != expmap.end(); i++) {
		cout << i->first << " = " << i->second << endl;
	}
}

//_______________________________________________________________________________
static void read (char * buffer) 
{
	if (*buffer) {
		gReader.parseString (buffer);
	}
}

//_______________________________________________________________________________
static void eval (char * name) 
{
	while ((*name == ' ') || (*name == '\t')) name++;
	string id = name;
	Sguidoexpression exp = gReader.getId(name);
	if (exp) {
		cout << "eval expression '" << name << "'" << endl;
		valueRenderer vr;
		Sguidoelement score = vr.render(exp);
		if (score) {
			cout << score << endl;
		}
		else cout << "null val returned" << endl;
	}
	else cout << "'" << name << "': no such expression !" << endl;
}

//_______________________________________________________________________________
// remove leading and trailing spaces
static char * strip (char * buff)
{
	while ((*buff == ' ') || (*buff == '	')) buff++;
	int len = strlen(buff);
	if (len) {
		char * ptr = &buff[strlen(buff)-1];
		while ((*ptr == ' ') || (*ptr == '	')) ptr--;
		ptr[1] = 0;
	}
	return buff;
}

//_______________________________________________________________________________
static void interactive () 
{
	cout << "G-SCOL - Guido Scores Programming language." << endl;
	cout << "> ";
	bool done = false;
	while (!done) {
		char * buffer = read (stdin, true);
		if (buffer) {
			char * cmd = strip( buffer);
			if (!strcmp(cmd, "quit") || !strcmp(cmd, "exit") || !strcmp(cmd, "bye")) 
				done = true;

			else if (!strcmp(cmd, "help") || !strcmp(cmd, "?"))	help();
			else if (!strcmp(cmd, "env"))		env();
			else if (!strncmp(cmd, "eval", 4))	eval(&cmd[5]);
			else read (cmd);

			if (!done) cout << "> ";
			free (buffer);
		}
		else {
			cerr << "fatal error: memory allocation failure"  << endl;
			exit(1);
		}
	}
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
#ifdef debug
	argc = 2;
	char * args[] = {"test.gsl"};
	char ** argsPtr = args;
#else
	if (argc > 2) usage(argv[0]);
	char ** argsPtr = &argv[1];
#endif
	if (argc == 2) {
		read (readfile(*argsPtr));
	} 
	interactive();
	return 0;
}
