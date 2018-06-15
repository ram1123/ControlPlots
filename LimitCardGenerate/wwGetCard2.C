#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <assert.h>
#include "TROOT.h"
#include "TLatex.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TString.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TSystem.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include <ctime>

#include "tdrstyle.C"
#include "utils.C" // Tokenize
#include "CMS_lumi.C"

#include <Python.h>


#include "controlplotvars_CHS.h"

typedef struct SampleInfo_t {
  int     index;
  TString samplename;
  TString treefilename;
  double xsecpblumi;
  double otherscale;
  int    nMCevents;
  int	 MCnegEvent;
  int    colorcode;
  int    stackit;
}
SampleInfo_t;
using namespace std;

double intLUMIinvpb;

double fs0[91] = {-900.0, -880.0, -860.0, -840.0, -820.0, -800.0, -780.0, -760.0, -740.0, -720.0, -700.0, -680.0, -660.0, -640.0, -620.0, -600.0, -580.0, -560.0, -540.0, -520.0, -500.0, -480.0, -460.0, -440.0, -420.0, -400.0, -380.0, -360.0, -340.0, -320.0, -300.0, -280.0, -260.0, -240.0, -220.0, -200.0, -180.0, -160.0, -140.0, -120.0, -100.0, -80.0, -60.0, -40.0, -20.0, 0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 220.0, 240.0, 260.0, 280.0, 300.0, 320.0, 340.0, 360.0, 380.0, 400.0, 420.0, 440.0, 460.0, 480.0, 500.0, 520.0, 540.0, 560.0, 580.0, 600.0, 620.0, 640.0, 660.0, 680.0, 700.0, 720.0, 740.0, 760.0, 780.0, 800.0, 820.0, 840.0, 860.0, 880.0, 900.0};
double fs1[67] = {-330.0, -320.0, -310.0, -300.0, -290.0, -280.0, -270.0, -260.0, -250.0, -240.0, -230.0, -220.0, -210.0, -200.0, -190.0, -180.0, -170.0, -160.0, -150.0, -140.0, -130.0, -120.0, -110.0, -100.0, -90.0, -80.0, -70.0, -60.0, -50.0, -40.0, -30.0, -20.0, -10.0, 0.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0, 170.0, 180.0, 190.0, 200.0, 210.0, 220.0, 230.0, 240.0, 250.0, 260.0, 270.0, 280.0, 290.0, 300.0, 310.0, 320.0, 330.0};
double fm0[85] = {-42.0, -41.0, -40.0, -39.0, -38.0, -37.0, -36.0, -35.0, -34.0, -33.0, -32.0, -31.0, -30.0, -29.0, -28.0, -27.0, -26.0, -25.0, -24.0, -23.0, -22.0, -21.0, -20.0, -19.0, -18.0, -17.0, -16.0, -15.0, -14.0, -13.0, -12.0, -11.0, -10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0};
double fm1[67] = {-165.0, -160.0, -155.0, -150.0, -145.0, -140.0, -135.0, -130.0, -125.0, -120.0, -115.0, -110.0, -105.0, -100.0, -95.0, -90.0, -85.0, -80.0, -75.0, -70.0, -65.0, -60.0, -55.0, -50.0, -45.0, -40.0, -35.0, -30.0, -25.0, -20.0, -15.0, -10.0, -5.0, 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 155.0, 160.0, 165.0};
double fm6[84] = {-84.0, -82.0, -80.0, -78.0, -76.0, -74.0, -72.0, -70.0, -68.0, -66.0, -64.0, -62.0, -60.0, -58.0, -56.0, -54.0, -52.0, -50.0, -48.0, -46.0, -44.0, -42.0, -40.0, -38.0, -36.0, -34.0, -32.0, -30.0, -28.0, -26.0, -24.0, -22.0, -20.0, -18.0, -16.0, -14.0, -12.0, -10.0, -8.0, -6.0, -4.0, -2.0, 0.0, 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0, 40.0, 42.0, 44.0, 46.0, 48.0, 50.0, 52.0, 54.0, 56.0, 58.0, 60.0, 62.0, 64.0, 66.0, 68.0, 70.0, 72.0, 74.0, 76.0, 78.0, 80.0, 82.0};
double fm7[121] = {-300.0, -295.0, -290.0, -285.0, -280.0, -275.0, -270.0, -265.0, -260.0, -255.0, -250.0, -245.0, -240.0, -235.0, -230.0, -225.0, -220.0, -215.0, -210.0, -205.0, -200.0, -195.0, -190.0, -185.0, -180.0, -175.0, -170.0, -165.0, -160.0, -155.0, -150.0, -145.0, -140.0, -135.0, -130.0, -125.0, -120.0, -115.0, -110.0, -105.0, -100.0, -95.0, -90.0, -85.0, -80.0, -75.0, -70.0, -65.0, -60.0, -55.0, -50.0, -45.0, -40.0, -35.0, -30.0, -25.0, -20.0, -15.0, -10.0, -5.0, 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0, 85.0, 90.0, 95.0, 100.0, 105.0, 110.0, 115.0, 120.0, 125.0, 130.0, 135.0, 140.0, 145.0, 150.0, 155.0, 160.0, 165.0, 170.0, 175.0, 180.0, 185.0, 190.0, 195.0, 200.0, 205.0, 210.0, 215.0, 220.0, 225.0, 230.0, 235.0, 240.0, 245.0, 250.0, 255.0, 260.0, 265.0, 270.0, 275.0, 280.0, 285.0, 290.0, 295.0, 300.0};
double ft0[69] = {-6.8, -6.6, -6.4, -6.2, -6.0, -5.8, -5.6, -5.4, -5.2, -5.0, -4.8, -4.6, -4.4, -4.2, -4.0, -3.8, -3.6, -3.4, -3.2, -3.0, -2.8, -2.6, -2.4, -2.2, -2.0, -1.8, -1.6, -1.4, -1.2, -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8, 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0, 6.2, 6.4, 6.6, 6.8};
double ft1[51] = {-12.5, -12.0, -11.5, -11.0, -10.5, -10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5};
double ft2[83] = {-20.5, -20.0, -19.5, -19.0, -18.5, -18.0, -17.5, -17.0, -16.5, -16.0, -15.5, -15.0, -14.5, -14.0, -13.5, -13.0, -12.5, -12.0, -11.5, -11.0, -10.5, -10.0, -9.5, -9.0, -8.5, -8.0, -7.5, -7.0, -6.5, -6.0, -5.5, -5.0, -4.5, -4.0, -3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5, 17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5};


