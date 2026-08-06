#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TBranch.h>

void addWeightBranch(const char *filename = "/eos/user/a/avijay/HZZ_mergedrootfiles/drellyan_ptz_0to50.root")
{
    // Open the ROOT file
    TFile* file = TFile::Open(filename, "UPDATE");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Get the tree from the file
    TTree* tree = dynamic_cast<TTree*>(file->Get("Events"));
    if (!tree) {
        std::cerr << "Tree not found!" << std::endl;
        file->Close();
        return;
    }

    // Create a variable to hold the weight and the number of jets
    Float_t weight;
    Int_t nJets;
    Bool_t isELE; // Branch name "HZZ2l2qNu_isELE"

    // Create a new branch for the weight
    TBranch* weightBranch = tree->Branch("Weight_nJets_FromDataMC_ge1jet", &weight, "Weight_nJets_FromDataMC_ge1jet/F");

    // Assume there is already a branch named "nJets" which holds the number of jets in each event
    tree->SetBranchAddress("HZZ2l2qNu_nJets", &nJets);
    tree->SetBranchAddress("HZZ2l2qNu_isELE", &isELE);

    // Loop over all entries in the tree
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        // if (i>500) break;

        // Assign weights based on the number of jets
	if (isELE) {
	    if (nJets == 1) weight = 0.8824074;
	    else if (nJets == 2) weight = 0.68684125;
            else if (nJets == 3) weight = 0.76812147;
            else if (nJets == 4) weight = 0.91860612;
            else if (nJets == 5) weight = 1.10500528;
            else if (nJets == 6) weight = 1.31654433;
            else if (nJets == 7) weight = 1.64961608;
            else if (nJets == 8) weight = 2.37517279;
            else if (nJets >= 9) weight = 10.7921858 ;
            else weight = 1.0; // Default weight for other cases (e.g., nJets < 2)
	} // for ge1jet
        /*if (isELE) {
            if (nJets == 2) weight = 0.6134163135791069;
            else if (nJets == 3) weight = 0.6998911097413478;
            else if (nJets == 4) weight = 0.8684340959074924;
            else if (nJets == 5) weight = 0.9863043200514038;
            else if (nJets == 6) weight = 1.1559435285279487;
            else if (nJets == 7) weight = 1.7876879342877086;
            else if (nJets == 8) weight = 1.3072115933482635;
            else if (nJets >= 9) weight = 0.758184751731264;
            else weight = 1.0; // Default weight for other cases (e.g., nJets < 2)
        }*/    // for VBF
        else
        {
	    if (nJets == 1) weight = 0.949076302;
            else if (nJets == 2) weight = 0.733207624;
            else if (nJets == 3) weight = 0.816821098;
            else if (nJets == 4) weight = 0.990226448;
            else if (nJets == 5) weight = 1.183387309;
            else if (nJets == 6) weight = 1.422906636;
            else if (nJets == 7) weight = 1.813024674;
            else if (nJets == 8) weight = 1.25945774;
            else if (nJets >= 9) weight = 1.796557795;
            else weight = 1.0; // Default weight for other cases (e.g., nJets < 2)
        } // for ge1jet
       /*
	{
            if (nJets == 2) weight = 0.6482485565055438;
            else if (nJets == 3) weight = 0.744610505216653;
            else if (nJets == 4) weight = 0.9354411582643493;
            else if (nJets == 5) weight = 1.1315308433742537;
            else if (nJets == 6) weight = 1.2286138112624483;
            else if (nJets == 7) weight = 1.7392576081209716;
            else if (nJets == 8) weight = 1.585752698779711;
            else if (nJets >= 9) weight = 2.970844765079073;
            else weight = 1.0; // Default weight for other cases (e.g., nJets < 2)
        }*/   //for VBF

        // Fill the new branch with the computed weight
        weightBranch->Fill();
    }

    // Write the changes to the file
    tree->Write("", TObject::kOverwrite); // Overwrite the old tree
    file->Close();
}
