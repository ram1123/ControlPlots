#include "controlplotvars_CHS_debug.h"

void RunMacro_lowmet()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/LowMET";

    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_ZeroJet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_0jet_electron\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_ZeroJet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_0jet_muon\", 0) ");
   gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_NoVBF_ge1Jet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_ge1jet_electron\", 0) ");
   gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMETControlRegion_MedBTag_NoVBF_ge1Jet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_ge1jet_muon\", 0) ");
   gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMET_VBF_ControlRegion_Electron.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_vbf_electron\", 0) ");
   gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_LowMET_VBF_ControlRegion_Muon.txt\", \"HZZ2l2nu_Samples13TeV_inclusive_dy.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_Inclusive_vbf_muon\", 0) ");
}