//======================================================================
class Sample {
public:
  Sample(const SampleInfo_t& sinfo) {
    info_ = sinfo;
    tree_ = 0;
    //cout << "sample = " << name_ << endl;
    //TFile *f = new TFile (sinfo.treefilename, "READ"); if (!f) { cerr << "Couldn't find file " << sinfo.treefilename << endl; return; }
    TFile *f =  TFile::Open("root://cmsxrootd.fnal.gov/"+sinfo.treefilename, "READ"); if (!f) { cerr << "Couldn't find file " << sinfo.treefilename << endl; return; }
    tree_ =  (TTree *)f->Get("otree"); if (!tree_) { cerr << "Couldn't find tree otree in file " << sinfo.treefilename << endl; return; }
  }
  ~Sample() { if (tree_) delete tree_; }
  TTree *Tree() const { return tree_; }
  TString name() const { return info_.samplename; }
  TString filename() const { return info_.treefilename; }
  bool stackit() const { return (info_.stackit != 0); }
  int colorcode() const { return info_.colorcode; }
  double otherscale() const { return info_.otherscale; }
  double cross() const {return info_.xsecpblumi; }
  int mcevent() const {return info_.nMCevents; }
  int mcevent_neg() const {return info_.MCnegEvent; }
  private:
    SampleInfo_t info_;
    TTree *tree_;
};

//======================================================================
//
void loadSamples(const char *filename,vector<Sample *>& samples)
{
  FILE *fp = fopen(filename,"r");
  if (!fp) {
    cout << "Error, file " << TString(filename) << " not found." << endl;
    exit(-1);
  }

  char line[512];

  intLUMIinvpb=-1; // obvious error condition

  for (int i=0; !feof(fp) && fgets(line,512,fp); i++) {
    if (!strlen(line) || line[0]=='#') continue; // comments are welcome

    string strline(line);
    strline.pop_back();     // shed the \n
    vector<string> fields;

    // expect columns with fields cutname, cutvalue, possible embedded spaces both
    // within and between, so " " or "\t" cannot be used as delimiters. Require quotes
    // instead.
    //
    Tokenize(strline,fields, " \t");

    //for (size_t j=0; j<fields.size(); j++)
    //cout << j << ": \"" << fields[j] << "\"" << endl;

    assert (fields.size()==8);

    SampleInfo_t s;
    s.index        = i;
    s.samplename   = fields[0];
    s.treefilename = fields[1];
    s.xsecpblumi   = str2dbl(fields[2]);
    s.otherscale   = str2dbl(fields[3]);
    s.nMCevents    = str2int(fields[4]);
    s.MCnegEvent   = str2int(fields[5]);
    s.colorcode    = str2int(fields[6]);
    s.stackit      = str2int(fields[7]);
    
    //if (!s.samplename.EqualTo("aQGC")) continue;
    
    cout << "Loading sample " << s.samplename << " -> " << s.treefilename << endl;
    
    
    if (!samples.size()) {
      if (s.samplename.EqualTo("data")) {
	intLUMIinvpb = s.xsecpblumi;
	s.xsecpblumi = 1;
	cout << "intLUMI = " << intLUMIinvpb << " pb^-1" << endl;
      } else {
	cerr << "First sample in the table must be 'data'" << endl;
	//exit(-1);
      }
    } else {
      s.otherscale *= intLUMIinvpb;
    }
    
    samples.push_back(new Sample(s) );
  }
}                                                         // loadSamples
//======================================================================

void loadCutString(const char *filename, TString& cutstring)
{
  FILE *fp = fopen(filename,"r");
  if (!fp) {
    cout << "Error, file " << TString(filename) << " not found." << endl;
    exit(-1);
  }

  char line[512];

  for (int i=0; !feof(fp) && fgets(line,512,fp); i++) {
    if (!strlen(line) || line[0]=='#') continue; // comments are welcome

    if (cutstring.Length()) cutstring += " && ";

    string strline(line);
    strline.pop_back();     // shed the \n
    vector<string> fields;

    // expect columns with fields cutname, cutvalue, possible embedded spaces both
    // within and between, so " " or "\t" cannot be used as delimiters. Require quotes
    // instead.
    //
    Tokenize(strline,fields, "\"");

    //for (size_t j=0; j<fields.size(); j++)
    //cout << j << ": \"" << fields[j] << "\"" << endl;

    assert (fields.size()==3);
    cutstring += TString(fields.at(2));
  }
}                                                       // loadCutString

