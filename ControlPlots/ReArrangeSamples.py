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
commanSample = ['data','WV_EWK']
#commanSample = ['data']

#SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_01_07_12h02.txt'  # with 30 GeV cut on b-jets
SampleFile = 'DibosonBoostedElMuSamples13TeV_2018_02_16_08h33.txt'  # 20 GeV cut on b-jets
SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_02_26_18h33.txt' # QCD/other depending on iso cut
SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_03_06_23h37.txt' # QCD/other depending on iso cut added three new variable for delta(met, jets)
SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_03_09_13h06_Isolation.txt'  # Isolation applied at pre-selection
#SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_CleanedCode_Isolated_2018_03_12_22h09.txt' # Cleaned code (ISOLATED)
#SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_CleanedCode_Isolated_NaNFixed_Btag20GeV_2018_03_15_21h34.txt' # cleaned and isolated
SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_CleanedCode_Isolated_NaNFixed_Btag30GeV_2018_03_16_00h13.txt' # clened and isolated 30 GeV, loose b-tag weight
#SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_CleanedCode_Isolated_NaNFixed_Btag30GeV_2018_03_16_03h34.txt' # cleaned and isolated 30GeV Medimum btag (only for TTBar CR

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

Dictionary = {"top":[topArrangement,topCutFile,"index_ttbar.php"],"wjet":[wjetArrangement,wjetCutFile,"index_wjet.php"],"zjet":[zjetArrangement,zjetCutFile,"index_zjet.php"],"qcd":[qcdArrangement,qcdCutFile,"index_qcd.php"],"qcds":[qcdShapeArrangement,qcdShapeCutFile,"index_qcds.php"]}

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
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_03_06_23h37.txt' # QCD/other depending on iso cut added three new variable for delta(met, jets)
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_03_09_13h15_AntiIsolation.txt' # Anti-Isolation applied at pre-selection
   SampleFile = 'DibosonBoostedElMuSamples13TeV_WWTree_IsoVarSaved_2018_03_12_11h41_AntiIsolationWithUpperBound.txt'

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

#os.system('cat DibosonBoostedElMuSamples13TeV.txt')
print('root -l -b -q '+cppFile+'\(\\"'+Dictionary[ControRegionToPlot][1]+'\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",0\)')
os.system('root -l -b -q '+cppFile+'\(\\"'+Dictionary[ControRegionToPlot][1]+'\\",\\"DibosonBoostedElMuSamples13TeV.txt\\",'+variableFile+',\\"'+Dictionary[ControRegionToPlot][0][-1]+'_ControlRegion.root\\",1\)')
os.system('mkdir -p '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
os.system('mv OutDir/* '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M')+"/")
print "*"*20
print('cp '+cppFile+' '+Dictionary[ControRegionToPlot][0][-2]+'_ControlRegion.root DibosonBoostedElMuSamples13TeV.txt ReArrangeSamples.py  '+Dictionary[ControRegionToPlot][1]+' '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
os.system('cp '+cppFile+' '+Dictionary[ControRegionToPlot][0][-2]+'_ControlRegion.root DibosonBoostedElMuSamples13TeV.txt ReArrangeSamples.py  '+Dictionary[ControRegionToPlot][1]+' '+ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M'))
os.system('cp '+Dictionary[ControRegionToPlot][0][-1]+ ' ' +ControRegionToPlot+'_ControlRegion_'+AddDirName+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M') +'/index.php')
