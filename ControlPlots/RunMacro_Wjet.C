void RunMacro_Wjet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2019_03_29_03h24.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    
}
