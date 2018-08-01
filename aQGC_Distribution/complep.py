import ROOT as r
import sys
import os
import argparse

r.gROOT.SetBatch(True)

parser = argparse.ArgumentParser(description='Process limit combine tool commands...')
parser.add_argument('-v', '--variable', type=str, help='variable name', default="lepton_pt")
parser.add_argument('-n', '--parNumber', type=int, help='SM parameter starting number for one of aQGC point', default=549)
parser.add_argument('-m', '--parName', type=str, help='aQGC parameter name', default="FT0")
parser.add_argument('-y', '--yMax', type=int, help='Set y-max value', default=21)
parser.add_argument('-u', '--parValue', type=float, nargs=2, help='par values for legend', default=[0.2, 0.4])
args = parser.parse_args()


#fileIn = r.TFile("DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36_NoBinbyBin_bkup.root","read")
fileIn = r.TFile("DibosonBoostedElMuSamples13TeV_WWTree_CommonNtuple_For1and2Lepton_MuonPtScale_2018_07_24_10h36_NoBinbyBin.root","read")
c1 = r.TCanvas("c1")

par = int(args.parNumber)
print "= par = ",par
h1 = fileIn.Get(args.variable+"_"+str(par));
h1.SetStats(0)
#h1.Rebin(3)
h1.SetLineColor(1)

h2 = fileIn.Get(args.variable+"_"+str(par+1));
#h2.Rebin(3)
h2.SetStats(0)
h2.SetLineColor(2)

h3 = fileIn.Get(args.variable+"_"+str(par+2));
#h3.Rebin(3)
h3.SetStats(0)
h3.SetLineColor(3)

h4 = fileIn.Get(args.variable+"_"+str(par+3));
#h4.Rebin(3)
h4.SetStats(0)
h4.SetLineColor(3)

h5 = fileIn.Get(args.variable+"_"+str(par-1));
#h5.Rebin(3)
h5.SetStats(0)
h5.SetLineColor(2)
h5.SetLineStyle(2)

h6 = fileIn.Get(args.variable+"_"+str(par-2));
#h6.Rebin(3)
h6.SetStats(0)
h6.SetLineColor(3)
h6.SetLineStyle(2)

h7 = fileIn.Get(args.variable+"_"+str(par-3));
#h7.Rebin(3)
h7.SetStats(0)
h7.SetLineColor(3)
h7.SetLineStyle(2)

h1.GetXaxis().SetTitle(args.variable)
#h1.SetMaximum(float(args.yMax))
h1.SetMaximum(float(max([h1.GetMaximum(), h2.GetMaximum(), h3.GetMaximum(), h5.GetMaximum(), h6.GetMaximum()])*1.50))
#h1.SetMaximum(2.5)
h1.Draw("hist")
h2.Draw("hist same")
h3.Draw("hist same")
#h4.Draw("hist same")
h5.Draw("hist same")
h6.Draw("hist same")
#h7.Draw("hist same")

leg = r.TLegend(0.3,0.7,0.90,0.9);
leg.SetNColumns(2)
leg.AddEntry(h1,"SM")
leg.AddEntry(h2,args.parName+" = "+str(args.parValue[0])+"#times 10^{-12} TeV^{-4}")
leg.AddEntry(h3,args.parName+" = "+str(args.parValue[1])+"#times 10^{-12} TeV^{-4}")
leg.AddEntry(h5,args.parName+" = -"+str(args.parValue[0])+"#times 10^{-12} TeV^{-4}")
leg.AddEntry(h6,args.parName+" = -"+str(args.parValue[1])+"#times 10^{-12} TeV^{-4}")
leg.Draw()

print "SM : ",h1.GetBinContent(2),"/",h1.Integral()," = ",h1.GetBinContent(2)/h1.Integral()
print "FT0 = 0.2 : ",h2.GetBinContent(2),"/",h2.Integral()," = ",h2.GetBinContent(2)/h2.Integral()
print "FT0 = 0.4 : ",h3.GetBinContent(2),"/",h3.Integral()," = ",h3.GetBinContent(2)/h3.Integral()

c1.SaveAs(args.variable+"_"+args.parName+".png")
c1.SaveAs(args.variable+"_"+args.parName+".pdf")
c1.SetLogy(1)
h1.SetMaximum(float(max([h1.GetMaximum(), h2.GetMaximum(), h3.GetMaximum(), h5.GetMaximum(), h6.GetMaximum()])*1.50*10))
c1.SaveAs(args.variable+"_"+args.parName+"_log.png")
c1.SaveAs(args.variable+"_"+args.parName+"_log.pdf")
