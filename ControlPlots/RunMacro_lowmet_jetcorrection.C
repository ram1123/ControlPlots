#include "controlplotvars_CHS_debug.h"

void RunMacro_lowmet_jetcorrection()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/HZZ2l2nu_controlplots/lowmet_controlregion/lowmet_";

     //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMET_VBF_ControlRegion_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_muon_vbf\", 0) ");
     //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMET_VBF_ControlRegion_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_electron_vbf\", 0) ");
     //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_NoVBF_ge1Jet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_muon_ge1jet\", 0) ");
     //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_NoVBF_ge1Jet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_electron_ge1jet\", 0) ");
     gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_ZeroJet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_muon_0jet\", 0) ");
     //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_ZeroJet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_v15_electron_0jet\", 0) ");
}
