#include <cmath>
#include "TH2F.h"
#include "Math/GenVector/LorentzVector.h"
#include "Math/GenVector/PtEtaPhiM4D.h"

//// UTILITY FUNCTIONS NOT IN TFORMULA ALREADY

float deltaPhi(float phi1, float phi2) {
    float result = phi1 - phi2;
    while (result > float(M_PI)) result -= float(2*M_PI);
    while (result <= -float(M_PI)) result += float(2*M_PI);
    return result;
}

float if3(bool cond, float iftrue, float iffalse) {
    return cond ? iftrue : iffalse;
}

float deltaR2(float eta1, float phi1, float eta2, float phi2) {
    float deta = std::abs(eta1-eta2);
    float dphi = deltaPhi(phi1,phi2);
    return deta*deta + dphi*dphi;
}
float deltaR(float eta1, float phi1, float eta2, float phi2) {
    return std::sqrt(deltaR2(eta1,phi1,eta2,phi2));
}

float pt_2(float pt1, float phi1, float pt2, float phi2) {
    phi2 -= phi1;
    return hypot(pt1 + pt2 * std::cos(phi2), pt2*std::sin(phi2));
}

float mt_2(float pt1, float phi1, float pt2, float phi2) {
    return std::sqrt(2*pt1*pt2*(1-std::cos(phi1-phi2)));
}

float mass_2_ene(float ene1, float eta1, float phi1, float m1, float ene2, float eta2, float phi2, float m2) {
    typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMVector;
    PtEtaPhiMVector unitp41(1.0,eta1,phi1,m1);
    PtEtaPhiMVector unitp42(1.0,eta2,phi2,m2);
    double theta1 = unitp41.Theta();
    double theta2 = unitp42.Theta();
    double pt1 = ene1*fabs(sin(theta1));
    double pt2 = ene2*fabs(sin(theta2));
    PtEtaPhiMVector p41(pt1,eta1,phi1,m1);
    PtEtaPhiMVector p42(pt2,eta2,phi2,m2);
    return (p41+p42).M();
}

float mass_2(float pt1, float eta1, float phi1, float m1, float pt2, float eta2, float phi2, float m2) {
    typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMVector;
    PtEtaPhiMVector p41(pt1,eta1,phi1,m1);
    PtEtaPhiMVector p42(pt2,eta2,phi2,m2);
    return (p41+p42).M();
}

float pt_3(float pt1, float phi1, float pt2, float phi2, float pt3, float phi3) {
    phi2 -= phi1;
    phi3 -= phi1;
    return hypot(pt1 + pt2 * std::cos(phi2) + pt3 * std::cos(phi3), pt2*std::sin(phi2) + pt3*std::sin(phi3));
}

float mass_3(float pt1, float eta1, float phi1, float m1, float pt2, float eta2, float phi2, float m2, float pt3, float eta3, float phi3, float m3) {
    typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMVector;
    PtEtaPhiMVector p41(pt1,eta1,phi1,m1);
    PtEtaPhiMVector p42(pt2,eta2,phi2,m2);
    PtEtaPhiMVector p43(pt3,eta3,phi3,m3);
    return (p41+p42+p43).M();
}

float pt_4(float pt1, float phi1, float pt2, float phi2, float pt3, float phi3, float pt4, float phi4) {
    phi2 -= phi1;
    phi3 -= phi1;
    phi4 -= phi1;
    return hypot(pt1 + pt2 * std::cos(phi2) + pt3 * std::cos(phi3) + pt4 * std::cos(phi4), pt2*std::sin(phi2) + pt3*std::sin(phi3) + pt4*std::sin(phi4));
}
 
float mass_4(float pt1, float eta1, float phi1, float m1, float pt2, float eta2, float phi2, float m2, float pt3, float eta3, float phi3, float m3, float pt4, float eta4, float phi4, float m4) {
    typedef ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double> > PtEtaPhiMVector;
    PtEtaPhiMVector p41(pt1,eta1,phi1,m1);
    PtEtaPhiMVector p42(pt2,eta2,phi2,m2);
    PtEtaPhiMVector p43(pt3,eta3,phi3,m3);
    PtEtaPhiMVector p44(pt4,eta4,phi4,m4);
    return (p41+p42+p43+p44).M();
}

float mt_llv(float ptl1, float phil1, float ptl2, float phil2, float ptv, float phiv) {
    float px = ptl1*std::cos(phil1) + ptl2*std::cos(phil2) + ptv*std::cos(phiv);
    float py = ptl1*std::sin(phil1) + ptl2*std::sin(phil2) + ptv*std::sin(phiv);
    float ht = ptl1+ptl2+ptv;
    return std::sqrt(std::max(0.f, ht*ht - px*px - py*py));
}

