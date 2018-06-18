// A simple TTreeReader use: read data from hsimple.root (written by hsimple.C)
#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
void readTree() {
   // Create a histogram for the values we read.
   TH1F *h1 = new TH1F("h1", "ntuple", 100, 0, 2400);
   // Open the file containing the tree.
   //TFile *myFile = TFile::Open("root:://cmseos.fnal.gov//eos/uscms/store/user/rasharma/SecondStep/WWTree_2018_01_03_14h54/HaddedFiles/WplusTo2JWminusToLNuJJ_EWK_LO_SM.root");
   TFile *myFile = TFile::Open("root:://cmseos.fnal.gov//eos/uscms/store/user/rasharma/SecondStep/WWTree_2018_01_06_20h00/HaddedFiles/TTToSemilepton.root");
   // Create a TTreeReader for the tree, for instance by passing the
   // TTree's name and the TDirectory / TFile it is in.
   TTreeReader myReader("otree", myFile);
   // The branch "px" contains floats; access them as myPx.
   TTreeReaderValue<Float_t> myPx(myReader, "mass_lvj_type0");
   TTreeReaderValue<Float_t> btag(myReader, "btag0Wgt");
   //TTreeReaderValue<Int_t> vbf(myReader, "isVBF");
   // Loop over all entries of the TTree or TChain.
   while (myReader.Next()) {
      // Just access the data as if myPx and myPy were iterators (note the '*'
      // in front of them):
      h1->Fill(*btag);
      //if (isnan(btag))
      //cout<<"btag0Wgt is nan"<<endl;
   }
   h1->Draw();
}
