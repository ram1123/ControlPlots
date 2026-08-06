#ifndef _COMMONCONTROLPLOTVARS_CHS_H
#define _COMMONCONTROLPLOTVARS_CHS_H

#include "plotvar_t.h"

const plotVar_t controlplotvars_CHS[] = {
    //    plotvar	MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg
    //
    {"PV_npvsGood", 0, 100, 100, 1, "Number of good primary vertices", "PV_npvsGood", 0, 100, 100, 1},
    {"massZ1", 0, 200, 50, 1, "Z_{ll} (GeV/C2)", "massZ1", 0, 200, 50, 1},
    {"pTZ1", 0, 500, 20, 1, "Z_{ll} p_{T} (GeV/c)", "pTZ1", 0, 500, 20, 1},
    {"etaZ1", -2.4, 2.4, 12, 1, "Z_{ll} #eta", "etaZ1", -2.4, 2.4, 12, 1},
    {"phiZ1", -3.14, 3.14, 12, 6, "Z_{ll} #phi", "phiZ1", -3.14, 3.14, 12, 1},
    {"pTL1", 0, 200, 26, 1, "Lepton1 (GeV/c)", "pTL1", 0, 200, 26, 1},
    {"etaL1", -2.5, 2.5, 8, 1, "Lepton1 #eta", "etaL1", -2.5, 2.5, 8, 0},
    {"phiL1", -3.14, 3.14, 8, 6, "Lepton1 #phi", "phiL1", -3.14, 3.14, 8, 0},
    {"pTL2", 0, 120, 26, 1, "Lepton2 (GeV/c)", "pTL2", 0, 120, 26, 1},
    {"etaL2", -2.5, 2.5, 8, 1, "Lepton2 #eta", "etaL2", -2.5, 2.5, 8, 0},
    {"phiL2", -3.14, 3.14, 8, 6, "Lepton2 #phi", "phiL2", -3.14, 3.14, 8, 0},
    {"MET_pt", 0, 2000, 80, 1, "MET_pt (GeV)", "MET_pt", 0, 2000, 80, 1},
    {"MET_phi", -3.14, 3.14, 12, 6, "MET_phi", "MET_phi", -3.14, 3.14, 12, 1},
    {"MET_sumEt", 0, 6000, 20, 1, "MET_sumEt (GeV)", "MET_sumEt", 0, 6000, 20, 1},
    {"PuppiMET_pt", 0, 2000, 20, 1, "PuppiMET_pt (GeV)", "PuppiMET_pt", 0, 2000, 80, 1},
    {"PuppiMET_phi", -3.14, 3.14, 12, 6, "PuppiMET_phi", "PuppiMET_phi", -3.14, 3.14, 12, 1},
    {"PuppiMET_sumEt", 0, 6000, 20, 1, "PuppiMET_sumEt (GeV)", "PuppiMET_sumEt", 0, 6000, 20, 1},
    {"HZZ2l2nu_ZZmT", 0, 1000, 20, 1, "HZZ2l2nu_ZZmT (GeV)", "HZZ2l2nu_ZZmT", 0, 1000, 20, 1},
    {"HZZ2l2nu_ZZpT", 0, 1000, 20, 1, "HZZ2l2nu_ZZpT (GeV)", "HZZ2l2nu_ZZpT", 0, 1000, 20, 1},
    {"HZZ2l2qNu_nJets", 0, 10, 10, 1, "HZZ2l2qNu_nJets", "HZZ2l2qNu_nJets", 0, 10, 10, 1},
    {"HZZ2l2qNu_nTightBtagJets", 0, 10, 10, 1, "HZZ2l2qNu_nTightBtagJets", "HZZ2l2qNu_nTightBtagJets", 0, 10, 10, 1},
    {"HZZ2l2qNu_nMediumBtagJets", 0, 10, 10, 1, "HZZ2l2qNu_nMediumBtagJets", "HZZ2l2qNu_nMediumBtagJets", 0, 10, 10, 1},
    {"HZZ2l2qNu_nLooseBtagJets", 0, 10, 10, 1, "HZZ2l2qNu_nLooseBtagJets", "HZZ2l2qNu_nLooseBtagJets", 0, 10, 10, 1},
    {"HZZ2l2nu_ifVBF", 0, 2, 2, 1, "HZZ2l2nu_ifVBF", "HZZ2l2nu_ifVBF", 0, 2, 2, 1},
    {"HZZ2l2qNu_isELE", 0, 2, 2, 1, "HZZ2l2qNu_isELE", "HZZ2l2qNu_isELE", 0, 2, 2, 1},
    {"HZZ2l2qNu_cutOppositeChargeFlag", 0, 2, 2, 1, "HZZ2l2qNu_cutOppositeChargeFlag", "HZZ2l2qNu_cutOppositeChargeFlag", 0, 2, 2, 1},

    // don't delete the following line!
    {"", 0.0, 0.0, 0, 0, "", "", 0., 0., 0, 0}};

#endif // _COMMONCONTROLPLOTVARS_CHS_H
