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

#include "tdrstyle.C"
#include "utils.C" // Tokenize
#include "CMS_lumi.C"

#include <Python.h>


typedef struct {
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

#include "controlplotvars_boosted.h"
#include "controlplotvars_common.h"
#include "controlplotvars_CHS.h"
#include "controlplotvars_Puppi.h"
#include "controlplotvars_vbf.h"
#include "controlplotvars_mva.h"
#include "controlplotvars_Nminus1plot.h"
#include "controlplotvars_CHS_signal.h"
#include "controlplotvars_CHS_signal_2lep.h"
//#include "controlplotvars_UpDn.h"



using namespace std;

double intLUMIinvpb;

//=====================================================================================
// SYNOPSIS:
//   1. Prepare "InData" and "OutDir" directories; e.g., "ln -s . OutDir" to go to current dir
//   2. Prepare "cuttable.txt" of cut names and cut strings
//   3. root [0] .L myControlPlots.C+
//      root [1] myControlPlots("cuttable.txt","sampleFileName.txt")
//
// ====================================================================================
// Self Function
// ====================================================================================
/*

*/
void cmspre(double intlumifbinv)
{
  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.95,0.92,"#sqrt{s} = 13 TeV");
  latex.SetTextAlign(31); // align right
  latex.DrawLatex(0.73,0.93,Form("#int #font[12]{L} dt = %.1f fb^{-1}", (float)intlumifbinv));
//  latex.DrawLatex(0.65,0.93,Form("2012B", (float)intlumifbinv));

  latex.SetTextAlign(11); // align left
//  latex.DrawLatex(0.15,0.93,"CMS,  #sqrt{s} = 7 TeV");//preliminary 2011");
  latex.SetTextSize(0.06);
  latex.DrawLatex(0.145,0.92,"CMS #bf{#it{preliminary}}");

}

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
  TH1 *Draw(const plotVar_t& pv, const TCut& cut, const TCut& cutSQ ) {
    if (!tree_) {
      cerr << "No tree to draw from." << endl;
      return 0;
    }
    double tmp = 0;
    cout << "\tDrawing " << pv.plotvar << " for sample = " << info_.samplename << " ... ";
    TString hname = TString("th1")+ pv.outfile + Form("%d",info_.index);
    TH1 *histo = new TH1D(hname, hname, pv.NBINS, pv.MINRange, pv.MAXRange);
    assert(histo);
    histo->Sumw2();
    cout << tree_->Draw(pv.plotvar+TString(">>")+hname, cut, "goff") << " entries, ";
    histo->SetBinContent(pv.NBINS,histo->GetBinContent(pv.NBINS)+histo->GetBinContent(pv.NBINS+1));
    //cout << histo->Integral() << " " << tmp << " " << "weighted entries, (";
    cout << histo->IntegralAndError(0,histo->GetNbinsX()+1,tmp) << " " << tmp << " " << "weighted entries";

#if 0
    if (strlen((const char *)cutSQ)) {
      hname = TString("th1") + pv.outfile + Form("%d",info_.index) + TString("SQ");
      TH1 *histoSQ = new TH1D(hname, hname, pv.NBINS, pv.MINRange, pv.MAXRange);
      tree_->Draw(pv.plotvar+TString(">>")+hname, cutSQ, "goff");
      for(int hi=1;hi<=pv.NBINS;hi++) {
	histo->SetBinError(hi,sqrt(histoSQ->GetBinContent(hi)));
      }
      delete histoSQ;
    }
#endif
    if (info_.nMCevents) {
      //cout<<"\n===> Evetns = "<<info_.xsecpblumi<<"\t"<<info_.nMCevents<<"\t"<<info_.MCnegEvent<<"\t"<<info_.colorcode<<endl;
      histo->Scale((info_.xsecpblumi*info_.otherscale)/(info_.nMCevents - info_.MCnegEvent));
      cout << ", " <<histo->IntegralAndError(1,histo->GetNbinsX(),tmp) << " " <<tmp<< " " << (histo->Integral(1,histo->GetNbinsX()+1)*info_.xsecpblumi*info_.otherscale)/(info_.nMCevents - info_.MCnegEvent) << " " << " scaled events in window";
    }
    cout << endl;

    return histo;
  }
