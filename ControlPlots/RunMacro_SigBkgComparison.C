void RunMacro_SigBkgComparison()
{
    gROOT->ProcessLine(".L myControlPlots_SignalBkg_Comparison.C+");

//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
// OPTIONS FOR PROCESSLINE
//
//	cut file,	sample file,	variable file,	OutputRootfileName,	0/1 if 1 then scale signal by 100,  RECREATE root file or UPDATE
//
    gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt\", commonplotvars_chs , \"SignalBackground_Comparison.root\", 1 ) ");
//-------------------------------------
   
//-------------------------------------
}
