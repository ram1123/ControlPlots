#ifndef _COMMONCONTROLPLOTVARS_CHS_2LEP_H
#define _COMMONCONTROLPLOTVARS_CHS_2LEP_H

#include "plotvar_t.h"

const plotVar_t controlplotvars_CHS_2lep[] = {
//    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg
//
//    LEPTONS
 { "mass_llj_PuppiAK8", 	600, 2500, 38, 1, 	"M_{ww}"  , "mass_llj_PuppiAK8_38Bins" , 600, 2500, 38, 0}, 
 { "mass_llj_PuppiAK8", 	600, 2500, 19, 1, 	"M_{ww}"  , "mass_llj_PuppiAK8_19Bins" , 600, 2500, 19, 0}, 
 { "mass_llj_PuppiAK8", 	600, 2500, 4, 1, 	"M_{ww}"  , "mass_llj_PuppiAK8_4Bins" , 600, 2500, 4, 0}, 

 { "nPV",		0, 50, 50, 1,	"Number of primary vertices", "nPV", 	0, 50, 50, 1},

 { "l_pt1",		30, 390, 12, 3,		"Lepton p_{T} (GeV)",     "lepton_pt1",       30,  390, 12, 1 },
 { "l_eta1",		-2.5, 2.5, 8, 1,	"Lepton #eta",            "lepton_eta1",    -2.5,  2.5,  8, 0 },
 { "l_phi1",		-4.5, 4.5, 8, 6,	"Lepton #phi",            "lepton_phi1",    -4.5, 4.5,  8, 0 },
 { "l_e1",		0, 500, 8, 3,		"Lepton Energy",            "lepton_e1",    0, 500,  8, 0 },
 { "l_charge1",		-2, 2, 4, 1,	"Lepton charge",            "lepton_charge1",    -2.0,  2.0,  4, 0 },

 { "l_pt2",		20, 810, 13, 3,		"Sub-Leading Lepton p_{T} (GeV)",     "lepton_pt",       20,  810, 13, 1 },
 { "l_eta2",	-2.4, 2.4, 8, 1,	"Sub-Leading Lepton #eta",            "lepton_eta",    -2.4,  2.4,  8, 0 },
 { "l_phi2",	-4.5, 4.5, 8, 1,	"Sub-Leading Lepton #phi",            "lepton_phi",    -4.5, 4.5,  8, 0 },
 { "l_e2",		0, 500, 8, 3,	"Sub-Leading Lepton energy",            "lepton_e",    0, 500,  8, 0 },
 { "l_charge2",		-2, 2, 8, 1,	"Sub-Leading Lepton #charge",            "lepton_charge",    -2.0,  2.0,  8, 0 },

//////	Leptonic & Hadronic W-boson 
 { "dilep_pt",	0,700, 20,3,	"W_{lep} p_{T} (GeV)",		"dilep_pt",	0,700, 20, 0}, 
 { "dilep_eta",	-2.5,2.5, 20,1,	"W_{lep}(#eta)",	"dilep_eta",	-2.5,2.5, 20, 0}, 
 { "dilep_phi",	-3.5,3.5, 20,1,	"W_{lep} (#phi)",	"dilep_phi", 	-3.5,3.5, 20, 0}, 
 { "dilep_m",	0,700, 20,3,	"M_{ll} (GeV)",		"dilep_m", 	0,700, 20, 0}, 
 
 { "ungroomed_PuppiAK8_jet_pt",	0, 800, 16, 3, "AK8 p_{T} (GeV)",		"ungroomed_PuppiAK8_jet_pt",  0, 800, 16, 1 },
 { "ungroomed_PuppiAK8_jet_eta", 	-2.4, 2.4, 12, 1,  "AK8 #eta",			"ungroomed_PuppiAK8_jet_eta", -2.4, 2.4, 12, 0},
 { "ungroomed_PuppiAK8_jet_phi", 	-3.4, 3.4, 12, 6,  "AK8 #phi",			"ungroomed_PuppiAK8_jet_phi", -3.4, 3.4, 12, 0},
 { "ungroomed_PuppiAK8_jet_e", 	0.0, 1000.0, 12, 3,  "AK8 Energy",			"ungroomed_PuppiAK8_jet_e", 0.0, 1000.0, 12, 0},
 { "ungroomed_PuppiAK8_jet_charge", 	-1.0, 1.0, 12, 1,  "AK8 charge",			"ungroomed_PuppiAK8_jet_charge", -1.0, 1.0, 12, 0},
// { "PuppiAK8_jet_mass", 	40, 150, 11, 3, "AK8 mass (GeV)",		"AK8_mass",    40.0, 150, 11, 1},
// { "PuppiAK8_jet_mass_pr", 	40, 150, 11, 3, "AK8 pruned mass (GeV)",	"AK8_mass_pr", 40.0, 150, 11, 1},
 { "PuppiAK8_jet_mass_so_corr", 	40, 150, 22, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so", 40.0, 150, 22, 1},
 { "PuppiAK8_jet_mass_so_corr", 	40, 150, 11, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_11bin", 40.0, 150, 11, 1},
// { "PuppiAK8_jet_mass_tr", 	40, 150, 11, 3, "AK8 tr mass (GeV)", 		"AK8_mass_tr", 40.0, 150, 11, 1},
// { "PuppiAK8_jet_mass", 	65, 105, 5, 3, "AK8 mass (GeV)",		"AK8_mass",    65, 105, 5, 1},
// { "PuppiAK8_jet_mass_pr", 	65, 105, 5, 3, "AK8 pruned mass (GeV)",		"AK8_mass_pr", 65, 105, 5, 1},
// { "PuppiAK8_jet_mass_so_corr", 	65, 105, 5, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so", 65, 105, 5, 1},
// { "PuppiAK8_jet_mass_tr", 	65, 105, 5, 3, "AK8 tr mass (GeV)", 		"AK8_mass_tr", 65, 105, 5, 1},
// { "PuppiAK8_jet_sj1_pt",	0, 800, 25, 3, "AK8 SJ1 pT (GeV)",	"PuppiAK8_jet_sj1_pt", 0, 800, 25, 1},
// { "PuppiAK8_jet_sj1_eta",	-2.4, 2.4, 25, 1, "AK8 SJ1 #eta",	"PuppiAK8_jet_sj1_eta", -2.4, 2.4, 25, 1},
// { "PuppiAK8_jet_sj1_phi",	-3, 3, 25, 6, "AK8 SJ1 #phi",	"PuppiAK8_jet_sj1_phi", -3, 3, 25, 1},
// { "PuppiAK8_jet_sj1_m",	0, 90, 25, 3, "AK8 SJ1 mass (GeV)",	"PuppiAK8_jet_sj1_m", 0, 90, 25, 1},
// { "PuppiAK8_jet_sj1_q",	-1, 1, 25, 1, "AK8 SJ1 charge",	"PuppiAK8_jet_sj1_q", -1, 1, 25, 1},
// { "PuppiAK8_jet_sj2_pt",	0, 400, 25, 3, "AK8 SJ2 pT (GeV)",	"PuppiAK8_jet_sj2_pt", 0, 400, 25, 1},
// { "PuppiAK8_jet_sj2_eta",	-2.4, 2.4, 25, 1, "AK8 SJ2 #eta",	"PuppiAK8_jet_sj2_eta", -2.4, 2.4, 25, 1},
// { "PuppiAK8_jet_sj2_phi",	-3, 3, 25, 6, "AK8 SJ2 #phi",	"PuppiAK8_jet_sj2_phi", -3, 3, 25, 1},
// { "PuppiAK8_jet_sj2_m",	0, 80, 25, 3, "AK8 SJ2 mass (GeV)",	"PuppiAK8_jet_sj2_m", 0, 80, 25, 1},
// { "PuppiAK8_jet_sj2_q",	-1, 1, 25, 1, "AK8 SJ2 charge",	"PuppiAK8_jet_sj2_q", -1, 1, 25, 1},
// { "PuppiAK8_jet_sj1_q*PuppiAK8_jet_sj2_q",	-20, 20, 25, 1, "AK8 (SJ1_q #times SJ2_q)",	"PuppiAK8_SJ1J2_chargeMultiplication", -20, 20, 25, 1},
// { "PuppiAK8jet_qjet",		0, 2, 20, 1, "PuppiAK8jet_qjet", 	"PuppiAK8jet_qjet", 0, 2, 20, 1},


//	Number of jets
 { "njets",  0, 10, 10, 1, "Number of VBF jets",	"njets", 0, 10, 10, 1},
 { "nBTagJet_loose", 0, 6, 6, 1, "number of VBF jets (Loose b-tag)", "nBTagJet_loose", 0, 6, 6, 1},
 { "nBTagJet_medium", 0, 6, 6, 1, "number of VBF jets (medium b-tag)", "nBTagJet_medium", 0, 6, 6, 1},

 
 { "PuppiAK8_jet_tau2tau1", 		0, 0.55, 10, 1, "AK8 #tau_{2}/#tau_{1}", 		"Puppi_AK8_jet_tau2tau1",0,0.55,10,0},
//	VBF JET 

 { "vbf_maxpt_j1_eta", -5.0, 5.0, 20, 1,	"Leading VBF Jet #eta",	"vbf_maxpt_j1_eta", 	-5.0, 5.0, 20, 0},
 { "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 1,	"Sub-Leading VBF Jet #eta", "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 0},
 { "vbf_maxpt_j2_pt", 30,330, 12, 3,		"Sub-Leading VBF Jet p_{T}", "vbf_maxpt_j2_pt", 30,330,12,0 },
 { "vbf_maxpt_j1_pt", 30, 630, 24, 3,		"Leading VBF Jet p_{T}",	"vbf_maxpt_j1_pt", 30,630,24,1 },
 { "vbf_maxpt_jj_m", 	800, 2500, 20, 3,		"VBF M_{jj} GeV",	"vbf_maxpt_jj_m",  800, 2500, 20, 1},
 { "vbf_maxpt_jj_Deta",	4.0, 9, 13, 1,	"VBF #Delta #eta",	"vbf_maxpt_jj_Deta", 4.0,9, 13, 1 },


//// Angular variables
// { "deltaR_lPuppiak8jet", 	0, 4.5, 10, 1, 	"#Delta R(leading lep,AK8)"  , "deltaR_lPuppiak8jet" , 0, 4.5, 10, 0}, 
// { "deltaR_l2Puppiak8jet", 	0, 4.5, 10, 1, 	"#Delta R(sub-leading lep, AK8)"  , "deltaR_l2Puppiak8jet" , 0, 4.5, 10, 0}, 
// { "deltaR_VLepPuppiak8jet", 	0, 4.5, 10, 1, 	"#Delta R(W_{lep}, AK8)"  , "deltaR_VLepPuppiak8jet" , 0, 4.5, 10, 0}, 
// { "pt_llj_PuppiAK8", 	0,2000, 10, 1, 	"p_{T} of ZV"  , "pt_llj_PuppiAK8" , 0,2000, 10, 0}, 
// { "eta_llj_PuppiAK8", 	-2.5, 2.5, 10, 1, 	"#eta of ZV"  , "eta_llj_PuppiAK8" , -2.5, 2.5, 10, 0}, 
// { "phi_llj_PuppiAK8", 	-4.5, 4.5, 10, 1, 	"#phi of ZV"  , "phi_llj_PuppiAK8" , -4.5, 4.5, 10, 0}, 
// { "ZeppenfeldWH", 	-5, 5, 10, 1, 		"Zeppenfeld (with hadronic W)"  , "ZeppenfeldWH" , -5, 5, 10, 0}, 
// { "PtBalance_2Lep",		0, 1.0, 10, 1,	"p_{T} Balance",	"PtBalance_2Lep",	0, 1.0, 10, 1 },
// { "BosonCentrality_2Lep",	0,4.0, 8, 1, 	"Boson Centrality",	"BosonCentrality_2Lep",0,4.0, 8, 1 },
// { "costheta1_2Lep", 	-1,1, 10, 6, 	"costheta1"  , "costheta1_2Lep" ,-1,1, 10, 0}, 
// { "costheta2_2Lep", 	-1,1, 10, 6, 	"costheta2"  , "costheta2_2Lep" ,-1,1, 10, 0}, 
// { "costhetastar_2Lep", 	-1,1, 10, 6, 	"costhetastar"  , "costhetastar_2Lep" ,-1,1, 10, 1}, 
// { "phi_2Lep", 	-3.5, 3.5, 20, 6, 	"phi"  , "phi_2Lep" , -3.5, 3.5, 20, 0}, 
// { "phi1_2Lep", 	-3.5, 3.5, 20, 6, 	"phi1"  , "phi1_2Lep" , -3.5, 3.5, 20, 0}, 
// { "VBSCentrality_2Lep", 	0, 3, 10, 1, 	"VBSCentrality"  , "VBSCentrality_2Lep" , 0, 3, 10, 1}, 
// { "RpT_2Lep", 	0, 80, 10, 1, 		"RpT"  , "RpT_2Lep",	0, 80, 10, 1}, 
// { "ZeppenfeldWL_2Lep", 	-5, 5, 10, 1, "Zeppenfeld (with leptonic W)"  , "ZeppenfeldWL_2Lep" , -5, 5, 10, 0}, 
// { "LeptonProjection_2Lep", 	0, 2, 10, 1, "Lepton Projection"  , "LeptonProjection_2Lep" ,0, 2, 10, 1}, 
// { "ZeppenfeldWL_2Lep/vbf_maxpt_jj_Deta", 	-1.0, 0.3, 20, 1, "ZeppenfeldWL/#Delta #eta jj"  , "ZeppenfeldWL_2Lep_new" , -1.0, 0.3, 20, 1}, 
// { "ZeppenfeldWH/vbf_maxpt_jj_Deta", 	-1.0, 0.3, 20, 1, 		"ZeppenfeldWH/#Delta #eta jj"  , "ZeppenfeldWH_new" , -1.0, 0.3, 20, 1}, 

 { "", 0.0,0.0,0,0,"","",0.,0.,0,0 }
};


#endif // _COMMONCONTROLPLOTVARS_CHS_H
