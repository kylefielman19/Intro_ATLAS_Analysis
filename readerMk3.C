#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TLorentzVector.h"
 
void NtupleReader() {

   // Create a histogram
   auto myHist = new TH1F("h1","ntuple",300,75000,105000);
 
   // Open the file containing the tree.
   auto myFile = TFile::Open("test_ntuple.root");

   // Create a TTreeReader
   TTreeReader myReader("nominal", myFile);
 
   TTreeReaderValue<Float_t> lp0(myReader, "lep_ID_0");
   TTreeReaderValue<Float_t> lp1(myReader, "lep_ID_1");
   TTreeReaderValue<Float_t> lp2(myReader, "lep_ID_2");
   TTreeReaderValue<Float_t> lp3(myReader, "lep_ID_3");
   TTreeReaderValue<Float_t> lpID[4]{lp0, lp1, lp2, lp3}; 

   TTreeReaderValue<Float_t> lpPHI0(myReader, "lep_Phi_0");
   TTreeReaderValue<Float_t> lpPHI1(myReader, "lep_Phi_1");
   TTreeReaderValue<Float_t> lpPHI2(myReader, "lep_Phi_2");
   TTreeReaderValue<Float_t> lpPHI3(myReader, "lep_Phi_3");
   TTreeReaderValue<Float_t> lpPHI[4]{lpPHI0, lpPHI1, lpPHI2, lpPHI3}; 

   TTreeReaderValue<Float_t> lpETA0(myReader, "lep_Eta_0");
   TTreeReaderValue<Float_t> lpETA1(myReader, "lep_Eta_1");
   TTreeReaderValue<Float_t> lpETA2(myReader, "lep_Eta_2");
   TTreeReaderValue<Float_t> lpETA3(myReader, "lep_Eta_3");
   TTreeReaderValue<Float_t> lpETA[4]{lpETA0, lpETA1, lpETA2, lpETA3}; 

   TTreeReaderValue<Float_t> lpE0(myReader, "lep_E_0");
   TTreeReaderValue<Float_t> lpE1(myReader, "lep_E_1");
   TTreeReaderValue<Float_t> lpE2(myReader, "lep_E_2");
   TTreeReaderValue<Float_t> lpE3(myReader, "lep_E_3");
   TTreeReaderValue<Float_t> lpE[4]{lpE0, lpE1, lpE2, lpE3}; 

   TTreeReaderValue<Float_t> lpPT0(myReader, "lep_Pt_0");
   TTreeReaderValue<Float_t> lpPT1(myReader, "lep_Pt_1");
   TTreeReaderValue<Float_t> lpPT2(myReader, "lep_Pt_2");
   TTreeReaderValue<Float_t> lpPT3(myReader, "lep_Pt_3");
   TTreeReaderValue<Float_t> lpPT[4]{lpPT0, lpPT1, lpPT2, lpPT3}; 

   TLorentzVector v1;
   TLorentzVector v2;
 
   float pT_combined_max = 0;
   float max_mass;
   int length = 4;


   // Loop over all entries of the TTree
   while (myReader.Next()) {

      pT_combined_max = 0; 

      for (int i = 0; i < length; i++){
          for (int j = i + 1; j < length; j++){

              // Check for muon anti-muon pair
              if (abs(*lpID[i]) != 13 || abs(*lpID[j])!= 13 || (*lpID[i])*(*lpID[j]) > 0){
                  break;
              }

              // Compare Z pT
              float pT_combined = *lpPT[i] + *lpPT[j]; 
              if (pT_combined < pT_combined_max) {
                  break;
              }

              v1.SetPtEtaPhiE((*lpPT[i]), (*lpETA[i]), (*lpPHI[i]), (*lpE[i])); 
              v2.SetPtEtaPhiE((*lpPT[j]), (*lpETA[j]), (*lpPHI[j]), (*lpE[j])); 

              // Update highest Z pT and the corresponding mass
              pT_combined_max = pT_combined; 
              max_mass = (v1+v2).M(); 

          } 
      }

      if((max_mass)>80000  && (max_mass)<102000 ){
      myHist->Fill(max_mass);
      }


   }
 
   // Output invariant mass distribution
   myHist->Draw();
}
