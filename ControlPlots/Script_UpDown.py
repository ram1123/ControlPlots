#! /usr/bin/env python
import os
import glob
import math
from array import array
import sys
import time
import subprocess
import tarfile
import datetime
import commands

currentDir = os.getcwd();
CMSSWDir =  currentDir+"/../";

#inputFolder = "/store/user/lnujj/WpWm_aQGC_Ntuples_Ram/FirstStepOutput/BaconNtuples/";
TestRun = 1

doMC = True;
doData = True;
category = ["el","mu"];

# Get date and time for output directory
## ADD "test" IN OUTPUT FOLDER IF YOU ARE TESTING SO THAT LATER YOU REMEMBER TO WHICH DIRECTORY YOU HAVE TO REMOVE FROM EOS
if TestRun:
	outputFolder = "/store/user/rasharma/ThirdStep_Distributions/WWTree_"+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M')+"_TEST/";
	OutputLogPath = "OutPut_Logs/Logs_" + datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M') + "_TEST";
else:
	outputFolder = "/store/user/rasharma/ThirdStep_Distributions/WWTree_"+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M');
	OutputLogPath = "OutPut_Logs/Logs_" + datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M');


print "Name of output dir: ",outputFolder
# create a directory on eos
os.system('xrdfs root://cmseos.fnal.gov/ mkdir ' + outputFolder)
# create directory in pwd for log files
os.system('mkdir -p ' + OutputLogPath)

# Function to create a tar file
def make_tarfile(output_filename, source_dir):
    with tarfile.open(output_filename, "w:gz") as tar:
            tar.add(source_dir, arcname=os.path.basename(source_dir))

# Get CMSSW directory path and name
cmsswDirPath = commands.getstatusoutput('echo ${CMSSW_BASE}')
CMSSWRel = os.path.basename(cmsswDirPath[1])

print "CMSSW release used : ",CMSSWRel

# create tarball of present working CMSSW base directory
os.system('rm CMSSW*.tgz')
#make_tarfile(CMSSWRel+".tgz", cmsswDirPath[1])

# send the created tarball to eos
os.system('xrdcp -f ' + CMSSWRel+".tgz" + ' root://cmseos.fnal.gov/'+outputFolder+"/" + CMSSWRel+".tgz")
#with open("ThingsUpdated.txt","a") as myfile:
#	CmdOutput = subprocess.check_output('git log --pretty=format:"%h - %an, %cd : %s" -2')
#	myfile.write("=========================================\n\n")
#	myfile.write(CmdOutput)
#myfile.close()
#os.system('xrdcp -f *.txt root://cmseos.fnal.gov/' + outputFolder)
#os.system('cp ThingsUpdated.txt ' + OutputLogPath)

# User Modifiable lines
# ------------------------------------------------------
IfControlPlots = 0    	# 0 -> Signal & background comparison only without data.
			# 1 -> data mc plots 

OutPutRootFileName = "testRoot.root" 

