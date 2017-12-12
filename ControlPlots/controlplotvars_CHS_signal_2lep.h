#ifndef _COMMONCONTROLPLOTVARS_CHS_SIGNAL_2LEP_H
#define _COMMONCONTROLPLOTVARS_CHS_SIGNAL_2LEP_H

#include "plotvar_t.h"

const plotVar_t commonplotvars_chs_signal_2lep[] = {

//    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg
//
//    LEPTONS
 { "ungroomed_AK8jet_pt+vbf_maxpt_j1_pt+vbf_maxpt_j2_pt",	0, 2000, 40, 3, "HT", "ht", 0, 2000, 40, 1},
 { "nPV",		0, 50, 50, 3,	"Number of primary vertices", "nPV", 	0, 50, 50, 1},
 { "l_pt1",		0, 300, 30, 3,		"Leading Lepton p_{T} (GeV)",     "lepton_pt1",       0,  300, 30, 1 },
 { "l_eta1",		-2.4, 2.4, 16, 1,	"Leading Lepton #eta",            "lepton_eta1",    -2.4,  2.4,  16, 0 },
 { "l_pt2",		0, 300, 30, 3,		"Subleading Lepton p_{T} (GeV)",     "lepton_pt2",       0,  300, 30, 1 },
 { "l_eta2",		-2.4, 2.4, 16, 1,	"Subleading Lepton #eta",            "lepton_eta2",    -2.4,  2.4,  16, 0 },

//////	Leptonic & Hadronic W-boson 
 { "dilep_pt",		0, 600, 30, 3,	"Z p_{T} (GeV)",		"z_pt", 	 0, 600, 30, 1 },
 { "dilep_m",		0, 400, 20, 3,	"Z Invariant Mass (GeV)",	"mZ", 	 0, 400, 20, 0 },

 { "ungroomed_AK8jet_pt",	200, 600, 20, 3, "AK8 p_{T} (GeV)",		"ungroomed_AK8jet_pt",  200, 600, 20, 1 },
 { "ungroomed_AK8jet_eta", 	-2.4, 2.4, 12, 1,  "AK8 #eta",			"ungroomed_AK8jet_eta", -2.4, 2.4, 12, 0},
 { "ungroomed_AK8jet_phi", 	-3.4, 3.4, 20, 1,  "AK8 #phi",			"ungroomed_AK8jet_eta", -3.4, 3.4, 20, 0},
 { "AK8jet_mass", 	55, 125, 14, 1, "AK8 mass (GeV)",		"AK8_mass",    55, 125, 14, 1},
 { "AK8jet_mass_pr", 	55, 125, 14, 1, "AK8 pruned mass (GeV)",	"AK8_mass_pr", 55, 125, 14, 1},
 { "AK8jet_mass_so", 	55, 125, 14, 1, "AK8 Softdrop mass (GeV)",	"AK8_mass_so", 55, 125, 14, 1},
 { "AK8jet_mass_tr", 	55, 125, 14, 1, "AK8 tr mass (GeV)", 		"AK8_mass_tr", 55, 125, 14, 1},
 { "mass_llj_PuppiAK8", 	0, 1600, 64, 1, "ZV invariant mass (GeV)",		"mass_llj_PuppiAK8",    0, 1600, 64, 1},

//	Number of jets
 { "njets",  0, 10, 10, 1, "Number of VBF jets",	"njets", 0, 10, 10, 1},
 { "nBTagJet_loose", 0, 6, 6, 1, "number of VBF jets (Loose b-tag)", "nBTagJet_loose", 0, 6, 6, 1},
 { "nBTagJet_medium", 0, 6, 6, 1, "number of VBF jets (medium b-tag)", "nBTagJet_medium", 0, 6, 6, 1},

 
 { "AK8jet_tau2tau1", 		0, 1, 20, 1, "AK8 #tau_{2}/#tau_{1}", 		"AK8_jet_tau2tau1",0,1,20,0},
 { "vbf_maxpt_jj_m", 	500, 2500, 20, 1,		"m_{jj} (VBF) GeV",	"vbf_maxpt_jj_m",  500, 2500, 20, 1},

//	VBF JET 

 { "vbf_maxpt_j1_eta", -5.0, 5.0, 50, 1,	"Leading VBF Jet #eta",	"vbf_maxpt_j1_eta", 	-5.0, 5.0, 50, 0},
 { "vbf_maxpt_j2_eta", -5.0, 5.0, 50, 1,	"Sub-Leading VBF Jet #eta", "vbf_maxpt_j2_eta", -5.0, 5.0, 50, 0},
 { "vbf_maxpt_j2_pt", 30,190, 16, 1,		"Sub-Leading VBF Jet p_{T}", "vbf_maxpt_j2_pt", 30,190,16,0 },
 { "vbf_maxpt_j1_pt", 30, 450, 42, 1,		"Leading VBF Jet p_{T}",	"vbf_maxpt_j1_pt", 30,450,42,1 },
 { "vbf_maxpt_jj_Deta",	2.5, 9, 26, 1,	"VBF #Delta #eta",	"vbf_maxpt_jj_Deta", 2.5,9, 26, 1 },

// Angular variables
 { "ZeppenfeldWH", 	-4, 4, 20, 1, 		"ZeppenfeldWH"  , "ZeppenfeldWH" , -4, 4, 20, 0}, 
 { "", 0.0,0.0,0,0,"","",0.,0.,0,0 }
};


#endif // _COMMONCONTROLPLOTVARS_CHS_H
