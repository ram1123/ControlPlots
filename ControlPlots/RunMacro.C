void RunMacro()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
  //gROOT->ProcessLine(".L model.C+");
//-------------------------------------
//	FOR LIMITS
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_T2.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial2.txt\", commonplotvars_chs ) ");
//-------------------------------------
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");
    

//-------------------------------------
//-------------------------------------
//	FOR TTbar CR 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_TTBarControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");


//-------------------------------------
//	FOR (mjj>800 && deta<4.0) or (mjj<800 && deta>4.0) CR 
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_MjjDetaControlRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");
    
//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"Nominal.root\" , 0 ) ");
    
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesup.txt\", commonplotvars_chs , \"JES_up.root\" ) ");
    //gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1_jesdn.txt\", commonplotvars_chs , \"JES_dn.root\" ) ");
   
//-------------------------------------
    //gROOT->ProcessLine("Wjet_loose()");
    //gROOT->ProcessLine("Wjet_tight()");
    //gROOT->ProcessLine("TopControl()");
    //gROOT->ProcessLine("Wjet_tighter()");
}
