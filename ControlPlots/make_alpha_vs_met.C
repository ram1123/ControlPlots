#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TCut.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>


// ============================================================================
// Configuration
// ============================================================================

// Sample list 
const char *SAMPLE_FILE = "HZZ2l2nu_Samples13TeV_ptz_dy_v15.txt";

// Variable 
const char *PLOT_VAR = "HZZ2l2nu_ZZmT";

const int    NBINS    = 20;
const double MIN_RANGE = 100.0;
const double MAX_RANGE = 1000.0;

// MET scan
const int MET_MIN  = 50;
const int MET_MAX  = 135;
const int MET_STEP = 5;


// ============================================================================
// Structure for storing a yield
// ============================================================================

struct YieldResult
{
    double value;
    double error;
    Long64_t entries;

    YieldResult()
        : value(0.0),
          error(0.0),
          entries(0)
    {}
};


// ============================================================================
// Get data ROOT file from sample list
// ============================================================================

TString getDataFileName(const char *sampleFile)
{
    std::ifstream fin(sampleFile);

    if (!fin.is_open())
    {
        std::cerr << "ERROR: cannot open sample file: " << sampleFile << std::endl;

        return "";
    }

    std::string line;

    while (std::getline(fin, line))
    {
        if (line.empty())
            continue;

        // Remove leading spaces
        size_t first = line.find_first_not_of(" \t");

        if (first == std::string::npos)
            continue;

        if (line[first] == '#')
            continue;

        std::stringstream ss(line);

        std::string sampleName;
        std::string treeFile;

        ss >> sampleName >> treeFile;

        if (sampleName == "data")
        {
            fin.close();
            return TString(treeFile);
        }
    }

    fin.close();

    std::cerr << "ERROR: could not find sample 'data' in " << sampleFile << std::endl;


    return "";
}


// ============================================================================
// Get N_out from the control-plot hist
//
//   1. Draw HZZ2l2nu_ZZmT
//   2. Use 20 bins from 100 to 1000 GeV
//   3. Fold overflow into the last normal bin
//   4. Take:
//          Integral(1, NBINS+1)
//
// This means:
//   - UNDERFLOW (<100 GeV) is NOT included
//   - OVERFLOW (>1000 GeV) is included
//
// ============================================================================

YieldResult getControlPlotYield(
    TTree *tree,
    const TString &cut,
    const TString &channelName,
    int metThreshold)
{
    YieldResult result;

    if (!tree)
    {
        std::cerr << "ERROR: null data tree" << std::endl;
        return result;
    }

    TString histName =
        Form(
            "h_%s_met%d",
            channelName.Data(),
            metThreshold
        );

    TH1D h(histName, histName, NBINS, MIN_RANGE, MAX_RANGE);

    h.Sumw2();

    TString drawExpression =
        Form(
            "%s>>%s",
            PLOT_VAR,
            histName.Data()
        );

    std::cout << "    variable = " << PLOT_VAR << std::endl;
    std::cout << "    histogram = " << NBINS << " bins [" << MIN_RANGE << ", " << MAX_RANGE << "] GeV" << std::endl;
    std::cout << "    cut = " << cut << std::endl;
    std::cout << "    weight = 1.0 (data)" << std::endl;


    // ------------------------------------------------------------------------
    // Fill histogram
    // ------------------------------------------------------------------------

    result.entries = tree->Draw(drawExpression, TCut(cut), "goff");

    // ------------------------------------------------------------------------
    // Reproduce Sample::Draw() overflow treatment
    // ------------------------------------------------------------------------

    double lastBin = h.GetBinContent(NBINS);

    double overflow = h.GetBinContent(NBINS + 1);

    h.SetBinContent(NBINS, lastBin + overflow);


    // ------------------------------------------------------------------------
    // Data yield
    //
    // ndata = th1data->Integral(1, th1data->GetNbinsX() + 1);
    //
    // NOTE:
    //   This excludes the underflow bin.
    // ------------------------------------------------------------------------

    double error = 0.0;

    result.value = h.IntegralAndError(1, NBINS + 1, error);
    result.error = error;
    std::cout << "    selected entries = " << result.entries << std::endl;
    std::cout << "    N_" << channelName << " = " << result.value << " +/- " << result.error << std::endl;
    return result;
}


