/*

  Copyright (C) 2007  Grame


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

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    research@grame.fr

*/

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>

#include "ARFactory.h"
#include "AROthers.h"
#include "ARTag.h"
#include "ARNote.h"
#include "durationvisitor.h"
#include "durationOperation.h"
#include "tree_browser.h"

using namespace std;

namespace guido 
{

//_______________________________________________________________________________
durationOperation::durationOperation() : fFactor(1)
{
	for (int i=0; i<kMaxDivider; i++)
		fPrimeNumbers[i] = false;
	fPrimeNumbers[23] = true;
	fPrimeNumbers[29] = true;
	fPrimeNumbers[31] = true;
	fPrimeNumbers[37] = true;
	fPrimeNumbers[41] = true;
	fPrimeNumbers[43] = true;
	fPrimeNumbers[47] = true;
	fPrimeNumbers[53] = true;
	fPrimeNumbers[59] = true;
	fPrimeNumbers[61] = true;
	fPrimeNumbers[67] = true;
	fPrimeNumbers[71] = true;
	fPrimeNumbers[73] = true;
	fPrimeNumbers[79] = true;
	fPrimeNumbers[83] = true;
	fPrimeNumbers[89] = true;
	fPrimeNumbers[97] = true;
	fPrimeNumbers[101] = true;
	fPrimeNumbers[103] = true;
	fPrimeNumbers[107] = true;
	fPrimeNumbers[109] = true;
	fPrimeNumbers[113] = true;
	fPrimeNumbers[127] = true;
	fPrimeNumbers[131] = true;
	fPrimeNumbers[137] = true;
	fPrimeNumbers[139] = true;
	fPrimeNumbers[149] = true;
	fPrimeNumbers[151] = true;
	fPrimeNumbers[157] = true;
}

//_______________________________________________________________________________
Sguidoelement durationOperation::operator() ( const Sguidoelement& score, float factor )
{
	if (!score) return 0;
	fFactor = float2rational(factor);
cerr << "durationOperation stretching factor " << string(fFactor) << endl;
	Sguidoelement outscore;
	if (score) {
		fCurrentDurationIn = fCurrentDurationOut = rational(1,4);
		tree_browser<guidoelement> browser(this);
		browser.browse (*score);
		outscore = fStack.top();
		fStack.pop();
	}
	return outscore;
}

//_______________________________________________________________________________
Sguidoelement durationOperation::operator() ( const Sguidoelement& score, const rational& targetDuration )
{
	if (!score) return 0;

	durationvisitor dv;
	rational dur = dv.duration (score);
	rational r = safeDiv (dur, targetDuration);
	Sguidoelement elt = (*this)(score, float(r));
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//_______________________________________________________________________________
SARMusic durationOperation::operator() ( const SARMusic& score1, const SARMusic& score2 )
{
	if (!score1) return 0;

	Sguidoelement elt;
	if (!score2) 
		elt = (*this)(score1, 1.0f);
	else {
		durationvisitor dv;
		rational s1d = dv.duration (score1);
		rational s2d = dv.duration (score2);
		rational r = s2d / s1d;
		elt = (*this)(score1, float(r));
	}
	return dynamic_cast<ARMusic*>((guidoelement*)elt);
}

//________________________________________________________________________
rational durationOperation::float2rational ( float val ) const
{
	int denum = 1000000; // to keep 6 significant numbers
	int num = int(val * denum);
	rational r(num, denum);
	r.rationalise();
	return r;
}

//________________________________________________________________________
rational durationOperation::safeDiv ( const rational& dur1, const rational& dur2 ) const
{
	rational result = dur1 / dur2;
	const rational null(0,1);

	if (result < null) {		// overflow has occured, try another way
cerr << "safeDiv try swap " << string(dur1) << " - " << string(dur2) << " ";
		rational swap1 (dur1.getNumerator(), dur2.getDenominator());
		rational swap2 (dur1.getDenominator(), dur2.getNumerator());
		swap1.rationalise();
		swap2.rationalise();
		result = swap1 / swap2;
cerr << ((result < null) ? "failed" : "ok") << endl;
	}

	if (result < null) {		// still overflow, try to approximate
cerr << "safeDiv try approximate ";
		rational approximation = dur1;
		while (result.getNumerator() < 0) {
			approximation.set(approximation.getNumerator()/2, approximation.getDenominator()/2);
			if (!approximation.getDenominator() || !approximation.getNumerator()) {
				result.set(0,1);		// no solution found
				break;
			}
			else result = approximation / dur2;
		}
cerr << ((result < null) ? "failed" : "ok ") << string(result) << endl;
	}
	result.rationalise();
	return result;
}
/*

//________________________________________________________________________
rational durationOperation::safeMult ( const rational& dur1, const rational& dur2 ) const
{
	rational result = dur1 * dur2;
	const rational null(0,1);
	
	if (result < null) {		// overflow has occured, try another way
cerr << "safeMult try swap " << string(dur1) << " - " << string(dur2) << " ";
		rational swap1 (dur1.getNumerator(), dur2.getDenominator());
		rational swap2 (dur1.getDenominator(), dur2.getNumerator());
		swap1.rationalise();
		swap2.rationalise();
		result = swap1 * swap2;
cerr << ((result < null) ? "failed" : "ok") << endl;
	}

	if (result < null) {		// still overflow, try to approximate
cerr << "safeMult try approximate ";
		rational approximation = dur1;
		while (result < null) {
			approximation.set(approximation.getNumerator()/2, approximation.getDenominator()/2);
			if (!approximation.getDenominator() || !approximation.getNumerator()) {
				result.set(0,1);		// no solution found
				break;
			}
			else result = approximation * dur2;
		}
cerr << ((result < null) ? "failed" : "ok") << endl;
	}

	result.rationalise();
	return result;
}
*/

//________________________________________________________________________
// a bounded multiplication operation:
// constraints the denominator to values <= maxDenom
// computes the closest approximation when necessary
rational durationOperation::boundedMult ( const rational& dur1, const rational& dur2, int maxDenom ) const
{
	rational result = dur1 * dur2;
	result.rationalise();
	if (result.getDenominator() > maxDenom) {
		float val = float(result);
		float err = 9999;			// used to store the minimum error
		rational approx(0,1);		// used to store the corresponding rational

		for (int div=1; div<kMaxDivider; div++) {
			if (fPrimeNumbers[div]==true) { // avoid prime numbers
				bool done = false;
				float previousErr = 9999;			// used to detect closest approximations
				for (int num=1; !done; num++) {
					rational r(num, div);
					float localVal = float(r);
					float localErr = (localVal > val) ? localVal - val : val - localVal;
					if ( localErr > previousErr) done = true;
					else {
						previousErr = localErr;
						if (localErr < err) {
							err = localErr;
							approx = r;
						}
					}
				}
			}
		}
//cerr << "boundedMult scan for " <<  string(result) << " -> " << string(approx) << endl;
		result = approx;		
	}
	return result;
}

//________________________________________________________________________
rational durationOperation::stretch ( const rational& duration )
{
	
	if (duration.getNumerator() != ARNote::kUndefined)
		fCurrentDurationIn = duration;
	rational stretched = fCurrentDurationIn;
	stretched.rationalise();
	stretched = boundedMult(stretched, fFactor);

	if (stretched == fCurrentDurationOut)
		stretched.set (ARNote::kUndefined, 4);
	else
		fCurrentDurationOut = stretched;
	return stretched;
}

//________________________________________________________________________
// normalize meter to get a pow(2) denominator 
rational durationOperation::normalizeMeter (const rational& meter) const
{
	rational normalized = meter;
	normalized.rationalise();
	switch ( meter.getDenominator()) {
		case 1:
			normalized.set (2*meter.getNumerator(), 2*meter.getDenominator());
			break;
#if 0
		case 2:
		case 4:
		case 8:
		case 16:
		case 32:
		case 64:
			break;
		default:
			normalized.set(0,1);
#endif
	}
	if (meter.getNumerator() == 1)
		normalized.set (2*meter.getNumerator(), 2*meter.getDenominator());
	return normalized;
}

//________________________________________________________________________
Sguidoattribute	durationOperation::stretchMeter (const rational& meter) const
{
	Sguidoattribute attr;
	rational newMeter = normalizeMeter (boundedMult(meter, fFactor, 64));
	if (newMeter.getNumerator()) {
		attr = guidoattribute::create();
		if (attr) attr->setValue (string(newMeter), true);
	}
	return attr;
}

//________________________________________________________________________
// The visit methods
//________________________________________________________________________
void durationOperation::visitStart ( SARNote& elt )
{
	SARNote note = copy(elt);
	rational duration = stretch(elt->duration());
	if (note) {
		*note = duration;
		Sguidoelement cc = note;
		push( copy (elt, cc), false );
	}
}

//________________________________________________________________________
void durationOperation::visitStart ( SARVoice& elt )
{
	fCurrentDurationIn = fCurrentDurationOut = rational(1,4);
	clonevisitor::visitStart(elt);
}

//________________________________________________________________________
void durationOperation::visitStart ( SARMeter& elt )
{
	rational meter;
	Sguidotag tag = elt;
	clonevisitor::visitStart(tag);
	return;
	
	if (fFactor != rational(1,1)) {
		Sguidoattribute attr = elt->getAttribute(0);
		if (attr) {
			string meterStr = attr->getValue();
			if (meterStr.size()) {
				if (meterStr == "C") attr = stretchMeter(rational(4,4));
				else if (meterStr == "C/") attr = stretchMeter(rational(2,2));
				else if (meterStr == "c/") attr = stretchMeter(rational(2,2));
				else {
					int num, denum;
					int n = sscanf (meterStr.c_str(), "%d/%d", &num, &denum);
					if (n == 2)
						attr = stretchMeter(rational(num,denum));
				}
			}
			if (attr) {
				tag = ARFactory::instance().createTag("meter");
				if (tag) tag->add(attr);
			}
		}
	}
	clonevisitor::visitStart(tag);
}

}
