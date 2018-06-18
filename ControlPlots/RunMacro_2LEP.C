#include "controlplotvars_CHS_2lep.h"

void RunMacro_2LEP()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_2LEP_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", controlplotvars_CHS_2lep, \"LEP_ptScale_Down.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_2LEP_Tighter_CHS.txt\", \"ZV_DibosonBoostedElMuSamples13TeV.txt\", controlplotvars_CHS_2lep, \"LEP_ptScale_Nominal.root\", 0) ");
    
}
