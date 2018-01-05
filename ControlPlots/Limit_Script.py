import os
import sys

MainRootMacro = 'myControlPlots.C'
SampleFile = 'DibosonBoostedElMuSamples13TeV.txt'
CutFile = 'DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt'
VariableFile = 'controlplotvars_CHS_Limit.h'

MCnameDict = [ "aQGC", "WV_EWK", "Z+jets", "Z+jets", "Diboson", "top", "W+jets", "QCD" , "VV"] 

CutFileDict_jes_up={"ungroomed_PuppiAK8_jet_pt"	:"ungroomed_PuppiAK8_jet_pt_jes_up",
		"ungroomed_PuppiAK8_jet_eta"	:"ungroomed_PuppiAK8_jet_eta_jes_up",
		"vbf_maxpt_j1_pt"		:"vbf_maxpt_j1_pt_jes_up",
		"vbf_maxpt_j2_pt"		:"vbf_maxpt_j2_pt_jes_up",
		"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jes_up",
		"pfMET_Corr"				:"pfMET_jes_up",
		"PuppiAK8_jet_mass_so"	:"ungroomed_PuppiAK8_jet_mass_jes_up",
		"vbf_maxpt_j2_eta"		:"vbf_maxpt_j2_eta_jes_up",
		"vbf_maxpt_j1_eta"		:"vbf_maxpt_j1_eta_jes_up",
		"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jes_up",
		"BosonCentrality_type0"		:"BosonCentrality_type0_jes_up",
		"ZeppenfeldWL_type0"		:"ZeppenfeldWL_type0_jes_up",
		"vbf_maxpt_jj_Deta"		:"vbf_maxpt_jj_Deta_jes_up",
		"ZeppenfeldWH"			:"ZeppenfeldWH_jes_up"
		}
CutFileDict_jes_dn={"ungroomed_PuppiAK8_jet_pt"	:"ungroomed_PuppiAK8_jet_pt_jes_dn",
		"ungroomed_PuppiAK8_jet_eta"	:"ungroomed_PuppiAK8_jet_eta_jes_dn",
		"vbf_maxpt_j1_pt"		:"vbf_maxpt_j1_pt_jes_dn",
		"vbf_maxpt_j2_pt"		:"vbf_maxpt_j2_pt_jes_dn",
		"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jes_dn",
		"pfMET_Corr"				:"pfMET_jes_dn",
		"PuppiAK8_jet_mass_so"	:"ungroomed_PuppiAK8_jet_mass_jes_dn",
		"vbf_maxpt_j2_eta"		:"vbf_maxpt_j2_eta_jes_dn",
		"vbf_maxpt_j1_eta"		:"vbf_maxpt_j1_eta_jes_dn",
		"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jes_dn",
		"BosonCentrality_type0"		:"BosonCentrality_type0_jes_dn",
		"ZeppenfeldWL_type0"		:"ZeppenfeldWL_type0_jes_dn",
		"vbf_maxpt_jj_Deta"		:"vbf_maxpt_jj_Deta_jes_dn",
		"ZeppenfeldWH"			:"ZeppenfeldWH_jes_dn"
		}
CutFileDict_jer_up={
		#"ungroomed_PuppiAK8_jet_pt"	:"ungroomed_PuppiAK8_jet_pt_jer_up",
		#"ungroomed_PuppiAK8_jet_eta"	:"ungroomed_PuppiAK8_jet_eta_jer_up",
		#"vbf_maxpt_j1_pt"		:"vbf_maxpt_j1_pt_jer_up",
		#"vbf_maxpt_j2_pt"		:"vbf_maxpt_j2_pt_jer_up",
		#"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jer_up",
		"pfMET_Corr"				:"pfMET_Corr_jerup",
		#"PuppiAK8_jet_mass_so"	:"ungroomed_PuppiAK8_jet_mass_jer_up",
		#"vbf_maxpt_j2_eta"		:"vbf_maxpt_j2_eta_jer_up",
		#"vbf_maxpt_j1_eta"		:"vbf_maxpt_j1_eta_jer_up",
		#"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jer_up",
		#"BosonCentrality_type0"		:"BosonCentrality_type0_jer_up",
		"ZeppenfeldWL_type0"		:"ZeppenfeldWL_type0_jer_up",
		#"ZeppenfeldWH"			:"ZeppenfeldWH_jer_up",
		#"vbf_maxpt_jj_Deta"		:"vbf_maxpt_jj_Deta_jer_up"
		}
