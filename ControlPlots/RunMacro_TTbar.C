void RunMacro_TTbar()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR TTbar CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_TTBarControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36.txt\", commonplotvars_chs , \"TTbarControlRegion.root\", 0) ");


}
