#include "controlplotvars_CHS_Limit.h"

void RunMacro_Limits_Templet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
    
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", commonplotvars_chs_limit, \"combine_limit.root\" , 0 , \"RECREATE\" , 1) ");
}