CutFileDict_jer_dn={
		#"ungroomed_PuppiAK8_jet_pt"	:"ungroomed_PuppiAK8_jet_pt_jer_dn",
		#"ungroomed_PuppiAK8_jet_eta"	:"ungroomed_PuppiAK8_jet_eta_jer_dn",
		#"vbf_maxpt_j1_pt"		:"vbf_maxpt_j1_pt_jer_dn",
		#"vbf_maxpt_j2_pt"		:"vbf_maxpt_j2_pt_jer_dn",
		#"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jer_dn",
		"pfMET_Corr"				:"pfMET_Corr_jerdn",
		#"PuppiAK8_jet_mass_so"	:"ungroomed_PuppiAK8_jet_mass_jer_dn",
		#"vbf_maxpt_j2_eta"		:"vbf_maxpt_j2_eta_jer_dn",
		#"vbf_maxpt_j1_eta"		:"vbf_maxpt_j1_eta_jer_dn",
		#"vbf_maxpt_jj_m"		:"vbf_maxpt_jj_m_jer_dn",
		"BosonCentrality_type0"		:"BosonCentrality_type0_jer_dn",
		"ZeppenfeldWL_type0"		:"ZeppenfeldWL_type0_jer_dn",
		#"ZeppenfeldWH"			:"ZeppenfeldWH_jer_dn",
		#"vbf_maxpt_jj_Deta"		:"vbf_maxpt_jj_Deta_jer_dn"
		}

fileName = ""

for suffix in ["_CMS_scale_jUp", "_CMS_scale_jDown", "_CMS_res_metUp", "_CMS_res_metDown", "_CMS_puUp", "_CMS_puDown", "_CMS_btagHFUp", "_CMS_btagHFDown", "_CMS_btagLFUp", "_CMS_btagLFDown" ]:
	########
	#	modify the sample file
	########
	for i, var in enumerate(MCnameDict):
		if i == 0:
			command1 = "sed 's/\<"+var+"\>/"+var+suffix+"/g' "+SampleFile+ " > " + os.path.splitext(SampleFile)[0]+suffix+".txt"
			command2 = "sed 's/\<"+var+"\>/"+var+suffix+"/g' "+MainRootMacro+ " > " + os.path.splitext(MainRootMacro)[0]+suffix+".C"
		else:
			command1 = "sed -i 's/\<"+var+"\>/"+var+suffix+"/g' "+os.path.splitext(SampleFile)[0]+suffix+".txt"
			command2 = "sed -i 's/\<"+var+"\>/"+var+suffix+"/g' "+os.path.splitext(MainRootMacro)[0]+suffix+".C"
		os.system(command1)
		os.system(command2)
		fileName1 = os.path.splitext(SampleFile)[0]+suffix+".txt"
		fileName2 = os.path.splitext(SampleFile)[0]+suffix+".txt"
	os.system("sed -i 's/myControlPlots/"+os.path.splitext(MainRootMacro)[0]+suffix+"/g' "+os.path.splitext(MainRootMacro)[0]+suffix+".C")
	print "\nFile created: ",fileName1,"\t",fileName2


print "\n\n============\n\n"


###########
#	modify the cut file
###########
OutCutFileName = ["_CMS_scale_jUp", "_CMS_scale_jDown", "_CMS_res_metUp", "_CMS_res_metDown"]
countCut = 0
for cutvars in [CutFileDict_jes_up,CutFileDict_jes_dn, CutFileDict_jer_up, CutFileDict_jer_dn]:
	for i,key in enumerate(cutvars):
		#print i, key,"\t => ", cutvars[key]
		if i == 0:
			command = "sed 's/"+key+"/"+cutvars[key]+"/g' "+ CutFile + " > " + os.path.splitext(CutFile)[0]+OutCutFileName[countCut]+".txt"
		else:
			command = "sed -i 's/"+key+"/"+cutvars[key]+"/g' "+ os.path.splitext(CutFile)[0]+OutCutFileName[countCut]+".txt"
		os.system(command)
		fileName = os.path.splitext(CutFile)[0]+OutCutFileName[countCut]+".txt"
	countCut+=1
	print "\nFile created: ",fileName

print "\n\n============\n\n"
for i,suffix in enumerate(["_met_jes_up","_met_jes_dn", "_met_jer_up", "_met_jer_dn"]):
	os.system("sed 's/mass_lvj_type0/mass_lvj_type0"+suffix+"/g' " + VariableFile + " > " + "Variable"+suffix+".h")
	print "\nFile created:  Variable"+suffix+".h"

