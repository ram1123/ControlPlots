#include "controlplotvars_CHS_debug.h"

void RunMacro_emu_jetcorrection()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/HZZ2l2nu_controlplots/emu_controlregion/emu_";

    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_VBF.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_dy_vbf_v15\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_NoVBF_ge1Jet.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_dy_ge1jet_v15\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_ZeroJet.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_dy_0jet_v15\", 0) ");
}
