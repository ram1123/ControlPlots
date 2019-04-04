void RunMacro_SignalRegion()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2019_03_27_16h16.txt\", commonplotvars_chs , \"SignalRegion.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2019_03_28_03h35_FullJetPho.txt\", commonplotvars_chs , \"SignalRegion.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2019_03_28_03h30_L1prefire_CleanJet_CleanPho.txt\", commonplotvars_chs , \"SignalRegion.root\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2019_03_28_14h27.txt\", commonplotvars_chs , \"SignalRegion.root\", 0) ");
    
}
