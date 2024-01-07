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

#include "common.cxx"

#include "gmn2tabvisitor.h"
#include "AROthers.h"
#include "guidoparser.h"


const char* gToolName = "guido2tab";

//_______________________________________________________________________________
static void doc(const char * name)
{
	cout << name ;
	cout << "\n\
---------------------------------------------------------------\n\
     Annotations for tablature and harmony generation\n\
---------------------------------------------------------------\n\
In order to generate an accordion tablature, the input gmn code\n\
must be annotated to guide the annotation process.\n\
Annotations are GMN line comments (% ...)\n\
---------------------------------------------------------------\n\
  Tablature annotations:\n\
Must be in the form:\n\
% tab: [PT] [GC]\n\
'% tab:' is the marker of tabulations annotations,\n\
it is followed by a single letter that indicates a mode:\n\
 'P' the key number is looked for in push mode\n\
 'T' the key number is looked for in pull mode\n\
followed by a single letter that indicates the prefered row:\n\
 'G' the key number is looked for in the first row\n\
 'C' the key number is looked for in the second row\n\
Note that a best effort is made to respect the tablature directives\n\
however, when a note doesn't exist in a given mode or a given row\n\
the system will look for it first in an alternate row, and eventually\n\
in the other mode\n\
---------------------------------------------------------------\n\
  Harmony annotations:\n\
Must be in the form:\n\
% H: letters | empty | '|'\n\
'% H:' is the marker of harmony annotations,\n\
'letters' are harmony strings as indicated in \\harmony tags\n\
    e.g: % H: A a a\n\
    Harmony strings may be followed by an optional duration expressed\n\
    like GMN notes duration.\n\
	e.g: % H: A/2 a/4\n\
    Note that when the duration is not specified, the system makes\n\
    use of the last indicated duration (initial value is 1/4)\n\
    Harmony strings may also be followed by a 'dx' attribute that\n\
    is passed thru to the \\harmony tag\n\
    e.g. % H: Adx=1 a a\n\
'empty' can be used when no harmony is present\n\
    it may also be followed by a duration\n\
'|' can be used to insert a \\bar at the given position\n\
 ";
	exit (1);
}

//_______________________________________________________________________________
static void usage(const char * name)
{
	cerr << "usage: " << name << " score [options]";
	cerr << "\n\
adds an accordion tablature and  harmony tags to a score\n\
args:\n\
   score: " << scoredesc << "\n\
   options:\n\
    -k         value: \n\
    --keyboard value: indicates the keyboard type. Must be in:\n\
      '3Rows'  : 3 rows standard keyboard (also known as Heim) [default]\n\
      '3RowsH2': 3 rows keyboard known as Heim2\n\
      '2RowsCG': 2 rows keyboard (C, G)\n\
      '2RowsDA': 2 rows keyboard (D, A)\n\
    -v      num: \n\
    --voice num: indicates the target voice [default is 1]\n\
    -d   : \n\
    --doc: print a short documentation"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static bool readOption(char ** args, int argc, const string& optName, string& out)
{
	for (int i=1; i<argc; i++) {
		if ((optName == args[i]) && ((i+1)<argc)) {
			out = args[i+1];
			return true;
		}
	}
	return false;
}

//_______________________________________________________________________________
static bool readOption(char ** args, int argc, const string optName)
{
	for (int i=1; i<argc; i++) {
		if (optName == args[i])
			return true;
	}
	return false;
}

//_______________________________________________________________________________
static bool readOption(char ** args, int argc, const string& optName, int& out)
{
	for (int i=1; i<argc; i++) {
		if ((optName == args[i]) && ((i+1)<argc)) {
			try {
				out = std::atoi( args[i+1] );
				return true;
			}
			catch (exception e) {
				return false;
			}
			return true;
		}
	}
	return false;
}

//_______________________________________________________________________________
static AccordionKeyboard::KBDType getKeyboard (const string& str)
{
	if (str == "3Rows")		return AccordionKeyboard::k3Rows;
	if (str == "3RowsH2")	return AccordionKeyboard::k3RowsH2;
	if (str == "2RowsCG")	return AccordionKeyboard::k2RowsCG;
	if (str == "2RowsCG")	return AccordionKeyboard::k2RowsDA;
	usage (gToolName);
	return AccordionKeyboard::kUnknown;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
	if (argc < 2) usage(gToolName);
	if (readOption (argv, argc, "-d") || readOption (argv, argc, "--doc") )
		doc(gToolName);

	AccordionKeyboard::KBDType kt = AccordionKeyboard::kDefault;
	string keyboard;
	if (readOption (argv, argc, "-k", keyboard) || readOption (argv, argc, "--keyboard", keyboard))
		kt = getKeyboard(keyboard);
	int voice = 1;
	if (!readOption (argv, argc, "-v", voice))
		readOption (argv, argc, "--voice", voice);
		
	string gmn, _stdin;
	if (!gmnVal (argv[1], gmn, _stdin)) return -1;

	guidoparser r;
	SARMusic score = r.parseString(gmn.c_str());
	if (score) {
//cerr << gToolName << " keyboard: " << kt << " voice " << voice << endl;
		gmn2tabvisitor v (kt);
		Sguidoelement elt = v.gmn2tab (score, voice);
		if (elt) cout << elt << endl;
	}
	else {
		const guidoparser::errInfo& err = r.getError();
		cout << "line " << err.line << " col " << err.col << " : " << err.msg << endl;
		return -1;
	}
	return 0;
}
