#include "controlplotvars_CHS_testing.h"

void RunMacro_emu()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/emu_debug";

    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_VBF.txt\", \"HZZ2l2nu_Samples13TeV_Ptz_dy.txt\", controlplotvars_CHS_testing, \"test.root\", \"" + OutPutPath + "\"  \"_Ptz_vbf\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_NoVBF_ge1Jet.txt\", \"HZZ2l2nu_Samples13TeV_Ptz_dy.txt\", controlplotvars_CHS_testing, \"test.root\", \"" + OutPutPath + "\"  \"_Ptz_ge1jet\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_ZeroJet.txt\", \"HZZ2l2nu_Samples13TeV_Ptz_dy.txt\", controlplotvars_CHS_testing, \"test.root\", \"" + OutPutPath + "\"  \"_Ptz_0jet\", 0) ");
}
