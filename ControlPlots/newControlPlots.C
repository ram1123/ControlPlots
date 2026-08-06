#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLegend.h>
#include <TFile.h>
#include <TTree.h>
#include <TPad.h>
#include <TStyle.h>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "controlplotvars_CHS_debug.h" // Header with plot variable definitions

struct Sample {
    std::string name;
    std::string fileLocation;
    double xsecOrLumi;
    double otherScale;
    long long nMCEvents;
    long long nMCNegEvents;
    int colorCode;
    bool stackIt;
};

std::vector<Sample> LoadSamples(const char* filename) {
    std::vector<Sample> samples;
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        if (line[0] == '#' || line.empty()) continue;
        std::istringstream iss(line);
        Sample sample;
        iss >> sample.name >> sample.fileLocation >> sample.xsecOrLumi >> sample.otherScale
            >> sample.nMCEvents >> sample.nMCNegEvents >> sample.colorCode >> sample.stackIt;
        samples.push_back(sample);
    }
    return samples;
}

void ProcessSamples(const std::vector<Sample>& samples) {
    TFile* outputFile = new TFile("comparison_plots.root", "RECREATE");

    // Loop over each sample
    for (const auto& sample : samples) {
        TFile* inputFile = TFile::Open(sample.fileLocation.c_str(), "READ");
        if (!inputFile || inputFile->IsZombie()) {
            std::cerr << "Failed to open file: " << sample.fileLocation << std::endl;
            continue;
        }

        TTree* tree = static_cast<TTree*>(inputFile->Get("Events"));
        if (!tree) {
            std::cerr << "Tree 'Events' not found in file: " << sample.fileLocation << std::endl;
            inputFile->Close();
            continue;
        }

        // Loop over each variable
        for (const auto &var : controlplotvars_CHS_debug)
        {
            if (std::string(var.plotvar) == "") break;

            // Creating histogram for each variable and sample
            std::string histName = sample.name + "_" + var.plotvar;
            TH1F* hist = new TH1F(histName.c_str(), (var.xlabel + std::string(" (") + sample.name + ")").c_str(), var.NBINS, var.MINRange, var.MAXRange);
            hist->SetLineColor(sample.colorCode);
            hist->SetFillColor(sample.colorCode * (sample.stackIt ? 1 : 0));  // Fill color only if stacking
            tree->Draw(TString::Format("%s>>%s", var.plotvar, histName.c_str()), "", "goff");
            hist->Write();
        }

        inputFile->Close();
    }

    outputFile->Close();
}

void DataMCComparison() {
    auto samples = LoadSamples("HZZ2l2nu_MuonSamples13TeV_2024_04_11.txt");
    ProcessSamples(samples);
}
