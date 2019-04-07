void RunMacro_Wjet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"CutFiles/DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"SampleFiles/DibosonBoostedElMuSamples13TeV_Run_2017_Frameworkupdate_WWTree_2019_04_05_07h46.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    
}
