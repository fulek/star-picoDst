#ifndef StPicoDst_h
#define StPicoDst_h


class StPicoDstMaker;
class StPicoEvent;
class StPicoTrack;
class StPicoEmcTrigger;
class StPicoMtdTrigger;
class StPicoBTOWHit;
class StPicoBTofHit;
class StPicoMtdHit;
class StPicoEmcPidTraits;
class StPicoBTofPidTraits;
class StPicoMtdPidTraits;
class StMuRpsCollection;

#include "TObject.h"
#include "TClonesArray.h"
#include "StPicoArrays.h"

class StPicoDst : public TObject {
public:
  /// constructor
  StPicoDst();
  /// set the pointers to the TClonesArrays
  static void set(StPicoDstMaker* maker);
  /// set the pointers to the TClonesArrays
  static void set(TClonesArray**);
  /// resets the pointers to the TClonesArrays to 0
  static void unset();

protected:
  /// array of TClonesArrays
  static TClonesArray** picoArrays;

public:
  /// returns pointer to the n-th TClonesArray
  static TClonesArray* picoArray(int type) { return picoArrays[type]; }

  /// returns pointer to current StPicoEvent (class holding the event wise information)
  static StPicoEvent* event() { return (StPicoEvent*)picoArrays[picoEvent]->UncheckedAt(0); }
  /// return pointer to i-th track
  static StPicoTrack* track(int i) { return (StPicoTrack*)picoArrays[picoTrack]->UncheckedAt(i); }
  /// return pointer to i-th trigger data
  static StPicoEmcTrigger* emcTrigger(int i) { return (StPicoEmcTrigger*)picoArrays[picoEmcTrigger]->UncheckedAt(i); }
  static StPicoMtdTrigger *mtdTrigger(int i) { return (StPicoMtdTrigger*)picoArrays[picoMtdTrigger]->UncheckedAt(i); }

  /// return pointer to i-th btow hit
  static StPicoBTOWHit* btowHit(int i) { return (StPicoBTOWHit*)picoArrays[picoBTOWHit]->UncheckedAt(i); }
  /// return pointer to i-th btof hit
  static StPicoBTofHit* btofHit(int i) { return (StPicoBTofHit*)picoArrays[picoBTofHit]->UncheckedAt(i); }
  /// return pointer to i-th mtd hit
  static StPicoMtdHit*  mtdHit(int i)  { return (StPicoMtdHit*)picoArrays[picoMtdHit]->UncheckedAt(i);   }

  /// return pointer to i-th emc pidTraits
  static StPicoEmcPidTraits* emcPidTraits(int i) { return (StPicoEmcPidTraits*)picoArrays[picoEmcPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th btof pidTraits
  static StPicoBTofPidTraits* btofPidTraits(int i) { return (StPicoBTofPidTraits*)picoArrays[picoBTofPidTraits]->UncheckedAt(i); }
  /// return pointer to i-th mtd pidTraits
  static StPicoMtdPidTraits* mtdPidTraits(int i) { return (StPicoMtdPidTraits*)picoArrays[picoMtdPidTraits]->UncheckedAt(i); }

  //returns pointer to current StMuRpsCollection
  static StMuRpsCollection* rpsCollection() { return (StMuRpsCollection*)picoArrays[picoRpsCollection]->UncheckedAt(0); }

  static unsigned int numberOfTracks() { return picoArrays[picoTrack]->GetEntries(); }
  static unsigned int numberOfEmcTriggers() { return picoArrays[picoEmcTrigger]->GetEntries(); }
  static unsigned int numberOfBTOWHits() { return picoArrays[picoBTOWHit]->GetEntries(); }
  static unsigned int numberOfBTofHits() { return picoArrays[picoBTofHit]->GetEntries(); }
  static unsigned int numberOfMtdHits()  { return picoArrays[picoMtdHit]->GetEntries();  }
  static unsigned int numberOfEmcPidTraits()  { return picoArrays[picoEmcPidTraits] ->GetEntries();  }
  static unsigned int numberOfBTofPidTraits() { return picoArrays[picoBTofPidTraits]->GetEntries();  }
  static unsigned int numberOfMtdPidTraits()  { return picoArrays[picoMtdPidTraits] ->GetEntries();  }

  virtual void Print(Option_t *option = "") const; ///< Print basic event info
  static void printTracks();
  static void printTriggers();
  static void printBTOWHits();
  static void printBTofHits();
  static void printMtdHits();
  static void printEmcPidTraits();
  static void printBTofPidTraits();
  static void printMtdPidTraits();

  ClassDef(StPicoDst,1)
};

#endif
