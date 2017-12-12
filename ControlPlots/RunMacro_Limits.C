void RunMacro_Limits()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
    
//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"Nominal.root\" , 1 ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesup.txt\", commonplotvars_chs , \"JES_up.root\", 0 ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesdn.txt\", commonplotvars_chs , \"JES_dn.root\" , 0) ");
   
//-------------------------------------
}