private:
  SampleInfo_t info_;
  TTree *tree_;
};

//======================================================================

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
    
    cout << "Loading sample " << s.samplename << " -> " << s.treefilename << endl;

    if (!samples.size()) {
      if (s.samplename.EqualTo("data")) {
	intLUMIinvpb = s.xsecpblumi;
	s.xsecpblumi = 1;
	cout << "intLUMI = " << intLUMIinvpb << " pb^-1" << endl;
      } else {
	cerr << "First sample in the table must be 'data'" << endl;
	exit(-1);
      }
    } else {
      s.otherscale *= intLUMIinvpb;
    }

    samples.push_back(new Sample(s) );
  }
}                                                         // loadSamples

//======================================================================

void myControlPlots(const char *cuttablefilename,
		    const char *samplefilename,
		    const plotVar_t plotvars[] = commonplotvars,
		    const string OutRootFile = "testrk.root"
		    )
//		    const plotVar_t plotvars[] = boostedplotvars )
{
  //gROOT->ProcessLine(".L tdrstyle.C");
  ofstream Logfile;

  TH1::SetDefaultSumw2(1);
 
  //TFile *outDC = new TFile("htt_mt_inputs.root","RECREATE");

  TString unwtcutstring;

  loadCutString(cuttablefilename, unwtcutstring);

  TString blinddatacutstring = unwtcutstring + "&&(1)";

  //  const char* the_cut = "1";
  //  double BINWIDTH = ((MAXRange-MINRange)/NBINS);

 // Get the input trees:

  vector<Sample *> samples;

  loadSamples(samplefilename,samples);

 // Data

  Sample *sdata = samples[0];

  if (sdata->Tree())
    cout << "ndata =" << sdata->Tree()->GetEntries() <<endl;

  TFile f(OutRootFile.c_str(), "RECREATE");
  //TFile f("plotvar_histo.root", "RECREATE");

  //============================================================
  //  VARIABLE LOOP
  //============================================================

  for (int ivar=0; ; ivar++) {

    plotVar_t pv = plotvars[ivar];
    TString outfile = TString("OutDir/")+TString(gSystem->BaseName(cuttablefilename)).ReplaceAll(".txt","")+TString("_")+pv.outfile;
    Logfile.open (outfile+".log");
    TString temp = TString("Yield of Variable : ")+pv.outfile;
    const std::string spaces(temp.Length(), ' ');
    const std::string second = "* " + spaces + " *";
    const std::string first(second.size(), '*');
    Logfile << first << std::endl;
    Logfile << second << std::endl;
    Logfile << "* " << temp << " *" << std::endl;
    Logfile << second << std::endl;
    Logfile << first << std::endl;
 
    if ( !pv.plotvar.Length() ) break;

    cout << pv.plotvar << "\t"<<pv.MINRange<<"\t" << pv.MAXRange<<"\t" << pv.NBINS<<"\tTHE CUT " << endl;

    if (!pv.plotvar.Contains("_smeared"))
      if ( sdata->Tree() && 
	   sdata->Tree()->Draw(pv.plotvar,"","goff",1) == -1 ) { // check if the variable exists in the tree
	cout << "\t...can't be plotted!" << endl;
	continue;
      }

    //TCut the_cut(TString("genWeight*trig_eff_Weight*id_eff_Weight*(")+unwtcutstring+TString(")"));
    TCut the_cut(TString("genWeight*trig_eff_Weight*id_eff_Weight*pu_Weight*(")+unwtcutstring+TString(")"));
    //TCut the_cut(unwtcutstring);
    //TCut the_cutE(TString("effwt*puwt*puwt*(")+unwtcutstring+TString(")"));

    TCut nullcut("");

    cout << "the_cut = "<< the_cut << endl;

    const double BINWIDTH = ((pv.MAXRange-pv.MINRange)/pv.NBINS);

    map<TString, TH1 *> m_histos;
    map<TString, bool> m_stacked;

    double totevents = 0.;

    //============================================================
    // DRAW THE VARIABLE FOR ALL SAMPLES, CREATE HISTOS
    //============================================================

    for (size_t isamp=0; isamp<samples.size(); isamp++) {
      Sample *s = samples[isamp];

      m_stacked[s->name()] = false;

      TH1 *h;

      if (s->name().EqualTo("data")) {
	plotVar_t pvnosmear = pv;
	//pvnosmear.plotvar.ReplaceAll("_smeared",""); // no smearing for data!
	h = s->Draw(pvnosmear, TCut(blinddatacutstring), nullcut); // effwt*puwt==1 for data! -- NO IT DOESN'T NECESSARILY!
      }
      else if (s->name().EqualTo("aQGCX100")){
	h = s->Draw(pv, the_cut*"(100.0*LHEWeight[993]/LHEWeight[0])", the_cut*"(100.0*LHEWeight[993]/LHEWeight[0])");
	if (s->stackit()) {
	  totevents += h->Integral(1,h->GetNbinsX()+1);
	} 
      }
      else {
	h = s->Draw(pv, the_cut, the_cut);
	if (s->stackit()) {
	  totevents += h->Integral(1,h->GetNbinsX()+1);
	}
      }
      
      if (!h) continue;

      map<TString, TH1 *>::iterator mit = m_histos.find(s->name());
      if (mit == m_histos.end()) {
	h->SetName(s->name());
	h->SetTitle(s->name());
	if (s->stackit()) {
	  if (s->name().EqualTo("W+jets"))
	    {
	      h->SetLineColor(TColor::GetColor(222,90,106));
	      h->SetFillColor(TColor::GetColor(222,90,106));
	      h->SetLineWidth(0);
	    }
	  else if(s->name().EqualTo("top"))
	    {
	      h->SetLineColor(TColor::GetColor(155,152,204));
	      h->SetFillColor(TColor::GetColor(155,152,204));	
	      h->SetLineWidth(0);
	    }
	  else if(s->name().EqualTo("Z+jets"))
	    {
	      h->SetLineColor(TColor::GetColor(248,206,104));
	      h->SetFillColor(TColor::GetColor(248,206,104));	
	      h->SetLineWidth(0);
	    }
	  else if(s->name().EqualTo("Diboson"))
	    {
	      h->SetLineColor(TColor::GetColor(250,202,255));
	      h->SetFillColor(TColor::GetColor(250,202,255));	
	      h->SetLineWidth(0);
	    }
	  else
	    {
	      h->SetLineColor(s->colorcode());
	      h->SetFillColor(s->colorcode());
	      h->SetLineWidth(0);
	    }
	}
	m_histos[s->name()] = h;
      } else {
	mit->second->Add(h);
      }
    }

    //============================================================
    // COUNT EVENTS, RENORM TO DATA, CONSTRUCT THE TSTACK & LEGEND
    //============================================================

    TH1 *th1data = m_histos["data"];
    //TH1 *aqgc = m_histos["aQGC"];

    double ndata=1., renorm=1.;
    if (th1data) {
      ndata  = th1data->Integral(1,th1data->GetNbinsX()+1);
      renorm = ndata/totevents;

      cout << "Total MC	= " << totevents << endl;
      cout << "data	= " << ndata  <<endl;
      cout  << "data/MC	= " << renorm << endl;
      Logfile << "Total MC	= " << totevents << endl;
      Logfile << "data	= " << ndata  <<endl;
      Logfile << "data/MC	= " << renorm << endl;
    }

    // Setup the stack and total
    THStack* hs = new THStack("hs","MC contribution");
    TH1D *th1tot = new TH1D("th1tot", "th1tot", pv.NBINS, pv.MINRange, pv.MAXRange);

    // Set up the legend

    float  legX0=0.65, legX1=0.99, legY0=0.54, legY1=0.88;
    //float  legX0=0.17, legX1=0.95, legY0=0.7, legY1=0.88;
    // float  legX0=0.52, legX1=0.89, legY0=0.54, legY1=0.88;
    // float  legX0=0.18, legX1=0.52, legY0=0.4, legY1=0.88;
    TLegend * Leg = new TLegend( legX0, legY0, legX1, legY1);
    Leg->SetFillColor(0);
    Leg->SetFillStyle(0);
    Leg->SetBorderSize(0);
    //Leg->SetTextSize(0.04);
    //Leg->SetNColumns(3);

    if (th1data){
      if (TString(cuttablefilename).Contains("Mu"))
	Leg->AddEntry(th1data,  "Observed",  "LP");
      else
	Leg->AddEntry(th1data,  "Observed",  "LP");
    }

    vector<double> binErrSQ(pv.NBINS,0.);

    vector<pair<TString, TH1 *> > v_legentries;

    TString oldsamplename;
    double maxval = -9e99;

    for (size_t isamp=1; isamp<samples.size(); isamp++) {
      Sample *s = samples[isamp];
      if (s->name()==oldsamplename) continue;

      map<TString, TH1 *>::iterator mit = m_histos.find(s->name());
      TH1 *h = mit->second;
      //h->SetLineColor(kBlack);
      h->SetLineWidth(    3.);
      //h->SetFillColor(color );
      //h->SetFillStyle(style );
      h->SetTitleSize  (0.055,"Y");
      h->SetTitleOffset(1.600,"Y");
      h->SetLabelOffset(0.014,"Y");
      h->SetLabelSize  (0.050,"Y");
      h->SetLabelFont  (42   ,"Y");
      h->SetTitleSize  (0.055,"X");
      h->SetTitleOffset(1.300,"X");
      h->SetLabelOffset(0.014,"X");
      h->SetLabelSize  (0.050,"X");
      h->SetLabelFont  (42   ,"X");
      //h->SetMarkerStyle(20);
      //h->SetMarkerColor(color);
      h->SetMarkerSize (0.6);
      h->GetYaxis()->SetTitleFont(42);
      h->GetXaxis()->SetTitleFont(42);
      //h->SetTitle("");  

      //if (s->stackit())
      //	h->Scale(renorm);
      //else
      //	h->Scale(ndata/h->Integral());

//      cout << s->name() << "	= " << Form("%4g,%7g,%4g",
//					 h->Integral(0,0),
//					 h->Integral(1,h->GetNbinsX()+1),
//					 h->Integral(h->GetNbinsX()+1,h->GetNbinsX()+1))
//	   << endl;
      cout << s->name() << "	= " << Form("%7g", h->Integral(1,h->GetNbinsX()+1)) << endl;
      Logfile << s->name() << "	= " << Form("%7g", h->Integral(1,h->GetNbinsX()+1)) << endl;

      if(s->stackit()) {
	// Compose the stack
	hs->Add(h);
	th1tot->Add(h);
	m_stacked[s->name()] = true;
	for (int ibin=1; ibin <= pv.NBINS; ibin++)
	  binErrSQ[ibin-1] += h->GetBinError(ibin)*h->GetBinError(ibin);
      }
      v_legentries.push_back(*mit);

      int maxbin = h->GetMaximumBin();
      maxval = std::max(maxval,h->GetBinContent(maxbin));

      oldsamplename=s->name();
      h->Write();
    }

    cout << "maxval " <<maxval <<endl;

    // Reverse the order for the legend
    for (vector<pair<TString, TH1 *> >::reverse_iterator
	   rit = v_legentries.rbegin();
	 rit != v_legentries.rend();
	 rit++)
      {
	//if(rit->first=="aQGC" || rit->first=="WV(EWK)")
	if(rit->first=="aQGCX100" || rit->first=="WV(EWK)X100")
	  Leg->AddEntry(rit->second, rit->first, "L" ); // "F");
	else
	  Leg->AddEntry(rit->second, rit->first, "F" ); // "F");
      }
    TH1D* th1totClone = ( TH1D*) th1tot->Clone("th1totClone");
    th1totClone->SetMarkerStyle(0);
    th1totClone->SetFillStyle(3003);
    th1totClone->SetFillColor(11);
    th1totClone->SetLineColor(0);

    for(int ibin=1; ibin<=th1totClone->GetNbinsX(); ++ibin) {
      th1totClone->SetBinError(ibin, sqrt(binErrSQ[ibin-1]));
    }

    //============================================================
    // SETUP THE CANVAS
    //============================================================

//    gROOT->ProcessLine(".L tdrstyle.C");
    setTDRStyle();
    //tdrStyle->SetErrorX(0.5);
    //tdrStyle->SetPadRightMargin(0.05);

    //tdrStyle->SetLegendBorderSize(0);

    TCanvas* c1 = new TCanvas(pv.plotvar,pv.plotvar,10,10, 800, 800);
    TPad *d1, *d2;
    
    c1->SetFillColor      (0);
    c1->SetBorderMode     (0);
    c1->SetBorderSize     (10);
    // Set margins to reasonable defaults
    c1->SetLeftMargin     (0.18);
    c1->SetRightMargin    (0.05);
    c1->SetTopMargin      (0.08);
    c1->SetBottomMargin   (0.15);
    // Setup a frame which makes sense
    c1->SetFrameFillStyle (0);
    c1->SetFrameLineStyle (0);
    c1->SetFrameBorderMode(0);
    c1->SetFrameBorderSize(10);
    c1->SetFrameFillStyle (0);
    c1->SetFrameLineStyle (0);
    c1->SetFrameBorderMode(0);
    c1->SetFrameBorderSize(10);

    if (th1data) {
      c1->Divide(1,2);
      d1 = (TPad*)c1->GetPad(1);
      d1->SetPad(0.01,0.30,0.95,0.99);
      //c1->cd();
      d2 = (TPad*)c1->GetPad(2);
      d2->SetPad(0.01,0.02,0.95,0.30);
      d1->cd();
      gPad->SetBottomMargin(0.0);
    }

    gPad->SetTopMargin(0.1);
    gPad->SetRightMargin(0.05);
    gPad->SetLeftMargin(0.14);

    gPad->SetLogy(0);

    if (th1tot->GetEntries())
      Leg->AddEntry(th1tot,  "Stat. Uncertainty",  "f");

    Leg->SetFillColor(0);

    TH1* th1totempty = new TH1D("th1totempty", "th1totempty", pv.ANBINS, pv.AMINRange, pv.AMAXRange);
    if (th1data) {
      th1data->SetMarkerStyle(20);
      th1data->SetLineColor(kBlack);
      th1data->SetMarkerSize(1.3);
      th1data->SetLineWidth(3);
    }

    th1tot->SetFillStyle(3013);
    th1tot->SetFillColor(13);
    th1tot->SetLineColor(kBlack);
    th1tot->SetLineWidth(1);
    th1tot->SetMarkerStyle(0);

    char tmpc[100];    sprintf(tmpc,"Events");
    if (pv.slog==1)    sprintf(tmpc,"Events/ %.1f",BINWIDTH);
    if (pv.slog==2)    sprintf(tmpc,"Events/ %.2f",BINWIDTH);
    if (pv.slog==3)    sprintf(tmpc,"Events/ %.0f GeV",BINWIDTH);
    if (pv.slog==6)    sprintf(tmpc,"Events/ %.1f rad",BINWIDTH);
    th1totempty->SetYTitle(tmpc);
    //  th1totempty->GetYaxis()->SetTitleSize(0.1);
    th1totempty->GetYaxis()->SetTitleOffset(1.2);
    th1totempty->GetYaxis()->SetLabelOffset(0.01);
    //  th1totempty->GetYaxis()->CenterTitle(true);
    th1totempty->GetYaxis()->SetLabelSize(0.04);
    // th1totClone->Draw("e3");   

    if (th1tot->GetEntries()) {
      th1tot->SetMinimum(0.1);
      th1totempty->SetMinimum(0.1);
    }

//    th1totempty->SetMaximum(2.5*maxval);
    th1totempty->SetMaximum(1.6*maxval);
    if(pv.slog==1) th1totempty->SetMaximum(1.6*maxval);

    // Draw it all

    th1totempty->Draw();

    if (th1data) {
      th1data->SetMinimum(0.1);
      th1data->SetBinErrorOption(TH1::kPoisson);
      th1data->Draw("e0same");
    }

    //th1tot->Draw("e2same");

    hs->SetMaximum(400.0);
    hs->Draw("samehist");
    if (pv.drawleg ==1)  Leg->Draw();  

    th1tot->Draw("e2same");

    if (th1data)
      th1data->Draw("e1same");
    //if(aqgc)
    //  aqgc->Draw("same");

    // draw unstacked histos separately.
    oldsamplename.Clear();
    for (size_t isamp=0; isamp<samples.size(); isamp++) {
      Sample *s = samples[isamp]; assert (s);
      if (s->name()==oldsamplename) continue;
      if (!s->stackit()) {
	map<TString, TH1 *>::iterator mit = m_histos.find(s->name());
	if (mit != m_histos.end()) {
	  TH1 *h = mit->second;
	  //if (h) h->Draw("histsame");	// To get line for data...
	  //if (h && s->name()=="WV(EWK)") 
	  if (h && s->name()=="WV(EWK)X100") 
	    {
	      h->SetFillStyle(0.);
	      //aqgc->SetLineStyle(11);
	      h->SetLineWidth(3.);
	      h->SetLineColor(kBlue+3);
	      cout << "Significance (SM EWK) = " << (h->Integral(1,h->GetNbinsX()+1)/100.0)/sqrt((h->Integral(1,h->GetNbinsX()+1)/100.0)+totevents) << endl;
	      Logfile << "Significance (SM EWK) = " << (h->Integral(1,h->GetNbinsX()+1)/100.0)/sqrt((h->Integral(1,h->GetNbinsX()+1)/100.0)+totevents) << endl;
	      h->Draw("histsame");
 
	    }
	  if (h && s->name()=="aQGCX100") 
	    {
	      h->SetFillStyle(0.);
	      //aqgc->SetLineStyle(11);
	      h->SetLineWidth(3.);
	      h->SetLineColor(kRed+3);
	      cout << "Significance (aQGC)   = " << (h->Integral(1,h->GetNbinsX()+1)/100.0)/sqrt((h->Integral(1,h->GetNbinsX()+1)/100.0)+totevents) << endl;
	      Logfile << "Significance (aQGC)   = " << (h->Integral(1,h->GetNbinsX()+1)/100.0)/sqrt((h->Integral(1,h->GetNbinsX()+1)/100.0)+totevents) << endl;
	      h->Draw("histsame");
	      //h->Draw("e1same");
	    }
  h->Write();
	}
      }
      oldsamplename=s->name();

    }

    //cmspre(intLUMIinvpb/1000.0);   
    CMS_lumi( d1, 4, 10 ); 
    // th1data->Draw("Axissame");
    gPad->RedrawAxis();

    if (th1data) {
      d2->cd();
      TH1F    * hhratio    = (TH1F*) th1data->Clone("hhratio")  ;
      hhratio->Sumw2();
      hhratio->SetStats(0);

      gPad->SetLeftMargin(0.14);
      gPad->SetTopMargin(0);
      gPad->SetRightMargin(0.05);
      gPad->SetFrameBorderSize(0);
      gPad->SetBottomMargin(0.3);
      gPad->SetTickx();
      
      hhratio->SetMarkerSize(1.25);
      //  hhratio->GetYaxis()->SetRangeUser(0.48,1.52);
      hhratio->GetYaxis()->SetRangeUser(0.5,1.5);
      hhratio->GetXaxis()->SetTitle(pv.xlabel);
      hhratio->GetXaxis()->SetTitleOffset(0.9);
      hhratio->GetXaxis()->SetTitleSize(0.15);
      hhratio->GetXaxis()->SetLabelSize(0.15);
      hhratio->GetYaxis()->SetTitleSize(0.1);
      hhratio->GetYaxis()->SetTitleOffset(0.5);
      hhratio->GetYaxis()->CenterTitle(true);
      hhratio->GetYaxis()->SetLabelSize(0.1);
      cout << hhratio->GetNbinsX() << endl;
      cout << th1tot->GetNbinsX() << endl;
      hhratio->Divide(th1tot);
      double binError(0.0), mcbinentry(0.0), mcerror(0.0);
      for(int i=0; i<hhratio->GetNbinsX(); ++i) {
	binError = hhratio->GetBinError(i);
	mcerror = th1tot->GetBinError(i);
	mcbinentry = th1tot->GetBinContent(i);
	if(mcbinentry>0.) mcerror /= mcbinentry;
	else mcerror = 0.0;
	binError = sqrt(binError*binError + mcerror*mcerror);
	hhratio->SetBinError(i, binError);
      }
      TH1D *th1emptyclone = new TH1D("th1emptyclone", "th1emptyclone", pv.ANBINS, pv.AMINRange, pv.AMAXRange);
      th1emptyclone->GetYaxis()->SetRangeUser(0.6,1.3999);
      th1emptyclone->GetXaxis()->SetTitle(pv.xlabel);
      th1emptyclone->GetXaxis()->SetTitleOffset(0.9);
      th1emptyclone->GetXaxis()->SetTitleSize(0.15);
      th1emptyclone->GetXaxis()->SetLabelSize(0.15);
      th1emptyclone->SetYTitle("Data/MC");
      th1emptyclone->GetYaxis()->SetTitleSize(0.13);
      th1emptyclone->GetXaxis()->SetNdivisions(505);
      th1emptyclone->GetYaxis()->SetNdivisions(505);
      th1emptyclone->GetYaxis()->SetTitleOffset(0.5);
      th1emptyclone->GetYaxis()->CenterTitle(true);
      th1emptyclone->GetYaxis()->SetLabelSize(0.1);
      th1emptyclone->Draw();

      TBox *errbox = new TBox(pv.AMINRange,0.974,pv.AMAXRange,1.026); // lumi systematic uncertainty
      errbox->SetFillColor(kGray);
      errbox->Draw();

#if 0
      TF1 *f1 = new TF1("f1", "pol1",  pv.AMINRange, pv.AMAXRange);
      f1->SetParameters(1.0,0.0);
      f1->SetParameters(1,0.0);
      //f1->FixParameter(0,1);
      //f1->FixParameter(1,0);
      //cout<<" par1   "f1->GetParameter(0)<<endl;
      //cout<<" par2   "f1->GetParameter(1)<<endl;
      
      f1->SetLineWidth(2);

      TFitResultPtr r =  hhratio->Fit("f1", "RBS");
      //TFitResultPtr r = hhratio->Fit(myFunc,"S");
      r->Print("V");     // print full information of fit including covariance matrix
#endif

      hhratio->Draw("esame");
      TLine *line; line = new TLine(pv.AMINRange,1.0,pv.AMAXRange,1.0);
      line->SetLineStyle(1);
      line->SetLineWidth(1);
      line->SetLineColor(1);
      line->Draw();
    }


    c1->Print(outfile+".pdf");
    c1->Print(outfile+".png");
    Logfile.close();
#if 0
    c1->Print(outfile+".C");
    //gPad->WaitPrimitive();
    c1->Modified();
    c1->Update();
    c1->SaveAs(outfile+".pdf"); 
#endif
  c1->Write();
  } // var loop

  //f.Write();

}                                                                // myControlPlots

