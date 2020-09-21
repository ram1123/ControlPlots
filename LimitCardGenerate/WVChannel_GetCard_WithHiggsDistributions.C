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

#include "WVChannel_GetCard_WithHiggsDistributions.h"

//======================================================================
bool DEBUG = true;

void model(const char *samplefilename,
           const TString OutPutRootFileName = "ch1_splitted_TF1_WV")
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
    int NBINS = 4;
    double MINRange = 600;
    double MAXRange = 2500;
    double massLEdges[5] = {600, 1075, 1550, 2025, 2500};
    //double massLEdges[9]={600, 700, 800, 900, 1000, 1200, 1500, 2000, 2500};
    
    
    
    const char* HistName[] = {	"data_obs",						// 0
        "diboson", "diboson_CMS_scale_lUp", "diboson_CMS_scale_lDown", "diboson_CMS_scale_jUp", "diboson_CMS_scale_jDown", "diboson_CMS_res_metUp", "diboson_CMS_res_metDown",
        "diboson_CMS_puUp", "diboson_CMS_puDown",	"diboson_CMS_btagHFUp", "diboson_CMS_btagHFDown", "diboson_CMS_btagLFUp", "diboson_CMS_btagLFDown", // 1
        "VVjjQCD", "VVjjQCD_CMS_scale_lUp", "VVjjQCD_CMS_scale_lDown", "VVjjQCD_CMS_scale_jUp", "VVjjQCD_CMS_scale_jDown", "VVjjQCD_CMS_res_metUp", "VVjjQCD_CMS_res_metDown",
        "VVjjQCD_CMS_puUp", "VVjjQCD_CMS_puDown", "VVjjQCD_CMS_btagHFUp", "VVjjQCD_CMS_btagHFDown", "VVjjQCD_CMS_btagLFUp", "VVjjQCD_CMS_btagLFDown", // 14
        "top", "top_CMS_scale_lUp", "top_CMS_scale_lDown", "top_CMS_scale_jUp", "top_CMS_scale_jDown",	"top_CMS_res_metUp", "top_CMS_res_metDown",
        "top_CMS_puUp", "top_CMS_puDown", "top_CMS_btagHFUp", "top_CMS_btagHFDown", "top_CMS_btagLFUp", "top_CMS_btagLFDown",		// 27
        "Vjets", "Vjets_CMS_scale_lUp", "Vjets_CMS_scale_lDown", "Vjets_CMS_scale_jUp", "Vjets_CMS_scale_jDown", "Vjets_CMS_res_metUp", "Vjets_CMS_res_metDown",
        "Vjets_CMS_puUp", "Vjets_CMS_puDown", "Vjets_CMS_btagHFUp", "Vjets_CMS_btagHFDown", "Vjets_CMS_btagLFUp", "Vjets_CMS_btagLFDown",	// 40
    };
    
    int SizeOf_HistName = sizeof(HistName)/sizeof(HistName[0]);
    if (DEBUG) std::cout << "Size of HistName array: " << sizeof(HistName)/sizeof(HistName[0]) << std::endl;
    
    TH1 *hists[SizeOf_HistName];
    
    int SizeOf_aQGC =   sizeof(fs0)/sizeof(fs0[0])+
    sizeof(fs1)/sizeof(fs1[0])+
    sizeof(fm0)/sizeof(fm0[0])+
    sizeof(fm1)/sizeof(fm1[0])+
    sizeof(fm2)/sizeof(fm2[0])+
    sizeof(fm3)/sizeof(fm3[0])+
    sizeof(fm4)/sizeof(fm4[0])+
    sizeof(fm5)/sizeof(fm5[0])+
    sizeof(fm6)/sizeof(fm6[0])+
    sizeof(fm7)/sizeof(fm7[0])+
    sizeof(ft0)/sizeof(ft0[0])+
    sizeof(ft1)/sizeof(ft1[0])+
    sizeof(ft2)/sizeof(ft2[0])+
    sizeof(ft5)/sizeof(ft5[0])+
    sizeof(ft6)/sizeof(ft6[0])+
    sizeof(ft7)/sizeof(ft7[0])+
    sizeof(ft8)/sizeof(ft8[0])+
    sizeof(ft9)/sizeof(ft9[0]);
    

    std::cout << "Size of fs0: "  << sizeof(fs0)/sizeof(fs0[0]) << std::endl;
    std::cout << "Size of fs1: "  << sizeof(fs1)/sizeof(fs1[0]) << std::endl;
    std::cout << "Size of fm0: "  << sizeof(fm0)/sizeof(fm0[0]) << std::endl;
    std::cout << "Size of fm1: "  << sizeof(fm1)/sizeof(fm1[0]) << std::endl;
    std::cout << "Size of fm2: "  << sizeof(fm2)/sizeof(fm2[0]) << std::endl;
    std::cout << "Size of fm3: "  << sizeof(fm3)/sizeof(fm3[0]) << std::endl;
    std::cout << "Size of fm4: "  << sizeof(fm4)/sizeof(fm4[0]) << std::endl;
    std::cout << "Size of fm5: "  << sizeof(fm5)/sizeof(fm5[0]) << std::endl;
    std::cout << "Size of fm6: "  << sizeof(fm6)/sizeof(fm6[0]) << std::endl;
    std::cout << "Size of fm7: "  << sizeof(fm7)/sizeof(fm7[0]) << std::endl;
    std::cout << "Size of ft0: "  << sizeof(ft0)/sizeof(ft0[0]) << std::endl;
    std::cout << "Size of ft1: "  << sizeof(ft1)/sizeof(ft1[0]) << std::endl;
    std::cout << "Size of ft2: "  << sizeof(ft2)/sizeof(ft2[0]) << std::endl;
    std::cout << "Size of ft5: "  << sizeof(ft5)/sizeof(ft5[0]) << std::endl;
    std::cout << "Size of ft6: "  << sizeof(ft6)/sizeof(ft6[0]) << std::endl;
    std::cout << "Size of ft7: "  << sizeof(ft7)/sizeof(ft7[0]) << std::endl;
    std::cout << "Size of ft8: "  << sizeof(ft8)/sizeof(ft8[0]) << std::endl;
    std::cout << "Size of ft9: "  << sizeof(ft9)/sizeof(ft9[0]) << std::endl;

    if (DEBUG) std::cout << "Size of aQGC array: " << SizeOf_aQGC << std::endl;
    
    TH1 *histo_aqgc[SizeOf_aQGC];
    for(int j=0;j<SizeOf_aQGC;j++)
    {
        stringstream ss;
        ss << j;
        TString temp = "aQGC_"+ss.str();
        const char* name = temp.Data();
        histo_aqgc[j] = new TH1D(name, name, NBINS, massLEdges);
        histo_aqgc[j]->Sumw2();
    }
    //let's define few histograms for the uncertainties
    TH1D* histo_diboson_EWK_CMS_QCDScaleBounding[6];
    TH1D* histo_VVjjQCD_EWK_CMS_QCDScaleBounding[6];
    for(int i = 0; i<6; i++)
    {
        stringstream ss;
        ss << i;
        string temp = ss.str()+"_QCDScale_QCD";
        string temp1 = ss.str()+"_QCDScale_diboson";
        const char* name = temp.c_str();
        const char* name1 = temp1.c_str();
        histo_diboson_EWK_CMS_QCDScaleBounding[i] = new TH1D(name1, name1, NBINS,massLEdges);
        histo_diboson_EWK_CMS_QCDScaleBounding[i]->Sumw2();
        histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i] = new TH1D(name, name, NBINS,massLEdges);
        histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->Sumw2();
    }
    TH1D* histo_diboson_EWK_CMS_PDFScaleBounding[100];
    TH1D* histo_VVjjQCD_EWK_CMS_PDFScaleBounding[100];
    for(int i = 0; i<100; i++)
    {
        stringstream ss;
        ss << i;
        string temp = ss.str()+"_PDFScale_diboson";
        string temp1 = ss.str()+"_PDFScale_VVJJQCD";
        const char* name = temp.c_str();
        const char* name1 = temp1.c_str();
        histo_diboson_EWK_CMS_PDFScaleBounding[i] = new TH1D(name, name, NBINS,massLEdges);
        histo_diboson_EWK_CMS_PDFScaleBounding[i]->Sumw2();
        histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i] = new TH1D(name1, name1, NBINS,massLEdges);
        histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->Sumw2();
    }
    
    TH1D* histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Up = new TH1D("VVjjQCD_VVjjQCD_QCDScaleUp","", NBINS,massLEdges);
    histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Up->Sumw2();
    
    TH1D* histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Down = new TH1D("VVjjQCD_VVjjQCD_QCDScaleDown","", NBINS,massLEdges);
    histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Down->Sumw2();
    
    TH1D* histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Up = new TH1D("VVjjQCD_pdf_ggbarUp","", NBINS,massLEdges);
    histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Up->Sumw2();
    
    TH1D* histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Down = new TH1D("VVjjQCD_pdf_ggbarDown","", NBINS,massLEdges);
    histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Down->Sumw2();
    
    
    TH1D* histo_diboson_EWK_CMS_QCDScaleBounding_Up = new TH1D("diboson_diboson_QCDScaleUp","", NBINS,massLEdges);
    histo_diboson_EWK_CMS_QCDScaleBounding_Up->Sumw2();
    
    TH1D* histo_diboson_EWK_CMS_QCDScaleBounding_Down = new TH1D("diboson_diboson_QCDScaleDown","", NBINS,massLEdges);
    histo_diboson_EWK_CMS_QCDScaleBounding_Down->Sumw2();
    
    TH1D* histo_diboson_EWK_CMS_PDFScaleBounding_Up = new TH1D("diboson_pdf_qqbarUp","", NBINS,massLEdges);
    histo_diboson_EWK_CMS_PDFScaleBounding_Up->Sumw2();
    
    TH1D* histo_diboson_EWK_CMS_PDFScaleBounding_Down = new TH1D("diboson_pdf_qqbarDown","", NBINS,massLEdges);
    histo_diboson_EWK_CMS_PDFScaleBounding_Down->Sumw2();
    
    
    // histo for JES, JER, UP, Btag, LEP up/down uncertanities
    for (int i=0; i<SizeOf_HistName; i++)
    {
        hists[i] = new TH1D(HistName[i],HistName[i], NBINS,massLEdges);
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
        
        cout<< "Running for  ==>  " << s->name() << "\t" << endl;
        if(s->name().EqualTo("data")) {
            //intLUMIinvpb = s->cross();
            cout<< "Lumi = " << intLUMIinvpb << endl;
        }
        
        
        TTree *mytree = s->Tree();
        TH1F *myth1f = s->TInputHist();
        
        
        const float MUON_MASS = 0.1056583745;
        const float ELE_MASS  = 0.000511;
        
        int run=-1, ls=-1,evt=-1, nJet30=-1, nJet50=-1, nBtag_loose=-1, nBtag_medium=-1,nBtag_tight=-1;
        float nPV=-1, nPU_mean=-1, puWeight=1, puWeight_Up=1, puWeight_Dn=1, L1PFWeight=1, genWeight=1;
        float aqgcWeight[1000]={};
        float trig_eff_Weight=1;
        float lep1_pt=-1, lep1_eta=-999, lep1_phi=-1, lep1_m=-1, lep1_q=-1, lep1_iso=-1,lep1_idEffWeight=1, lep1_pt_scaleUp=-1, lep1_pt_scaleDn=-1, lep2_pt=-1, lep2_eta=-999, lep2_phi=-1, lep2_m=-1, lep2_q=-1, lep2_iso=-1,lep2_idEffWeight=1, lep2_pt_scaleUp=-1, lep2_pt_scaleDn=-1;
        float dilep_m=-1, dilep_pt=-1,dilep_eta=-999, dilep_phi=-1, dilep_m_scaleUp=-1, dilep_m_scaleDn=-1, dilep_pt_scaleUp=-1, dilep_pt_scaleDn=-1;
        float MET=-1, MET_phi=-1, MET_2017raw=-1, MET_scaleUp=-1, MET_scaleDn=-1, neu_pz_type0=-999, neu_pz_type0_scaleUp=-999, neu_pz_type0_scaleDn=-999;
        float vbf1_AK4_pt=-1, vbf1_AK4_eta=-999, vbf1_AK4_phi=-1, vbf1_AK4_m=-1, vbf1_AK4_gqid=-1, vbf1_AK4_axis2=-1, vbf1_AK4_ptD =-1, vbf1_AK4_pt_scaleUp=-1, vbf1_AK4_pt_scaleDn=-1, vbf1_AK4_m_scaleUp=-1, vbf1_AK4_m_scaleDn=-1, vbf2_AK4_pt=-1, vbf2_AK4_eta=-999, vbf2_AK4_phi=-1, vbf2_AK4_m=-1, vbf2_AK4_gqid=-1, vbf2_AK4_axis2=-1, vbf2_AK4_ptD =-1, vbf2_AK4_pt_scaleUp=-1, vbf2_AK4_pt_scaleDn=-1, vbf2_AK4_m_scaleUp=-1, vbf2_AK4_m_scaleDn=-1;
        float vbf_pt=-1, vbf_eta=-999, vbf_phi=-1, vbf_m=-1, vbf_pt_scaleUp=-1, vbf_pt_scaleDn=-1, vbf_m_scaleUp=-1, vbf_m_scaleDn=-1;
        float bos_PuppiAK8_m_sd0=-1, bos_PuppiAK8_m_sd0_corr=-1, bos_PuppiAK8_pt=-1, bos_PuppiAK8_eta=-999, bos_PuppiAK8_phi=-1, bos_PuppiAK8_tau2tau1=-999, bos_PuppiAK8_m_sd0_corr_scaleUp=-1, bos_PuppiAK8_m_sd0_corr_scaleDn=-1, bos_PuppiAK8_pt_scaleUp=-1, bos_PuppiAK8_pt_scaleDn=-1, bos_PuppiAK8_e2_sdb1=-999, bos_PuppiAK8_e3_sdb1=-999, bos_PuppiAK8_e3_v1_sdb1=-999, bos_PuppiAK8_e3_v2_sdb1=-999, bos_PuppiAK8_e4_v1_sdb1=-999, bos_PuppiAK8_e4_v2_sdb1=-999, bos_PuppiAK8_e2_sdb2=-999, bos_PuppiAK8_e3_sdb2=-999, bos_PuppiAK8_e3_v1_sdb2=-999, bos_PuppiAK8_e3_v2_sdb2=-999, bos_PuppiAK8_e4_v1_sdb2=-999, bos_PuppiAK8_e4_v2_sdb2=-999;
        float  bos_j1_AK4_pt=-1, bos_j1_AK4_eta=-999, bos_j1_AK4_phi=-1, bos_j1_AK4_m=-1, bos_j1_AK4_pt_scaleUp=-1, bos_j1_AK4_pt_scaleDn=-1, bos_j1_AK4_m_scaleUp=-1, bos_j1_AK4_m_scaleDn=-1, bos_j2_AK4_pt=-1, bos_j2_AK4_eta=-999, bos_j2_AK4_phi=-1, bos_j2_AK4_m=-1, bos_j2_AK4_pt_scaleUp=-1, bos_j2_AK4_pt_scaleDn=-1, bos_j2_AK4_m_scaleUp=-1, bos_j2_AK4_m_scaleDn=-1;
        float bos_AK4AK4_pt=-1, bos_AK4AK4_eta=-999, bos_AK4AK4_phi=-1, bos_AK4AK4_m=-1, bos_AK4AK4_pt_scaleUp=-1, bos_AK4AK4_pt_scaleDn=-1, bos_AK4AK4_m_scaleUp=-1, bos_AK4AK4_m_scaleDn=-1;
        float dibos_m=-1, dibos_pt=-1, dibos_eta=-999, dibos_phi=-1, dibos_m_scaleUp=-1, dibos_m_scaleDn=-1, dibos_pt_scaleUp=-1, dibos_pt_scaleDn=-1, bosCent=-999, zeppLep=-999, zeppHad=-999;
        
        mytree->SetBranchStatus("*",0);
        mytree->SetBranchStatus("run",1);
        mytree->SetBranchAddress("run",&run);
        mytree->SetBranchStatus("evt",1);
        mytree->SetBranchAddress("evt", & evt);
        mytree->SetBranchStatus("nJet30",1);
        mytree->SetBranchAddress("nJet30", & nJet30);
        mytree->SetBranchStatus("nJet50",1);
        mytree->SetBranchAddress("nJet50", & nJet50);
        mytree->SetBranchStatus("nBtag_loose",1);
        mytree->SetBranchAddress("nBtag_loose", & nBtag_loose);
        mytree->SetBranchStatus("nBtag_medium",1);
        mytree->SetBranchAddress("nBtag_medium", & nBtag_medium);
        mytree->SetBranchStatus("nBtag_tight",1);
        mytree->SetBranchAddress("nBtag_tight", & nBtag_tight);
        mytree->SetBranchStatus("nPV",1);
        mytree->SetBranchAddress("nPV", & nPV);
        mytree->SetBranchStatus("nPU_mean",1);
        mytree->SetBranchAddress("nPU_mean", & nPU_mean);
        mytree->SetBranchStatus("puWeight",1);
        mytree->SetBranchAddress("puWeight", & puWeight);
        mytree->SetBranchStatus("puWeight_Up",1);
        mytree->SetBranchAddress("puWeight_Up", & puWeight_Up);
        mytree->SetBranchStatus("puWeight_Dn",1);
        mytree->SetBranchAddress("puWeight_Dn", & puWeight_Dn);
        mytree->SetBranchStatus("genWeight",1);
        mytree->SetBranchAddress("genWeight", & genWeight);
        // mytree->SetBranchStatus(",1);
        // mytree->SetBranchAddress(", &);
        if (s->name().EqualTo("aQGC"))mytree->SetBranchStatus("aqgcWeight",1);
        if (s->name().EqualTo("aQGC"))mytree->SetBranchAddress("aqgcWeight", & aqgcWeight);
        mytree->SetBranchStatus("L1PFWeight",1);
        mytree->SetBranchAddress("L1PFWeight", & L1PFWeight);
        mytree->SetBranchStatus("lep1_pt",1);
        mytree->SetBranchAddress("lep1_pt", & lep1_pt);
        mytree->SetBranchStatus("lep1_eta",1);
        mytree->SetBranchAddress("lep1_eta", & lep1_eta);
        mytree->SetBranchStatus("lep1_phi",1);
        mytree->SetBranchAddress("lep1_phi", & lep1_phi);
        mytree->SetBranchStatus("lep1_m",1);
        mytree->SetBranchAddress("lep1_m", & lep1_m);
        mytree->SetBranchStatus("lep1_q",1);
        mytree->SetBranchAddress("lep1_q", & lep1_q);
        mytree->SetBranchStatus("lep1_iso",1);
        mytree->SetBranchAddress("lep1_iso", & lep1_iso);
        mytree->SetBranchStatus("lep1_idEffWeight",1);
        mytree->SetBranchAddress("lep1_idEffWeight", & lep1_idEffWeight);
        mytree->SetBranchStatus("lep1_pt_scaleUp",1);
        mytree->SetBranchAddress("lep1_pt_scaleUp", & lep1_pt_scaleUp);
        mytree->SetBranchStatus("lep1_pt_scaleDn",1);
        mytree->SetBranchAddress("lep1_pt_scaleDn", & lep1_pt_scaleDn);
        mytree->SetBranchStatus("lep2_pt",1);
        mytree->SetBranchAddress("lep2_pt", & lep2_pt);
        mytree->SetBranchStatus("lep2_eta",1);
        mytree->SetBranchAddress("lep2_eta", & lep2_eta);
        mytree->SetBranchStatus("lep2_phi",1);
        mytree->SetBranchAddress("lep2_phi", & lep2_phi);
        mytree->SetBranchStatus("lep2_m",1);
        mytree->SetBranchAddress("lep2_m", & lep2_m);
        mytree->SetBranchStatus("lep2_q",1);
        mytree->SetBranchAddress("lep2_q", & lep2_q);
        mytree->SetBranchStatus("lep2_iso",1);
        mytree->SetBranchAddress("lep2_iso", & lep2_iso);
        mytree->SetBranchStatus("lep2_idEffWeight",1);
        mytree->SetBranchAddress("lep2_idEffWeight", & lep2_idEffWeight);
        mytree->SetBranchStatus("lep2_pt_scaleUp",1);
        mytree->SetBranchAddress("lep2_pt_scaleUp", & lep2_pt_scaleUp);
        mytree->SetBranchStatus("lep2_pt_scaleDn",1);
        mytree->SetBranchAddress("lep2_pt_scaleDn", & lep2_pt_scaleDn);
        mytree->SetBranchStatus("dilep_m",1);
        mytree->SetBranchAddress("dilep_m", & dilep_m);
        mytree->SetBranchStatus("dilep_pt",1);
        mytree->SetBranchAddress("dilep_pt", & dilep_pt);
        mytree->SetBranchStatus("dilep_eta",1);
        mytree->SetBranchAddress("dilep_eta", & dilep_eta);
        mytree->SetBranchStatus("dilep_phi",1);
        mytree->SetBranchAddress("dilep_phi", & dilep_phi);
        mytree->SetBranchStatus("dilep_m_scaleUp",1);
        mytree->SetBranchAddress("dilep_m_scaleUp", & dilep_m_scaleUp);
        mytree->SetBranchStatus("dilep_m_scaleDn",1);
        mytree->SetBranchAddress("dilep_m_scaleDn", & dilep_m_scaleDn);
        mytree->SetBranchStatus("dilep_pt_scaleUp",1);
        mytree->SetBranchAddress("dilep_pt_scaleUp", & dilep_pt_scaleUp);
        mytree->SetBranchStatus("dilep_pt_scaleDn",1);
        mytree->SetBranchAddress("dilep_pt_scaleDn", & dilep_pt_scaleDn);
        mytree->SetBranchStatus("MET",1);
        mytree->SetBranchAddress("MET", & MET);
        mytree->SetBranchStatus("MET_phi",1);
        mytree->SetBranchAddress("MET_phi", & MET_phi);
        mytree->SetBranchStatus("MET_2017raw",1);
        mytree->SetBranchAddress("MET_2017raw", & MET_2017raw);
        mytree->SetBranchStatus("MET_scaleUp",1);
        mytree->SetBranchAddress("MET_scaleUp", & MET_scaleUp);
        mytree->SetBranchStatus("MET_scaleDn",1);
        mytree->SetBranchAddress("MET_scaleDn", & MET_scaleDn);
        mytree->SetBranchStatus("neu_pz_type0",1);
        mytree->SetBranchAddress("neu_pz_type0", & neu_pz_type0);
        mytree->SetBranchStatus("neu_pz_type0_scaleUp",1);
        mytree->SetBranchAddress("neu_pz_type0_scaleUp", & neu_pz_type0_scaleUp);
        mytree->SetBranchStatus("neu_pz_type0_scaleDn",1);
        mytree->SetBranchAddress("neu_pz_type0_scaleDn", & neu_pz_type0_scaleDn);
        mytree->SetBranchStatus("vbf1_AK4_pt",1);
        mytree->SetBranchAddress("vbf1_AK4_pt", & vbf1_AK4_pt);
        mytree->SetBranchStatus("vbf1_AK4_eta",1);
        mytree->SetBranchAddress("vbf1_AK4_eta", & vbf1_AK4_eta);
        mytree->SetBranchStatus("vbf1_AK4_phi",1);
        mytree->SetBranchAddress("vbf1_AK4_phi", & vbf1_AK4_phi);
        mytree->SetBranchStatus("vbf1_AK4_m",1);
        mytree->SetBranchAddress("vbf1_AK4_m", & vbf1_AK4_m);
        mytree->SetBranchStatus("vbf1_AK4_gqid",1);
        mytree->SetBranchAddress("vbf1_AK4_gqid", & vbf1_AK4_gqid);
        mytree->SetBranchStatus("vbf1_AK4_axis2",1);
        mytree->SetBranchAddress("vbf1_AK4_axis2", & vbf1_AK4_axis2);
        mytree->SetBranchStatus("vbf1_AK4_ptD",1);
        mytree->SetBranchAddress("vbf1_AK4_ptD", & vbf1_AK4_ptD);
        mytree->SetBranchStatus("vbf1_AK4_pt_scaleUp",1);
        mytree->SetBranchAddress("vbf1_AK4_pt_scaleUp", & vbf1_AK4_pt_scaleUp);
        mytree->SetBranchStatus("vbf1_AK4_pt_scaleDn",1);
        mytree->SetBranchAddress("vbf1_AK4_pt_scaleDn", & vbf1_AK4_pt_scaleDn);
        mytree->SetBranchStatus("vbf1_AK4_m_scaleUp",1);
        mytree->SetBranchAddress("vbf1_AK4_m_scaleUp", & vbf1_AK4_m_scaleUp);
        mytree->SetBranchStatus("vbf1_AK4_m_scaleDn",1);
        mytree->SetBranchAddress("vbf1_AK4_m_scaleDn", & vbf1_AK4_m_scaleDn);
        mytree->SetBranchStatus("vbf2_AK4_pt",1);
        mytree->SetBranchAddress("vbf2_AK4_pt", & vbf2_AK4_pt);
        mytree->SetBranchStatus("vbf2_AK4_eta",1);
        mytree->SetBranchAddress("vbf2_AK4_eta", & vbf2_AK4_eta);
        mytree->SetBranchStatus("vbf2_AK4_phi",1);
        mytree->SetBranchAddress("vbf2_AK4_phi", & vbf2_AK4_phi);
        mytree->SetBranchStatus("vbf2_AK4_m",1);
        mytree->SetBranchAddress("vbf2_AK4_m", & vbf2_AK4_m);
        mytree->SetBranchStatus("vbf2_AK4_gqid",1);
        mytree->SetBranchAddress("vbf2_AK4_gqid", & vbf2_AK4_gqid);
        mytree->SetBranchStatus("vbf2_AK4_axis2",1);
        mytree->SetBranchAddress("vbf2_AK4_axis2", & vbf2_AK4_axis2);
        mytree->SetBranchStatus("vbf2_AK4_ptD",1);
        mytree->SetBranchAddress("vbf2_AK4_ptD", & vbf2_AK4_ptD);
        mytree->SetBranchStatus("vbf2_AK4_pt_scaleUp",1);
        mytree->SetBranchAddress("vbf2_AK4_pt_scaleUp", & vbf2_AK4_pt_scaleUp);
        mytree->SetBranchStatus("vbf2_AK4_pt_scaleDn",1);
        mytree->SetBranchAddress("vbf2_AK4_pt_scaleDn", & vbf2_AK4_pt_scaleDn);
        mytree->SetBranchStatus("vbf2_AK4_m_scaleUp",1);
        mytree->SetBranchAddress("vbf2_AK4_m_scaleUp", & vbf2_AK4_m_scaleUp);
        mytree->SetBranchStatus("vbf2_AK4_m_scaleDn",1);
        mytree->SetBranchAddress("vbf2_AK4_m_scaleDn", & vbf2_AK4_m_scaleDn);
        mytree->SetBranchStatus("vbf_pt",1);
        mytree->SetBranchAddress("vbf_pt", & vbf_pt);
        mytree->SetBranchStatus("vbf_eta",1);
        mytree->SetBranchAddress("vbf_eta", & vbf_eta);
        mytree->SetBranchStatus("vbf_phi",1);
        mytree->SetBranchAddress("vbf_phi", & vbf_phi);
        mytree->SetBranchStatus("vbf_m",1);
        mytree->SetBranchAddress("vbf_m", & vbf_m);
        mytree->SetBranchStatus("vbf_pt_scaleUp",1);
        mytree->SetBranchAddress("vbf_pt_scaleUp", & vbf_pt_scaleUp);
        mytree->SetBranchStatus("vbf_pt_scaleDn",1);
        mytree->SetBranchAddress("vbf_pt_scaleDn", & vbf_pt_scaleDn);
        mytree->SetBranchStatus("vbf_m_scaleUp",1);
        mytree->SetBranchAddress("vbf_m_scaleUp", & vbf_m_scaleUp);
        mytree->SetBranchStatus("vbf_m_scaleDn",1);
        mytree->SetBranchAddress("vbf_m_scaleDn", & vbf_m_scaleDn);
        mytree->SetBranchStatus("bos_PuppiAK8_m_sd0",1);
        mytree->SetBranchAddress("bos_PuppiAK8_m_sd0", & bos_PuppiAK8_m_sd0);
        mytree->SetBranchStatus("bos_PuppiAK8_m_sd0_corr",1);
        mytree->SetBranchAddress("bos_PuppiAK8_m_sd0_corr", & bos_PuppiAK8_m_sd0_corr);
        mytree->SetBranchStatus("bos_PuppiAK8_pt",1);
        mytree->SetBranchAddress("bos_PuppiAK8_pt", & bos_PuppiAK8_pt);
        mytree->SetBranchStatus("bos_PuppiAK8_eta",1);
        mytree->SetBranchAddress("bos_PuppiAK8_eta", & bos_PuppiAK8_eta);
        mytree->SetBranchStatus("bos_PuppiAK8_phi",1);
        mytree->SetBranchAddress("bos_PuppiAK8_phi", & bos_PuppiAK8_phi);
        mytree->SetBranchStatus("bos_PuppiAK8_tau2tau1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_tau2tau1", & bos_PuppiAK8_tau2tau1);
        mytree->SetBranchStatus("bos_PuppiAK8_m_sd0_corr_scaleUp",1);
        mytree->SetBranchAddress("bos_PuppiAK8_m_sd0_corr_scaleUp", & bos_PuppiAK8_m_sd0_corr_scaleUp);
        mytree->SetBranchStatus("bos_PuppiAK8_m_sd0_corr_scaleDn",1);
        mytree->SetBranchAddress("bos_PuppiAK8_m_sd0_corr_scaleDn", & bos_PuppiAK8_m_sd0_corr_scaleDn);
        mytree->SetBranchStatus("bos_PuppiAK8_pt_scaleUp",1);
        mytree->SetBranchAddress("bos_PuppiAK8_pt_scaleUp", & bos_PuppiAK8_pt_scaleUp);
        mytree->SetBranchStatus("bos_PuppiAK8_pt_scaleDn",1);
        mytree->SetBranchAddress("bos_PuppiAK8_pt_scaleDn", & bos_PuppiAK8_pt_scaleDn);
        mytree->SetBranchStatus("bos_PuppiAK8_e2_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e2_sdb1", & bos_PuppiAK8_e2_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_sdb1", & bos_PuppiAK8_e3_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_v1_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_v1_sdb1", & bos_PuppiAK8_e3_v1_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_v2_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_v2_sdb1", & bos_PuppiAK8_e3_v2_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e4_v1_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e4_v1_sdb1", & bos_PuppiAK8_e4_v1_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e4_v2_sdb1",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e4_v2_sdb1", & bos_PuppiAK8_e4_v2_sdb1);
        mytree->SetBranchStatus("bos_PuppiAK8_e2_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e2_sdb2", & bos_PuppiAK8_e2_sdb2);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_sdb2", & bos_PuppiAK8_e3_sdb2);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_v1_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_v1_sdb2", & bos_PuppiAK8_e3_v1_sdb2);
        mytree->SetBranchStatus("bos_PuppiAK8_e3_v2_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e3_v2_sdb2", & bos_PuppiAK8_e3_v2_sdb2);
        mytree->SetBranchStatus("bos_PuppiAK8_e4_v1_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e4_v1_sdb2", & bos_PuppiAK8_e4_v1_sdb2);
        mytree->SetBranchStatus("bos_PuppiAK8_e4_v2_sdb2",1);
        mytree->SetBranchAddress("bos_PuppiAK8_e4_v2_sdb2", & bos_PuppiAK8_e4_v2_sdb2);
        mytree->SetBranchStatus("bos_j1_AK4_pt",1);
        mytree->SetBranchAddress("bos_j1_AK4_pt", & bos_j1_AK4_pt);
        mytree->SetBranchStatus("bos_j1_AK4_eta",1);
        mytree->SetBranchAddress("bos_j1_AK4_eta", & bos_j1_AK4_eta);
        mytree->SetBranchStatus("bos_j1_AK4_phi",1);
        mytree->SetBranchAddress("bos_j1_AK4_phi", & bos_j1_AK4_phi);
        mytree->SetBranchStatus("bos_j1_AK4_m",1);
        mytree->SetBranchAddress("bos_j1_AK4_m", & bos_j1_AK4_m);
        mytree->SetBranchStatus("bos_j1_AK4_pt_scaleUp",1);
        mytree->SetBranchAddress("bos_j1_AK4_pt_scaleUp", & bos_j1_AK4_pt_scaleUp);
        mytree->SetBranchStatus("bos_j1_AK4_pt_scaleDn",1);
        mytree->SetBranchAddress("bos_j1_AK4_pt_scaleDn", & bos_j1_AK4_pt_scaleDn);
        mytree->SetBranchStatus("bos_j1_AK4_m_scaleUp",1);
        mytree->SetBranchAddress("bos_j1_AK4_m_scaleUp", & bos_j1_AK4_m_scaleUp);
        mytree->SetBranchStatus("bos_j1_AK4_m_scaleDn",1);
        mytree->SetBranchAddress("bos_j1_AK4_m_scaleDn", & bos_j1_AK4_m_scaleDn);
        mytree->SetBranchStatus("bos_j2_AK4_pt",1);
        mytree->SetBranchAddress("bos_j2_AK4_pt", & bos_j2_AK4_pt);
        mytree->SetBranchStatus("bos_j2_AK4_eta",1);
        mytree->SetBranchAddress("bos_j2_AK4_eta", & bos_j2_AK4_eta);
        mytree->SetBranchStatus("bos_j2_AK4_phi",1);
        mytree->SetBranchAddress("bos_j2_AK4_phi", & bos_j2_AK4_phi);
        mytree->SetBranchStatus("bos_j2_AK4_m",1);
        mytree->SetBranchAddress("bos_j2_AK4_m", & bos_j2_AK4_m);
        mytree->SetBranchStatus("bos_j2_AK4_pt_scaleUp",1);
        mytree->SetBranchAddress("bos_j2_AK4_pt_scaleUp", & bos_j2_AK4_pt_scaleUp);
        mytree->SetBranchStatus("bos_j2_AK4_pt_scaleDn",1);
        mytree->SetBranchAddress("bos_j2_AK4_pt_scaleDn", & bos_j2_AK4_pt_scaleDn);
        mytree->SetBranchStatus("bos_j2_AK4_m_scaleUp",1);
        mytree->SetBranchAddress("bos_j2_AK4_m_scaleUp", & bos_j2_AK4_m_scaleUp);
        mytree->SetBranchStatus("bos_j2_AK4_m_scaleDn",1);
        mytree->SetBranchAddress("bos_j2_AK4_m_scaleDn", & bos_j2_AK4_m_scaleDn);
        mytree->SetBranchStatus("bos_AK4AK4_pt",1);
        mytree->SetBranchAddress("bos_AK4AK4_pt", & bos_AK4AK4_pt);
        mytree->SetBranchStatus("bos_AK4AK4_eta",1);
        mytree->SetBranchAddress("bos_AK4AK4_eta", & bos_AK4AK4_eta);
        mytree->SetBranchStatus("bos_AK4AK4_phi",1);
        mytree->SetBranchAddress("bos_AK4AK4_phi", & bos_AK4AK4_phi);
        mytree->SetBranchStatus("bos_AK4AK4_m",1);
        mytree->SetBranchAddress("bos_AK4AK4_m", & bos_AK4AK4_m);
        mytree->SetBranchStatus("bos_AK4AK4_pt_scaleUp",1);
        mytree->SetBranchAddress("bos_AK4AK4_pt_scaleUp", & bos_AK4AK4_pt_scaleUp);
        mytree->SetBranchStatus("bos_AK4AK4_pt_scaleDn",1);
        mytree->SetBranchAddress("bos_AK4AK4_pt_scaleDn", & bos_AK4AK4_pt_scaleDn);
        mytree->SetBranchStatus("bos_AK4AK4_m_scaleUp",1);
        mytree->SetBranchAddress("bos_AK4AK4_m_scaleUp", & bos_AK4AK4_m_scaleUp);
        mytree->SetBranchStatus("bos_AK4AK4_m_scaleDn",1);
        mytree->SetBranchAddress("bos_AK4AK4_m_scaleDn", & bos_AK4AK4_m_scaleDn);
        mytree->SetBranchStatus("dibos_m",1);
        mytree->SetBranchAddress("dibos_m", & dibos_m);
        mytree->SetBranchStatus("dibos_pt",1);
        mytree->SetBranchAddress("dibos_pt", & dibos_pt);
        mytree->SetBranchStatus("dibos_eta",1);
        mytree->SetBranchAddress("dibos_eta", & dibos_eta);
        mytree->SetBranchStatus("dibos_phi",1);
        mytree->SetBranchAddress("dibos_phi", & dibos_phi);
        mytree->SetBranchStatus("dibos_m_scaleUp",1);
        mytree->SetBranchAddress("dibos_m_scaleUp", & dibos_m_scaleUp);
        mytree->SetBranchStatus("dibos_m_scaleDn",1);
        mytree->SetBranchAddress("dibos_m_scaleDn", & dibos_m_scaleDn);
        mytree->SetBranchStatus("dibos_pt_scaleUp",1);
        mytree->SetBranchAddress("dibos_pt_scaleUp", & dibos_pt_scaleUp);
        mytree->SetBranchStatus("dibos_pt_scaleDn",1);
        mytree->SetBranchAddress("dibos_pt_scaleDn", & dibos_pt_scaleDn);
        mytree->SetBranchStatus("bosCent",1);
        mytree->SetBranchAddress("bosCent", & bosCent);
        mytree->SetBranchStatus("zeppLep",1);
        mytree->SetBranchAddress("zeppLep", & zeppLep);
        mytree->SetBranchStatus("zeppHad",1);
        mytree->SetBranchAddress("zeppHad", & zeppHad);
        
        ///************************************************/////*
        int nEvents=-1, nNegEvents=-1, type=-1, nBTagJet_loose=-1;
        //*************************************************//
        float nTotal=0, nNeg=0;
        if (!(isamp==0)){
            nTotal = myth1f->GetBinContent(2);
            nNeg = myth1f->GetBinContent(1);
        }
        cout<<nTotal<<"   "<<nNeg<<endl;
        
        // cout<< " Reading sample : " << isamp << "   " << s->name() << endl;
        for(int i = 0; i<mytree->GetEntries(); i++)
        {
            mytree->GetEntry(i);
            
            bool isEle=false, isResolved=false, isZ=false;
            
            if (bos_PuppiAK8_m_sd0_corr > 0 && bos_AK4AK4_m < 0) { isResolved=false; }
            else if (bos_PuppiAK8_m_sd0_corr < 0 && bos_AK4AK4_m > 0) { isResolved=true; }
            else {
                cout << "both or neither of resolved and boosted mass is defined" << endl;
                continue;
            }
            if (lep1_m == ELE_MASS){isEle=true;}
            else if (lep1_m == MUON_MASS){isEle=false;}
            else {
                cout << "lepton is not electron or muon! skipping" << endl;
                continue;
            }
            
            if (1)	//----------------	Nominal, PU up, PU down
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    if(s->name().EqualTo("data"))	 hists[0]->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[1]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[14]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[27]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[40]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    
                    //------	PU UP
                    if(s->name().EqualTo("WV_EWK"))	 hists[8]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[21]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[34]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[47]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    //------	PU Down
                    if(s->name().EqualTo("WV_EWK"))	 hists[9]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[22]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[35]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[48]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    //------	btag HF Up
                    if(s->name().EqualTo("WV_EWK"))	 hists[10]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[23]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[36]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[49]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    //------	btag HF Down
                    if(s->name().EqualTo("WV_EWK"))	 hists[11]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[24]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[37]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[50]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    //------	btag LF Up
                    if(s->name().EqualTo("WV_EWK"))	 hists[12]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[25]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[38]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[51]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    //------	btag LF Down
                    if(s->name().EqualTo("WV_EWK"))	 hists[13]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Diboson")) 	 hists[26]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("top"))  	 hists[39]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    if(s->name().EqualTo("Vjets"))	 hists[52]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    
                    
                    // To get QCD scale bounding we need to add QCD scale for all signal and bkg. But except for WV_EWK and Diboson others are taken care of using background estimation. For top there is not QCD scale bounding present in MC.
                    //     if(s->name().EqualTo("WV_EWK")||s->name().EqualTo("Diboson"))
                    // 	{
                    //  if(s->name().EqualTo("WV_EWK"))
                    //    {
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[0]->Fill(dibos_m,((LHEWeight[1]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[1]->Fill(dibos_m,((LHEWeight[2]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[2]->Fill(dibos_m,((LHEWeight[3]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[3]->Fill(dibos_m,((LHEWeight[4]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[4]->Fill(dibos_m,((LHEWeight[6]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_diboson_EWK_CMS_QCDScaleBounding[5]->Fill(dibos_m,((LHEWeight[8]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    for(int npdf=0; npdf<100; npdf++) histo_diboson_EWK_CMS_PDFScaleBounding[npdf]->Fill(dibos_m,((LHEWeight[9+npdf]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    }
                    //  if(s->name().EqualTo("Diboson"))
                    //    {
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[0]->Fill(dibos_m,((LHEWeight[1]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[1]->Fill(dibos_m,((LHEWeight[2]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[2]->Fill(dibos_m,((LHEWeight[3]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[3]->Fill(dibos_m,((LHEWeight[4]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[4]->Fill(dibos_m,((LHEWeight[6]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    histo_VVjjQCD_EWK_CMS_QCDScaleBounding[5]->Fill(dibos_m,((LHEWeight[8]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    for(int npdf=0; npdf<100; npdf++) histo_VVjjQCD_EWK_CMS_PDFScaleBounding[npdf]->Fill(dibos_m,((LHEWeight[9+npdf]/LHEWeight[0])*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                    //    }
                    // }
                    
                    if(s->name().EqualTo("aQGC"))
                    {
                        for (int j=0;j<SizeOf_aQGC;j++)
                        {
                            histo_aqgc[j]->Fill(dibos_m,(((aqgcWeight[j]))*xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nmc-2*nneg)));
                            // std::cout << j <<  "\taQGC weight : " << aqgcWeight[j] << std::endl;
                        }
                        // std::cout << "=========RAM============" << std::endl;
                    }
                }
            }
            
            if (1)	//--------------------------- LEP up
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    //if(s->name().EqualTo("data"))	 histo_data_LEPUp->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[2]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))   hists[15]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[28]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[41]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
            
            if (1)	//--------------------------- LEP down
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[3]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))   hists[16]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[29]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[42]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
            
            if (1)	//-------------------	JES up
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[4] ->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))  	 hists[17]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[30]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[43]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
            
            if (1)	//-------------------	JES down
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[5]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))  	 hists[18]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[31]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[44]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
            
            if (1)	//-------------------	JER up
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    
                    //if(s->name().EqualTo("data"))	 histo_data_LEPDown->Fill(dibos_m);
                    if(s->name().EqualTo("WV_EWK"))	 hists[6]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))  	 hists[19]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[32]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[45]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
            
            if (1)	//-------------------	JER down
            {
                if ( !(
                       (fabs(vbf1_AK4_eta)>2.65 && fabs(vbf1_AK4_eta)<3.139) &&
                       (fabs(vbf2_AK4_eta)>2.65 && fabs(vbf2_AK4_eta)<3.139) &&
                       (vbf_m < 500) &&
                       (fabs(vbf1_AK4_eta - vbf2_AK4_eta)<2.5) &&
                       (nBtag_loose==0 && vbf1_AK4_pt>50 && vbf2_AK4_pt>50) &&
                       (isResolved==true && (bos_AK4AK4_m>65 &&bos_AK4AK4_m<105)) &&
                       (isResolved==false && (bos_PuppiAK8_m_sd0_corr>65 &&bos_PuppiAK8_m_sd0_corr<105)) &&
                       (lep2_pt>0) &&
                       (isEle==true && (lep1_pt<35 || abs(lep1_eta)>2.5 || (abs(lep1_eta)>1.4442 && abs(lep1_eta)<1.566))) &&
                       (isEle==false && (lep1_pt<35 || abs(lep1_eta)>2.4)) &&
                       (isZ==true && (dilep_m < 81 || dilep_m > 101)) &&
                       
                       (isZ==true && isEle==true && (lep2_pt<20 || abs(lep2_eta)>2.5 || (abs(lep2_eta)>1.4442 && abs(lep2_eta)<1.566))) &&
                       (isZ==true && isEle==false && (lep2_pt<20 || abs(lep2_eta)>2.4)) &&
                       (isZ==true && (lep1_q*lep2_q)==1) &&
                       (isZ==false && MET<30)
                       ))
                {
                    
                    if(s->name().EqualTo("WV_EWK"))	 hists[7]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Diboson"))  	 hists[20]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("top"))  	 hists[33]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                    if(s->name().EqualTo("Vjets"))	 hists[46]->Fill(dibos_m,(xsec*otherscale*genWeight*trig_eff_Weight*lep1_idEffWeight*puWeight)/(1.0*(nTotal-2*nNeg)));
                }
            }
        }
        //cout<<"\n\n ====>  " << hists[27]->Integral() << endl;
    }
    
    
    // include overflow bin in last bin for all histograms
    for (int i=0; i<SizeOf_HistName; i++)
    {
        hists[i]->SetBinContent(NBINS,hists[i]->GetBinContent(NBINS)+hists[i]->GetBinContent(NBINS+1));
        cout << HistName[i] << " = " << hists[i]->Integral() << endl;
        //hists[i]->Write();
    }
    
    for (int i=0; i<6; i++)
    {
        histo_diboson_EWK_CMS_QCDScaleBounding[i]->SetBinContent(NBINS,histo_diboson_EWK_CMS_QCDScaleBounding[i]->GetBinContent(NBINS)+histo_diboson_EWK_CMS_QCDScaleBounding[i]->GetBinContent(NBINS+1));
        histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->SetBinContent(NBINS,histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->GetBinContent(NBINS)+histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->GetBinContent(NBINS+1));
    }
    for (int i=0; i<99; i++)
    {
        histo_diboson_EWK_CMS_PDFScaleBounding[i]->SetBinContent(NBINS,histo_diboson_EWK_CMS_PDFScaleBounding[i]->GetBinContent(NBINS)+histo_diboson_EWK_CMS_PDFScaleBounding[i]->GetBinContent(NBINS+1));
        histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->SetBinContent(NBINS,histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->GetBinContent(NBINS)+histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->GetBinContent(NBINS+1));
    }
    for (int j=0;j<SizeOf_aQGC;j++){
        histo_aqgc[j]->SetBinContent(NBINS,histo_aqgc[j]->GetBinContent(NBINS)+histo_aqgc[j]->GetBinContent(NBINS+1));
        //std::cout << "aqgc integral " << histo_aqgc[j]->Integral() << std::endl;
    }
    
    //ok now we calculate the uncertainty
    std::cout << "EWK Scale uncertainties" << std::endl;
    for(int bin=1; bin<NBINS+1; bin++)
    {
        double systQCDScale=0;
        for (int i = 0; i<6; i++)
        {
            if(TMath::Abs(histo_diboson_EWK_CMS_QCDScaleBounding[i]->GetBinContent(bin)-hists[1]->GetBinContent(bin)) > systQCDScale) systQCDScale = TMath::Abs(histo_diboson_EWK_CMS_QCDScaleBounding[i]->GetBinContent(bin)-hists[1]->GetBinContent(bin));
        }
        std::cout << "bin number " << bin << " " << 1 + systQCDScale/hists[1]->GetBinContent(bin) << std::endl;
        histo_diboson_EWK_CMS_QCDScaleBounding_Up  ->SetBinContent(bin,hists[1]->GetBinContent(bin) + systQCDScale);
        histo_diboson_EWK_CMS_QCDScaleBounding_Down->SetBinContent(bin,hists[1]->GetBinContent(bin) - systQCDScale);
        systQCDScale=0;
        for (int i = 0; i<6; i++)
        {
            if(TMath::Abs(histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->GetBinContent(bin)-hists[14]->GetBinContent(bin)) > systQCDScale) systQCDScale = TMath::Abs(histo_VVjjQCD_EWK_CMS_QCDScaleBounding[i]->GetBinContent(bin)-hists[14]->GetBinContent(bin));
        }
        histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Up  ->SetBinContent(bin,hists[14]->GetBinContent(bin) + systQCDScale);
        histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Down->SetBinContent(bin,hists[14]->GetBinContent(bin) - systQCDScale);
        std::cout << "bin number " << bin << " " << 1 + systQCDScale/hists[14]->GetBinContent(bin) << std::endl;
        // HistCount = 0;
        int CountCHhist=0;
    }
    
    std::cout << "EWK PDF uncertainties" << std::endl;
    for(int bin=1; bin<NBINS+1; bin++)
    {
        double systPDFScale_1=0, systPDFScale_2=0;
        for (int i = 0; i<99; i++)
        {
            systPDFScale_1 = systPDFScale_1 + (histo_diboson_EWK_CMS_PDFScaleBounding[i]->GetBinContent(bin)-hists[1]->GetBinContent(bin))*(histo_diboson_EWK_CMS_PDFScaleBounding[i]->GetBinContent(bin)-hists[1]->GetBinContent(bin));
            systPDFScale_2 = systPDFScale_2 + (histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->GetBinContent(bin)-hists[14]->GetBinContent(bin))*(histo_VVjjQCD_EWK_CMS_PDFScaleBounding[i]->GetBinContent(bin)-hists[14]->GetBinContent(bin));
        }
        systPDFScale_1 = sqrt(systPDFScale_1/99.);
        systPDFScale_2 = sqrt(systPDFScale_2/99.);
        std::cout << "bin number " << bin << " " << 1 + systPDFScale_1/hists[1]->GetBinContent(bin)  << std::endl;
        std::cout << "bin number " << bin << " " << 1 + systPDFScale_2/hists[14]->GetBinContent(bin)  << std::endl;
        histo_diboson_EWK_CMS_PDFScaleBounding_Up->SetBinContent(bin, hists[1]->GetBinContent(bin) +  systPDFScale_1);
        histo_diboson_EWK_CMS_PDFScaleBounding_Down->SetBinContent(bin, hists[1]->GetBinContent(bin) - systPDFScale_1);
        histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Up->SetBinContent(bin, hists[14]->GetBinContent(bin) + systPDFScale_2);
        histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Down->SetBinContent(bin, hists[14]->GetBinContent(bin) - systPDFScale_2);
        int CountCHhist=0;
    }
    
    
    
    //map<TString, TH1 *>::iterator mit = m_histos.find("ZV(EWK)");
    TH1 *h = 0;//mit->second;
    std::cout << "Did we ever get here? " << std::endl;
    TFile *outFile = new TFile("ch1_splitted_TF1_hfs0.root","RECREATE");
    TFile *outFile1 = new TFile("ch1_splitted_TF1_hfs1.root","RECREATE");
    TFile *outFile2 = new TFile("ch1_splitted_TF1_hfm0.root","RECREATE");
    TFile *outFile3 = new TFile("ch1_splitted_TF1_hfm1.root","RECREATE");
    TFile *outFile4 = new TFile("ch1_splitted_TF1_hfm6.root","RECREATE");
    TFile *outFile5 = new TFile("ch1_splitted_TF1_hfm7.root","RECREATE");
    TFile *outFile6 = new TFile("ch1_splitted_TF1_hft0.root","RECREATE");
    TFile *outFile7 = new TFile("ch1_splitted_TF1_hft1.root","RECREATE");
    TFile *outFile8 = new TFile("ch1_splitted_TF1_hft2.root","RECREATE");
    
    // In this for loop the used histogram `hists[1]` contains information for WV_EWK
    for(int i = 1; i<hists[1]->GetNbinsX()+1; i++)
    {
        stringstream ss;
        ss << i;
        std::string hist_name_temp = "bin_content_par1_"+ss.str();
        const char* hist_name = hist_name_temp.c_str();
        TH1D  *hfs0  = new TH1D(hist_name, hist_name, sizeof(fs0)/sizeof(fs0[0])-1 ,fs0[0], fs0[sizeof(fs0)/sizeof(fs0[0])-1] );
        TH1D  *hfs1  = new TH1D(hist_name, hist_name, sizeof(fs1)/sizeof(fs1[0])-1 ,fs1[0], fs1[sizeof(fs1)/sizeof(fs1[0])-1] );
        TH1D  *hfm0  = new TH1D(hist_name, hist_name, sizeof(fm0)/sizeof(fm0[0])-1 ,fm0[0], fm0[sizeof(fm0)/sizeof(fm0[0])-1] );
        TH1D  *hfm1  = new TH1D(hist_name, hist_name, sizeof(fm1)/sizeof(fm1[0])-1 ,fm1[0], fm1[sizeof(fm1)/sizeof(fm1[0])-1] );
        TH1D  *hfm6  = new TH1D(hist_name, hist_name, sizeof(fm6)/sizeof(fm6[0])-1 ,fm6[0], fm6[sizeof(fm6)/sizeof(fm6[0])-1] );
        TH1D  *hfm7  = new TH1D(hist_name, hist_name, sizeof(fm7)/sizeof(fm7[0])-1 ,fm7[0], fm7[sizeof(fm7)/sizeof(fm7[0])-1] );
        TH1D  *hft0  = new TH1D(hist_name, hist_name, sizeof(ft0)/sizeof(ft0[0])-1 ,ft0[0], ft0[sizeof(ft0)/sizeof(ft0[0])-1] );
        TH1D  *hft1  = new TH1D(hist_name, hist_name, sizeof(ft1)/sizeof(ft1[0])-1 ,ft1[0], ft1[sizeof(ft1)/sizeof(ft1[0])-1] );
        TH1D  *hft2  = new TH1D(hist_name, hist_name, sizeof(ft2)/sizeof(ft2[0])-1 ,ft2[0], ft2[sizeof(ft2)/sizeof(ft2[0])-1] );
        
        // Added this just to grab the appropriate position aQGC points to fill the aQGC histo par
        int temp_numbers[] = {0, -1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10, -11, 11, -12, 12, -13, 13, -14, 14, -15, 15, -16, 16, -17, 17, -18, 18, -19, 19, -20, 20, -21, 21, -22, 22, -23, 23, -24, 24, -25, 25, -26, 26, -27, 27, -28, 28, -28, 29, -30, 30};

        for(int j = 0; j<(SizeOf_aQGC); j++)
        {
            if(j<(sizeof(ft1)/sizeof(ft1[0])))
            {   
                int temp_size = sizeof(ft1)/sizeof(ft1[0]);

                double w = histo_aqgc[j]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j]->GetBinError(i)/histo_aqgc[j]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));

                hft1->SetBinContent( temp_size/2 + 1 + temp_numbers[j], histo_aqgc[j]->GetBinContent(i)/hists[1]->GetBinContent(i));
                hft1->SetBinError(temp_size/2 + 1 + temp_numbers[j], err);

                if (DEBUG) std::cout << "ft1 \t " << histo_aqgc[j]->GetBinContent(i) << " " << hists[1]->GetBinContent(i) << " " << histo_aqgc[j]->GetBinError(i) << " " <<  hists[1]->GetBinError(i) << " " << err << "\t" << hft1->GetBinContent(j+1) << std::endl;
            }
            else if(j>=sizeof(ft1)/sizeof(ft1[0]) && j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0])))
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hft0->SetBinContent(j-537+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                //std::cout << "fs1 \t " << histo_aqgc[j-0]->GetBinContent(i) << " " << hists[1]->GetBinContent(i) << " " << histo_aqgc[j-0]->GetBinError(i) << " " <<  hists[1]->GetBinError(i) << " " << err << "\t" << hft0->GetBinContent(j-537+1) << std::endl;
                hft0->SetBinError(j-537+1,err);
            }
            else if(j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0])) && 
                    j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0])) )
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hft2->SetBinContent(j-604+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hft2->SetBinError(j-604+1,err);
                //hft2->SetBinContent(j+1-604,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]))  && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0])  )
                ) 
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfm1->SetBinContent(j-689+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfm1->SetBinError(j-689+1,err);
                //hfm1->SetBinContent(j+1-689,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0])  ) && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0])  ) 
                ) 
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfm6->SetBinContent(j-756+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfm6->SetBinError(j-756+1,err);
                //hfm6->SetBinContent(j+1-756,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0])  ) && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0])  ) 
                )                 
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfm7->SetBinContent(j-840+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfm7->SetBinError(j-840+1,err);
                //hfm7->SetBinContent(j+1-840,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0])  ) && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0]) + sizeof(fm6)/sizeof(fm6[0])  ) 
                )                 
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfs0->SetBinContent(j-961+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfs0->SetBinError(j-961+1,err);
                //hfs0->SetBinContent(j+1-961,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0]) + sizeof(fm6)/sizeof(fm6[0])  ) && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0]) + sizeof(fm6)/sizeof(fm6[0]) + sizeof(fm7)/sizeof(fm7[0])  ) 
                )                  
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfs1->SetBinContent(j-1030+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfs1->SetBinError(j-1030+1,err);
                //hfs1->SetBinContent(j+1-1030,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
            else if( 
                j>=(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0]) + sizeof(fm6)/sizeof(fm6[0])+ sizeof(fm7)/sizeof(fm7[0])  ) && 
                j<(sizeof(ft1)/sizeof(ft1[0]) + sizeof(ft0)/sizeof(ft0[0]) + sizeof(ft2)/sizeof(ft2[0]) + sizeof(ft5)/sizeof(ft5[0]) + sizeof(ft7)/sizeof(ft7[0]) + sizeof(ft6)/sizeof(ft6[0]) + sizeof(fm6)/sizeof(fm6[0]) + sizeof(fm7)/sizeof(fm7[0]) + sizeof(fm4)/sizeof(fm4[0])  ) 
                )                  
            {
                double w = histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i);
                double e1 = histo_aqgc[j-0]->GetBinError(i)/histo_aqgc[j-0]->GetBinContent(i);
                double e2 = hists[1]->GetBinError(i)/hists[1]->GetBinContent(i);
                hfm0->SetBinContent(j-1081+1,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
                double err = sqrt(e1*e1+e2*e2)*w;//TMath::Abs(((1-2*w)*e1*e1 + w*w*e2*e2 )/(hists[1]->GetBinContent(i)*hists[1]->GetBinContent(i)));
                hfm0->SetBinError(j-1081+1,err);
                //hfm0->SetBinContent(j+1-1081,histo_aqgc[j-0]->GetBinContent(i)/hists[1]->GetBinContent(i));
            }
        }
        outFile->cd();
        TF1 *fit_1 = new TF1(hist_name,"pol2",fs0[0]-10,fs0[sizeof(fs0)/sizeof(fs0[0])-1]-10);
        //hfs0->Fit(hist_name,"R");
        //fit_1->Write();
        hfs0->Write();
        outFile1->cd();
        TF1 *fit_2 = new TF1(hist_name,"pol2",fs1[0]-5,fs1[sizeof(fs1)/sizeof(fs1[0])-1]-5);
        //hfs1->Fit(hist_name,"R");
        hfs1->Write();
        //fit_2->Write();
        outFile2->cd();
        //hfs0->Write();
        TF1 *fit_3 = new TF1(hist_name,"pol2",fm0[0]-0.5,fm0[sizeof(fm0)/sizeof(fm0[0])-1]-0.5);
        //hfm0->Fit(hist_name,"R");
        //fit_3->Write();
        hfm0->Write();
        outFile3->cd();
        TF1 *fit_4 = new TF1(hist_name,"pol2",fm1[0]-2.5,fm1[sizeof(fm1)/sizeof(fm1[0])-1]-2.5);
        //hfm1->Fit(hist_name,"R");
        //fit_4->Write();
        hfm1->Write();
        outFile4->cd();
        TF1 *fit_5 = new TF1(hist_name,"pol2",fm6[0]-1.0,fm6[sizeof(fm6)/sizeof(fm6[0])-1]-1.0);
        //hfm6->Fit(hist_name,"R");
        //fit_5->Write();
        hfm6->Write();
        outFile5->cd();
        TF1 *fit_6 = new TF1(hist_name,"pol2",fm7[0]-2.5,fm7[sizeof(fm7)/sizeof(fm7[0])-1]-2.5);
        //hfm7->Fit(hist_name,"R");
        //fit_6->Write();
        hfm7->Write();
        outFile6->cd();
        hft0->Write();
        TF1 *fit_7 = new TF1(hist_name,"pol2",ft0[0]-0.1,ft0[sizeof(ft0)/sizeof(ft0[0])-1]-0.1);
        //hft0->Fit(hist_name,"R");
        //fit_7->Write();
        outFile7->cd();
        // hft1->Write();
        TF1 *fit_8 = new TF1(hist_name,"pol4+pol2",ft1[0],ft1[sizeof(ft1)/sizeof(ft1[0])-1]);
        hft1->Fit(hist_name,"R");
        // fit_8->Write();
        hft1->Write();
        outFile8->cd();
        TF1 *fit_9 = new TF1(hist_name,"pol2",ft2[0]-0.25,ft2[sizeof(ft2)/sizeof(ft2[0])-1]-0.25);
        //hft2->Fit(hist_name,"R");
        //fit_9->Write();
        hft2->Write();
        //f.Write();
        //delete hft0; delete  hft1; delete hft2; delete hfs0; delete hfs1; delete hfm0;   delete hfm1;   delete hfm6;   delete hfm7;
    }
    //outFile->Write();
    outFile->Close();outFile1->Close();outFile2->Close();outFile3->Close();outFile4->Close();outFile5->Close();outFile6->Close();outFile7->Close();outFile8->Close();
    
    
    
    //TFile f("ch1_splitted_TF1_NoBinbyBin.root", "RECREATE");	// if name change then change this name also in first time where script add_stat_shapes.py appears
    TString OutRootFileSuffix = "_NoBinbyBin";
    TFile f(OutPutRootFileName + OutRootFileSuffix + ".root", "RECREATE");	// if name change then change this name also in first time where script add_stat_shapes.py appears
    
    
    // Write all histograms...
    for (int i=0; i<SizeOf_HistName; i++)
    {
        hists[i]->Write();
    }
    for (int i = 0; i < SizeOf_aQGC; ++i)
    {
        histo_aqgc[i]->Write();
    }
    
    histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Up->Write();
    histo_VVjjQCD_EWK_CMS_QCDScaleBounding_Down->Write();
    histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Up->Write();
    histo_VVjjQCD_EWK_CMS_PDFScaleBounding_Down->Write();
    histo_diboson_EWK_CMS_QCDScaleBounding_Up->Write();
    histo_diboson_EWK_CMS_QCDScaleBounding_Down->Write();
    histo_diboson_EWK_CMS_PDFScaleBounding_Up->Write();
    histo_diboson_EWK_CMS_PDFScaleBounding_Down->Write();
    
    
    //-------------------------------------------------------------------------------------
    //
    //		Create Data card
    //
    //-------------------------------------------------------------------------------------
    // char outputLimitsShape[200];
    // sprintf(outputLimitsShape,"histo_limits_WV.txt");
    // ofstream newcardShape;
    // newcardShape.open(outputLimitsShape);
    // newcardShape << Form("imax 1 number of channels\n");
    // newcardShape << Form("jmax * number of background\n");
    // newcardShape << Form("kmax * number of nuisance parameters\n");
    
    // newcardShape << Form("shapes * * WVchannel_datacard.root $PROCESS $PROCESS_$SYSTEMATIC\n");
    // newcardShape << Form("shapes data_obs * WVchannel_datacard.root histo_Data\n");
    // newcardShape << Form("shapes Higgs * WVchannel_datacard.root histo_Higgs_M$MASS histo_Higgs_M$MASS_$SYSTEMATIC\n");
    // newcardShape << Form("Observation %d\n", -1/*(int)histo_Data->GetBinContent(nb)*/);
    // //newcardShape << Form("bin wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d wz%2s%4s%d\n",finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1,finalStateName,ECMsb.Data(),nb-1);
    // newcardShape << Form("process aQGC Wjet WV top Zjet\n");
    // newcardShape << Form("process 0 1 2 3 4\n");
    // newcardShape << Form("rate %8.5f %8.5f  %8.5f  %8.5f  %8.5f  %8.5f\n",-1.,-1.,-1.,-1.,-1.,-1.) ;
    // //-------------------------------------------------------------------------------------
    
    // newcardShape.close();
    
    f.Write();
    f.Close();
    
    //-----------------------------------------------------
    //
    //	Add bin-by-bin uncertanities
    //
    //-----------------------------------------------------
    // TString command1 = "./add_stat_shapes.py --filter Vjets --prefix Vjets_bbb " + OutPutRootFileName + OutRootFileSuffix + ".root WVchannel_datacard_BBB2.root";
    // system(command1);
    
    // char command2[3000];
    // sprintf(command2,"./add_stat_shapes.py --filter diboson --prefix diboson_bbb WVchannel_datacard_BBB2.root WVchannel_datacard_BBB3.root");
    // system(command2);
    
    // char command3[3000];
    // sprintf(command3,"./add_stat_shapes.py --filter VVjjQCD --prefix VVjjQCD_bbb WVchannel_datacard_BBB3.root WVchannel_datacard_BBB4.root");
    // system(command3);
    
    // char command4[3000];
    // sprintf(command4,"./add_stat_shapes.py --filter top --prefix top_bbb WVchannel_datacard_BBB4.root WVchannel_datacard_BBB5.root");
    // system(command4);
    
    // char command5[3000];
    // sprintf(command5,"./add_stat_shapes.py --filter W1+jets --prefix W1+jets_bbb WVchannel_datacard_BBB5.root WVchannel_datacard_BBB6.root");
    // system(command5);
    
    // TString command6 = "rm WVchannel_datacard_BBB2.root WVchannel_datacard_BBB3.root WVchannel_datacard_BBB4.root WVchannel_datacard_BBB5.root; mv WVchannel_datacard_BBB6.root " + OutPutRootFileName + ".root";
    // system(command6);
}

void WVChannel_GetCard_WithHiggsDistributions()
{
    int start_s=clock();
    model("files2016_WV.txt",
          "ch1_splitted_TF1_WV");
    
    int stop_s=clock();
    cout << "time: " << double(stop_s-start_s)/(double(CLOCKS_PER_SEC)*60.0) <<" min" << endl;
    
}
