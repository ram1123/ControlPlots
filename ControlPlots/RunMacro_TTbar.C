void RunMacro_TTbar()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR TTbar CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_TTBarControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", commonplotvars_chs , \"TTbarControlRegion.root\", 1) ");


}
