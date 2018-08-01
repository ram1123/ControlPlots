#include "controlplotvars_CHS_2lep.h"

void RunMacro_Zjet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_ZjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", controlplotvars_CHS_2lep, \"ZjetControlRegion.root\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_ZjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36.txt\", controlplotvars_CHS_2lep, \"ZjetControlRegion.root\", 0) ");
    
}
