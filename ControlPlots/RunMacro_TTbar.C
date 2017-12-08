void RunMacro_TTbar()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR TTbar CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_TTBarControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"TTbarControlRegion.root\", 1) ");


}
