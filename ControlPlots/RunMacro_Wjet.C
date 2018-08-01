void RunMacro_Wjet()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_09_18h38.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_06_12_05h33.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CleanedCode_Isolated_NaNFixed_Btag30GeV_2018_03_16_00h13.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_2018_04_06_09h22.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36.txt\", commonplotvars_chs , \"WjetControlRegion.root\", 0) ");
    
}