// ============================================================================
// Calculate alpha
//
// alpha = numerator / N_emu
// ============================================================================

double calculateAlpha(double numerator, double numeratorError, double denominator, double denominatorError,
    double &alphaError)
{
    alphaError = 0.0;

    if (denominator <= 0.0)
        return -1.0;

    double alpha = numerator / denominator;

    if (numerator > 0.0)
    {
        alphaError = alpha * std::sqrt( std::pow(numeratorError / numerator,2) + std::pow(denominatorError / denominator, 2));
    }

    return alpha;
}


// ============================================================================
// Main
// ============================================================================

void make_alpha_vs_met()
{
    // =========================================================================
    // Find data file
    // =========================================================================

    TString dataFile =
        getDataFileName(SAMPLE_FILE);

    if (dataFile.IsNull())
        return;


    std::cout << std::endl << "Opening DATA file:" << std::endl << dataFile << std::endl;


    // =========================================================================
    // Open ROOT file
    // =========================================================================

    TFile *fData = TFile::Open(dataFile, "READ");

    if (!fData || fData->IsZombie())
    {
        std::cerr << "ERROR: could not open data ROOT file: " << dataFile << std::endl;

        if (fData)
            delete fData;

        return;
    }


    // =========================================================================
    // Get Events tree
    // =========================================================================

    TTree *dataTree = dynamic_cast<TTree *>(fData->Get("Events"));

    if (!dataTree)
    {
        std::cerr << "ERROR: tree 'Events' not found." << std::endl;

        fData->Close();
        delete fData;

        return;
    }


    std::cout << "Data entries = " << dataTree->GetEntries() << std::endl;


    // =========================================================================
    // Check that HZZ2l2nu_ZZmT exists
    // =========================================================================

    if (!dataTree->GetBranch(PLOT_VAR))
    {
        std::cerr << "ERROR: branch '" << PLOT_VAR << "' was not found in the data tree." << std::endl;

        fData->Close();
        delete fData;

        return;
    }


    // =========================================================================
    // Output CSV
    // =========================================================================

    std::ofstream csv(
        "alpha_vs_met.csv"
    );

    if (!csv.is_open())
    {
        std::cerr << "ERROR: could not create alpha_vs_met.csv" << std::endl;

        fData->Close();
        delete fData;

        return;
    }


    csv
        << "MET,"
        << "Nee,Nee_err,"
        << "Nmumu,Nmumu_err,"
        << "Nemu,Nemu_err,"
        << "alpha_ee,alpha_ee_err,"
        << "alpha_mumu,alpha_mumu_err"
        << std::endl;


    // =========================================================================
    // ROOT output
    // =========================================================================

    TFile *fOut = new TFile("alpha_vs_met.root", "RECREATE");


    // =========================================================================
    // Graphs
    // =========================================================================

    const int nPoints = (MET_MAX - MET_MIN) / MET_STEP + 1;


    TGraphErrors *grAlphaEE = new TGraphErrors(nPoints);

    TGraphErrors *grAlphaMuMu = new TGraphErrors(nPoints);


    grAlphaEE->SetName(
        "alpha_ee_vs_met"
    );

    grAlphaEE->SetTitle(
        "#alpha(ee) vs MET threshold;MET threshold [GeV];#alpha(ee)"
    );


    grAlphaMuMu->SetName(
        "alpha_mumu_vs_met"
    );

    grAlphaMuMu->SetTitle(
        "#alpha(#mu#mu) vs MET threshold;MET threshold [GeV];#alpha(#mu#mu)"
    );


    // =========================================================================
    // Header
    // =========================================================================

    std::cout
        << std::endl;

    std::cout
        << std::setw(6)
        << "MET"
        << std::setw(16)
        << "N_ee"
        << std::setw(16)
        << "N_mumu"
        << std::setw(16)
        << "N_emu"
        << std::setw(20)
        << "alpha_ee"
        << std::setw(20)
        << "alpha_mumu"
        << std::endl;

    std::cout
        << std::string(90, '-')
        << std::endl;


    // =========================================================================
    // MET loop
    // =========================================================================

    int point = 0;

    for (
        int met = MET_MIN;
        met <= MET_MAX;
        met += MET_STEP
    )
    {
        std::cout
            << std::endl
            << "============================================================"
            << std::endl;

        std::cout
            << "MET threshold = "
            << met
            << " GeV"
            << std::endl;

        std::cout
            << "============================================================"
            << std::endl;


        // =====================================================================
        // Common cuts for ee/mumu
        // =====================================================================

        TString commonMllCuts =
            Form(
                "((pTL1>25)&&(pTL2>25))"
                "&&"
                "(HZZ2l2qNu_nMediumBtagJets==0)"
                "&&"
                "(pT_MET>%d)"
                "&&"
                "((massZ1>40&&massZ1<70)"
                "||(massZ1>110&&massZ1<200))"
                "&&"
                "(pTZ1>55)"
                "&&"
                "(Triggers_HZZ2l2nu_SingleLep==1)"
                "&&"
                "(HZZ2l2qNu_cutOppositeChargeFlag==0)",
                met
            );


        // =====================================================================
        // ee selection
        //
        //electron/muon mll sideband definition:
        //     HZZ2l2qNu_isELE == 1
        // =====================================================================

        TString cutEE =
            "("
            "HZZ2l2qNu_isELE==1"
            ")"
            "&&"
            "("
            + commonMllCuts
            + ")"
            "&&"
            "(passZZ2l2nuSelection==1)";


        // =====================================================================
        // mumu selection
        //
        //     HZZ2l2qNu_isELE == 0
        // =====================================================================

        TString cutMuMu =
            "("
            "HZZ2l2qNu_isELE==0"
            ")"
            "&&"
            "("
            + commonMllCuts
            + ")"
            "&&"
            "(passZZ2l2nuSelection==1)";


        // =====================================================================
        // emu selection
        // =====================================================================

        TString cutEMu = Form(
            "((pTL1>25)&&(pTL2>25))"
            "&&"
            "(HZZ2l2qNu_nMediumBtagJets==0)"
            "&&"
            "(pT_MET>%d)"
            "&&"
            "((massZ1>40&&massZ1<70)"
            "||(massZ1>110&&massZ1<200))"
            "&&"
            "(pTZ1>55)"
            "&&"
            "(Triggers_HZZ2l2nu_SingleLep==1)"
            "&&"
            "(passZZ2l2nu_emuCR_Selection==1)",
            met
        );

        // =====================================================================
        // Get control-plot yields
        // =====================================================================

        std::cout
            << std::endl
            << "Getting N_ee ..."
            << std::endl;

        YieldResult nee =
            getControlPlotYield(
                dataTree,
                cutEE,
                "ee",
                met
            );


        std::cout
            << std::endl
            << "Getting N_mumu ..."
            << std::endl;

        YieldResult nmumu =
            getControlPlotYield(
                dataTree,
                cutMuMu,
                "mumu",
                met
            );


        std::cout
            << std::endl
            << "Getting N_emu ..."
            << std::endl;

        YieldResult nemu =
            getControlPlotYield(
                dataTree,
                cutEMu,
                "emu",
                met
            );


        // =====================================================================
        // Calculate alpha
        // =====================================================================

        double alphaEEError = 0.0;
        double alphaMuMuError = 0.0;


        double alphaEE =
            calculateAlpha(
                nee.value,
                nee.error,
                nemu.value,
                nemu.error,
                alphaEEError
            );


        double alphaMuMu =
            calculateAlpha(
                nmumu.value,
                nmumu.error,
                nemu.value,
                nemu.error,
                alphaMuMuError
            );


        // =====================================================================
        // Print result
        // =====================================================================

        std::cout
            << std::fixed
            << std::setprecision(4)
            << std::setw(6)
            << met
            << std::setw(16)
            << nee.value
            << std::setw(16)
            << nmumu.value
            << std::setw(16)
            << nemu.value
            << std::setw(12)
            << alphaEE
            << " +/- "
            << std::setw(7)
            << alphaEEError
            << std::setw(12)
            << alphaMuMu
            << " +/- "
            << std::setw(7)
            << alphaMuMuError
            << std::endl;


        // =====================================================================
        // CSV
        // =====================================================================

        csv
            << met << ","
            << nee.value << ","
            << nee.error << ","
            << nmumu.value << ","
            << nmumu.error << ","
            << nemu.value << ","
            << nemu.error << ","
            << alphaEE << ","
            << alphaEEError << ","
            << alphaMuMu << ","
            << alphaMuMuError
            << std::endl;


        // =====================================================================
        // Graphs
        // =====================================================================

        grAlphaEE->SetPoint(
            point,
            met,
            alphaEE
        );

        grAlphaEE->SetPointError(
            point,
            0.0,
            alphaEEError
        );


        grAlphaMuMu->SetPoint(
            point,
            met,
            alphaMuMu
        );

        grAlphaMuMu->SetPointError(
            point,
            0.0,
            alphaMuMuError
        );


        point++;
    }


    // =========================================================================
    // Save ROOT objects
    // =========================================================================

    fOut->cd();

    grAlphaEE->Write();
    grAlphaMuMu->Write();

    fOut->Close();

    csv.close();


    // =========================================================================
    // Make alpha plot
    // =========================================================================

    TCanvas *c1 = new TCanvas("c_alpha", "Alpha vs MET", 800, 600);


    grAlphaEE->SetMarkerStyle(20);
    grAlphaEE->SetMarkerSize(1.2);
    grAlphaEE->SetLineWidth(2);

    grAlphaMuMu->SetMarkerStyle(21);
    grAlphaMuMu->SetMarkerSize(1.2);
    grAlphaMuMu->SetLineWidth(2);


    grAlphaEE->Draw("AP");

    grAlphaEE->GetXaxis()->SetTitle(
        "MET threshold [GeV]"
    );

    grAlphaEE->GetYaxis()->SetTitle(
        "#alpha"
    );


    grAlphaMuMu->Draw("P SAME");


    TLegend *leg = new TLegend(0.60, 0.70, 0.88, 0.88);

    leg->SetBorderSize(0);
    leg->SetFillStyle(0);

    leg->AddEntry(
        grAlphaEE,
        "#alpha(ee)",
        "PE"
    );

    leg->AddEntry(
        grAlphaMuMu,
        "#alpha(#mu#mu)",
        "PE"
    );

    leg->Draw();


    c1->SaveAs(
        "alpha_vs_met.pdf"
    );

    c1->SaveAs(
        "alpha_vs_met.png"
    );


    // =========================================================================
    // Cleanup
    // =========================================================================

    delete leg;
    delete c1;

    fData->Close();
    delete fData;


    std::cout
        << std::endl
        << "============================================================"
        << std::endl;

    std::cout
        << "Finished."
        << std::endl;

    std::cout
        << "alpha_vs_met.csv"
        << std::endl;

    std::cout
        << "alpha_vs_met.root"
        << std::endl;

    std::cout
        << "alpha_vs_met.pdf"
        << std::endl;

    std::cout
        << "alpha_vs_met.png"
        << std::endl;

    std::cout
        << "============================================================"
        << std::endl;
}