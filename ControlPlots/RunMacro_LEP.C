void RunMacro_LEP()
{
  gROOT->ProcessLine(".L myControlPlots.C+");
//-------------------------------------
//	FOR W+Jet CR 
//-------------------------------------
    gROOT->ProcessLine("myControlPlots(\"DibosonBoostedElMuCuts13TeV_LEP_Tighter_CHS.txt\", \"DibosonBoostedElMuSamples13TeV.txt\", commonplotvars_chs , \"WVchannel_LEPptScale_Down.root\", 0) ");
    
}
