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

TestRun = 0
OUTDIR = 'Limits'
JobName = OUTDIR+'_mww000'
CopyFiles = ['RunMacro_Limits.C', 'DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt','DibosonBoostedElMuCuts13TeV_SignalRegion_jesUP_CHS.txt', 'DibosonBoostedElMuCuts13TeV_SignalRegion_jerUP_CHS.txt', 'DibosonBoostedElMuCuts13TeV_SignalRegion_jerDOWN_CHS.txt', 'DibosonBoostedElMuCuts13TeV_SignalRegion_jesDOWN_CHS.txt', 'DibosonBoostedElMuSamples13TeV.txt', 'myControlPlots.C', 'controlplotvars_CHS.h']


# Get date and time for output directory
## ADD "test" IN OUTPUT FOLDER IF YOU ARE TESTING SO THAT LATER YOU REMEMBER TO WHICH DIRECTORY YOU HAVE TO REMOVE FROM EOS
if TestRun:
	outputFolder = "/store/user/rasharma/ThirdStep_Distributions/"+OUTDIR+'/'+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M')+"_TEST/";
	OutputLogPath = "Logs/"+JobName+'/' + datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M') + "_TEST";
else:
	outputFolder = "/store/user/rasharma/ThirdStep_Distributions/"+OUTDIR+'/'+datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M');
	OutputLogPath = "Logs/"+JobName+'/' + datetime.datetime.now().strftime('%Y_%m_%d_%Hh%M');


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
make_tarfile(CMSSWRel+".tgz", cmsswDirPath[1])

# send the created tarball to eos
os.system('xrdcp -f ' + CMSSWRel+".tgz" + ' root://cmseos.fnal.gov/'+outputFolder+"/" + CMSSWRel+".tgz")

os.system('git diff myControlPlots.C > git_diff.patch')
os.system('git diff DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt >> git_diff.patch')
os.system('git diff controlplotvars_CHS_Limit.h >> git_diff.patch')
os.system('git diff RunMacro_Limits_Templet.C >> git_diff.patch')
os.system('git diff DibosonBoostedElMuSamples13TeV.txt >> git_diff.patch')

os.system('xrdcp -f git_diff.patch root://cmseos.fnal.gov/'+outputFolder+'/git_diff.patch')

outJDL = open("runstep2condor.jdl","w");


outJDL.write("Executable = runstep2condor.sh\n");
outJDL.write("Universe = vanilla\n");
#outJDL.write("Requirements =FileSystemDomain==\"fnal.gov\" && Arch==\"X86_64\"");
outJDL.write("Notification = ERROR\n");
outJDL.write("Should_Transfer_Files = YES\n");
outJDL.write("WhenToTransferOutput = ON_EXIT\n");
#outJDL.write("include : list-infiles.sh |\n");
#outJDL.write("Transfer_Input_Files = "+inputlist+"\n");
outJDL.write("x509userproxy = $ENV(X509_USER_PROXY)\n");

outJDL.write("Output = "+OutputLogPath+"/"+JobName+".stdout\n");
outJDL.write("Error  = "+OutputLogPath+"/"+JobName+".stdout\n");
outJDL.write("Queue\n");
	    
outJDL.close();


command = "python Limit_Script.py"

outScript = open("runstep2condor.sh","w");
outScript.write('#!/bin/bash');
outScript.write("\n"+'echo "Starting job on " `date`');
outScript.write("\n"+'echo "Running on: `uname -a`"');
outScript.write("\n"+'echo "System software: `cat /etc/redhat-release`"');
outScript.write("\n"+'source /cvmfs/cms.cern.ch/cmsset_default.sh');
outScript.write("\n"+'### copy the input root files if they are needed only if you require local reading');
outScript.write("\n"+'xrdcp -f root://cmseos.fnal.gov/'+outputFolder+"/" + CMSSWRel+".tgz  .");
outScript.write("\n"+'tar -xf '+ CMSSWRel +'.tgz' );
outScript.write("\n"+'rm '+ CMSSWRel +'.tgz' );
outScript.write("\n"+'cd ' + CMSSWRel + '/src/PlottingCodes/ControlPlots' );
outScript.write("\n"+'echo "====> PWD: " ');
outScript.write("\n"+'pwd');
outScript.write("\n"+'echo "====> List files : " ');
outScript.write("\n"+'ls'); 
outScript.write("\n"+'rm OutDir/*');
outScript.write("\n"+'echo "============================================" ');
outScript.write("\n"+'echo "====> List output files : " ');
outScript.write("\n"+'ls OutDir/');
outScript.write("\n"+'echo "============================================" ');
outScript.write("\n"+'scramv1 b ProjectRename');
outScript.write("\n"+'eval `scram runtime -sh`');
outScript.write("\n"+command);
outScript.write("\n"+'echo "====> List output files : " ');
outScript.write("\n"+'ls OutDir/');
outScript.write("\n"+'echo "xrdcp output for condor"');
outScript.write("\n"+'xrdcp -f combine_limit.root root://cmseos.fnal.gov/'+outputFolder+'/');
outScript.write("\n"+'for FILE in OutDir/*');
outScript.write("\n"+'do');
outScript.write("\n"+'\techo "xrdcp -r -f ${FILE} root://cmseos.fnal.gov/'+outputFolder+'/"');
outScript.write("\n"+'\txrdcp -r -f ${FILE} root://cmseos.fnal.gov/'+outputFolder+'/ 2>&1');
outScript.write("\n"+'done');
for files in CopyFiles:
	outScript.write("\n"+'xrdcp -f '+files+'  root://cmseos.fnal.gov/'+outputFolder+'/');
outScript.write("\n"+'cd ${_CONDOR_SCRATCH_DIR}');
outScript.write("\n"+'rm -rf ' + CMSSWRel);
outScript.write("\n");
outScript.close();
os.system("chmod 777 runstep2condor.sh");

print "===> Set Proxy Using:";
print "\tvoms-proxy-init --voms cms --valid 168:00";
print "\"condor_submit runstep2condor.jdl\" to submit";
os.system("condor_submit runstep2condor.jdl")