CutArray = [
		#'  Name                     Cut string',
		#'"type=ele(1),muon(0)',
		'"BDT_response"		"(BDT_response>-0.3)"',
		'"El or Mu"			"((type==1) || (type==0))"',
		'"1 lepton"		"(l_pt2<0)"',
		#'"Good Muon"		"((l_pt1>30.) && (abs(l_eta1)<2.5))"',
		#'"Good FatJet"		"((ungroomed_PuppiAK8_jet_pt>200)&&(abs(ungroomed_PuppiAK8_jet_eta)<2.4)&&(PuppiAK8_jet_tau2tau1<0.55))"',
		#'"m_{J}<65 && m_{J}>105"	"((PuppiAK8_jet_mass_so<65) || (PuppiAK8_jet_mass_so>105))"',
		#'">=0 Medium b-tag AK4"	"(nBTagJet_medium>0)"',
		#'">=0 Loose b-tag AK4"	"(nBTagJet_loose==0)"',
		#'"pfMET_Corr>50"		"(pfMET_Corr>50)"',
		#'"W p_{T}>200"		"(v_pt_type0>200.)"',
		#'"VBF jet deta > 4.0"    "(abs(vbf_maxpt_j2_eta-vbf_maxpt_j1_eta)>4.0)"',
		#'##"HF Exclusion"		"(abs(vbf_maxpt_j1_eta)<3.0)"',
		#'##"HF Exclusion"		"(abs(vbf_maxpt_j2_eta)<3.0)"',
		#'"VBF jet pts > 30"	"((vbf_maxpt_j1_pt>30) && (vbf_maxpt_j2_pt>30))"',
		#'"VBF Mjj > 800"         "(vbf_maxpt_jj_m>800)"',
		#'"Diboson Topology"	"(issignal_PuppiAK8==1)"',
		#'"BosonCentrality_type0>0.9"	"(BosonCentrality_type0>0.9)"',
		#'#"PtBalance_type0<0.3"		"(PtBalance_type0<0.3)"',
		#'#"HT>500"			"(ungroomed_PuppiAK8_jet_pt+vbf_maxpt_j1_pt+vbf_maxpt_j2_pt > 500)"',
		#'#"costheta2_type0>0.5"		"(costheta2_type0>0.5)"',
		#'#"deltaphi_METPuppiak8jet>2.3"	"(deltaphi_METPuppiak8jet>2.3)"',
		#'#"-1.5<ZeppenfeldWL_type0<1.0"	"((ZeppenfeldWL_type0>-1.5) && (ZeppenfeldWL_type0<1.0))"',
	    ]

# End user edit lies
# ------------------------------------------------------

VarInFile = open("controlplotvars_CHS.h")

outJDL = open("runstep2condor.jdl","w");

for line in VarInFile:
   if line.find('{') != -1 and line.find('}') != -1:
      if line.find('//') == -1:
	 if line.find('""') == -1:
            #print line
	    varToPlot = line
	    print varToPlot
	    varFileWrite = open("controlplotvars_UpDn.h","w")
	    
	    # Mandatory lines to write infile
	    varFileWrite.write('#ifndef _UPDOWNPLOTVARS_CHS_H\n')
	    varFileWrite.write('#define _UPDOWNPLOTVARS_CHS_H\n\n')
	    varFileWrite.write('#include "plotvar_t.h"\n\n')
	    varFileWrite.write('const plotVar_t updownplotvars_chs[] = {\n')
	    varFileWrite.write('//    plotvar   MINRange  MAXRange  NBINS  slog xlabel outfile AMINRange  AMAXRange ANBINS drawleg\n')
	    varFileWrite.write(varToPlot+'\n')
	    varFileWrite.write('\n{ "", 0.0,0.0,0,0,"","",0.,0.,0,0 }\n };\n\n #endif\n')
	    varFileWrite.close()
	    # Variable header file generated
	    
	    
	    # Start makeing cut file
	    cutFileWrite = open("DibosonBoostedMuCuts13TeV_Script.txt","w")
	    for cuts in CutArray:
	    	cutFileWrite.write(cuts+'\n')
	    cutFileWrite.close();
	    
	    # Start making run c++ file
	    runFilewrite = open("RunCpp.C",'w')
	    runFilewrite.write('#include "controlplotvars_UpDn.h"\n\nvoid RunCpp()\n{\n')
	    #runFilewrite.write('\tgROOT->ProcessLine(".L myControlPlots.C+");\n\n')
	    runFilewrite.write('\tgROOT->ProcessLine(".L myControlPlots_SignalBkg_Comparison.C+");\n\n')
	    #runFilewrite.write('\tgROOT->ProcessLine("myControlPlots(\\"DibosonBoostedMuCuts13TeV_Script.txt\\", \\"DibosonBoostedMuSamples13TeV_2017-11-07_14h59_OnlyCHS.txt\\", updownplotvars_chs, \\"'+OutPutRootFileName+'\\" ) ");\n\n}\n')
	    runFilewrite.write('\tgROOT->ProcessLine("myControlPlots_SignalBkg_Comparison(\\"DibosonBoostedElMuCuts13TeV_BDT.txt\\", \\"DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT.txt\\", updownplotvars_chs ) ");\n\n}\n')
	    runFilewrite.close()
	    
	    
	    # Run the generated macro
	    #os.system('root -l -b -q RunCpp.C')

	    outJDL.write("Executable = runstep2condor.sh\n");
	    outJDL.write("Universe = vanilla\n");
	    #outJDL.write("Requirements =FileSystemDomain==\"fnal.gov\" && Arch==\"X86_64\"");
	    outJDL.write("Notification = ERROR\n");
	    outJDL.write("Should_Transfer_Files = YES\n");
	    outJDL.write("WhenToTransferOutput = ON_EXIT\n");
	    #outJDL.write("include : list-infiles.sh |\n");
	    outJDL.write("Transfer_Input_Files = "+inputlist+"\n");
	    outJDL.write("x509userproxy = $ENV(X509_USER_PROXY)\n");
	    
	    outJDL.write("Output = "+OutputLogPath+"/"+line.split()[1]+".stdout\n");
	    outJDL.write("Error  = "+OutputLogPath+"/"+line.split()[1]+".stdout\n");
	    #outJDL.write("Arguments = -n "+str(samples[i][1])+" -o WWTree_"+str(samples[i][1])+" -w "+str(samples[i][0])+" -no "+ str(samples[i][2]) + " -noNeg " + str(samples[i][3]) + " -lumi "+str(lumi)+" --ismc 1 -trig 1 -c lpc\n");
	    outJDL.write("Queue\n");
	    
