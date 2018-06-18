import os
import sys
import time
import datetime

#############################
#	common files
#############################
ControRegionToPlot = sys.argv[1]	# top, wjet, zjet, all
AddDirName = sys.argv[2] # This will be added in the directory name


#commanSample = ['data','WV_EWK','aQGC']
#commanSample = ['data','WV_EWK']
commanSample = ['data']

#SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_01_07_12h02.txt'  # with 30 GeV cut on b-jets
SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_02_16_08h33.txt'  # 20 GeV cut on b-jets
SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_02_26_18h33.txt' # QCD/other depending on iso cut

variableFile = 'commonplotvars_chs'

cppFile = 'myControlPlots.C'

# Cut Files

topCutFile = 'DibosonBoostedElMuCuts13TeV_TTBarControlRegion_CHS.txt'
wjetCutFile = 'DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt'
zjetCutFile = 'DibosonBoostedElMuCuts13TeV_ZjetControlRegion_Tighter_CHS.txt'
qcdCutFile = 'DibosonBoostedElMuCuts13TeV_QCD_CHS.txt'
qcdShapeCutFile = 'DibosonBoostedElMuCuts13TeV_QCD_Shape.txt'


topArrangement= commanSample + ['Z+jets','Diboson','W+jets','SingleTop','TTbar','top']
#topArrangement= commanSample + ['QCD','Z+jets','Diboson','W+jets','SingleTop','TTbar']
wjetArrangement = commanSample + ['Z+jets','SingleTop','TTbar','top','Diboson','W+jets']
#wjetArrangement = commanSample + ['Z+jets','SingleTop','TTbar','top','Diboson','W+jets']
#wjetArrangement = commanSample + ['Z+jets','Diboson','QCD','SingleTop','TTbar','top','W+jets']
zjetArrangement = commanSample + ['W+jets','Diboson','QCD','SingleTop','TTbar','top','Z+jets']
qcdArrangement = commanSample + ['Z+jets','Diboson','SingleTop','TTbar','top','W+jets','V+jets']
#qcdArrangement = commanSample + ['QCD']
qcdShapeArrangement = commanSample + ['Z+jets','Diboson','SingleTop','TTbar','top','W+jets','V+jets','QCD']

Dictionary = {"top":[topArrangement,topCutFile],"wjet":[wjetArrangement,wjetCutFile],"zjet":[zjetArrangement,zjetCutFile],"qcd":[qcdArrangement,qcdCutFile],"qcds":[qcdShapeArrangement,qcdShapeCutFile]}

print Dictionary[ControRegionToPlot]

if ControRegionToPlot == "zjet":
   print "\n\nRemember to change the variable txt file. There you need to add variables related to 2 lepton case\n\n"
   variableFile = 'controlplotvars_CHS_2lep'
   cppFile = 'myControlPlots.C'
   time.sleep(30)

if ControRegionToPlot == "qcd":
   SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_02_23_12h07.txt' # QCD
   SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_02_24_21h01_QCD_Iso3p0.txt' # QCD
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_02_26_13h34.txt' # QCD
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_02_26_18h33.txt' # QCD/other depending on iso cut

if ControRegionToPlot == "qcds":	# For QCD Shape
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_QCD_Shape_2018_02_28_14h07.txt'# but of not applied trigger
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_QCD_Shape_2018_03_01_13h07.txt'
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_QCD_Shape_2018_03_01_21h23.txt'

# delete if there is anything inside OutDir
os.system('rm OutDir/*')

sampleOutFile = open("DibosonBoostedElMuSamples13TeV.txt","w")
for sample in Dictionary[ControRegionToPlot][0]:
   sampleInputFile = open(SampleFile,"r")
   for line in sampleInputFile:
      if line.split()[0] == sample:
	sampleOutFile.write(line)
sampleOutFile.close()

#leptonpt = [30, 50, 70, 90, 110]
leptonpt = [60, 65,75,80,85]

for lepPt in leptonpt:
	os.system("sed 's/l_pt1>30./l_pt1<"+str(lepPt)+"/g' "+Dictionary[ControRegionToPlot][1]+"  > CutTxtFile.txt")
	os.system('cat CutTxtFile.txt')
	print('root -l -b -q '+cppFile+'\(\\"CutTxtFile.txt\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",0\)')
	os.system('root -l -b -q '+cppFile+'\(\\"CutTxtFile.txt\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",0\)')
	os.system('mkdir -p '+ControRegionToPlot+'_ControlRegion_'+str(lepPt)+"_"+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
	os.system('mv OutDir/* '+ControRegionToPlot+'_ControlRegion_'+str(lepPt)+"_"+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M')+"/")
	os.system('cp '+cppFile+' '+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root DibosonBoostedElMuSamples13TeV.txt ReArrangeSamples.py  CutTxtFile.txt '+ControRegionToPlot+'_ControlRegion_'+str(lepPt)+"_"+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
	#print('root -l -b -q '+cppFile+'\(\\"'+Dictionary[ControRegionToPlot][1]+'\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",0\)')
	#os.system('root -l -b -q '+cppFile+'\(\\"'+Dictionary[ControRegionToPlot][1]+'\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",0\)')
	#os.system('mkdir -p '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
	#os.system('mv OutDir/* '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M')+"/")
	#os.system('cp '+cppFile+' '+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root DibosonBoostedElMuSamples13TeV.txt ReArrangeSamples.py  '+Dictionary[ControRegionToPlot][1]+' '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
