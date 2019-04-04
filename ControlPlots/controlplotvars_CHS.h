#ifndef _COMMONCONTROLPLOTVARS_CHS_H
#define _COMMONCONTROLPLOTVARS_CHS_H

#include "plotvar_t.h"

const plotVar_t commonplotvars_chs[] = {
////    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg
////
// { "nPV",		0, 50, 50, 1,	"Number of primary vertices", "nPV", 	0, 50, 50, 1},
//------------    LEPTONS  	-------------------

// { "l_pt1",		0, 390, 26, 3,		"Lepton p_{T} (GeV)",     "lepton_pt",       0,  390, 26, 1 },
// { "l_eta1",		-2.5, 2.5, 8, 1,	"Lepton #eta",            "lepton_eta",    -2.5,  2.5,  8, 0 },
// { "l_iso1", 	0, 3.0, 15, 2, "Lepton isolation",		"l_iso1",    0, 3.0, 15, 1},
// { "l_phi1",		-4.5, 4.5, 8, 6,	"Lepton #phi",            "lepton_phi",    -4.5, 4.5,  8, 0 },
// { "l_e1",		0, 500, 8, 3,		"Lepton Energy",            "lepton_e",    0, 500,  8, 0 },
// { "l_charge1",		-2, 2, 4, 1,	"Lepton charge",            "lepton_charge",    -2.0,  2.0,  4, 0 },
//
////-------------- 	MET	-------------------
// { "pfMET_Corr",	0.0, 500, 20, 3,	"pf MET (GeV)",		"pfMET_Corr",	 0.0, 500, 20, 0 },
// { "pfMET_Corr_phi",	-3.5, 3.5, 20, 6,	"pf MET #phi",		"pfMET_Corr_phi",-3.5,  3.5, 20, 0 },
// //{ "nu_pz_type0",	-500, 500, 25, 3,	"Reconstructed Neutrino p_{Z}",	"nu_pz_type0", -500, 500, 25, 1},
//
////--------------	AK8 Jet		------------
// { "nGoodPuppiAK8jets",		0, 10, 10, 3,	"Number of Good AK8 jets",	"nGoodPuppiAK8jets", 0, 10, 10, 1 },
// { "ungroomed_PuppiAK8_jet_pt",	200, 1200, 20, 3, "AK8 p_{T} (GeV)",		"ungroomed_PuppiAK8_jet_pt",  200, 1200, 20, 1 },
// { "ungroomed_PuppiAK8_jet_eta", 	-2.4, 2.4, 12, 1,  "AK8 #eta",			"ungroomed_PuppiAK8_jet_eta", -2.4, 2.4, 12, 0},
// { "ungroomed_PuppiAK8_jet_phi", 	-3.4, 3.4, 12, 6,  "AK8 #phi",			"ungroomed_PuppiAK8_jet_phi", -3.4, 3.4, 12, 0},
// { "ungroomed_PuppiAK8_jet_e", 	0.0, 1000.0, 12, 3,  "AK8 Energy",			"ungroomed_PuppiAK8_jet_e", 0.0, 1000.0, 12, 0},
//// { "ungroomed_PuppiAK8_jet_charge", 	-1.0, 1.0, 12, 1,  "AK8 charge",			"ungroomed_PuppiAK8_jet_charge", -1.0, 1.0, 12, 0},
////// { "PuppiAK8_jet_mass", 	40, 150, 11, 3, "AK8 mass (GeV)",		"AK8_mass",    40.0, 150, 11, 1},
////// { "PuppiAK8_jet_mass_pr", 	40, 150, 11, 3, "AK8 pruned mass (GeV)",	"AK8_mass_pr", 40.0, 150, 11, 1},
// //{ "PuppiAK8_jet_mass_so_corr", 	65, 105, 13, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_LSB", 65, 105, 13, 1},
// { "PuppiAK8_jet_mass_so_corr", 	40, 150, 22, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_22bin", 40.0, 150, 22, 1},
// { "PuppiAK8_jet_mass_so_corr", 	40, 150, 11, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_11bin", 40.0, 150, 11, 1},
////// { "PuppiAK8_jet_mass_tr", 	40, 150, 11, 3, "AK8 tr mass (GeV)", 		"AK8_mass_tr", 40.0, 150, 11, 1},
////// { "PuppiAK8_jet_mass", 	65, 105, 5, 3, "AK8 mass (GeV)",		"AK8_mass",    65, 105, 5, 1},
////// { "PuppiAK8_jet_mass_pr", 	65, 105, 5, 3, "AK8 pruned mass (GeV)",		"AK8_mass_pr", 65, 105, 5, 1},
////// { "PuppiAK8_jet_mass_tr", 	65, 105, 5, 3, "AK8 tr mass (GeV)", 		"AK8_mass_tr", 65, 105, 5, 1},
//// { "PuppiAK8_jet_sj1_pt",	0, 800, 25, 3, "AK8 SJ1 pT (GeV)",	"PuppiAK8_jet_sj1_pt", 0, 800, 25, 1},
//// { "PuppiAK8_jet_sj1_eta",	-2.4, 2.4, 25, 1, "AK8 SJ1 #eta",	"PuppiAK8_jet_sj1_eta", -2.4, 2.4, 25, 1},
//// { "PuppiAK8_jet_sj1_phi",	-3, 3, 25, 6, "AK8 SJ1 #phi",	"PuppiAK8_jet_sj1_phi", -3, 3, 25, 1},
//// { "PuppiAK8_jet_sj1_m",	0, 90, 25, 3, "AK8 SJ1 mass (GeV)",	"PuppiAK8_jet_sj1_m", 0, 90, 25, 1},
//// { "PuppiAK8_jet_sj1_q",	-1, 1, 25, 1, "AK8 SJ1 charge",	"PuppiAK8_jet_sj1_q", -1, 1, 25, 1},
//// { "PuppiAK8_jet_sj2_pt",	0, 400, 25, 3, "AK8 SJ2 pT (GeV)",	"PuppiAK8_jet_sj2_pt", 0, 400, 25, 1},
//// { "PuppiAK8_jet_sj2_eta",	-2.4, 2.4, 25, 1, "AK8 SJ2 #eta",	"PuppiAK8_jet_sj2_eta", -2.4, 2.4, 25, 1},
//// { "PuppiAK8_jet_sj2_phi",	-3, 3, 25, 6, "AK8 SJ2 #phi",	"PuppiAK8_jet_sj2_phi", -3, 3, 25, 1},
//// { "PuppiAK8_jet_sj2_m",	0, 150, 25, 3, "AK8 SJ2 mass (GeV)",	"PuppiAK8_jet_sj2_m", 0, 150, 25, 1},
//// { "PuppiAK8_jet_sj2_q",	-1, 1, 25, 1, "AK8 SJ2 charge",	"PuppiAK8_jet_sj2_q", -1, 1, 25, 1},
//// { "PuppiAK8_jet_sj1_q*PuppiAK8_jet_sj2_q",	-20, 20, 25, 1, "AK8 (SJ1_q #times SJ2_q)",	"PuppiAK8_SJ1J2_chargeMultiplication", -20, 20, 25, 1},
////// { "PuppiAK8jet_qjet",		0, 2, 20, 1, "PuppiAK8jet_qjet", 	"PuppiAK8jet_qjet", 0, 2, 20, 1},
// { "PuppiAK8_jet_tau2tau1", 		0, 0.55, 10, 1, "AK8 #tau_{2}/#tau_{1}", 		"Puppi_AK8_jet_tau2tau1",0,0.55,10,0},
//
//
////--------------	VBF Jet		------------
// { "njets",  0, 10, 10, 1, "Number of VBF jets",	"njets", 0, 10, 10, 1},
// { "nBTagJet_loose", 0, 6, 6, 1, "number of VBF jets (Loose b-tag)", "nBTagJet_loose", 0, 6, 6, 1},
// { "nBTagJet_medium", 0, 6, 6, 1, "number of VBF jets (medium b-tag)", "nBTagJet_medium", 0, 6, 6, 1},
// { "vbf_maxpt_j1_eta", -5.0, 5.0, 20, 1,	"Leading VBF Jet #eta",	"vbf_maxpt_j1_eta", 	-5.0, 5.0, 20, 0},
// { "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 1,	"Sub-Leading VBF Jet #eta", "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 0},
// { "vbf_maxpt_j2_pt", 30,330, 12, 3,		"Sub-Leading VBF Jet p_{T}", "vbf_maxpt_j2_pt", 30,330,12,0 },
// { "vbf_maxpt_j1_pt", 30, 630, 24, 3,		"Leading VBF Jet p_{T}",	"vbf_maxpt_j1_pt", 30,630,24,1 },
// { "vbf_maxpt_jj_m", 	500, 2500, 20, 3,		"VBF M_{jj} GeV",	"vbf_maxpt_jj_m",  500, 2500, 20, 1},
// { "vbf_maxpt_jj_Deta",	0.0, 9, 18, 1,	"VBF #Delta #eta",	"vbf_maxpt_jj_Deta", 0.0,9, 18, 1 },
//
//
////----------------	4 body mass	---------------
{ "mass_lvj_type0_PuppiAK8", 	600, 2500, 4, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_4bin",    600, 2500, 4, 1},
// //{ "mt_lvj_type0_PuppiAK8", 	600, 2500, 4, 3, "MT_{WW} (GeV)",		"mt_lvj_type0_PuppiAK8_4bin",    600, 2500, 4, 1},
// //{ "mass_lvj_type0_PuppiAK8", 	600, 2500, 38, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_38bin",    600, 2500, 38, 1},
// //{ "mt_lvj_type0_PuppiAK8", 	600, 2500, 38, 3, "MT_{WW} (GeV)",		"mt_lvj_type0_PuppiAK8_38bin",    600, 2500, 38, 1},
// { "mass_lvj_type0_PuppiAK8", 	600, 2500, 19, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_19bin",    600, 2500, 19, 1},
// { "mt_lvj_type0_PuppiAK8", 	600, 2500, 19, 3, "MT_{WW} (GeV)",		"mt_lvj_type0_PuppiAK8_19bin",    600, 2500, 19, 1},
// { "mass_lvj_type0_PuppiAK8", 	600, 2500, 38, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_38bin",    600, 2500, 38, 1},
// { "mass_lvj_type0_PuppiAK8", 	0.0, 2500, 50, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_38bin",    0.0, 2500, 50, 1},
////
//////////	Leptonic & Hadronic W-boson 
// { "v_pt_type0",		0, 800, 16, 3,	"W p_{T} (GeV)",		"v_pt", 	 0, 800, 16, 1 },
// { "v_mt_type0",		0, 400, 8, 3,	"W Transverse Mass (GeV)",	"v_mt", 	 0, 400, 8, 0 },
////
//////----------	Other Variables	------------------------
////
// { "deltaR_lPuppiak8jet", 0, 7.0, 20, 1, "#Delta R(l,AK8 jet)", "deltaR_lPuppiak8jet", 0, 7.0, 20, 1},
// { "deltaphi_METPuppiak8jet", 0, 3.14, 15, 1, "#Delta #phi(pfMET,AK8 jet)", "deltaphi_METPuppiak8jet", 0, 3.14, 15, 1},
// { "deltaphi_METvbfJ1", 0, 3.14, 15, 1, "#Delta #phi(pfMET,jet1)", "deltaphi_METvbfJ1", 0, 3.14, 15, 1},
// { "deltaphi_METvbfJ2", 0, 3.14, 15, 1, "#Delta #phi(pfMET,jet2)", "deltaphi_METvbfJ2", 0, 3.14, 15, 1},
// { "deltaphi_METmin", 0, 3.14, 15, 1, "#Delta #phi(pfMET,jets)_{min}", "deltaphi_METmin", 0, 3.14, 15, 1},
// { "deltaphi_VPuppiak8jet",0, 3.14, 15, 1, "#Delta #phi(Leptonic W,AK8 jet)", "deltaphi_VPuppiak8jet", 0, 3.14, 15, 1},
// { "(ungroomed_PuppiAK8_jet_pt-l_pt1)/pfMET_Corr",	0, 10, 40, 1, "(AK8 p_{T} - Lepton p_{T})/pfMET",		"AK8minusLeptonptByMet",  0, 10, 40, 1 },
// { "vbf_maxpt_j2_pt/pfMET_Corr",	0, 5, 20, 1, "Sub-leading VBF p_{T}/pfMET",		"SubLeadingVBFptByMet",  0, 5, 20, 1 },
// { "vbf_maxpt_j1_pt/pfMET_Corr",	0, 15, 20, 1, "Leading VBF p_{T}/pfMET",		"LeadingVBFptByMet",  0, 15, 20, 1 },
// { "(vbf_maxpt_j1_pt+vbf_maxpt_j2_pt+ungroomed_PuppiAK8_jet_pt+l_pt1)/pfMET_Corr",	0, 30, 20, 1, "H_{T}/pfMET",		"HTByMET",  0, 30, 20, 1 },
//  { "BDT_response", -1.0,1.0,20,1, "BDT Response",  "BDT_response", -1.0, 1.0, 20, 1},
// { "PuppiAK8jet_e3_sdb1/(PuppiAK8jet_e2_sdb1*PuppiAK8jet_e2_sdb1*PuppiAK8jet_e2_sdb1)", 	0.05,3.5,25, 1, "D2",	"d2_ECF", 0.05,3.5,25, 1},
// { "PuppiAK8jet_e3_v2_sdb1/(PuppiAK8jet_e2_sdb1*PuppiAK8jet_e2_sdb1)", 	0.00,0.5,25, 1, "N2",	"n2_ECF", 0.00,0.5,25, 1},
// { "l_pt1+ungroomed_PuppiAK8_jet_pt+vbf_maxpt_j1_pt+vbf_maxpt_j2_pt",	0, 1500, 15, 3, "HT", "ht", 0, 1500, 15, 1},
//
//
// { "PtBalance_type0",		0, 1.0, 10, 1,	"p_{T} Balance",	"PtBalance_type0",	0, 1.0, 10, 1 },
// { "BosonCentrality_type0",	1, 4.0, 10, 1, 	"Boson Centrality",	"BosonCentrality_type0",1, 4.0, 10, 1 },
////
////// Angular variables
//// //{ "LeptonProjection_run2", 	0, 2, 10, 1, "LeptonProjection_run2"  , "LeptonProjection_run2" ,0, 2, 10, 1}, 
//// //{ "LeptonProjection_type2", 	0, 2, 10, 1, "LeptonProjection_type2"  , "LeptonProjection_type2" ,0, 2, 10, 1}, 
//// { "LeptonProjection_type0", 	0, 2, 10, 1, "Lepton Projection"  , "LeptonProjection_type0" ,0, 2, 10, 1}, 
//// //{ "ZeppenfeldWL_run2", 	-5, 5, 10, 1, "ZeppenfeldWL_run2"  , "ZeppenfeldWL_run2" , -5, 5, 10, 0}, 
//// //{ "ZeppenfeldWL_type2", 	-5, 5, 10, 1, "ZeppenfeldWL_type2"  , "ZeppenfeldWL_type2" , -5, 5, 10, 0}, 
//// { "ZeppenfeldWL_type0", 	-4, 4, 10, 1, "Zeppenfeld (with leptonic W)"  , "ZeppenfeldWL_type0" , -4, 4, 10, 0}, 
//// { "ZeppenfeldWH", 	-4, 4, 10, 1, 		"Zeppenfeld (with hadronic W)"  , "ZeppenfeldWH" , -4, 4, 10, 0}, 
// { "ZeppenfeldWL_type0/vbf_maxpt_jj_Deta", 	-0.3, 0.3, 10, 1, "ZeppenfeldWL/#Delta #eta jj"  , "ZeppenfeldWL_type0_new" , -0.3, 0.3, 10, 1},  
// { "ZeppenfeldWH/vbf_maxpt_jj_Deta", 	-0.3, 0.3, 10, 1, 		"ZeppenfeldWH/#Delta #eta jj"  , "ZeppenfeldWH_new" , -0.3, 0.3, 10, 1}, 
//// //{ "RpT_run2", 		0, 80, 10, 1, 		"RpT_run2"  , "RpT_run2" ,	0, 80, 10, 1}, 
//// //{ "RpT_type2", 	0, 80, 10, 1, 		"RpT_type2"  , "RpT_type2",	0, 80, 10, 1}, 
//// { "RpT_type0", 	0, 80, 10, 1, 		"RpT"  , "RpT_type0",	0, 80, 10, 1}, 
//// { "WWRapidity", 	-2.5, 2.5, 10, 1, 	"WW Rapidity"  , "TempWWRapidity" , -2.5, 2.5, 10, 0}, 
// //{ "VBSCentrality_run2", 	0, 3, 10, 1, 	"VBSCentrality_run2"  , "VBSCentrality_run2" , 0, 3, 10, 1}, 
// //{ "VBSCentrality_type2", 	0, 3, 10, 1, 	"VBSCentrality_type2"  , "VBSCentrality_type2" , 0, 3, 10, 1}, 
// { "VBSCentrality_type0", 	0, 3, 10, 1, 	"VBSCentrality"  , "VBSCentrality_type0" , 0, 3, 10, 1}, 
// //{ "costhetastar_run2", 	-1,1, 10, 1, 	"costhetastar_run2"  , "costhetastar_run2" ,-1,1, 10, 1}, 
// //{ "costhetastar_type2", 	-1,1, 10, 1, 	"costhetastar_type2"  , "costhetastar_type2" ,-1,1, 10, 1}, 
// { "costhetastar_type0", 	-1,1, 10, 6, 	"costhetastar"  , "costhetastar_type0" ,-1,1, 10, 1}, 
// //{ "costheta1_run2", 	-1,1, 10, 1, 	"costheta1_run2"  , "costheta1_run2" ,-1,1, 10, 0}, 
// //{ "costheta1_type2", 	-1,1, 10, 1, 	"costheta1_type2"  , "costheta1_type2" ,-1,1, 10, 0}, 
// { "costheta1_type0", 	-1,1, 10, 6, 	"costheta1"  , "costheta1_type0" ,-1,1, 10, 0}, 
// //{ "costheta2_run2", 	-1,1, 10, 6, 	"costheta2_run2"  , "costheta2_run2" ,-1,1, 10, 0}, 
// //{ "costheta2_type2", 	-1,1, 10, 6, 	"costheta2_type2"  , "costheta2_type2" ,-1,1, 10, 0}, 
// { "costheta2_type0", 	-1,1, 10, 6, 	"costheta2"  , "costheta2_type0" ,-1,1, 10, 0}, 
// //{ "phi_run2", 	-3.5, 3.5, 20, 6, 	"phi_run2"  ,  "phi_run2" ,  -3.5, 3.5, 20, 0}, 
// //{ "phi_type2", 	-3.5, 3.5, 20, 6,	"phi_type2"  , "phi_type2" , -3.5, 3.5, 20, 0}, 
// { "phi_type0", 	-3.5, 3.5, 20, 6, 	"phi"  , "phi_type0" , -3.5, 3.5, 20, 0}, 
// //{ "phi1_run2", 	-3.5, 3.5, 20, 6, 	"phi1_run2"  ,  "phi1_run2" ,  -3.5, 3.5, 20, 0}, 
// //{ "phi1_type2", 	-3.5, 3.5, 20, 6,	"phi1_type2"  , "phi1_type2" , -3.5, 3.5, 20, 0}, 
// { "phi1_type0", 	-3.5, 3.5, 20, 6, 	"phi1"  , "phi1_type0" , -3.5, 3.5, 20, 0}, 
// { "ungroomed_PuppiAK8_jet_pt/pfMET_Corr",	0, 15, 15, 3, "AK8 p_{T}/pfMET",		"AK8ptByMet",  0, 15, 15, 1 },
// { "l_pt1/pfMET_Corr",	0, 10, 20, 1, "Lepton p_{T}/pfMET",		"LeptonptByMet",  0, 10, 20, 1 },
// { "pfMET_Corr/(sqrt(vbf_maxpt_j1_pt+vbf_maxpt_j2_pt+ungroomed_PuppiAK8_jet_pt+l_pt1))",		0, 24, 12, 3,		"s = E_{T}^{miss}/#sqrt{#sum E_{T}}",     "s_dist",       0,  24, 12, 1 },

 { "", 0.0,0.0,0,0,"","",0.,0.,0,0 }
};


#endif // _COMMONCONTROLPLOTVARS_CHS_H
