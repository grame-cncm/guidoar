/*
  GUIDO Library
  Copyright (C) 2006  Grame

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

#ifdef WIN32
# pragma warning (disable : 4786)
#endif

#include <iostream>

#include "guidotags.h"
#include "guidovariable.h"
#include "ARFactory.h"
#include "ARChord.h"
#include "ARNote.h"
#include "AROthers.h"
#include "ARTag.h"

using namespace std; 

namespace guido 
{

//______________________________________________________________________________
template<int elt>
class newTagFunctor : public functor<Sguidotag,long> {
	public:
		Sguidotag operator ()(long id) { return ARTag<elt>::create(id); }
};

//______________________________________________________________________________
SARMusic ARFactory::createMusic() const
{
	SARMusic elt = ARMusic::create();
	if (elt) elt->setName("music");
	return elt;
}

//______________________________________________________________________________
SARVoice ARFactory::createVoice() const
{
	SARVoice elt = ARVoice::create();
	if (elt) elt->setName("voice");
	return elt;
}

//______________________________________________________________________________
SARChord ARFactory::createChord() const
{
	SARChord elt = ARChord::create();
	if (elt) elt->setName("chord");
	return elt;
}

//______________________________________________________________________________
SARNote ARFactory::createNote(const std::string& name) const
{
	SARNote elt = ARNote::create();
	if (elt) elt->setName(name);
	return elt;
}

//______________________________________________________________________________
Sguidovariable ARFactory::createVariable(const std::string& name) const
{
	Sguidovariable var = guidovariable::create();
	var->setName(name);
	return var;
}

//______________________________________________________________________________
Sguidotag ARFactory::createTag(const string& eltname, long id) const
{ 
	map<std::string, NewTagFunctor*>::const_iterator i = fMap.find( eltname );
	if (i != fMap.end()) {
		NewTagFunctor* f= i->second;
		if (f) {
			Sguidotag elt = (*f)(id);
			elt->setName(eltname);
			return elt;
		}
	}
	cerr << "Sguidoelement factory::create called with unknown element \"" << eltname << "\"" << endl;
	return 0;
}

//______________________________________________________________________________
ARFactory::ARFactory() 
{
	fMap["acc"]			= new newTagFunctor<kTAcc>;
	fMap["accidental"]	= new newTagFunctor<kTAccidental>;
	fMap["accelBegin"]	= new newTagFunctor<kTAccelBegin>;
	fMap["accelEnd"]	= new newTagFunctor<kTAccelEnd>;
	fMap["accelerando"]	= new newTagFunctor<kTAccel>;
	fMap["accel"]		= fMap["accelerando"];;
	fMap["accent"]		= new newTagFunctor<kTAccent>;
	fMap["accolade"]	= new newTagFunctor<kTAccol>;
	fMap["accol"]		= new newTagFunctor<kTAccol>;
	fMap["alter"]		= new newTagFunctor<kTAlter>;
	fMap["arpeggio"]	= new newTagFunctor<kTArpeggio>;
	fMap["auto"]		= new newTagFunctor<kTAuto>;
	fMap["bar"]			= new newTagFunctor<kTBar>;
	fMap["barFormat"]	= new newTagFunctor<kTBarFormat>;
	fMap["beam"]		= new newTagFunctor<kTBeam>;
	fMap["bm"]			= fMap["beam"];
	fMap["b"]			= fMap["beam"];
	fMap["beamBegin"]	= new newTagFunctor<kTBeamBegin>;
	fMap["beamEnd"]		= new newTagFunctor<kTBeamEnd>;
	fMap["beamsAuto"]	= new newTagFunctor<kTBeamsAuto>;
	fMap["beamsFull"]	= new newTagFunctor<kTBeamsFull>;
	fMap["beamsOff"]	= new newTagFunctor<kTBeamsOff>;
	fMap["bembel"]		= new newTagFunctor<kTBembel>;
	fMap["bow"]			= new newTagFunctor<kTBow>;
	fMap["breathMark"]	= new newTagFunctor<kTBreathMark>;
	fMap["chord"]		= new newTagFunctor<kTChord>;
	fMap["clef"]		= new newTagFunctor<kTClef>;
	fMap["cluster"]		= new newTagFunctor<kTCluster>;
	fMap["coda"]		= new newTagFunctor<kTCoda>;
	fMap["color"]		= new newTagFunctor<kTColor>;
	fMap["colour"]		= fMap["color"];
	fMap["composer"]	= new newTagFunctor<kTComposer>;
	fMap["cresc"]		= new newTagFunctor<kTCresc>;
	fMap["crescendo"]	= fMap["cresc"];
	fMap["crescBegin"]	= new newTagFunctor<kTCrescBegin>;
	fMap["crescEnd"]	= new newTagFunctor<kTCrescEnd>;
	fMap["cue"]			= new newTagFunctor<kTCue>;
	fMap["daCapo"]		= new newTagFunctor<kTDaCapo>;
	fMap["daCapoAlFine"] 	= new newTagFunctor<kTDaCapoAlFine>;
	fMap["daCoda"]			= new newTagFunctor<kTDaCoda>;
	fMap["dalSegno"]		= new newTagFunctor<kTDalSegno>;
	fMap["dalSegnoAlFine"]	= new newTagFunctor<kTDalSegnoAlFine>;
	fMap["decresc"]		= new newTagFunctor<kTDecresc>;
	fMap["decrescendo"]	= fMap["decresc"];
	fMap["dim"]			= fMap["decresc"];
	fMap["diminuendo"]	= fMap["dim"];
	fMap["decrescBegin"]= new newTagFunctor<kTDecrescBegin>;
	fMap["dimBegin"]	= new newTagFunctor<kTDimBegin>;
	fMap["diminuendoBegin"]	= fMap["dimBegin"];
	fMap["decrescEnd"]		= new newTagFunctor<kTDecrescEnd>;
	fMap["dimEnd"]			= new newTagFunctor<kTDimEnd>;
	fMap["diminuendoEnd"]	= fMap["dimEnd"];
	fMap["dispDur"]			= new newTagFunctor<kTDispDur>;
	fMap["displayDuration"]	= fMap["dispDur"];
	fMap["dotFormat"]	= new newTagFunctor<kTDotFormat>;
	fMap["doubleBar"]	= new newTagFunctor<kTDoubleBar>;
	fMap["endBar"]		= new newTagFunctor<kTEndBar>;
	fMap["fBeam"]		= new newTagFunctor<kTFBeam>;
	fMap["fBeamBegin"]	= new newTagFunctor<kTFBeamBegin>;
	fMap["fBeamEnd"]	= new newTagFunctor<kTFBeamEnd>;
	fMap["fermata"]		= new newTagFunctor<kTFermata>;
	fMap["fine"]		= new newTagFunctor<kTFine>;
	fMap["fingering"]	= new newTagFunctor<kTFingering>;
	fMap["fing"]		= fMap["fingering"];
	fMap["footer"]		= new newTagFunctor<kTFooter>;
	fMap["glissando"]	= new newTagFunctor<kTGlissando>;
	fMap["glissandoBegin"]	= new newTagFunctor<kTGlissandoBegin>;
	fMap["glissandoEnd"]	= new newTagFunctor<kTGlissandoEnd>;
	fMap["grace"]		= new newTagFunctor<kTGrace>;
	fMap["harmonic"]	= new newTagFunctor<kTHarmonic>;
	fMap["harmony"]		= new newTagFunctor<kTHarmony>;
	fMap["headsCenter"]	= new newTagFunctor<kTHeadsCenter>;
	fMap["headsLeft"]	= new newTagFunctor<kTHeadsLeft>;
	fMap["headsNormal"]	= new newTagFunctor<kTHeadsNormal>;
	fMap["headsReverse"]= new newTagFunctor<kTHeadsReverse>;
	fMap["headsRight"]	= new newTagFunctor<kTHeadsRight>;
	fMap["instr"]		= new newTagFunctor<kTInstr>;
	fMap["instrument"]	= fMap["instr"];
	fMap["intens"]		= new newTagFunctor<kTIntens>;
	fMap["intensity"]	= fMap["intens"];
	fMap["i"]			= fMap["intens"];
	fMap["key"]			= new newTagFunctor<kTKey>;
	fMap["label"]		= new newTagFunctor<kTLabel>;
	fMap["lyrics"]		= new newTagFunctor<kTLyrics>;
	fMap["marcato"]		= new newTagFunctor<kTMarcato>;
	fMap["mark"]		= new newTagFunctor<kTMark>;
	fMap["meter"]		= new newTagFunctor<kTMeter>;
	fMap["mordent"]		= new newTagFunctor<kTMord>;
	fMap["mord"]		= fMap["mordent"];
	fMap["mrest"]		= new newTagFunctor<kTMrest>;
	fMap["newLine"]		= new newTagFunctor<kTNewLine>;
	fMap["newSystem"]	= new newTagFunctor<kTNewSystem>;
	fMap["newPage"]		= new newTagFunctor<kTNewPage>;
	fMap["noteFormat"]	= new newTagFunctor<kTNoteFormat>;
	fMap["oct"]			= new newTagFunctor<kTOct>;
	fMap["octava"]		= fMap["oct"];
	fMap["pageFormat"]	= new newTagFunctor<kTPageFormat>;
	fMap["pedalOn"]		= new newTagFunctor<kTPedalOn>;
	fMap["pedalOff"]	= new newTagFunctor<kTPedalOff>;
	fMap["pizzicato"]	= new newTagFunctor<kTPizz>;
	fMap["pizz"]		= fMap["pizzicato"];
	fMap["repeatBegin"]	= new newTagFunctor<kTRepeatBegin>;
	fMap["repeatEnd"]	= new newTagFunctor<kTRepeatEnd>;
	fMap["restFormat"]	= new newTagFunctor<kTRestFormat>;
	fMap["ritBegin"]	= new newTagFunctor<kTRitBegin>;
	fMap["ritEnd"]		= new newTagFunctor<kTRitEnd>;
	fMap["ritardando"]	= new newTagFunctor<kTRit>;
	fMap["rit"]			= fMap["ritardando"];
	fMap["segno"]		= new newTagFunctor<kTSegno>;
	fMap["set"]			= fMap["auto"];
//	fMap["shortFermata"]= new newTagFunctor<kTShortFermata>;
	fMap["slur"]		= new newTagFunctor<kTSlur>;
	fMap["sl"]			= fMap["slur"];
	fMap["slurBegin"]	= new newTagFunctor<kTSlurBegin>;
	fMap["slurEnd"]		= new newTagFunctor<kTSlurEnd>;
	fMap["space"]		= new newTagFunctor<kTSpace>;
	fMap["special"]		= new newTagFunctor<kTSpecial>;
	fMap["splitChord"]	= new newTagFunctor<kTSplitChord>;
	fMap["staccBegin"]	= new newTagFunctor<kTStaccBegin>;
	fMap["staccEnd"]	= new newTagFunctor<kTStaccEnd>;
	fMap["staccato"]	= new newTagFunctor<kTStacc>;
	fMap["stacc"]		= fMap["staccato"];
	fMap["staff"]		= new newTagFunctor<kTStaff>;
	fMap["staffFormat"]	= new newTagFunctor<kTStaffFormat>;
	fMap["staffOff"]	= new newTagFunctor<kTStaffOff>;
	fMap["staffOn"]		= new newTagFunctor<kTStaffOn>;
	fMap["stemsAuto"]	= new newTagFunctor<kTStemsAuto>;
	fMap["stemsDown"]	= new newTagFunctor<kTStemsDown>;
	fMap["stemsOff"]	= new newTagFunctor<kTStemsOff>;
	fMap["stemsUp"]		= new newTagFunctor<kTStemsUp>;
	fMap["symbol"]		= new newTagFunctor<kTSymbol>;
	fMap["systemFormat"]= new newTagFunctor<kTSystemFormat>;
	fMap["tempo"]		= new newTagFunctor<kTTempo>;
	fMap["tenuto"]		= new newTagFunctor<kTTen>;
	fMap["ten"]			= fMap["tenuto"];
	fMap["text"]		= new newTagFunctor<kTText>;
	fMap["t"]			= fMap["text"];
	fMap["tie"]			= new newTagFunctor<kTTie>;
	fMap["tieBegin"]	= new newTagFunctor<kTTieBegin>;
	fMap["tieEnd"]		= new newTagFunctor<kTTieEnd>;
	fMap["title"]		= new newTagFunctor<kTTitle>;
	fMap["tremolo"]		= new newTagFunctor<kTTrem>;
	fMap["trem"]		= fMap["tremolo"];
	fMap["tremoloBegin"]= new newTagFunctor<kTTremBegin>;
	fMap["tremBegin"]	= fMap["tremoloBegin"];
	fMap["tremoloEnd"]	= new newTagFunctor<kTTremEnd>;
	fMap["tremEnd"]		= fMap["tremoloEnd"];
	fMap["trill"]		= new newTagFunctor<kTTrill>;
	fMap["trillBegin"]	= new newTagFunctor<kTTrillBegin>;
	fMap["trillEnd"]	= new newTagFunctor<kTTrillEnd>;
	fMap["tuplet"]		= new newTagFunctor<kTTuplet>;
	fMap["tupletBegin"]	= new newTagFunctor<kTTupletBegin>;
	fMap["tupletEnd"]	= new newTagFunctor<kTTupletEnd>;
	fMap["turn"]		= new newTagFunctor<kTTurn>;
	fMap["units"]		= new newTagFunctor<kTUnits>;
	fMap["volta"]		= new newTagFunctor<kTVolta>;
	fMap["voltaBegin"]	= new newTagFunctor<kTVoltaBegin>;
	fMap["voltaEnd"]	= new newTagFunctor<kTVoltaEnd>;
}

//______________________________________________________________________________
// WARNING !
// the functors map contains aliases that must be set to 0 before deallocation
//
ARFactory::~ARFactory()
{
	fMap["accel"]		= 0;
	fMap["b"]			= 0;
	fMap["bm"]			= 0;
	fMap["chord"]		= 0;
	fMap["colour"]		= 0;
	fMap["crescendo"]	= 0;
	fMap["decrescendo"]	= 0;
	fMap["dim"]			= 0;
	fMap["diminuendo"]	= 0;
	fMap["diminuendoBegin"]	= 0;
	fMap["diminuendoEnd"]	= 0;
	fMap["displayDuration"]	= 0;
	fMap["fing"]		= 0;
	fMap["i"]			= 0;
	fMap["instrument"]	= 0;
	fMap["intensity"]	= 0;
	fMap["mord"]		= 0;
	fMap["octava"]		= 0;
	fMap["pizz"]		= 0;
	fMap["rit"]			= 0;
	fMap["set"]			= 0;
	fMap["sl"]			= 0;
	fMap["stacc"]		= 0;
	fMap["t"]			= 0;
	fMap["ten"]			= 0;
	fMap["trem"]		= 0;
	fMap["tremBegin"]	= 0;
	fMap["tremEnd"]		= 0;

	TFunctors::iterator i = fMap.begin();
	while (i != fMap.end()) {
		delete i->second;
		i++;
	}
}


} // namespace
