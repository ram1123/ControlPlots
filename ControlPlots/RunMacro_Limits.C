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
//	cut file,	sample file,	variable file,	OutputRootfileName,	0/1 if 1 then scale signal by 100,  RECREATE root file or UPDATE, 0/1 need data histo or not
//
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", commonplotvars_chs , \"Nominal.root\" , 0 , \"RECREATE\" , 1) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_jes_up.txt\", commonplotvars_chs_jes_up , \"Nominal.root\", 0 , \"UPDATE\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_jes_up.txt\", commonplotvars_chs_jes_up , \"jes_up.root\", 0 , \"RECREATE\") ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_jes_dn.txt\", commonplotvars_chs_jes_dn , \"Nominal.root\" , 0, \"UPDATE\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_jes_dn.txt\", commonplotvars_chs_jes_dn , \"jes_dn.root\" , 1, \"RECREATE\") ");
  /*
    //
    //
    //	Add PU up/dn
    //
    gROOT->Reset();
    system("sed 's/pu_Weight/pu_Weight_up/g' myControlPlots.C > myControlPlots_temp_up.C");
    system("sed -i 's/myControlPlots/myControlPlots_temp_up/g' myControlPlots_temp_up.C");
    gROOT->ProcessLine(".L myControlPlots_temp_up.C+");
    gROOT->ProcessLine("myControlPlots_temp_up(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_pu_up.txt\", commonplotvars_chs , \"Nominal.root\" , 0 , \"UPDATE\" , 0) ");
    system("rm myControlPlots_temp_up.C");

    gROOT->Reset();
    system("sed 's/pu_Weight/pu_Weight_down/g' myControlPlots.C > myControlPlots_temp_dn.C");
    system("sed -i 's/myControlPlots/myControlPlots_temp_dn/g' myControlPlots_temp_dn.C");
    gROOT->ProcessLine(".L myControlPlots_temp_dn.C+");
    gROOT->ProcessLine("myControlPlots_temp_dn(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_pu_dn.txt\", commonplotvars_chs , \"Nominal.root\" , 0 , \"UPDATE\" , 0) ");
    system("rm myControlPlots_temp_dn.C");

 */  
//-------------------------------------
}
