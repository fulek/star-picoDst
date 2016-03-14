#ifndef StPicoBTOWHit_h
#define StPicoBTOWHit_h

class StPicoDst;

#include "TObject.h"
#include "stdio.h"

class StPicoBTOWHit : public TObject {
 public:
  StPicoBTOWHit();
  ~StPicoBTOWHit();
  StPicoBTOWHit(int, int, float);
  void    Clear(const Option_t *opt="");
  virtual void Print(const Char_t *option = "") const;  ///< Print trigger info
 
  Int_t   id() const;
  Int_t   adc() const;
  Float_t energy() const;

 protected:
  UShort_t mId;    // towerId 1-4800
  UShort_t mAdc;   // adc
  Short_t  mE;     // Energy * 1000;
  

  friend class StPicoDst;

  ClassDef(StPicoBTOWHit, 1)
};

inline Int_t   StPicoBTOWHit::id() const     { return (Int_t)mId; }
inline Int_t   StPicoBTOWHit::adc() const    { return (Int_t)mAdc; }
inline Float_t StPicoBTOWHit::energy() const { return (Float_t)mE/1000.; }
#endif
