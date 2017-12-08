void RunMacro_mjj()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR (mjj>800 && deta<4.0) or (mjj<800 && deta>4.0) CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_MjjDetaControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs, \"mjjDetajjControlRegion.root\", 1 ) ");
}
