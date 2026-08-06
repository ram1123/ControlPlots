#include "controlplotvars_CHS_debug.h"

void RunMacro_mll()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/HZZ2l2nu_controlplots/mllsideband_controlregion/mll_";

    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_VBF_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_vbf_muon_v15\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_VBF_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_vbf_electron_v15\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_NoVBF_ge1Jet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_ge1jet_muon_v15\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_NoVBF_ge1Jet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_ge1jet_electron_v15\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_ZeroJet_Muon.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_0jet_muon_v15\", 0) ");
    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_ZeroJet_Electron.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_ptz_0jet_electron_v15\", 0) ");

}
