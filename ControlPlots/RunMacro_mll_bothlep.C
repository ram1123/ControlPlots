#include "controlplotvars_CHS_debug.h"

void RunMacro_mll_bothlep()
{
    gROOT->ProcessLine(".L myControlPlots.C+");
    TString OutPutPath = "/eos/user/a/avijay/mll";

    gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_VBF_eleormu.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_bothlep_v15_vbf\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_NoVBF_ge1Jet_eleormu.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_bothlep_v15_ge1jet\", 0) ");
    //gROOT->ProcessLine("myControlPlots(\"HZZ2l2nu_Cuts_mllControlRegion_MedBTag_ZeroJet_eleormu.txt\", \"HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt\", controlplotvars_CHS_debug, \"test.root\", \"" + OutPutPath + "\"  \"_bothlep_v15_0jet\", 0) ");
}
