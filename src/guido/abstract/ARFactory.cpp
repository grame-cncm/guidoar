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
	fMap["acc"]			= new newTagFunctor<kTacc>;
	fMap["accidental"]	= new newTagFunctor<kTaccidental>;
	fMap["accelBegin"]	= new newTagFunctor<kTaccelBegin>;
	fMap["accelEnd"]	= new newTagFunctor<kTaccelEnd>;
	fMap["accelerando"]	= new newTagFunctor<kTaccelerando>;
	fMap["accel"]		= new newTagFunctor<kTaccel>;
	fMap["accent"]		= new newTagFunctor<kTaccent>;
	fMap["accolade"]	= new newTagFunctor<kTaccolade>;
	fMap["accol"]		= new newTagFunctor<kTaccol>;
	fMap["alter"]		= new newTagFunctor<kTalter>;
	fMap["arpeggio"]	= new newTagFunctor<kTarpeggio>;
	fMap["auto"]		= new newTagFunctor<kTauto>;
	fMap["bar"]			= new newTagFunctor<kTbar>;
	fMap["barFormat"]	= new newTagFunctor<kTbarFormat>;
	fMap["beam"]		= new newTagFunctor<kTbeam>;
	fMap["bm"]			= fMap["beam"];
	fMap["b"]			= fMap["beam"];
	fMap["beamBegin"]	= new newTagFunctor<kTbeamBegin>;
	fMap["beamEnd"]		= new newTagFunctor<kTbeamEnd>;
	fMap["beamsAuto"]	= new newTagFunctor<kTbeamsAuto>;
	fMap["beamsFull"]	= new newTagFunctor<kTbeamsFull>;
	fMap["beamsOff"]	= new newTagFunctor<kTbeamsOff>;
	fMap["bembel"]		= new newTagFunctor<kTbembel>;
	fMap["breathMark"]	= new newTagFunctor<kTbreathMark>;
	fMap["clef"]		= new newTagFunctor<kTclef>;
	fMap["cluster"]		= new newTagFunctor<kTcluster>;
	fMap["coda"]		= new newTagFunctor<kTcoda>;
	fMap["color"]		= new newTagFunctor<kTcolor>;
	fMap["colour"]		= fMap["color"];
	fMap["composer"]	= new newTagFunctor<kTcomposer>;
	fMap["cresc"]		= new newTagFunctor<kTcresc>;
	fMap["crescendo"]	= new newTagFunctor<kTcrescendo>;
	fMap["crescBegin"]	= new newTagFunctor<kTcrescBegin>;
	fMap["crescEnd"]	= new newTagFunctor<kTcrescEnd>;
	fMap["cue"]			= new newTagFunctor<kTcue>;
	fMap["daCapo"]		= new newTagFunctor<kTdaCapo>;
	fMap["daCapoAlFine"] 	= new newTagFunctor<kTdaCapoAlFine>;
	fMap["daCoda"]			= new newTagFunctor<kTdaCoda>;
	fMap["dalSegno"]		= new newTagFunctor<kTdalSegno>;
	fMap["dalSegnoAlFine"]	= new newTagFunctor<kTdalSegnoAlFine>;
	fMap["decresc"]		= new newTagFunctor<kTdecresc>;
	fMap["decrescendo"]	= fMap["decresc"];
	fMap["dim"]			= fMap["decresc"];
	fMap["diminuendo"]	= fMap["dim"];
	fMap["decrescBegin"]= new newTagFunctor<kTdecrescBegin>;
	fMap["dimBegin"]	= new newTagFunctor<kTdimBegin>;
	fMap["diminuendoBegin"]	= fMap["dimBegin"];
	fMap["decrescEnd"]		= new newTagFunctor<kTdecrescEnd>;
	fMap["dimEnd"]			= new newTagFunctor<kTdimEnd>;
	fMap["diminuendoEnd"]	= fMap["dimEnd"];
	fMap["dispDur"]			= new newTagFunctor<kTdispDur>;
	fMap["displayDuration"]	= fMap["dispDur"];
	fMap["dotFormat"]	= new newTagFunctor<kTdotFormat>;
	fMap["doubleBar"]	= new newTagFunctor<kTdoubleBar>;
	fMap["endBar"]		= new newTagFunctor<kTendBar>;
	fMap["fBeam"]		= new newTagFunctor<kTfBeam>;
	fMap["fBeamBegin"]	= new newTagFunctor<kTfBeamBegin>;
	fMap["fBeamEnd"]	= new newTagFunctor<kTfBeamEnd>;
	fMap["fermata"]		= new newTagFunctor<kTfermata>;
	fMap["fine"]		= new newTagFunctor<kTfine>;
	fMap["fingering"]	= new newTagFunctor<kTfingering>;
	fMap["footer"]		= new newTagFunctor<kTfooter>;
	fMap["fing"]		= new newTagFunctor<kTfing>;
	fMap["glissando"]	= new newTagFunctor<kTglissando>;
	fMap["glissandoBegin"]	= new newTagFunctor<kTglissandoBegin>;
	fMap["glissandoEnd"]	= new newTagFunctor<kTglissandoEnd>;
	fMap["grace"]		= new newTagFunctor<kTgrace>;
	fMap["harmonic"]	= new newTagFunctor<kTharmonic>;
	fMap["harmony"]		= new newTagFunctor<kTharmony>;
	fMap["headsCenter"]	= new newTagFunctor<kTheadsCenter>;
	fMap["headsLeft"]	= new newTagFunctor<kTheadsLeft>;
	fMap["headsNormal"]	= new newTagFunctor<kTheadsNormal>;
	fMap["headsReverse"]= new newTagFunctor<kTheadsReverse>;
	fMap["headsRight"]	= new newTagFunctor<kTheadsRight>;
	fMap["instrument"]	= new newTagFunctor<kTinstrument>;
	fMap["instr"]		= new newTagFunctor<kTinstr>;
	fMap["intensity"]	= new newTagFunctor<kTintensity>;
	fMap["intens"]		= new newTagFunctor<kTintens>;
	fMap["i"]			= fMap["intens"];
	fMap["key"]			= new newTagFunctor<kTkey>;
	fMap["label"]		= new newTagFunctor<kTlabel>;
	fMap["lyrics"]		= new newTagFunctor<kTlyrics>;
	fMap["marcato"]		= new newTagFunctor<kTmarcato>;
	fMap["mark"]		= new newTagFunctor<kTmark>;
	fMap["meter"]		= new newTagFunctor<kTmeter>;
	fMap["mordent"]		= new newTagFunctor<kTmordent>;
	fMap["mord"]		= fMap["mordent"];
	fMap["mrest"]		= new newTagFunctor<kTmrest>;
	fMap["newLine"]		= new newTagFunctor<kTnewLine>;
	fMap["newSystem"]	= new newTagFunctor<kTnewSystem>;
	fMap["newPage"]		= new newTagFunctor<kTnewPage>;
	fMap["noteFormat"]	= new newTagFunctor<kTnoteFormat>;
	fMap["oct"]			= new newTagFunctor<kToct>;
	fMap["octava"]		= fMap["oct"];
	fMap["pageFormat"]	= new newTagFunctor<kTpageFormat>;
	fMap["pedalOn"]		= new newTagFunctor<kTpedalOn>;
	fMap["pedalOff"]	= new newTagFunctor<kTpedalOff>;
	fMap["pizzicato"]	= new newTagFunctor<kTpizzicato>;
	fMap["pizz"]		= fMap["pizzicato"];
	fMap["repeatBegin"]	= new newTagFunctor<kTrepeatBegin>;
	fMap["repeatEnd"]	= new newTagFunctor<kTrepeatEnd>;
	fMap["restFormat"]	= new newTagFunctor<kTrestFormat>;
	fMap["ritBegin"]	= new newTagFunctor<kTritBegin>;
	fMap["ritEnd"]		= new newTagFunctor<kTritEnd>;
	fMap["ritardando"]	= new newTagFunctor<kTritardando>;
	fMap["rit"]			= fMap["ritardando"];
	fMap["segno"]		= new newTagFunctor<kTsegno>;
	fMap["set"]			= fMap["auto"];
	fMap["shortFermata"]= new newTagFunctor<kTshortFermata>;
	fMap["slur"]		= new newTagFunctor<kTslur>;
	fMap["sl"]			= fMap["slur"];
	fMap["slurBegin"]	= new newTagFunctor<kTslurBegin>;
	fMap["slurEnd"]		= new newTagFunctor<kTslurEnd>;
	fMap["space"]		= new newTagFunctor<kTspace>;
	fMap["special"]		= new newTagFunctor<kTspecial>;
	fMap["staccBegin"]	= new newTagFunctor<kTstaccBegin>;
	fMap["staccEnd"]	= new newTagFunctor<kTstaccEnd>;
	fMap["staccato"]	= new newTagFunctor<kTstaccato>;
	fMap["stacc"]		= fMap["staccato"];
	fMap["staff"]		= new newTagFunctor<kTstaff>;
	fMap["staffFormat"]	= new newTagFunctor<kTstaffFormat>;
	fMap["staffOff"]	= new newTagFunctor<kTstaffOff>;
	fMap["staffOn"]		= new newTagFunctor<kTstaffOn>;
	fMap["stemsAuto"]	= new newTagFunctor<kTstemsAuto>;
	fMap["stemsDown"]	= new newTagFunctor<kTstemsDown>;
	fMap["stemsOff"]	= new newTagFunctor<kTstemsOff>;
	fMap["stemsUp"]		= new newTagFunctor<kTstemsUp>;
	fMap["systemFormat"]= new newTagFunctor<kTsystemFormat>;
	fMap["tempo"]		= new newTagFunctor<kTtempo>;
	fMap["tenuto"]		= new newTagFunctor<kTtenuto>;
	fMap["ten"]			= fMap["tenuto"];
	fMap["text"]		= new newTagFunctor<kTtext>;
	fMap["t"]			= fMap["text"];
	fMap["tie"]			= new newTagFunctor<kTtie>;
	fMap["tieBegin"]	= new newTagFunctor<kTtieBegin>;
	fMap["tieEnd"]		= new newTagFunctor<kTtieEnd>;
	fMap["title"]		= new newTagFunctor<kTtitle>;
	fMap["tremolo"]		= new newTagFunctor<kTtremolo>;
	fMap["trem"]		= fMap["tremolo"];
	fMap["tremoloBegin"]= new newTagFunctor<kTtremoloBegin>;
	fMap["tremBegin"]	= fMap["tremoloBegin"];
	fMap["tremoloEnd"]	= new newTagFunctor<kTtremoloEnd>;
	fMap["tremEnd"]		= fMap["tremoloEnd";
	fMap["trill"]		= new newTagFunctor<kTtrill>;
	fMap["trillBegin"]	= new newTagFunctor<kTtrillBegin>;
	fMap["trillEnd"]	= new newTagFunctor<kTtrillEnd>;
	fMap["tuplet"]		= new newTagFunctor<kTtuplet>;
	fMap["tupletBegin"]	= new newTagFunctor<kTtupletBegin>;
	fMap["tupletEnd"]	= new newTagFunctor<kTtupletEnd>;
	fMap["turn"]		= new newTagFunctor<kTturn>;
	fMap["units"]		= new newTagFunctor<kTunits>;
	fMap["volta"]		= new newTagFunctor<kTvolta>;
	fMap["voltaBegin"]	= new newTagFunctor<kTvoltaBegin>;
	fMap["voltaEnd"]	= new newTagFunctor<kTvoltaEnd>;
}

//______________________________________________________________________________
// WARNING !
// the functors map contains aliases that must be set to 0 before deallocation
//
ARFactory::~ARFactory()
{
	fMap["bm"]			= 0;
	fMap["b"]			= 0;
	fMap["colour"]		= 0;
	fMap["i"]			= 0;
	fMap["set"]			= 0;
	fMap["sl"]			= 0;
	fMap["chord"]		= 0;
	fMap["t"]			= 0;
	TFunctors::iterator i = fMap.begin();
	while (i != fMap.end()) {
		delete i->second;
		i++;
	}
}


} // namespace
