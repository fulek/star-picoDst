#ifndef STAR_StPicoDstMaker
#define STAR_StPicoDstMaker
#include "StMaker.h"
#include "TClonesArray.h"
class TFile;
class TTree;
class StFile;
class StMuDst;
class StMuEvent;
class StMuTrack;
class StBTofHeader;
class StEmcCollection;
class StEmcPosition;
class StEmcGeom;
class StPicoDst;
class StPicoEvent;
class StPicoTrack;
class StPicoV0;
class StPicoCut;

#include "StPicoConstants.h"
#include "StPicoArrays.h"
#include <vector>
#include <utility>
#include <string>

#if !defined(ST_NO_NAMESPACES)
using namespace std;
#endif

class StPicoDstMaker : public StMaker {
 public: 
   StPicoDstMaker(const char *name="PicoDst");
   StPicoDstMaker(int mode, const char* fileName="", const char* name="PicoDst"); 
   virtual ~StPicoDstMaker();

   virtual Int_t Init();
   virtual Int_t Make();
   virtual void  Clear(Option_t *option="");
   virtual Int_t Finish();

   void printArrays();
   void SetStatus(const char *arrType,int status);

   void setRunNumber(Int_t);              
   void setCreatingPhiWgt(Bool_t);
   /// Returns null pointer if no StPicoDst
   StPicoDst *picoDst();
   /// In read mode, returns pointer to the chain of .picoDst.root files
   TChain* chain();
   /// Returns pointer to the current TTree, the top level io structure
   TTree* tree();
        
   /// Sets the split level for the file and all branches. Please refer to the ROOT manual (http://root.cern.ch) for more info
   void setSplit(int=99);
   /// Sets the buffer size for all branches.
   void setBufferSize(int=65536*4);
   /// Sets the compression level for the file and all branches. 0 means no compression, 9 is the higher compression level.
   void setCompression(int comp=9);
                          
 protected:
 #define saveDelete(t) { delete t; t=0;}
 
   void streamerOff();
  
   void openWrite();
   void write();
   void closeWrite(); 
   Int_t openRead();
   void  read();
   void setBranchAddresses();
   void closeRead();
   void setBranchAddresses(TChain*);
   void clearIndices();

   void initEmc();
   void finishEmc();
   
   void DeclareHistos();
   void WriteHistos();
   void FillHistograms(int, float*);

   void assignArrays();
   void clearArrays();
   void zeroArrays();
   void createArrays();
   TClonesArray* clonesArray(TClonesArray*& p, const char* type, int size, int& counter);

   Int_t MakeRead();
   Int_t MakeWrite();

   void fillTracks();
   void fillEvent();
   void fillV0();

   Int_t phiBin(int, StMuTrack *, float);
   void  addPhiWeight(StMuTrack *, float, float*);
   Int_t centrality(int);   
   bool getBEMC(StMuTrack *, int*, int*, float*, float*, int*);
   
   enum ioMode {ioRead, ioWrite};
   
   StMuDst*   mMuDst;
   StMuEvent* mMuEvent;
   StBTofHeader*    mBTofHeader;
   StEmcCollection* mEmcCollection;
   StEmcPosition*   mEmcPosition;
   StEmcGeom*       mEmcGeom[4];
   StPicoDst* mPicoDst;
   StPicoCut* mPicoCut;
   Int_t      mCentrality;
   Float_t    mBField;

   Int_t      mIoMode;         //! I/O mode:  0: - write,   1: - read
   Bool_t     mCreatingPhiWgt; //! creating phi weight files

   TString   mInputFileName;        //! *.list - MuDst or picoDst
   TString   mOutputFileName;       //! FileName
   TString   mPhiWgtFileName;       //! phi weight filename
   TString   mPhiTestFileName;       //! phi weight filename
   TFile*    mOutputFile;
   TFile*    mPhiWgtFile;
   Int_t     mRunNumber;

   TChain*   mChain;
   TTree*    mTTree;
   
   int mEventCounter;
   int mSplit;
   int mCompression;
   int mBufferSize;
   
   Int_t mIndex2Primary[nTrk];
   Int_t mMap2Track[nTrk];

   //
   TH1D*    mPhiWgtHist[nCen+1][nEW*nDet];
   static const char* mEW[nEW*nDet]; //!={"EE","EW","WE","WW","FarWest","West","East","FarEast"};
   Float_t mPhiWeightRead[nCen+1][nEW*nDet*nPhi];
   Float_t mPhiWeightWrite[nEW*nDet*nPhi];  // phi weight for the current event
         
   //
   friend class StPicoDst;

   TClonesArray*   mPicoAllArrays[__NALLPICOARRAYS__];   
   TClonesArray**  mPicoArrays;   //[__NPICOARRAYS__]
   TClonesArray**  mPicoV0Arrays; //[__NPICOV0ARRAYS__]
   char            mStatusArrays[__NALLPICOARRAYS__];
   
   ClassDef(StPicoDstMaker,1)
};

inline StPicoDst* StPicoDstMaker::picoDst() { return mPicoDst; }
inline TChain* StPicoDstMaker::chain() { return mChain; }
inline TTree* StPicoDstMaker::tree() { return mTTree; }
inline void StPicoDstMaker::setSplit(int split) { mSplit = split;}
inline void StPicoDstMaker::setCompression(int comp) { mCompression = comp;}
inline void StPicoDstMaker::setBufferSize(int buf) { mBufferSize = buf; }
inline void StPicoDstMaker::setRunNumber(int run) { mRunNumber = run; }
inline void StPicoDstMaker::setCreatingPhiWgt(bool val) { mCreatingPhiWgt = val; }
#endif