float mt_lllv(float ptl1, float phil1, float ptl2, float phil2, float ptl3, float phil3, float ptv, float phiv) {
    float px = ptl1*std::cos(phil1) + ptl2*std::cos(phil2) + ptl3*std::cos(phil3) + ptv*std::cos(phiv);
    float py = ptl1*std::sin(phil1) + ptl2*std::sin(phil2) + ptl3*std::sin(phil3) + ptv*std::sin(phiv);
    float ht = ptl1+ptl2+ptl3+ptv;
    return std::sqrt(std::max(0.f, ht*ht - px*px - py*py));
}


float mtw_wz3l(float pt1, float eta1, float phi1, float m1, float pt2, float eta2, float phi2, float m2, float pt3, float eta3, float phi3, float m3, float mZ1, float met, float metphi) 
{
    if (abs(mZ1 - mass_2(pt1,eta1,phi1,m1,pt2,eta2,phi2,m2)) < 0.01) return mt_2(pt3,phi3,met,metphi);
    if (abs(mZ1 - mass_2(pt1,eta1,phi1,m1,pt3,eta3,phi3,m3)) < 0.01) return mt_2(pt2,phi2,met,metphi);
    if (abs(mZ1 - mass_2(pt2,eta2,phi2,m2,pt3,eta3,phi3,m3)) < 0.01) return mt_2(pt1,phi1,met,metphi);
    return 0;
}

float u1_2(float met_pt, float met_phi, float ref_pt, float ref_phi) 
{
    float met_px = met_pt*std::cos(met_phi), met_py = met_pt*std::sin(met_phi);
    float ref_px = ref_pt*std::cos(ref_phi), ref_py = ref_pt*std::sin(ref_phi);
    float ux = - met_px + ref_px, uy = - met_px + ref_px;
    return (ux*ref_px + uy*ref_py)/ref_pt;
}
float u2_2(float met_pt, float met_phi, float ref_pt, float ref_phi)
{
    float met_px = met_pt*std::cos(met_phi), met_py = met_pt*std::sin(met_phi);
    float ref_px = ref_pt*std::cos(ref_phi), ref_py = ref_pt*std::sin(ref_phi);
    float ux = - met_px + ref_px, uy = - met_px + ref_px;
    return (ux*ref_py - uy*ref_px)/ref_pt;
}

int monojetIDcentralJet(float jetClean_leadClean, float jetClean_eta)
{

  // if jet is central, apply monojet ID requiring jetClean_leadClean (which is 1 or 0 depending on the jet to pass the ID)
  // if jet is not central, this selection is not applied and condition is always considered true (that is 1)
  // this condition is tipically applied on the leading jet

  // WARNING: jetClean_leadClean is a float, but it should be a flag, so better to cast it to int after summing 0.5
  // e.g. if 1 in float is read as 0.9999999...., then when casting the flag could be converted to 0, so add 0.5 and (int) 1.4999999 will be 1

  if (abs(jetClean_eta) < 2.5) return ((int) (jetClean_leadClean + 0.5));
  else return 1;

}

int lepTightIdAndPt(float nLepT, float lep1_pt, int lep1_tightID, float lep2_pt, int lep2_tightID, float pT_threshold, int absLepPdgId)
{

  // when using nMu20T and nEle40T in Z(ll), if there is only 1 tightID lepton it is not guaranteed that the tight one is that with highest pT.
  // this function manage the possible cases, so it basically returns -->  (lep1_isTight and pT1> XXX) || lep2_isTight and pT2 > XXX)
  // usually the requirement on the number of tight leptons from the Z is used together with nMu10V or nEle10V = 2.
  //Therefore,  only the case nTightLeptons = 1 or 2 are considered

  // this function as it is can be useful only when you have to require, e.g., nEle40T > X and pT(lead e) > Y, con y != 40

  int NlepT = (int) (nLepT + 0.5); 

  if (NlepT == 1) {

    if      (absLepPdgId == 11) return ( (lep1_tightID >= 3 && lep1_pt > pT_threshold) || (lep2_tightID >= 3 && lep2_pt > pT_threshold) );
    else if (absLepPdgId == 13) return ( (lep1_tightID >= 1 && lep1_pt > pT_threshold) || (lep2_tightID >= 1 && lep2_pt > pT_threshold) );
    else                        return 0;   // in case the pdgId is wrong

  } else if (NlepT == 2) {

    return (lep1_pt > pT_threshold || lep2_pt > pT_threshold);

  } else return 0;

}

