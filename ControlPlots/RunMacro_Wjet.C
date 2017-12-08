void RunMacro_Wjet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 1) ");
    
}
