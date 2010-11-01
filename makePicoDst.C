
#include <TSystem>

class StMaker;
class StChain;
class StPicoDstMaker;
class StMuDstMaker;


StChain *chain;
void makePicoDst(const Int_t runnumber=11100044, const Char_t *inputFile="st_physics_11100044_raw_1010001.MuDst.root", const bool creatingPhiWgt = kFALSE)
{
        Int_t nEvents = 10000000;
//	Int_t nEvents = 50;	
//Load all the System libraries
	
  	gSystem->Load("libTable");
  	gSystem->Load("libPhysics");
  	gSystem->Load("St_base");
  	gSystem->Load("StChain");
  	gSystem->Load("St_Tables");
  	gSystem->Load("StUtilities");        // new addition 22jul99
  	gSystem->Load("StTreeMaker");
  	gSystem->Load("StIOMaker");
  	gSystem->Load("StarClassLibrary");
  	gSystem->Load("StTriggerDataMaker"); // new starting from April 2003
  	gSystem->Load("StBichsel");
  	gSystem->Load("StEvent");
  	gSystem->Load("StEventUtilities");
  	gSystem->Load("StDbLib");
  	gSystem->Load("StEmcUtil");
  	gSystem->Load("StTofUtil");
  	gSystem->Load("StPmdUtil");
  	gSystem->Load("StPreEclMaker");
  	gSystem->Load("StStrangeMuDstMaker");
  	gSystem->Load("StMuDSTMaker");

	if(!creatingPhiWgt) {
		gSystem->Load("StTpcDb");
		gSystem->Load("StMcEvent");
		gSystem->Load("StMcEventMaker");
		gSystem->Load("StDaqLib");
		gSystem->Load("libgen_Tables");
 		gSystem->Load("libsim_Tables");
  		gSystem->Load("libglobal_Tables");
		gSystem->Load("StEmcTriggerMaker");
		gSystem->Load("StEmcUtil");//mine
		gSystem->Load("StEmcRawMaker");
		gSystem->Load("StEmcADCtoEMaker");
		gSystem->Load("StPreEclMaker");
		gSystem->Load("StEpcMaker");
		gSystem->Load("StEmcSimulatorMaker");
		gSystem->Load("StEmcUtil");
		gSystem->Load("StDbBroker");
		gSystem->Load("StDetectorDbMaker");
		gSystem->Load("StDbUtilities");
		gSystem->Load("St_db_Maker");
	}

        gSystem->Load("StPicoDstMaker");

	chain = new StChain();

	StMuDstMaker *MuDstMaker = new StMuDstMaker(0,0,"",inputFile,"MuDst",100);
        MuDstMaker->SetStatus("*",0);
        MuDstMaker->SetStatus("MuEvent",1);
        MuDstMaker->SetStatus("PrimaryVertices",1);
        MuDstMaker->SetStatus("PrimaryTracks",1);
        MuDstMaker->SetStatus("GlobalTracks",1);
        MuDstMaker->SetStatus("BTof*",1);
        MuDstMaker->SetStatus("Emc*",1);
	
	if(!creatingPhiWgt) {
		St_db_Maker *dbMk = new St_db_Maker("db","MySQL:StarDb","$STAR/StarDb","StarDb");

		StEmcADCtoEMaker *adc2e = new StEmcADCtoEMaker();
  		adc2e->setPrint(false);
  		//adc2e->setFillHisto(false);
  		//adc2e->setDebug(false); //more histograms
  		//adc2e->setSMDRmsCut(0,0);
  		adc2e->saveAllStEvent(true);
  		//adc2e->setRemoveGhostEvent(false);
  		//adc2e->setTallyHist(mTally);
  		//adc2e->setDbName("Calibrations/emc/y3");

 	 	StPreEclMaker *pre_ecl=new StPreEclMaker();
  		pre_ecl->setPrint(kFALSE);
  		StEpcMaker *epc=new StEpcMaker();
  		epc->setPrint(kFALSE);
	}
	
	StPicoDstMaker *picoMaker = new StPicoDstMaker(1,inputFile,"picoDst");
        picoMaker->setRunNumber(runnumber);

	chain->Init();
	cout<<"chain->Init();"<<endl;
	int total = 0;
	for (Int_t i=0; i<nEvents; i++){
	  if(i%100==0)
		cout << "Working on eventNumber " << i << endl;
		
	  chain->Clear();
	  int iret = chain->Make(i);
		
	  if (iret) { cout << "Bad return code!" << iret << endl; break;}

	  total++;
		
	}
	
	cout << "****************************************** " << endl;
	cout << "Work done... now its time to close up shop!"<< endl;
	cout << "****************************************** " << endl;
	chain->Finish();
	cout << "****************************************** " << endl;
	cout << "total number of events  " << total << endl;
	cout << "****************************************** " << endl;
	
	delete chain;
	
	
}