//======================================================================

//======================================================================

void model(const char *cuttablefilename,
	   const char *samplefilename,
	   const plotVar_t plotvars[] = commonplotvars_chs)
{
  cout<< "done..." << endl;

  TString unwtcutstring;
  
  loadCutString(cuttablefilename, unwtcutstring);
  
  TString blinddatacutstring = unwtcutstring + "&&(0)";
  
  cout<< "Cut string = \n\t" << blinddatacutstring << endl;

  vector<Sample *> samples;
  
  loadSamples(samplefilename,samples);
  
  // Data
  
  Sample *sdata = samples[0];
  
  if (sdata->Tree())
    cout << "ndata =" << sdata->Tree()->GetEntries() <<endl;

  TFile f("signal_proc_ch1_splitted_TH1.root", "RECREATE");
  
  //============================================================
  //  VARIABLE LOOP
  //============================================================
  int NBINS = 4;
  double MINRange = 600;
  double MAXRange = 2500;


  TH1 *hists[53];

  const char* HistName[53] = {	"Data",						// 0
  			"WV_EWK", "WV_EWK_LEPUp", "WV_EWK_LEPDown", "WV_EWK_CMS_scale_jUp", "WV_EWK_CMS_scale_jDown", "WV_EWK_CMS_res_metUp", "WV_EWK_CMS_res_metDown", 
			"WV_EWK_CMS_puUp", "WV_EWK_CMS_puDown",	"WV_EWK_CMS_btagHFUp", "WV_EWK_CMS_btagHFDown", "WV_EWK_CMS_btagLFUp", "WV_EWK_CMS_btagLFDown", // 1	
			"Diboson", "Diboson_LEPUp", "Diboson_LEPDown", "Diboson_CMS_scale_jUp", "Diboson_CMS_scale_jDown", "Diboson_CMS_res_metUp", "Diboson_CMS_res_metDown", 
			"Diboson_CMS_puUp", "Diboson_CMS_puDown", "Diboson_CMS_btagHFUp", "Diboson_CMS_btagHFDown", "Diboson_CMS_btagLFUp", "Diboson_CMS_btagLFDown", // 14
			"top", "top_LEPUp", "top_LEPDown", "top_CMS_scale_jUp", "top_CMS_scale_jDown",	"top_CMS_res_metUp", "top_CMS_res_metDown", 
			"top_CMS_puUp", "top_CMS_puDown", "top_CMS_btagHFUp", "top_CMS_btagHFDown", "top_CMS_btagLFUp", "top_CMS_btagLFDown",		// 27
			"Vjets", "Vjets_LEPUp", "Vjets_LEPDown", "Vjets_CMS_scale_jUp", "Vjets_CMS_scale_jDown", "Vjets_CMS_res_metUp", "Vjets_CMS_res_metDown", 
			"Vjets_CMS_puUp", "Vjets_CMS_puDown", "Vjets_CMS_btagHFUp", "Vjets_CMS_btagHFDown", "Vjets_CMS_btagLFUp", "Vjets_CMS_btagLFDown"	// 40
			};
  
  for (int i=0; i<53; i++)
  {
    hists[i] = new TH1D(HistName[i],HistName[i], NBINS, MINRange, MAXRange);
    hists[i]->Sumw2();
  }
  //============================================================
  // DRAW THE VARIABLE FOR ALL SAMPLES, CREATE HISTOS
  //============================================================    
  
  for (size_t isamp=0; isamp<samples.size(); isamp++) {
    Sample *s = samples[isamp];
    
    double xsec = s->cross();
    double otherscale = s->otherscale();
    int nmc =  s->mcevent();
    int nneg = s->mcevent_neg();

    //cout<< " == > " << s->name() << "\t" << s->cross() << endl;
    if(s->name().EqualTo("data")) { 
    	//intLUMIinvpb = s->cross(); 
      cout<< "Lumi = " << intLUMIinvpb << endl;
    }
    
    TTree *mytree = s->Tree();
    
    int nEvents=-1, nNegEvents=-1, type=-1, nBTagJet_loose=-1;
    float l_pt1=-1, l_pt2=-1, l_eta1=-999, l_eta2=-999, ungroomed_PuppiAK8_jet_pt=-1, ungroomed_PuppiAK8_jet_eta=-1, PuppiAK8_jet_tau2tau1=-1, dilep_m=-1, PuppiAK8_jet_mass_so_corr=-1, v_pt=-1;
    float l_pt1_Up=-1, l_pt1_Down=-1, l_pt2_Up=-1,l_pt2_Down=-1;
    float vbf_maxpt_jj_m=-1, vbf_maxpt_j2_eta=-999, vbf_maxpt_j1_eta=-999, vbf_maxpt_j1_pt=-1, vbf_maxpt_j2_pt=-1;
    float pfMET_Corr=-1, mass_lvj_type0=-1, mass_llj_PuppiAK8=-1;
    float mass_lvj_type0_LEP_Up=-1, mass_lvj_type0_LEP_Down=-1, mass_lvj_type0_PuppiAK8_jes_up=-1, mass_lvj_type0_PuppiAK8_jes_dn=-1;
    float genWeight=-1, trig_eff_Weight=-1, id_eff_Weight=-1, pu_Weight=-1, btag0Wgt=-1;
    float pu_Weight_down=-1,pu_Weight_up=-1, btag0WgtDownHF=-1, btag0WgtUpHF=-1, btag0WgtUpLF=-1, btag0WgtDownLF=-1;

    float ZeppenfeldWL_type0=-1, ZeppenfeldWH=-1, BosonCentrality_type0=-1;
    float ZeppenfeldWL_type0_LEP_Up=-1, ZeppenfeldWL_type0_LEP_Down=-1, BosonCentrality_type0_LEP_Up=-1, BosonCentrality_type0_LEP_Down=-1;
    //float LHEWeight[1164];
    float ungroomed_PuppiAK8_jet_pt_jes_up=-1, ungroomed_PuppiAK8_jet_pt_jes_dn=-1, ungroomed_PuppiAK8_jet_eta_jes_up=-1, ungroomed_PuppiAK8_jet_eta_jes_dn=-1, ungroomed_PuppiAK8_jet_mass_jes_up=-1, ungroomed_PuppiAK8_jet_mass_jes_dn=-1, vbf_maxpt_jj_m_jes_up=-1, vbf_maxpt_jj_m_jes_dn=-1, vbf_maxpt_j2_eta_jes_up=-1, vbf_maxpt_j2_eta_jes_dn=-1, vbf_maxpt_j1_pt_jes_up=-1, vbf_maxpt_j1_pt_jes_dn=-1, vbf_maxpt_j2_pt_jes_up=-1, vbf_maxpt_j2_pt_jes_dn=-1, pfMET_jes_up=-1, pfMET_jes_dn=-1, ZeppenfeldWL_type0_jes_up=-1, ZeppenfeldWL_type0_jes_dn=-1, ZeppenfeldWH_jes_up=-1, ZeppenfeldWH_jes_dn=-1, BosonCentrality_type0_jes_up=-1, BosonCentrality_type0_jes_dn=-1, vbf_maxpt_j1_eta_jes_up=-1, vbf_maxpt_j1_eta_jes_dn=-1;
    float pfMET_Corr_jerup=-1, pfMET_Corr_jerdn=-1, ZeppenfeldWL_type0_jer_up=-1, ZeppenfeldWL_type0_jer_dn=-1, mass_lvj_type0_PuppiAK8_jer_up=-1, mass_lvj_type0_PuppiAK8_jer_dn=-1;
    
    mytree->SetBranchStatus("*",0);
    //mytree->SetBranchStatus("nEvents",1);
    //mytree->SetBranchStatus("nNegEvents",1);
    //mytree->SetBranchStatus("LHEWeight",1);
    mytree->SetBranchStatus("type",1);
    mytree->SetBranchStatus("nBTagJet_loose",1);
    //mytree->SetBranchAddress("nEvents",   &nEvents);
    //mytree->SetBranchAddress("nNegEvents",   &nNegEvents);
    //mytree->SetBranchAddress("LHEWeight",LHEWeight);
    mytree->SetBranchAddress("type",&type);
    mytree->SetBranchAddress("nBTagJet_loose",&nBTagJet_loose);

    mytree->SetBranchStatus("l_pt1",1);
    mytree->SetBranchAddress("l_pt1",&l_pt1);	
    mytree->SetBranchStatus("l_pt1_Up",1);
    mytree->SetBranchAddress("l_pt1_Up",&l_pt1_Up);	
    mytree->SetBranchStatus("l_pt1_Down",1);
    mytree->SetBranchAddress("l_pt1_Down",&l_pt1_Down);	

    mytree->SetBranchStatus("l_eta1",1);
    mytree->SetBranchAddress("l_eta1",&l_eta1);	

    mytree->SetBranchStatus("l_pt2",1);
    mytree->SetBranchAddress("l_pt2",&l_pt2);
    mytree->SetBranchStatus("l_pt2_Up",1);
    mytree->SetBranchAddress("l_pt2_Up",&l_pt2_Up);	
    mytree->SetBranchStatus("l_pt2_Down",1);
    mytree->SetBranchAddress("l_pt2_Down",&l_pt2_Down);	

    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_pt",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_pt",&ungroomed_PuppiAK8_jet_pt);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_pt_jes_up",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_pt_jes_up",&ungroomed_PuppiAK8_jet_pt_jes_up);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_pt_jes_dn",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_pt_jes_dn",&ungroomed_PuppiAK8_jet_pt_jes_dn);

    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_eta",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_eta",&ungroomed_PuppiAK8_jet_eta);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_eta_jes_up",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_eta_jes_up",&ungroomed_PuppiAK8_jet_eta_jes_up);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_eta_jes_dn",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_eta_jes_dn",&ungroomed_PuppiAK8_jet_eta_jes_dn);

    mytree->SetBranchStatus("PuppiAK8_jet_tau2tau1",1);
    mytree->SetBranchAddress("PuppiAK8_jet_tau2tau1",&PuppiAK8_jet_tau2tau1);

    //mytree->SetBranchStatus("dilep_m",1);
    //mytree->SetBranchAddress("dilep_m",&dilep_m);

    mytree->SetBranchStatus("PuppiAK8_jet_mass_so_corr",1);
    mytree->SetBranchAddress("PuppiAK8_jet_mass_so_corr",&PuppiAK8_jet_mass_so_corr);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_mass_jes_up",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_mass_jes_up",&ungroomed_PuppiAK8_jet_mass_jes_up);
    mytree->SetBranchStatus("ungroomed_PuppiAK8_jet_mass_jes_dn",1);
    mytree->SetBranchAddress("ungroomed_PuppiAK8_jet_mass_jes_dn",&ungroomed_PuppiAK8_jet_mass_jes_dn);

    //mytree->SetBranchStatus("v_pt",1);
    //mytree->SetBranchAddress("v_pt",&v_pt);

    mytree->SetBranchStatus("vbf_maxpt_jj_m",1);
    mytree->SetBranchAddress("vbf_maxpt_jj_m",&vbf_maxpt_jj_m);
    mytree->SetBranchStatus("vbf_maxpt_jj_m_jes_up",1);
    mytree->SetBranchAddress("vbf_maxpt_jj_m_jes_up",&vbf_maxpt_jj_m_jes_up);
    mytree->SetBranchStatus("vbf_maxpt_jj_m_jes_dn",1);
    mytree->SetBranchAddress("vbf_maxpt_jj_m_jes_dn",&vbf_maxpt_jj_m_jes_dn);

    mytree->SetBranchStatus("vbf_maxpt_j2_eta",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_eta",&vbf_maxpt_j2_eta);
    mytree->SetBranchStatus("vbf_maxpt_j2_eta_jes_up",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_eta_jes_up",&vbf_maxpt_j2_eta_jes_up);
    mytree->SetBranchStatus("vbf_maxpt_j2_eta_jes_dn",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_eta_jes_dn",&vbf_maxpt_j2_eta_jes_dn);

    mytree->SetBranchStatus("vbf_maxpt_j1_eta",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_eta",&vbf_maxpt_j1_eta);
    mytree->SetBranchStatus("vbf_maxpt_j1_eta_jes_up",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_eta_jes_up",&vbf_maxpt_j1_eta_jes_up);
    mytree->SetBranchStatus("vbf_maxpt_j1_eta_jes_dn",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_eta_jes_dn",&vbf_maxpt_j1_eta_jes_dn);

    mytree->SetBranchStatus("vbf_maxpt_j1_pt",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_pt",&vbf_maxpt_j1_pt);
    mytree->SetBranchStatus("vbf_maxpt_j1_pt_jes_up",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_pt_jes_up",&vbf_maxpt_j1_pt_jes_up);
    mytree->SetBranchStatus("vbf_maxpt_j1_pt_jes_dn",1);
    mytree->SetBranchAddress("vbf_maxpt_j1_pt_jes_dn",&vbf_maxpt_j1_pt_jes_dn);

    mytree->SetBranchStatus("vbf_maxpt_j2_pt",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_pt",&vbf_maxpt_j2_pt);
    mytree->SetBranchStatus("vbf_maxpt_j2_pt_jes_up",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_pt_jes_up",&vbf_maxpt_j2_pt_jes_up);
    mytree->SetBranchStatus("vbf_maxpt_j2_pt_jes_dn",1);
    mytree->SetBranchAddress("vbf_maxpt_j2_pt_jes_dn",&vbf_maxpt_j2_pt_jes_dn);

    mytree->SetBranchStatus("pfMET_Corr",1);
    mytree->SetBranchAddress("pfMET_Corr",&pfMET_Corr);
    mytree->SetBranchStatus("pfMET_jes_up",1);
    mytree->SetBranchAddress("pfMET_jes_up",&pfMET_jes_up);
    mytree->SetBranchStatus("pfMET_jes_dn",1);
    mytree->SetBranchAddress("pfMET_jes_dn",&pfMET_jes_dn);
    mytree->SetBranchStatus("pfMET_Corr_jerup",1);
    mytree->SetBranchAddress("pfMET_Corr_jerup",&pfMET_Corr_jerup);
    mytree->SetBranchStatus("pfMET_Corr_jerdn",1);
    mytree->SetBranchAddress("pfMET_Corr_jerdn",&pfMET_Corr_jerdn);

    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8",&mass_lvj_type0);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_LEP_Up",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_LEP_Up",&mass_lvj_type0_LEP_Up);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_LEP_Down",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_LEP_Down",&mass_lvj_type0_LEP_Down);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_jes_up",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_jes_up",&mass_lvj_type0_PuppiAK8_jes_up);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_jes_dn",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_jes_dn",&mass_lvj_type0_PuppiAK8_jes_dn);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_jer_up",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_jer_up",&mass_lvj_type0_PuppiAK8_jer_up);
    mytree->SetBranchStatus("mass_lvj_type0_PuppiAK8_jer_dn",1);
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8_jer_dn",&mass_lvj_type0_PuppiAK8_jer_dn);

    //mytree->SetBranchStatus("mass_llj_PuppiAK8",1);
    //mytree->SetBranchAddress("mass_llj_PuppiAK8",&mass_llj_PuppiAK8);
    mytree->SetBranchStatus("genWeight",1);
    mytree->SetBranchAddress("genWeight",&genWeight);
    mytree->SetBranchStatus("trig_eff_Weight",1);
    mytree->SetBranchAddress("trig_eff_Weight",&trig_eff_Weight);
    mytree->SetBranchStatus("id_eff_Weight",1);
    mytree->SetBranchAddress("id_eff_Weight",&id_eff_Weight);

    mytree->SetBranchStatus("pu_Weight",1);
    mytree->SetBranchAddress("pu_Weight",&pu_Weight);
    mytree->SetBranchStatus("pu_Weight_up",1);
    mytree->SetBranchAddress("pu_Weight_up",&pu_Weight_up);
    mytree->SetBranchStatus("pu_Weight_down",1);
    mytree->SetBranchAddress("pu_Weight_down",&pu_Weight_down);

    mytree->SetBranchStatus("btag0Wgt",1);
    mytree->SetBranchAddress("btag0Wgt",&btag0Wgt);
    mytree->SetBranchStatus("btag0WgtUpHF",1);
    mytree->SetBranchAddress("btag0WgtUpHF",&btag0WgtUpHF);
    mytree->SetBranchStatus("btag0WgtDownHF",1);
    mytree->SetBranchAddress("btag0WgtDownHF",&btag0WgtDownHF);
    mytree->SetBranchStatus("btag0WgtUpLF",1);
    mytree->SetBranchAddress("btag0WgtUpLF",&btag0WgtUpLF);
    mytree->SetBranchStatus("btag0WgtDownLF",1);
    mytree->SetBranchAddress("btag0WgtDownLF",&btag0WgtDownLF);

    mytree->SetBranchStatus("ZeppenfeldWL_type0",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0",&ZeppenfeldWL_type0);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_LEP_Up",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_LEP_Up",&ZeppenfeldWL_type0_LEP_Up);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_LEP_Down",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_LEP_Down",&ZeppenfeldWL_type0_LEP_Down);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_jes_up",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_jes_up",&ZeppenfeldWL_type0_jes_up);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_jes_dn",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_jes_dn",&ZeppenfeldWL_type0_jes_dn);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_jer_up",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_jer_up",&ZeppenfeldWL_type0_jer_up);
    mytree->SetBranchStatus("ZeppenfeldWL_type0_jer_dn",1);
    mytree->SetBranchAddress("ZeppenfeldWL_type0_jer_dn",&ZeppenfeldWL_type0_jer_dn);

    mytree->SetBranchStatus("ZeppenfeldWH",1);
    mytree->SetBranchAddress("ZeppenfeldWH",&ZeppenfeldWH);
    mytree->SetBranchStatus("ZeppenfeldWH_jes_up",1);
    mytree->SetBranchAddress("ZeppenfeldWH_jes_up",&ZeppenfeldWH_jes_up);
    mytree->SetBranchStatus("ZeppenfeldWH_jes_dn",1);
    mytree->SetBranchAddress("ZeppenfeldWH_jes_dn",&ZeppenfeldWH_jes_dn);

    mytree->SetBranchStatus("BosonCentrality_type0",1);
    mytree->SetBranchAddress("BosonCentrality_type0",&BosonCentrality_type0);
    mytree->SetBranchStatus("BosonCentrality_type0_LEP_Up",1);
    mytree->SetBranchAddress("BosonCentrality_type0_LEP_Up",&BosonCentrality_type0_LEP_Up);
    mytree->SetBranchStatus("BosonCentrality_type0_LEP_Down",1);
    mytree->SetBranchAddress("BosonCentrality_type0_LEP_Down",&BosonCentrality_type0_LEP_Down);
    mytree->SetBranchStatus("BosonCentrality_type0_jes_up",1);
    mytree->SetBranchAddress("BosonCentrality_type0_jes_up",&BosonCentrality_type0_jes_up);
    mytree->SetBranchStatus("BosonCentrality_type0_jes_dn",1);
    mytree->SetBranchAddress("BosonCentrality_type0_jes_dn",&BosonCentrality_type0_jes_dn);
    
    //cout<< " Reading sample : " << isamp << "   " << s->name() << endl;
    for(int i = 0; i<mytree->GetEntries(); i++)
    {
      //std::cout << vbf_maxpt_jj_m << std::endl;
      mytree->GetEntry(i);

      if(!(type==0||type==1)) continue;

      if (1)	//----------------	Nominal, PU up, PU down
      {
	      if(!(l_pt2<0 && l_pt1>30)) continue;
	      if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	      if(!(((type==0)&&(pfMET_Corr>50)) || ((type==1)&&(pfMET_Corr>80)))) continue;
	      if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	      if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	      if(!(nBTagJet_loose==0)) continue;
	      //if(!(dilep_m>76 && dilep_m<107)) continue;
	      if(!(vbf_maxpt_jj_m>800)) continue;
	      if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	      if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	      if(!(mass_lvj_type0>600)) continue;
	      //if(!(v_pt>200.)) continue;
	      if(!(BosonCentrality_type0>1.0)) continue;
	      if(!((abs(ZeppenfeldWL_type0)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	      if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
    
	      if(s->name().EqualTo("data"))	 hists[0]->Fill(mass_lvj_type0);
	      if(s->name().EqualTo("WV_EWK"))	 hists[1]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[14]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[27]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[40]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[8]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_up*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[21]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_up*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[34]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_up*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[47]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_up*btag0Wgt)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[9]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_down*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[22]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_down*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[35]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_down*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[48]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight_down*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[10]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[23]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[36]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[49]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpHF)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[11]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[24]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[37]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownHF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[50]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownHF)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[12]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[25]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[38]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[51]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtUpLF)/(1.0*(nmc-2*nneg)));

	      if(s->name().EqualTo("WV_EWK"))	 hists[13]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson")) 	 hists[26]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[39]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownLF)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[52]->Fill(mass_lvj_type0,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0WgtDownLF)/(1.0*(nmc-2*nneg)));
      }

      if (1)	//--------------------------- LEP up
      {
	      if(!(l_pt2_Up<0 && l_pt1_Up>30)) continue;
	      if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	      if(!(((type==0)&&(pfMET_Corr>50)) || ((type==1)&&(pfMET_Corr>80)))) continue;
	      if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	      if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	      if(!(nBTagJet_loose==0)) continue;
	      //if(!(dilep_m>76 && dilep_m<107)) continue;
	      if(!(vbf_maxpt_jj_m>800)) continue;
	      if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	      if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	      if(!(mass_lvj_type0_LEP_Up>600)) continue;
	      //if(!(v_pt>200.)) continue;
	      if(!(BosonCentrality_type0_LEP_Up>1.0)) continue;
	      if(!((abs(ZeppenfeldWL_type0_LEP_Up)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	      if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
   
	      //if(s->name().EqualTo("data"))	 histo_data_LEPUp->Fill(mass_lvj_type0_LEP_Up);
	      if(s->name().EqualTo("WV_EWK"))	 hists[2]->Fill(mass_lvj_type0_LEP_Up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson"))   hists[15]->Fill(mass_lvj_type0_LEP_Up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[28]->Fill(mass_lvj_type0_LEP_Up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[41]->Fill(mass_lvj_type0_LEP_Up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
      }

      if (1)	//--------------------------- LEP down
      {
	      if(!(l_pt2_Down<0 && l_pt1_Down>30)) continue;
	      if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	      if(!(((type==0)&&(pfMET_Corr>50)) || ((type==1)&&(pfMET_Corr>80)))) continue;
	      if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	      if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	      if(!(nBTagJet_loose==0)) continue;
	      //if(!(dilep_m>76 && dilep_m<107)) continue;
	      if(!(vbf_maxpt_jj_m>800)) continue;
	      if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	      if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	      if(!(mass_lvj_type0_LEP_Down>600)) continue;
	      //if(!(v_pt>200.)) continue;
	      if(!(BosonCentrality_type0_LEP_Down>1.0)) continue;
	      if(!((abs(ZeppenfeldWL_type0_LEP_Down)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	      if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
   
	      //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(mass_lvj_type0_LEP_Down);
	      if(s->name().EqualTo("WV_EWK"))	 hists[3]->Fill(mass_lvj_type0_LEP_Down,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("Diboson"))   hists[16]->Fill(mass_lvj_type0_LEP_Down,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("top"))  	 hists[29]->Fill(mass_lvj_type0_LEP_Down,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      if(s->name().EqualTo("V+jets"))	 hists[42]->Fill(mass_lvj_type0_LEP_Down,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
      }

	if (1)	//-------------------	JES up
	{
	   if(!(l_pt2<0 && l_pt1>30)) continue;
	   if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	   if(!(((type==0)&&(pfMET_jes_up>50)) || ((type==1)&&(pfMET_jes_up>80)))) continue;
	   if(!((ungroomed_PuppiAK8_jet_pt_jes_up>200)&&(abs(ungroomed_PuppiAK8_jet_eta_jes_up)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	   if(!((ungroomed_PuppiAK8_jet_mass_jes_up>65) && (ungroomed_PuppiAK8_jet_mass_jes_up<105))) continue;
	   if(!(nBTagJet_loose==0)) continue;
	   //if(!(dilep_m>76 && dilep_m<107)) continue;
	   if(!(vbf_maxpt_jj_m_jes_up>800)) continue;
	   if(!(abs(vbf_maxpt_j2_eta_jes_up-vbf_maxpt_j1_eta_jes_up)>4.0)) continue;
	   if(!((vbf_maxpt_j1_pt_jes_up>30) && (vbf_maxpt_j2_pt_jes_up>30))) continue;
	   if(!(mass_lvj_type0_PuppiAK8_jes_up>600)) continue;
	   //if(!(v_pt>200.)) continue;
	   if(!(BosonCentrality_type0_jes_up>1.0)) continue;
	   if(!((abs(ZeppenfeldWL_type0_jes_up)/abs(vbf_maxpt_j2_eta_jes_up-vbf_maxpt_j1_eta_jes_up))<0.3)) continue;
	   if(!((abs(ZeppenfeldWH_jes_up)/abs(vbf_maxpt_j2_eta_jes_up-vbf_maxpt_j1_eta_jes_up))<0.3)) continue;

	   //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(mass_lvj_type0_PuppiAK8_jes_up);
	   if(s->name().EqualTo("WV_EWK"))	 hists[4]->Fill(mass_lvj_type0_PuppiAK8_jes_up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("Diboson"))  	 hists[17]->Fill(mass_lvj_type0_PuppiAK8_jes_up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("top"))  	 hists[30]->Fill(mass_lvj_type0_PuppiAK8_jes_up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("V+jets"))	 hists[43]->Fill(mass_lvj_type0_PuppiAK8_jes_up,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	}

	if (1)	//-------------------	JES down
	{
	   if(!(l_pt2<0 && l_pt1>30)) continue;
	   if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	   if(!(((type==0)&&(pfMET_jes_dn>50)) || ((type==1)&&(pfMET_jes_dn>80)))) continue;
	   if(!((ungroomed_PuppiAK8_jet_pt_jes_dn>200)&&(abs(ungroomed_PuppiAK8_jet_eta_jes_dn)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	   if(!((ungroomed_PuppiAK8_jet_mass_jes_dn>65) && (ungroomed_PuppiAK8_jet_mass_jes_dn<105))) continue;
	   if(!(nBTagJet_loose==0)) continue;
	   //if(!(dilep_m>76 && dilep_m<107)) continue;
	   if(!(vbf_maxpt_jj_m_jes_dn>800)) continue;
	   if(!(abs(vbf_maxpt_j2_eta_jes_dn-vbf_maxpt_j1_eta_jes_dn)>4.0)) continue;
	   if(!((vbf_maxpt_j1_pt_jes_dn>30) && (vbf_maxpt_j2_pt_jes_dn>30))) continue;
	   if(!(mass_lvj_type0_PuppiAK8_jes_dn>600)) continue;
	   //if(!(v_pt>200.)) continue;
	   if(!(BosonCentrality_type0_jes_dn>1.0)) continue;
	   if(!((abs(ZeppenfeldWL_type0_jes_dn)/abs(vbf_maxpt_j2_eta_jes_dn-vbf_maxpt_j1_eta_jes_dn))<0.3)) continue;
	   if(!((abs(ZeppenfeldWH_jes_dn)/abs(vbf_maxpt_j2_eta_jes_dn-vbf_maxpt_j1_eta_jes_dn))<0.3)) continue;

	   //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(mass_lvj_type0_PuppiAK8_jes_dn);
	   if(s->name().EqualTo("WV_EWK"))	 hists[5]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("Diboson"))  	 hists[18]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("top"))  	 hists[31]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("V+jets"))	 hists[44]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	}

	if (1)	//-------------------	JER up
	{
	   if(!(l_pt2<0 && l_pt1>30)) continue;
	   if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	   if(!(((type==0)&&(pfMET_Corr_jerup>50)) || ((type==1)&&(pfMET_Corr_jerup>80)))) continue;
	   if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	   if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	   if(!(nBTagJet_loose==0)) continue;
	   //if(!(dilep_m>76 && dilep_m<107)) continue;
	   if(!(vbf_maxpt_jj_m>800)) continue;
	   if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	   if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	   if(!(mass_lvj_type0_PuppiAK8_jer_up>600)) continue;
	   //if(!(v_pt>200.)) continue;
	   if(!(BosonCentrality_type0>1.0)) continue;
	   if(!((abs(ZeppenfeldWL_type0_jer_up)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	   if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;

	   //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(mass_lvj_type0_PuppiAK8_jes_dn);
	   if(s->name().EqualTo("WV_EWK"))	 hists[6]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("Diboson"))  	 hists[19]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("top"))  	 hists[32]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("V+jets"))	 hists[45]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	}

	if (1)	//-------------------	JER down
	{
	   if(!(l_pt2<0 && l_pt1>30)) continue;
	   if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	   if(!(((type==0)&&(pfMET_Corr_jerdn>50)) || ((type==1)&&(pfMET_Corr_jerdn>80)))) continue;
	   if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	   if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	   if(!(nBTagJet_loose==0)) continue;
	   //if(!(dilep_m>76 && dilep_m<107)) continue;
	   if(!(vbf_maxpt_jj_m>800)) continue;
	   if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	   if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	   if(!(mass_lvj_type0_PuppiAK8_jer_dn>600)) continue;
	   //if(!(v_pt>200.)) continue;
	   if(!(BosonCentrality_type0>1.0)) continue;
	   if(!((abs(ZeppenfeldWL_type0_jer_dn)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	   if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;

	   //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(mass_lvj_type0_PuppiAK8_jes_dn);
	   if(s->name().EqualTo("WV_EWK"))	 hists[7]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("Diboson"))  	 hists[20]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("top"))  	 hists[33]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	   if(s->name().EqualTo("V+jets"))	 hists[46]->Fill(mass_lvj_type0_PuppiAK8_jes_dn,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	}
      }
  }


  for (int i=0; i<53; i++)
  {
    // include overflow bin in last bin
    hists[i]->SetBinContent(NBINS,hists[i]->GetBinContent(NBINS)+hists[i]->GetBinContent(NBINS+1));
    cout << HistName[i] << " = " << hists[i]->Integral() << endl;
  }

  f.Write();
}

void wwGetCard2()
{
  int start_s=clock();
  model("DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt",
		 "DibosonBoostedElMuSamples13TeV.txt",
		 commonplotvars_chs);
  int stop_s=clock();
  cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

}
