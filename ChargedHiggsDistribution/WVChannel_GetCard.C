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

void model(const char *samplefilename,
	   const plotVar_t plotvars[] = commonplotvars_chs,
	   const TString OutPutRootFileName = "ch1_splitted_TF1")
{
  cout<< "done..." << endl;

  vector<Sample *> samples;
  
  loadSamples(samplefilename,samples);
  
  // Data
  
  Sample *sdata = samples[0];
  
  if (sdata->Tree())
    cout << "ndata =" << sdata->Tree()->GetEntries() <<endl;

  //============================================================
  //  VARIABLE LOOP
  //============================================================
  //int NBINS = 25;
  //double MINRange = 600;
  //double MAXRange = 2500;
  //> Float_t bins[] = { 50, 55, 60, 65, 72, 80, 90, 100, 120, 160 };
  //> Int_t  binnum = sizeof(bins)/sizeof(Float_t) - 1; // or just = 9
  //

  double bins[9] = {600, 700, 800, 900, 1000, 1200, 1500, 2000, 2500};
  int NBINS = 8;



  TString OutRootFileSuffix = "_NoBinbyBin";
  TFile f(OutPutRootFileName + OutRootFileSuffix + ".root", "RECREATE");	// if name change then change this name also in first time where script add_stat_shapes.py appears


  TH1 *hists[53];

  
  cout<< "Size of sample = " << samples.size() << endl;
  // histo for JES, JER, UP, Btag, LEP up/down uncertanities
  /*
  for (int i=0; i<53; i++)
  {
    stringstream ss;
    ss << i;
    string temp = ss.str();
    const char* name = temp.c_str();
    hists[i] = new TH1D(name,name,NBINS, bins);
    hists[i]->Sumw2();
  }
  */
  //============================================================
  // DRAW THE VARIABLE FOR ALL SAMPLES, CREATE HISTOS
  //============================================================    
  

  hists[0] = new TH1D("data","data;M_{WW} (GeV);Events",NBINS, bins);
  hists[0]->Sumw2();
  TString namePrev = "data";
  int countSample = 0;
  for (size_t isamp=0; isamp<samples.size(); isamp++) {
    Sample *s = samples[isamp];
    
    double xsec = s->cross();
    double otherscale = s->otherscale();
    int nmc =  s->mcevent();
    int nneg = s->mcevent_neg();
    TString NewName = s->name();

    cout<<"\n\n\n\n---"<<endl;
    if (NewName != namePrev) 
    {  
    	countSample++;
	//stringstream ss;
	//ss << countSample;
	//string temp = ss.str();
	//const char* name = temp.c_str();
	TString name = s->name() + ";M_{WW} (GeV);Events";
	hists[countSample] = new TH1D(s->name(),s->name(),NBINS, bins);
	hists[countSample]->Sumw2();
	cout<<"==> Hist created: "<< countSample << "\t" << s->name() << "\t" << hists[countSample]->GetName() << endl;
    }
    namePrev = NewName;


    cout<< "Running for  ==>  " << s->name() << "\t" << endl;
    if(s->name().EqualTo("data")) { 
    	//intLUMIinvpb = s->cross(); 
      cout<< "Lumi = " << intLUMIinvpb << endl;
    }
    
    TTree *mytree = s->Tree();
    
    int nEvents=-1, nNegEvents=-1, type=-1, nBTagJet_loose=-1;
    float l_pt1=-1, l_pt2=-1, l_eta1=-999, l_eta2=-999, ungroomed_PuppiAK8_jet_pt=-1, ungroomed_PuppiAK8_jet_eta=-1, PuppiAK8_jet_tau2tau1=-1, dilep_m=-1, PuppiAK8_jet_mass_so_corr=-1, v_pt=-1;
    float l_pt1_Up=-1, l_pt1_Down=-1, l_pt2_Up=-1,l_pt2_Down=-1;
    float vbf_maxpt_jj_m=-1, vbf_maxpt_j2_eta=-999, vbf_maxpt_j1_eta=-999, vbf_maxpt_j1_pt=-1, vbf_maxpt_j2_pt=-1;
    float pfMET_Corr=-1, mass_llj_PuppiAK8=-1;
    float mass_lvj_type0_PuppiAK8=-1, mass_lvj_type0_LEP_Up=-1, mass_lvj_type0_LEP_Down=-1, mass_lvj_type0_PuppiAK8_jes_up=-1, mass_lvj_type0_PuppiAK8_jes_dn=-1, mass_lvj_type0_PuppiAK8_jer_up=-1, mass_lvj_type0_PuppiAK8_jer_dn=-1;
    float mt_lvj_type0_PuppiAK8=-1, mt_lvj_type0_LEP_Up=-1, mt_lvj_type0_LEP_Down=-1, mt_lvj_type0_PuppiAK8_jes_up=-1, mt_lvj_type0_PuppiAK8_jes_dn=-1, mt_lvj_type0_PuppiAK8_jer_up=-1, mt_lvj_type0_PuppiAK8_jer_dn=-1;
    float genWeight=-1, trig_eff_Weight=-1, id_eff_Weight=-1, pu_Weight=-1, btag0Wgt=-1;
    float pu_Weight_down=-1,pu_Weight_up=-1, btag0WgtDownHF=-1, btag0WgtUpHF=-1, btag0WgtUpLF=-1, btag0WgtDownLF=-1;

    float ZeppenfeldWL_type0=-1, ZeppenfeldWH=-1, BosonCentrality_type0=-1;
    float ZeppenfeldWL_type0_LEP_Up=-1, ZeppenfeldWL_type0_LEP_Down=-1, BosonCentrality_type0_LEP_Up=-1, BosonCentrality_type0_LEP_Down=-1;
    float LHEWeight[1164];
    float ungroomed_PuppiAK8_jet_pt_jes_up=-1, ungroomed_PuppiAK8_jet_pt_jes_dn=-1, ungroomed_PuppiAK8_jet_eta_jes_up=-1, ungroomed_PuppiAK8_jet_eta_jes_dn=-1, vbf_maxpt_jj_m_jes_up=-1, vbf_maxpt_jj_m_jes_dn=-1, vbf_maxpt_j2_eta_jes_up=-1, vbf_maxpt_j2_eta_jes_dn=-1, vbf_maxpt_j1_pt_jes_up=-1, vbf_maxpt_j1_pt_jes_dn=-1, vbf_maxpt_j2_pt_jes_up=-1, vbf_maxpt_j2_pt_jes_dn=-1, pfMET_jes_up=-1, pfMET_jes_dn=-1, ZeppenfeldWL_type0_jes_up=-1, ZeppenfeldWL_type0_jes_dn=-1, ZeppenfeldWH_jes_up=-1, ZeppenfeldWH_jes_dn=-1, BosonCentrality_type0_jes_up=-1, BosonCentrality_type0_jes_dn=-1, vbf_maxpt_j1_eta_jes_up=-1, vbf_maxpt_j1_eta_jes_dn=-1;
    float pfMET_Corr_jerup=-1, pfMET_Corr_jerdn=-1, ZeppenfeldWL_type0_jer_up=-1, ZeppenfeldWL_type0_jer_dn=-1;
    
    mytree->SetBranchStatus("*",0);
    mytree->SetBranchStatus("LHEWeight",1);
    mytree->SetBranchAddress("LHEWeight",LHEWeight);
    mytree->SetBranchStatus("type",1);
    mytree->SetBranchAddress("type",&type);
    mytree->SetBranchStatus("nBTagJet_loose",1);
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
    mytree->SetBranchStatus("PuppiAK8_jet_mass_so_corr",1);
    mytree->SetBranchAddress("PuppiAK8_jet_mass_so_corr",&PuppiAK8_jet_mass_so_corr);

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
    mytree->SetBranchAddress("mass_lvj_type0_PuppiAK8",&mass_lvj_type0_PuppiAK8);
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
    cout<< "Reading sample : " << s->name() << "\t" << countSample << endl << endl;
    for(int i = 0; i<mytree->GetEntries(); i++)
    {
      //std::cout << vbf_maxpt_jj_m << std::endl;
      mytree->GetEntry(i);

      if(!(type==0||type==1)) continue;

      if (1)	//----------------	Nominal, PU up, PU down
      {
	      if(!(l_pt2<0 && l_pt1>50)) continue;
	      if(!(((type==0)&&(abs(l_eta1)<2.4))||((type==1)&&((abs(l_eta1)<2.5)&&!(abs(l_eta1)>1.4442 && abs(l_eta1)<1.566))))) continue;
	      if(!(((type==0)&&(pfMET_Corr>50)) || ((type==1)&&(pfMET_Corr>80)))) continue;
	      if(!((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))) continue;
	      if(!((PuppiAK8_jet_mass_so_corr>65) && (PuppiAK8_jet_mass_so_corr<105))) continue;
	      if(!(nBTagJet_loose==0)) continue;
	      if(!(vbf_maxpt_jj_m>800)) continue;
	      if(!(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)) continue;
	      if(!((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))) continue;
	      if(!(mass_lvj_type0_PuppiAK8>600)) continue;
	      if(!(BosonCentrality_type0>1.0)) continue;
	      if(!((abs(ZeppenfeldWL_type0)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
	      if(!((abs(ZeppenfeldWH)/abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta))<0.3)) continue;
    
	      if(s->name().EqualTo("data")){
	      	hists[0]->Fill(mass_lvj_type0_PuppiAK8);
		hists[0]->SetName(s->name());
	      }
	      else{
	      	hists[countSample]->Fill(mass_lvj_type0_PuppiAK8,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
		//hists[countSample]->SetName(s->name());
	      }
	      //if(s->name().EqualTo("WV_EWK"))	 hists[41]->Fill(mass_lvj_type0_PuppiAK8,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      //if(s->name().EqualTo("Diboson")) 	 hists[42]->Fill(mass_lvj_type0_PuppiAK8,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      //if(s->name().EqualTo("top"))  	 hists[43]->Fill(mass_lvj_type0_PuppiAK8,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
	      //if(s->name().EqualTo("Vjets"))	 hists[44]->Fill(mass_lvj_type0_PuppiAK8,(xsec*otherscale*genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*btag0Wgt)/(1.0*(nmc-2*nneg)));
      }


      }
      cout<<"\t\t\t" << s->name() << "\t\t" << hists[countSample]->GetName() << endl;
      //cout<<"\n\n ====>  " << hists[27]->Integral() << endl;
  }

  
  // include overflow bin in last bin for all histograms
  for (int i=0; i<=countSample; i++)
  {
    hists[i]->SetBinContent(NBINS,hists[i]->GetBinContent(NBINS)+hists[i]->GetBinContent(NBINS+1));
    cout << hists[i]->GetName() << " = " << hists[i]->Integral() << endl;
    //hists[i]->Write();
  }




  // Write all histograms... 
//  for (int i=0; i<53; i++)
 // {
  //  hists[i]->Write();
 // }

    //-------------------------------------------------------------------------------------
    //
    //		Create Data card
    //
    //-------------------------------------------------------------------------------------
    #if 0
    char outputLimitsShape[200];
    sprintf(outputLimitsShape,"histo_limits_WV.txt");
    ofstream newcardShape;
    newcardShape.open(outputLimitsShape);
    newcardShape << Form("imax 1 number of channels\n");
    newcardShape << Form("jmax * number of background\n");
    newcardShape << Form("kmax * number of nuisance parameters\n");

    newcardShape << Form("shapes * * WVchannel_datacard.root $PROCESS $PROCESS_$SYSTEMATIC\n");
    newcardShape << Form("shapes data_obs * WVchannel_datacard.root histo_Data\n");
    newcardShape << Form("shapes Higgs * WVchannel_datacard.root histo_Higgs_M$MASS histo_Higgs_M$MASS_$SYSTEMATIC\n");
    newcardShape << Form("Observation %d\n", -1/*(int)histo_Data->GetBinContent(nb)*/);
    //newcardShape << Form("bin wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d\n",finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1);
    newcardShape << Form("process aQGC Wjet WV top Zjet\n");
    newcardShape << Form("process 0 1 2 3 4\n");
    newcardShape << Form("rate %8.5f %8.5f  %8.5f  %8.5f  %8.5f  %8.5f\n",-1.,-1.,-1.,-1.,-1.,-1.) ;
    //-------------------------------------------------------------------------------------

    newcardShape.close();
    #endif

  f.Write();
  f.Close();
}

void WVChannel_GetCard()
{
  int start_s=clock();
  model("DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36.txt",
	commonplotvars_chs,
	"ChargedHiggs_VariableBin");

  int stop_s=clock();
  cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;

}
