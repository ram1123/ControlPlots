import CMS_lumi, tdrstyle
tdrstyle.setTDRStyle()



#change the CMS_lumi variables (see CMS_lumi.py)
CMS_lumi.lumi_7TeV = "4.8 fb^{-1}"
CMS_lumi.lumi_8TeV = "18.3 fb^{-1}"
CMS_lumi.lumi_13TeV = "36 fb^{-1}"
CMS_lumi.writeExtraText = 1
CMS_lumi.extraText = "Preliminary"
CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

CMS_lumi.lumiTextOffset = +0.20

iPos = 10

iPeriod = 4

if( iPos==0 ): CMS_lumi.relPosX = 0.12


fileIn = open("cutoffscale.dat","read")


count = len(open("cutoffscale.dat").readlines(  ))
print count

from ROOT import TCanvas, TGraph, TMultiGraph,TAxis
c1 = TCanvas( 'c1', 'A Simple Graph Example', 1000,700 )

#c1.SetFillColor( 42 )
#c1.SetGrid()

mg = TMultiGraph()
from array import array

n = count
x, y = array( 'd' ), array( 'd' )

#for i in range( n ):
coutn  = 0
for i in fileIn:
   j=i.split()
   print j
   x.append(float(j[0]))
   y.append(float(j[1]))
   print(' i %f %f %f ' % (coutn,x[coutn],y[coutn]))
   coutn+=1
fileIn.close()
gr = TGraph( n, x, y )
gr.SetLineColor( 2 )
gr.SetLineWidth( 4 )
gr.SetMarkerColor( 4 )
gr.SetMarkerStyle( 21 )
gr.SetTitle( 'a simple graph' )
gr.GetXaxis().SetTitle( 'X title' )
gr.GetYaxis().SetTitle( 'Y title' )
#gr.Draw( 'ACP' )
#c1.SaveAs("test.png")



fileIn = open("cutoffscale.dat","read")
xx, yy = array( 'd' ), array( 'd' )
coutn  = 0
for i in fileIn:
   j=i.split()
   print j
   xx.append(float(j[0]))
   yy.append(float(j[2]))
   print(' i %f %f %f ' % (coutn,xx[coutn],yy[coutn]))
   coutn+=1

gr1 = TGraph( n, xx, yy )
gr1.SetLineColor( 2 )
gr1.SetLineWidth( 4 )
gr1.SetMarkerColor( 4 )
gr1.SetMarkerStyle( 21 )
##gr1.SetTitle( 'a simple graph' )
##gr1.GetXaxis().SetTitle( 'X title' )
##gr1.GetYaxis().SetTitle( 'Y title' )
#gr1.Draw( 'CP' )

mg.Add(gr)
mg.Add(gr1)
mg.SetMaximum(0.4)
mg.SetMinimum(-0.4)

#mg.GetXaxis().SetTitle("M_{WW} (GeV) CutOff Scale")
#mg.GetYaxis().SetTitle("FT0 (95% CL)")
mg.SetTitle(";M_{WW} (GeV) CutOff Scale;FT0 (95% CL)");

from ROOT import TPad, TH1F

pad1 = TPad("pad1", "pad1", 0.0, 0.0, 0.8, 1.0)
pad1.SetTopMargin(0.07)  # joins upper and lower plot
pad1.SetBottomMargin(0.13)  # joins upper and lower plot
pad1.SetLeftMargin(0.15)
pad1.SetRightMargin(0.0)
#pad1.SetLogy(1)
pad1.SetGridx()
pad1.SetTickx(1)
pad1.SetTicky(1)
pad1.Draw()
# Lower ratio plot is pad2
c1.cd()
pad2 = TPad("pad2", "pad2", 0.8, 0.00, 1.0, 1.0)
#pad2.SetLogy(1)
pad2.SetTopMargin(0.07)  # joins upper and lower plot
pad2.SetBottomMargin(0.13)
pad2.SetLeftMargin(0.0)
pad2.SetRightMargin(0.06)
pad2.SetGridx()
pad2.SetTickx(1)
pad2.SetTicky(1)
pad2.Draw()

c1.cd()

pad1.cd()
mg.Draw("AP ")
CMS_lumi.CMS_lumi(c1, iPeriod, iPos)

pad2.cd()
h1 = TH1F("h1","",1,0,10);

h1.SetBinContent(1,0.15);
h1.SetStats(0)
h1.SetMaximum(0.4)
h1.SetMinimum(-0.4)
h1.SetMarkerSize(1);
h1.SetMarkerStyle(21);
h1.SetMarkerColor(4);
h1.GetXaxis().SetBinLabel(1,"#infty");
h1.GetXaxis().SetLabelSize(0.4);
h1.GetYaxis().SetLabelOffset(999);
h1.GetYaxis().SetLabelSize(0);

h1.Draw("P")

h2 = TH1F("h2","",1,0,10);

h2.SetBinContent(1,-0.15);
h2.SetStats(0)
h2.SetMaximum(0.4)
h2.SetMinimum(-0.4)
h2.SetMarkerSize(1);
h2.SetMarkerStyle(21);
h2.SetMarkerColor(4);
h2.GetXaxis().SetBinLabel(1,"#infty");
h2.GetXaxis().SetLabelSize(0.3);
h2.GetYaxis().SetLabelOffset(999);
h2.GetYaxis().SetLabelSize(0);


h2.Draw("P same")



c1.SaveAs("test.png")