print "\n\n============\n\n"
###########
#	modify the run file
###########
print "**"*40
printVar = " Running for Nominal case "
print "*\n*","\t\t",printVar,"\n*"
print "**"*40

command = "root -l -b -q RunMacro_Limits_Templet.C"

os.system(command)
for i,suffix in enumerate(["_met_jes_up","_met_jes_dn", "_met_jer_up", "_met_jer_dn"]):
	print "\n\n","**"*40,"\n*\n","*\t\t Running for ",suffix,"\n*\n","**"*40
	os.system("cp RunMacro_Limits_Templet.C RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/controlplotvars_CHS_Limit.h/"+"Variable"+suffix+".h"+"/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/RunMacro_Limits_Templet/RunMacro_Limits_"+suffix+"/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/myControlPlots/"+os.path.splitext(MainRootMacro)[0]+OutCutFileName[i]+"/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/DibosonBoostedElMuCuts13TeV_SignalRegion_CHS.txt/"+os.path.splitext(CutFile)[0]+OutCutFileName[i]+".txt" + "/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/DibosonBoostedElMuSamples13TeV.txt/"+os.path.splitext(SampleFile)[0]+OutCutFileName[i]+".txt" + "/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/RECREATE/UPDATE/g' RunMacro_Limits_"+suffix+".C")
	os.system("sed -i 's/1)/0)/g' RunMacro_Limits_"+suffix+".C")
	os.system("root -l -b -q RunMacro_Limits_"+suffix+".C")

##################
#	for PU
##################

weights = {"pu_Weight_up":["pu_Weight","CMS_puUp"], "pu_Weight_down":["pu_Weight","CMS_puDown"], "btag0WgtUpHF*pu_Weight":["pu_Weight","CMS_btagHFUp"], "btag0WgtDownHF*pu_Weight":["pu_Weight","CMS_btagHFDown"], "btag0WgtUpLF*pu_Weight":["pu_Weight","CMS_btagLFUp"], "btag0WgtDownLF*pu_Weight":["pu_Weight","CMS_btagLFDown"]}

for i,key in enumerate(weights):
	print "\n\n","**"*40,"\n*\n","*\t\t Running for ",key,"\t",weights[key][0],"\n*\n","**"*40
	print key,weights[key][0]
	os.system("sed -i 's/"+weights[key][0]+"/"+key+"/g' "+"myControlPlots_"+weights[key][1]+".C")
	os.system("sed 's/myControlPlots/myControlPlots_"+weights[key][1]+"/g' RunMacro_Limits_Templet.C > RunMacro_Limits_Templet_"+weights[key][1]+".C")
	os.system("sed -i 's/RECREATE/UPDATE/g' RunMacro_Limits_Templet_"+weights[key][1]+".C")
	os.system("sed -i 's/RunMacro_Limits_Templet/RunMacro_Limits_Templet_"+weights[key][1]+"/g' RunMacro_Limits_Templet_"+weights[key][1]+".C")
	os.system("sed -i 's/1)/0)/g' RunMacro_Limits_Templet_"+weights[key][1]+".C")
	os.system("sed -i 's/DibosonBoostedElMuSamples13TeV.txt/DibosonBoostedElMuSamples13TeV_"+weights[key][1]+".txt/g' RunMacro_Limits_Templet_"+weights[key][1]+".C")
	os.system("root -l -b -q RunMacro_Limits_Templet_"+weights[key][1]+".C")

################
#
#	Delete all created files
#
################
for suffix in ["_CMS_scale_jUp", "_CMS_scale_jDown", "_CMS_res_metUp", "_CMS_res_metDown", "_CMS_puUp", "_CMS_puDown",  "_CMS_btagHFUp", "_CMS_btagHFDown", "_CMS_btagLFUp", "_CMS_btagLFDown" ]:
	os.system("rm "+os.path.splitext(SampleFile)[0]+suffix+".txt")
for i,name in enumerate(OutCutFileName):
	os.system("rm "+os.path.splitext(CutFile)[0]+OutCutFileName[i]+".txt")
for suffix in ["_met_jes_up","_met_jes_dn", "_met_jer_up", "_met_jer_dn"]:
	os.system("rm  Variable"+suffix+".h")
	os.system("rm RunMacro_Limits_"+suffix+".C")
for i,key in enumerate(weights):
	os.system("rm myControlPlots_"+weights[key][1]+".C")
	os.system("rm RunMacro_Limits_Templet_"+weights[key][1]+".C")
	
os.system("rm *.so *.pcm *.d")
