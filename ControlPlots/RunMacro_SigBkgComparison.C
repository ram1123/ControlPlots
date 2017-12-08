void RunMacro_SigBkgComparison()
{
    gROOT->ProcessLine(".L myControlPlots_SignalBkg_Comparison.C+");


//    gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedMuCuts13TeV_Signal_CHS.txt\", \"DibosonBoostedMuSamples13TeV_2017-11-07_14h59_OnlyCHS.txt\", commonplotvars_chs_signal ) ");
//
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT.txt\", commonplotvars_chs ) ");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");
//-------------------------------------
//-------------------------------------
//	FOR LIMITS
//-------------------------------------
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_T2.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs ) ");
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_BDT.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial2.txt\", commonplotvars_chs ) ");
//-------------------------------------
    //
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElCuts13TeV_Signal_CHS.txt\", \"DibosonBoostedMuSamples13TeV_2017-11-07_14h59_OnlyCHS.txt\", commonplotvars_chs_signal ) ");

    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedMuCuts13TeV_Signal_CHS_2lep.txt\", \"DibosonBoostedMuSamples13TeV_InData_11Oct_OnlyCHS.txt\", commonplotvars_chs_signal ) ");
    //gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElCuts13TeV_Signal_CHS_2lep.txt\", \"DibosonBoostedElSamples13TeV_InData_11Oct_OnlyCHS.txt\", commonplotvars_chs_signal ) ");
    //gROOT->ProcessLine("Wjet_loose()");
    //gROOT->ProcessLine("Wjet_tight()");
    //gROOT->ProcessLine("TopControl()");
    //gROOT->ProcessLine("Wjet_tighter()");
}
