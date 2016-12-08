#! /bin/bash

uptothiscut="deta2j"
var4shape="detajj_fullsel"
lumi="24.5"
var="detajj"
#fitdir="mjj_mjj1000_deta3p0_dphijm2p0"
storeDir="VBF_shape_study_24p5fb"         # name of directory containing all the tests you would do. You can specify the luminosity used in the name
fitdir="detajj_mjj1000_deta3p0_dphijm2p0"   # name of dir that contains the output
other_options=""  # "1bin" for cut and count ike test, otherwise keep empty for shape analysis with many bins
combinedir="/afs/cern.ch/work/m/mciprian/combine/CMSSW_7_4_7/src/HiggsAnalysis/CombinedLimit/myTest/${storeDir}/${fitdir}"  # dir where you run combine
plotterDirPath="/afs/cern.ch/work/m/mciprian/monoJet_new/CMSSW_8_0_19/src/CMGTools/MonoXAnalysis/python/plotter"

test -d templates/ && rm -r templates/

vbfdm/analysis.py --fullControlRegions --pdir templates/ -U ${uptothiscut} -l ${lumi}
vbfdm/analysis.py --propSystToVar ${var4shape} -U ${uptothiscut} -l ${lumi}
vbfdm/analysis.py --tF ${var4shape} -U ${uptothiscut} -l ${lumi}

source vbfdm/make_cards.sh templates/cards ${lumi} ${uptothiscut} ${var} all ${other_options}

cd ${plotterDirPath}/templates/cards/${uptothiscut}/${var4shape}/125.0/
combineCards.py SR=vbfdm.card.txt ZM=zmumu.card.txt ZE=zee.card.txt WM=wmunu.card.txt WE=wenu.card.txt > comb.card.txt

mkdir -p ${combinedir}
cp ${plotterDirPath}/templates/cards/${uptothiscut}/${var4shape}/125.0/* ${combinedir}/

cd ${combinedir}
eval `scramv1 runtime -sh`
combine -M Asymptotic comb.card.txt --run expected > log_combine.txt 2>&1 # probably not all the output will be put in the file, don't know why
# appending more info in file doesn't work, still trying to understand it. For now, just put the output for limit (previous command)
#echo " " >> log_combine.txt 2>&1
#echo " " >> log_combine.txt 2>&1
combine -M MaxLikelihoodFit --saveNormalizations --saveShapes --saveWithUncertainties comb.card.txt #>> log_combine.txt 2>&1

cp ${combinedir}/* ${plotterDirPath}/templates/cards/${uptothiscut}/${var4shape}/125.0/

cd  ${plotterDirPath}/
eval `scramv1 runtime -sh`
source doAllRegionPostFit.sh ${uptothiscut} ${var4shape} ${lumi}

mkdir -p ${HOME}/www/vbfHiggsToInv/80X/heppy/${storeDir}/${fitdir}/
cp -r templates/ ${HOME}/www/vbfHiggsToInv/80X/heppy/${storeDir}/${fitdir}/