outJDL.close();


inputlist = "controlplotvars_UpDn.h, DibosonBoostedMuCuts13TeV_Script.txt, RunCpp.C, DibosonBoostedElMuCuts13TeV_BDT.txt"
command = "root -l -b -q RunCpp.C"

outScript = open("runstep2condor.py","w");
outScript.write('#! /usr/bin/env python');
outScript.write('\nimport os
		\nimport glob
		\nimport math
		\nfrom array import array
		\nimport sys
		\nimport time
		\nimport subprocess
		\nimport tarfile
		\nimport datetime
		\nimport commands\n');
outScript.write("\n"+'print "Starting job on ",datetime.datetime.now().strftime("%Y-%m-%d_%Hh%M")');
outScript.write("\n"+'print "Running on: "`uname -a`"');
outScript.write("\n"+'echo "System software: `cat /etc/redhat-release`"');
outScript.write("\n"+'source /cvmfs/cms.cern.ch/cmsset_default.sh');
outScript.write("\n"+'### copy the input root files if they are needed only if you require local reading');
outScript.write("\n"+'xrdcp -s root://cmseos.fnal.gov//store/user/rasharma/' + CMSSWRel +'.tgz  .');
outScript.write("\n"+'tar -xf '+ CMSSWRel +'.tgz' );
outScript.write("\n"+'rm '+ CMSSWRel +'.tgz' );
outScript.write("\n"+'cd ' + CMSSWRel + '/src/PlottingCodes/ControlPlots/' );
outScript.write("\n"+'scramv1 b ProjectRename');
outScript.write("\n"+'eval `scram runtime -sh`');
outScript.write("\n"+command);
outScript.write("\n"+'echo "====> List output files : " ');
outScript.write("\n"+'ls OutDir/');
outScript.write("\n"+'xrdcp OutDir/*  root://cmseos.fnal.gov/' + outputFolder);
outScript.write("\n"+'rm OutDir/*');
outScript.write("\n"+'cd ${_CONDOR_SCRATCH_DIR}');
outScript.write("\n"+'rm -rf ' + CMSSWRel);
outScript.write("\n");
outScript.close();
os.system("chmod 777 runstep2condor.sh");

print "===> Set Proxy Using:";
print "\tvoms-proxy-init --voms cms --valid 168:00";
print "\"condor_submit runstep2condor.jdl\" to submit";
