#ifndef _COMMONCONTROLPLOTVARS_CHS_H
#define _COMMONCONTROLPLOTVARS_CHS_H

#include "plotvar_t.h"

const plotVar_t commonplotvars_chs[] = {
////    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg
////
//------------    LEPTONS  	-------------------

 { "l_pt1",		30, 1530, 30, 3,		"Lepton p_{T} (GeV)",     "lepton_pt_30bin",       30, 1530, 30, 1 },
 { "l_pt1",		30, 1500, 147, 3,		"Lepton p_{T} (GeV)",     "lepton_pt_147bin",       50, 1500, 147, 1 },
 { "l_pt1",		30, 1500, 49, 3,		"Lepton p_{T} (GeV)",     "lepton_pt_49bin",       50, 1500, 49, 1 },
 { "l_pt1",		30, 1500, 26, 3,		"Lepton p_{T} (GeV)",     "lepton_pt_26bin",       50, 1500, 26, 1 },
 { "l_eta1",		-2.5, 2.5, 8, 1,	"Lepton #eta",            "lepton_eta",    -2.5,  2.5,  8, 0 },

//-------------- 	MET	-------------------
 { "pfMET_Corr",	0.0, 1500, 30, 3,	"pf MET (GeV)",		"pfMET_Corr",	 0.0, 1500, 30, 0 },

//--------------	AK8 Jet		------------
 { "nGoodPuppiAK8jets",		0, 10, 10, 3,	"Number of Good AK8 jets",	"nGoodPuppiAK8jets", 0, 10, 10, 1 },
 { "ungroomed_PuppiAK8_jet_pt",	200, 4500, 43, 3, "AK8 p_{T} (GeV)",		"ungroomed_PuppiAK8_jet_pt",  200, 4500, 43, 1 },
 { "ungroomed_PuppiAK8_jet_eta", 	-2.4, 2.4, 12, 1,  "AK8 #eta",			"ungroomed_PuppiAK8_jet_eta", -2.4, 2.4, 12, 0},
 { "PuppiAK8_jet_mass_so_corr", 	40, 150, 22, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_22bin", 40.0, 150, 22, 1},
 { "PuppiAK8_jet_mass_so_corr", 	40, 150, 11, 3, "AK8 Softdrop mass (GeV)",	"AK8_mass_so_11bin", 40.0, 150, 11, 1},
 { "PuppiAK8_jet_tau2tau1", 		0, 0.55, 10, 1, "AK8 #tau_{2}/#tau_{1}", 		"Puppi_AK8_jet_tau2tau1",0,0.55,10,0},


//--------------	VBF Jet		------------
 { "vbf_maxpt_j1_eta", -5.0, 5.0, 20, 1,	"Leading VBF Jet #eta",	"vbf_maxpt_j1_eta", 	-5.0, 5.0, 20, 0},
 { "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 1,	"Sub-Leading VBF Jet #eta", "vbf_maxpt_j2_eta", -5.0, 5.0, 20, 0},
 { "vbf_maxpt_j2_pt", 30,330, 12, 3,		"Sub-Leading VBF Jet p_{T}", "vbf_maxpt_j2_pt", 30,330,12,0 },
 { "vbf_maxpt_j1_pt", 30, 630, 24, 3,		"Leading VBF Jet p_{T}",	"vbf_maxpt_j1_pt", 30,630,24,1 },
 { "vbf_maxpt_jj_m", 	800, 4500, 37, 3,		"VBF M_{jj} GeV",	"vbf_maxpt_jj_m",  800, 4500, 37, 1},
 { "vbf_maxpt_jj_Deta",	4.0, 10.0, 18, 1,	"VBF #Delta #eta",	"vbf_maxpt_jj_Deta", 4.0, 10.0, 18, 1 },


//----------------	4 body mass	---------------
 { "mass_lvj_type0_PuppiAK8", 	600, 4500, 39, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_39bin",    600, 4500, 39, 1},
 { "mass_lvj_type0_PuppiAK8", 	600, 4500, 78, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_78bin",    600, 4500, 78, 1},
 { "mass_lvj_type0_PuppiAK8", 	600, 4500, 8, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_8bin",    600, 4500, 8, 1},
 { "mass_lvj_type0_PuppiAK8", 	600, 2500, 4, 3, "M_{WW} (GeV)",		"mass_lvj_type0_PuppiAK8_4bin",    600, 2500, 4, 1},


 { "", 0.0,0.0,0,0,"","",0.,0.,0,0 }
};


#endif // _COMMONCONTROLPLOTVARS_CHS_H
