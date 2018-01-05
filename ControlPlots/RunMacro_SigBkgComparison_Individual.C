void RunMacro_SigBkgComparison_Individual()
{
  gROOT->ProcessLine(".L myControlPlots_SignalBkg_Comparison_Individual.C+");
  //gROOT->ProcessLine(".L model.C+");
    
//-------------------------------------
//	FOR Signal Region 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots_SignalBkg_Comparison_Individual(\"DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", commonplotvars_chs , \"SignalBKg_Comp_Individual.root\" ) ");
    
   
//-------------------------------------
    //gROOT->ProcessLine("Wjet_loose()");
    //gROOT->ProcessLine("Wjet_tight()");
    //gROOT->ProcessLine("TopControl()");
    //gROOT->ProcessLine("Wjet_tighter()");
}