float minDphi_jetsMet_withNjets(int nJet, int nJetToUse, float &jetPhiArrayFirstElement, float metPhi)
{
  //================================
  // WARNING
  //
  // at the moment the function doesn't work inside a txt cut file, it looks like I cannot pass the pointer to the collection
  // also passing the first element as a reference and getting the address of location doesn't work
  // following issue is raised
  // Error in <TTreeFormula::Compile>:  Bad numerical expression : "minDphi_jetsMet_withNjets(nJetClean,50,JetClean_phi[0],metNoMu_phi)"
  //================================


  // this function computes and returns the minimum deltaPhi between met and the first jets
  // nJet is the dimension of the collection of jets to use for computation
  // nJetToUse sets how many jets to use (no more than nJet)
  // jetPhiArray is the list of phi for the jets collection, taken from the pointer to first element location
  // metPhi is the phi for met (can use any met)

  float minDphi = 999;
  float* jetPhiArray = &jetPhiArrayFirstElement;

  if (nJet <= nJetToUse) nJetToUse = nJet;
  
  for (int i = 0; i < nJetToUse; i++) {
    float tmp_dphi = fabs(deltaPhi(jetPhiArray[i],metPhi));
    minDphi = (minDphi <= tmp_dphi) ? minDphi : tmp_dphi;
  }
  
  return fabs(minDphi);  // this value is already in [0, Pi] by definition, but in this way it is clearer

}

int goodJetCleanNHF_eta3to3p2(float jetclean1_eta, float jetclean1_phi, float jetFwd1_nhef, float jetFwd1_eta, float jetFwd1_phi, float jetFwd2_nhef, float jetFwd2_eta, float jetFwd2_phi)
{

  // to be fixed

  // check if jet is forward (eta > 2.5, we need 3.0 < eta < 3.2)
  // if yes, then JetClean belongs to JetFwd collection and JetFwd1 should coincides with JetClean1
  // actually JetFwd1 might not be a clean jet. We pass the leading 2 forward jet and make a match using DeltaR
  // if neither JetFwd are matched, return 1 (function returns a flag used to apply a cut, so 1 means that cut is irrelevant)

  if (std::abs(jetclean1_eta) > 3.0 && std::abs(jetclean1_eta) < 3.2) {
    if (deltaR(jetclean1_eta, jetclean1_phi, jetFwd1_eta, jetFwd1_phi) < 0.1 ) return (jetFwd1_nhef < 0.96);
    else if (deltaR(jetclean1_eta, jetclean1_phi, jetFwd2_eta, jetFwd2_phi) < 0.1 ) return (jetFwd2_nhef < 0.96);
    else return 1;
  } else {
    return 1;
  }

}

float vbfdm_2Dto1D(float mjj, float detajj) {
  float bins_mjj[6] = {0,750,1100,2000,3000,7000};
  float bins_detajj[4] = {0,3,5,20};
  
  TH2F binning("binning_2D","",5,bins_mjj,3,bins_detajj);
  if (detajj<bins_detajj[1] && mjj>bins_mjj[2]) return 3;
  else if (detajj>bins_detajj[1] && detajj<bins_detajj[2] && mjj>bins_mjj[4]) return 7;
  else if (detajj>bins_detajj[2] && mjj<bins_mjj[3]) return 8;
  else return binning.GetNbinsX()*(binning.GetYaxis()->FindBin(detajj)-1) + binning.GetXaxis()->FindBin(mjj) - 2*(detajj>bins_detajj[1] && detajj<bins_detajj[2]) - 5*(detajj>bins_detajj[2]);
}


float mt_lu_cart(float lep_pt, float lep_phi, float u_x, float u_y)
{
  float lep_px = lep_pt*std::cos(lep_phi), lep_py = lep_pt*std::sin(lep_phi);
  float u = hypot(u_x,u_y);
  float uDotLep = u_x*lep_px + u_y*lep_py;
  return sqrt(2*lep_pt*sqrt(u*u+lep_pt*lep_pt+2*uDotLep) + 2*uDotLep + 2*lep_pt*lep_pt);
}

float Hypot(float x, float y) {
  return hypot(x,y);
}


// float ptZfromLeptons(float pt1, float eta1, float phi1, float mass1, float pt2, float eta2, float phi2, float mass2) {

  

// }

void functions() {}
