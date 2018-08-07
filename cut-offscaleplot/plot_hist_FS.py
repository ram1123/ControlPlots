import ROOT as r

import CMS_lumi, tdrstyle
tdrstyle.setTDRStyle()



#change the CMS_lumi variables (see CMS_lumi.py)
CMS_lumi.lumi_7TeV = "4.8 fb^{-1}"
CMS_lumi.lumi_8TeV = "18.3 fb^{-1}"
CMS_lumi.lumi_13TeV = "35.9 fb^{-1}"
CMS_lumi.writeExtraText = 0
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

CMS_lumi.lumiTextOffset = +0.25

iPos = 10

iPeriod = 4

#if( iPos==0 ): CMS_lumi.relPosX = 0.12



fileIn = open("cutoffscale_FS.dat","read")

count = len(open("cutoffscale.dat").readlines(  ))

r.gStyle.SetOptStat(0)

h1 = r.TH1F("h1",";M_{VV} cut-off scale (TeV);FS0 (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)
h2 = r.TH1F("h2",";M_{VV} cut-off scale (TeV);FS0 (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)

h3 = r.TH1F("h3",";M_{VV} cut-off scale (TeV);FT's (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)
h4 = r.TH1F("h4",";M_{VV} cut-off scale (TeV);FT's (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)

h5 = r.TH1F("h5",";M_{VV} cut-off scale (TeV);FT's (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)
h6 = r.TH1F("h6",";M_{VV} cut-off scale (TeV);FT's (#times 10^{-12} TeV^{-4}), 95% CL",7,0,7)

count = 1
countpar = 1
for line in fileIn:
  if line[0]=="@": continue;
  values = line.split()
  print values
  if countpar == 1:
  	h1.SetBinContent(count, float(values[1]))
  	h2.SetBinContent(count, float(values[2]))
  	h1.GetXaxis().SetBinLabel(count, values[0]);
  	h2.GetXaxis().SetBinLabel(count, values[0]);
	print "Hist: ",countpar,":",count,"\t",values[0],"\t",values[1],"\t",values[2]
  	count +=1
  if countpar == 2:
  	h3.SetBinContent(count, float(values[1]))
  	h4.SetBinContent(count, float(values[2]))
  	h3.GetXaxis().SetBinLabel(count, values[0]);
  	h4.GetXaxis().SetBinLabel(count, values[0]);
	print "Hist: ",countpar,":",count,"\t",values[0],"\t",values[1],"\t",values[2]
  	count +=1
  if countpar == 3:
  	h5.SetBinContent(count, float(values[1]))
  	h6.SetBinContent(count, float(values[2]))
  	h5.GetXaxis().SetBinLabel(count, values[0]);
  	h6.GetXaxis().SetBinLabel(count, values[0]);
	print "Hist: ",countpar,":",count,"\t",values[0],"\t",values[1],"\t",values[2]
  	count +=1
  if count == 8 and countpar ==2:
    	print "\n\n","Switch to another histogram","\n\n"
	count = 1
	countpar = 3
  if count == 8 and countpar == 1: 
    print "\n\n","Switch to another histogram","\n\n"
    count = 1
    countpar = 2

c1 = r.TCanvas( 'c1', 'A Simple Graph Example', 1000,700 )
h1.SetMarkerSize(1.0)
h2.SetMarkerSize(1.0)
h3.SetMarkerSize(1.0)
h4.SetMarkerSize(1.0)
h5.SetMarkerSize(1.0)
h6.SetMarkerSize(1.0)
h1.SetMarkerStyle(9)
h2.SetMarkerStyle(9)
h3.SetMarkerStyle(24)
h4.SetMarkerStyle(24)
h5.SetMarkerStyle(26)
h6.SetMarkerStyle(26)
h1.SetMaximum(8.0)
h1.SetMinimum(-8.0)
h1.Draw("p")
h2.Draw("same p")
#h3.Draw("same p")
#h4.Draw("same p")
#h5.Draw("same p")
#h6.Draw("same p")


CMS_lumi.CMS_lumi(c1, iPeriod, iPos)

c1.SaveAs("FS0.png")
