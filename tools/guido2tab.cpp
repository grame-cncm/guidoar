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
static void usage(const char * name)
{
	cerr << "usage: " << name << "score [keybord]"  << endl;
	cerr << "       adds an accordion tablature to a score"  << endl;
	cerr << "       options:"  << endl;
	cerr << "           keybord: [optional] indicates the keyboard type. Must be in: "  << endl;
	cerr << "               - '3Rows'   : classical keyboard with 3 standard rows (also known as Heim) [default]"  << endl;
	cerr << "               - '3RowsH2' : 3 rows keyboard known as Heim2"  << endl;
	cerr << "               - '2RowsCG' : 2 rows keyboard (C, G)"  << endl;
	cerr << "               - '2RowsDA' : 2 rows keyboard (D, A)"  << endl;
	exit (1);
}

//_______________________________________________________________________________
static gmn2tabvisitor::kbType getKeyboard (const string& str)
{
	if (str == "3Rows")		return gmn2tabvisitor::k3Rows;
	if (str == "3RowsH2")	return gmn2tabvisitor::k3RowsH2;
	if (str == "2RowsCG")	return gmn2tabvisitor::k2RowsCG;
	if (str == "2RowsCG")	return gmn2tabvisitor::k2RowsDA;
	usage (gToolName);
	return gmn2tabvisitor::kUnknown;
}

//_______________________________________________________________________________
int main(int argc, char *argv[]) 
{
	if (argc < 2) usage(gToolName);
	if (argc > 3) usage(gToolName);
	gmn2tabvisitor::kbType kt = (argc == 3) ? getKeyboard(argv[2]) : gmn2tabvisitor::kDefault;
		
	string gmn, _stdin;
	if (!gmnVal (argv[1], gmn, _stdin)) return -1;

	guidoparser r;
	SARMusic score = r.parseString(gmn.c_str());
	if (score) {
		gmn2tabvisitor v;
		Sguidoelement elt = v.gmn2tab (score, 1);
		cout << elt << endl;
	}
	else {
		const guidoparser::errInfo& err = r.getError();
		cout << "line " << err.line << " col " << err.col << " : " << err.msg << endl;
		return -1;
	}
	return 0;
}
