<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Set-up instructions](#set-up-instructions)
- [Control Plot Instructions](#control-plot-instructions)
- [How To Run Limits](#how-to-run-limits)
- [Manual Run Code](#manual-run-code)
- [Run with scripts](#run-with-scripts)
- [Condor Job submission](#condor-job-submission)
- [Color codes](#color-codes)

<!-- /TOC -->
# Set-up instructions

	cmsrel CMSSW_9_0_1
	cd CMSSW_9_0_1/src
	git clone git@github.com:osWW-VBS/ControlPlots.git
	cd ControlPlots

* Prepare "InData" and "OutDir" directories; e.g.,

		ln -s <Path_of_InputData> InData_v2
		mkdir OutDir

* Add all signal, background and data samples in file **DibosonBoostedMuSamples13TeV.txt** (for electrons), **DibosonBoostedElSamples13TeV.txt** (for muons)

# Control Plot Instructions
There exists main three macros.

1. For control plots:`myControlPlots.C`
2. For signal background comparison
	1. Add all background together and normalize signal to number of events in background then plot: `myControlPlots_SignalBkg_Comparison.C`
	2. Normalize all background to unity and compare all using sames: `myControlPlots_SignalBkg_Comparison_Individual.C`

# How To Run Limits

* There is a script named `Limit_Script.py`. This will create a root file having all the up/down distribution for JES, JER, PU, and btag.
* This takes five input files. They are:
	1. **myControlPlots.C**
	2. **DibosonBoostedElMuSamples13TeV.txt**: Check if its the updated files.
	3. **DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt**: Cuts for signal region.
	4. **controlplotvars_CHS_Limit.h**: It contains the observable variable. By default it contains **mWW**.
	5. **RunMacro_Limits_Templet.C**: This runs the macro `myControlPlots.C`. But, it will run this default code for nominal and for rest up/downs it will copy and modify this templet then it will run.
* The script `Limit_Script.py` run all the default setting for nominal one but for rest it is just going to generate the relevent files on fly, and run it.
* After running all this at the end the script `Limit_Script.py` will delete all the files that it generated on fly.

# Manual Run Code

To run any one of them follow the following steps:

	$root -l
	[0].L myControlPlots.C+
	[1]myControlPlots("DibosonBoostedElMuCuts13TeV_WjetControlRegion_Tighter_CHS.txt", "DibosonBoostedElMuSamples13TeV_2017-11-26_OnlyCHS_BDT_limit_Trial1.txt", commonplotvars_chs , "WjetControlRegion.root", 1)
For all macro list of input arguments is as follows:
1. First argument: name of cut txt files
2. Second argument: Name of txt file contaning sample information.
3. function name that contains list of variables to plot, its available in \*.h files
4. Fourth argument : name of output root files
5. bool 0 or 1: if 1 then signal is scaled by 100 else not scaled.
6. Sixth argument (`RECREATE` or `UPDATE`): This will either append output root file or create a new one.


# Run with scripts

* There exits several `RunMacro_*.C` scripts that one should use corresponding to the purpose like wjet CR or TTbar CR or signal-background comparison, etc.
* For Example if we need W+jet control plots. We will run :
	* ` root -l -b -q RunMacro_Wjet.C`
	* Before running above command please check few input files. Like:
	 	* cut txt file
		* input variable txt file
		* input data txt file. Here you might need to modify the path.
		* if working file local files then comment this line ([link](https://github.com/osWW-VBS/PlottingCodes/blob/a0a1590b5620bdffb7f5e36ac589c8049bbf6bb3/ControlPlots/myControlPlots.C#L139)) and uncomment the line just above it.



# Condor Job submission

1. There exits a script `Submit_lpc_CondorJob.py`. Jut one need to choose the available option 0-4 for each case and run it.
2. Check option here [link](https://github.com/osWW-VBS/PlottingCodes/blob/a0a1590b5620bdffb7f5e36ac589c8049bbf6bb3/ControlPlots/Submit_lpc_CondorJob.py#L17-L19)
3. Before submitting check the corresponding, txt files if its the updated one.
4. Also, you can add or modify a new category by appropriatly modifying [this](https://github.com/osWW-VBS/PlottingCodes/blob/a0a1590b5620bdffb7f5e36ac589c8049bbf6bb3/ControlPlots/Submit_lpc_CondorJob.py#L24-L28) block.

# Color codes

https://github.com/bkargoll/TriggerStudies/blob/7d41d560bd4c554eac4b8405484e5cbfdf858106/plotting/colors.h
