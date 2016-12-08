#!/bin/bash/

selstep=""
variable=""
lumi=""

if [[ "X$1" == "X" ]]; then echo "Provide selection step!"; exit; fi
selstep="$1"; shift;
if [[ "X$1" == "X" ]]; then echo "Provide variables to use for shape analyis!"; exit; fi
variable="$1"; shift;
echo "Will do postfit plots for ${variable}"
if [[ "X$1" == "X" ]]; then echo "Provide luminosity!"; exit; fi
lumi="$1"; shift;
echo "MC components will be normalized to ${lumi}/fb"

# if no data in SR (because you are blinding) keep SR line commented

# SR
#python postFitPlots.py vbfdm/mca-80X-sync.txt templates/SR/${selstep}/plots.root ${variable} templates/cards/${selstep}/${variable}/125.0/mlfit.root SR ${lumi}
# ZM CR
python postFitPlots.py vbfdm/mca-80X-muonCR.txt templates/ZMCR/${selstep}/plots.root ${variable} templates/cards/${selstep}/${variable}/125.0/mlfit.root ZM ${lumi}
# WM
python postFitPlots.py vbfdm/mca-80X-muonCR.txt templates/WMCR/${selstep}/plots.root ${variable} templates/cards/${selstep}/${variable}/125.0/mlfit.root WM ${lumi}
# ZE CR
python postFitPlots.py vbfdm/mca-80X-electronCR.txt templates/ZECR/${selstep}/plots.root ${variable} templates/cards/${selstep}/${variable}/125.0/mlfit.root ZE ${lumi}
# WE CR
python postFitPlots.py vbfdm/mca-80X-electronCR.txt templates/WECR/${selstep}/plots.root ${variable} templates/cards/${selstep}/${variable}/125.0/mlfit.root WE ${lumi}
