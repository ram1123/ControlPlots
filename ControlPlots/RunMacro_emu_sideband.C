#include "controlplotvars_CHS_debug.h"

void RunMacro_emu_sideband()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/emu_new_sideband_";

    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_VBF_sideband.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_vbf\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_NoVBF_ge1Jet_sideband.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_ge1jet\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_emuControlRegion_MedBTag_ZeroJet_sideband.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_0jet\", 0) ");
}