//================================================================================
/* 
void dibresNobtagElplots()
{
  myControlPlots("DibosonResolvedElCuts.txt",
		 "DibosonResolvedElSamples13TeV.txt",
		 commonplotvars);
}

//================================================================================


void Nminus1_plots_met()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 met
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 met
		 );
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 met
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 met
		 );
}

void Nminus1_plots_fat_jet()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 fat_jet
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 fat_jet
		 );
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 fat_jet
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 fat_jet
		 );
}

void Nminus1_plots_vbfmjj()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 vbfmjj
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 vbfmjj
		 );
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 vbfmjj
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 vbfmjj
		 );
}

void Nminus1_plots_vbfdEta()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 vbfdEta
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 vbfdEta
		 );
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 vbfdEta
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 vbfdEta
		 );
}

void Nminus1_plots_nbtag()
{
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 nbtag
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt",
		 nbtag
		 );
}

void Wjet_loose()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_loose.txt",
  		 "DibosonBoostedElSamples13TeV.txt"
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_loose.txt",
  		 "DibosonBoostedMuSamples13TeV.txt"
		 );
}

void Wjet_tight()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedElSamples13TeV.txt"
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_tight.txt",
  		 "DibosonBoostedMuSamples13TeV.txt"
		 );
}

void TopControl()
{
  myControlPlots("DibosonBoostedElCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedElSamples13TeV.txt"
		 );
  myControlPlots("DibosonBoostedMuCuts13TeV_TTBarControlRegion.txt",
  		 "DibosonBoostedMuSamples13TeV.txt"
		 );
}

void Wjet_tighter()
{
  myControlPlots("DibosonBoostedElCuts13TeV_WjetControlRegion_Tighter.txt",
  		 "DibosonBoostedElSamples13TeV.txt",
		 commonplotvars_chs );
  //myControlPlots("DibosonBoostedMuCuts13TeV_WjetControlRegion_Tighter.txt",
  //		 "DibosonBoostedMuSamples13TeV.txt",
  //		 commonplotvars_chs );
}
void dibresabtagElplots()
{
  myControlPlots("DibosonResolvedElCuts.txt",
		 "DibosonResolvedElSamples13TeV.txt",
		 commonplotvars);
}

void dibresabtagMuplots()
{
  myControlPlots("DibosonResolvedMuCuts.txt",
		 "DibosonResolvedMuSamples13TeV.txt");
}

//================================================================================

void dibbooElplots(const char *cuttablefilename = "DibosonBoostedElCuts13TeV.txt",
		   const char *samplefilename = "DibosonBoostedElSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 boostedplotvars);
}

void dibbooMuplots(const char *cuttablefilename = "DibosonBoostedMuCuts13TeV.txt",
		   const char *samplefilename = "DibosonBoostedMuSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 boostedplotvars);
}

//================================================================================

void dibbooElVBFplots(const char *cuttablefilename = "DibosonBoostedElCuts13TeV.txt",
		      const char *samplefilename = "DibosonBoostedElSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 vbfplotvars);
}

void dibbooMuVBFplots(const char *cuttablefilename = "DibosonBoostedMuCuts13TeV.txt",
		      const char *samplefilename = "DibosonBoostedMuSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 vbfplotvars);
}

//================================================================================

void dibbooElMVAplots(const char *cuttablefilename = "DibosonBoostedElCuts13TeV.txt",
		      const char *samplefilename = "DibosonBoostedElSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 mvaplotvars);
}

void dibbooMuMVAplots(const char *cuttablefilename = "DibosonBoostedMuCuts13TeV.txt",
		      const char *samplefilename = "DibosonBoostedMuSamples13TeV.txt")
{
  myControlPlots(cuttablefilename,
		 samplefilename,
		 mvaplotvars);
}
*/
