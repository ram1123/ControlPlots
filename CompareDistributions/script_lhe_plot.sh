#python make_aQGC_plots.py -n ../WWAnalysisRun2/OutPutRootFile_VBFsel1.root  --grid -v AK4_DR_GENRECO_11 AK4_DR_GENRECO_12 AK4_DR_GENRECO_21 AK4_DR_GENRECO_22  --leg "DR(led - led)" "DR(led - SubLed)" "DR(SubLed - Led)" "DR(SubLed - SubLed)" --xmin 0 --xmax 10 --xlabel "#Delta R(GEN-RECO)" --cut "vbf_maxpt_jj_Deta<1.0" -o VBFsel1_GEN_RECO_DR.png --legPos "tr"
#python make_aQGC_plots.py -n /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/Pure_SM/Pure_SM.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_Only/aQGC_SM_Only.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_reweight/aQGC_SM_reweight_New.root --grid -v Iqrk1_pt --leg "SM" "SM (in NP)" "Reweighted SM)" --xmin 0 --xmax 500 --xlabel "Leading VBF quark p_{T}" --cut "" -o Iqrk1_pt.png --legPos "tr" -t "tree"
python make_aQGC_plots.py -n /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/Pure_SM/Pure_SM.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_Only/aQGC_SM_Only.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_reweight/aQGC_SM_reweight_New.root --grid -v Iqrk1_pt --leg "SM" "SM (in NP)" "Reweighted SM)" --xmin 0 --xmax 500 --xlabel "Leading VBF quark p_{T}" --cut "" -o Iqrk1_pt.png --legPos "tr" -t "tree" --weight "" "" "SM_Weight" 
python make_aQGC_plots.py -n /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/Pure_SM/Pure_SM.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_Only/aQGC_SM_Only.root /uscms_data/d3/asahmed/SM_Renormalization/genproductions/bin/MadGraph5_aMCatNLO/aQGC_SM_reweight/aQGC_SM_reweight_New.root --grid -v mWW --leg "SM" "SM (in NP)" "Reweighted SM" --xmin 0 --xmax 5000 --xlabel "Invariant mass of WW" --cut "" -o mWW.png --legPos "tr" -t "tree" --weight "" "" "SM_Weight" 