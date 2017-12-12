#include "controlplotvars_CHS_jes_up.h"
#include "controlplotvars_CHS_jes_dn.h"

void RunMacro_Limits()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
    
//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
// OPTIONS FOR PROCESSLINE
//
//	cut file,	sample file,	variable file,	OutputRootfileName,	0/1 if 1 then scale signal by 100,  RECREATE root file or UPDATE
//
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"Nominal.root\" , 0 , \"RECREATE\" ) ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesup.txt\", commonplotvars_chs_jes_up , \"Nominal.root\", 0 , \"UPDATE\") ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesdn.txt\", commonplotvars_chs_jes_dn , \"Nominal.root\" , 0, \"UPDATE\") ");
   
//-------------------------------------
}
