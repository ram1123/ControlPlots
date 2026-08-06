import ROOT

# Open the ROOT file
file = ROOT.TFile.Open("ge1jet_muon_10_10_new.root")

# Define the histogram names
histogram_names = ["data;1", "DYJets;1", "Top;1", "Triboson;1", "WJets;1", "Dibosons;1"]
entries = {}

# Define the x-axis value of interest
x_value = 9

# Loop through each histogram
for name in histogram_names:
    hist = file.Get(name)
    
    # Find the bin for the specified x value
    bin_index = hist.FindBin(x_value)
    entry = hist.GetBinContent(bin_index)

    print(f"Entries for histogram '{name}' at x = {x_value}: {entry}")

    #entries[name] = entry

    #ratio = entries["data;1"] / (entries["DYJets;1"] + entries["DYJets;1"] + entries["DYJets;1"] + entries["DYJets;1"] + entries["DYJets;1"])
    #print(f"Ratio (data / DYJets) at x = {x_value}: {ratio}")
