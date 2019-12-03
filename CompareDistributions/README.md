# How To Use


Make comparison distribution w.r.t. aQGC distribution
-----------------------------------------------------

   ```python
   python make_aQGC_plots.py -n Pure_SM.root aQGC_SM_Only.root aQGC_SM_reweight_New.root 
        --grid 
        -v Iqrk1_pt 
        --leg "SM" "SM (in NP)" "Reweighted SM)" 
        --xmin 0 --xmax 500 
        --xlabel "Leading VBF quark p_{T}" 
        --cut "" 
        -o Iqrk1_pt.png 
        --legPos "tr" 
        -t "tree" 
        --weight "" "" "SM_Weight"
   ```

In the above command the first two root files does not have any weights, while for the third we have to apply the weight named `SM_Weight`. So, we used the option named `--weight` and kept first two string as blank and third as `SM_Weight`.	

If one just wants to plot the distribution but not ratio plot then the `main()` function of `make_aQGC_plots.py` should look like
```python
def main():
    plot_info = getPlotArgs()
    print plot_info
    print "\n======= Start Makeing plots =================\n"

    plotter.CompHistFromTwoFile(plot_info)
```

if one wants to make ratio plot then one should use the function `CompHistFromTwoFileWithRatio(plot_info)` instad of `CompHistFromTwoFile(plot_info)` in the above patch.

# List of functions

## Basic Functions

## General Plotting Functions

1. CompHistFromTwoBranchSameFile
1. CompHistFromTwoFile

## aQGC specific function
1. **openRootFile**: 
2. **getaQGC_parameters**:
3. **aQGC_GetHisto**:
4. 


# To-Do

1. auto legend size
