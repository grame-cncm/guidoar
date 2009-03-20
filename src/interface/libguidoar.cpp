/*

  guidoar Library
  Copyright (C) 2008-2009  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <fstream>

#include "libguidoar.h"

#include "AROthers.h"
#include "clonevisitor.h"
#include "guidoelement.h"
#include "guidoparser.h"
#include "unrolled_guido_browser.h"
#include "bottomOperation.h"
#include "durationOperation.h"
#include "event2timevisitor.h"
#include "transposeOperation.h"

using namespace std;
namespace guido
{

//----------------------------------------------------------------------------
export int				guidoarVersion()	{ return 80; }
export const char*		guidoarVersionStr()	{ return "v.0.80"; }

//----------------------------------------------------------------------------
static SARMusic read (const char* buff)
{
	if (!buff) return 0;
	guidoparser r;
	return r.parseString(buff);
}

//----------------------------------------------------------------------------
export char * guidoread (const char* file)
{
	ifstream is (file, ios::in );
	if (!is.is_open()) return 0;
	
	// get length of file:
	is.seekg (0, ios::end);
	int length = is.tellg();
	is.seekg (0, ios::beg);

	// allocate memory:
	char * buffer = new char [length + 1];

	// read data as a block:
	is.read (buffer,length);
	is.close();
	buffer[length] = 0;
	return buffer;
}
//----------------------------------------------------------------------------
export char * guidoread (FILE * fd)
{
	if (!fd) return 0;
	string str;
	while (feof(fd))
		str += getc(fd);

	// allocate memory:
	char * buffer = new char [str.size()+1];
	memcpy(buffer, str.c_str(), str.size());
	buffer[str.size()] = 0;
	return buffer;
}

//----------------------------------------------------------------------------
export garErr guido2unrolled(const char* gmn, std::ostream& out)
{
	garErr err = kNoErr;
	Sguidoelement score =  read(gmn);
	if (score) {
		clonevisitor cv;
		unrolled_guido_browser ugb(&cv);
		ugb.browse (score);
		score = cv.result();
		if (score) out << score << endl;
		else err = kOperationFailed;			
	}
	else err = kInvalidArgument;
	return err;
}

//----------------------------------------------------------------------------
export garErr guidoBottom(const char* gmn, const char* gmnSpec, std::ostream& out)
{
	SARMusic score =  read(gmn);
	SARMusic dscore = read(gmnSpec);
	if (!score || !dscore) return kInvalidArgument;

	garErr err = kNoErr;
	bottomOperation tail;
	score = tail(score, dscore);
	if (score) out << Sguidoelement(score) << endl;
	else err = kOperationFailed;			
	return err;
}

export garErr guidoBottom(const char* gmn, int nvoices, std::ostream& out)
{
	Sguidoelement score =  read(gmn);
	if (!score) return kInvalidArgument;

	garErr err = kNoErr;
	bottomOperation tail;
	if (nvoices > 0)
		score = tail(score, nvoices);
	if (score) out << score << endl;
	else err = kOperationFailed;		
	return err;
}

//----------------------------------------------------------------------------
export garErr guidoSetDuration(const char* gmn, const char* gmnSpec, std::ostream& out)
{
	SARMusic score =  read(gmn);
	SARMusic dscore = read(gmnSpec);
	if (!score || !dscore) return kInvalidArgument;
	if (!score || !dscore) return kInvalidArgument;

	garErr err = kNoErr;
	durationOperation setdur;
	score = setdur(score, dscore);
	if (score) out << Sguidoelement(score) << endl;
	else err = kOperationFailed;		
	return err;
}

export garErr guidoSetDuration(const char* gmn, const rational& duration, std::ostream& out)
{
	Sguidoelement score =  read(gmn);
	if (!score) return kInvalidArgument;

	garErr err = kNoErr;
	durationOperation setdur;
	score = setdur(score, duration);
	if (score) out << score << endl;
	else err = kOperationFailed;		
	return err;
}

export garErr guidoMultDuration(const char* gmn, float duration, std::ostream& out)
{
	Sguidoelement score =  read(gmn);
	if (!score) return kInvalidArgument;

	garErr err = kNoErr;
	durationOperation setdur;
	score = setdur(score, duration);
	if (score) out << score << endl;
	else err = kOperationFailed;		
	return err;
}

//----------------------------------------------------------------------------
export rational	guidoEv2Time(const char* gmn, unsigned int index, unsigned int voice)
{
	Sguidoelement score =  read(gmn);
	if (!score) return kInvalidArgument;
	event2timevisitor convert;
	return convert.event2time (score, index, voice);
}

//----------------------------------------------------------------------------
export garErr guidoTranpose	(const char* gmn, int interval, std::ostream& out)
{
	Sguidoelement score =  read(gmn);
	if (!score) return kInvalidArgument;

	garErr err = kNoErr;
	transposeOperation trsp;
	score = trsp(score, interval);
	if (score) out << score << endl;
	else err = kOperationFailed;		
	return err;
}

export garErr guidoTranpose	(const char* gmn, const char* gmnSpec, std::ostream& out)
{
	SARMusic score =  read(gmn);
	SARMusic dscore = read(gmnSpec);
	if (!score || !dscore) return kInvalidArgument;

	garErr err = kNoErr;
	transposeOperation trsp;
	score = trsp(score, dscore);
	if (score) out << Sguidoelement(score) << endl;
	else err = kOperationFailed;		
	return err;
}

}
