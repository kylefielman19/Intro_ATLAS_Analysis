#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TLorentzVector.h"
 
void hsimpleReader() {

   // Create a histogram
   auto myHist = new TH1F("h1","ntuple",500,75000,125000);
 
   // Open the file containing the tree.
   auto myFile = TFile::Open("test_ntuple.root");

   // Create a TTreeReader
   TTreeReader myReader("nominal", myFile);
 
   TTreeReaderValue<Float_t> lp0(myReader, "lep_ID_0");
   TTreeReaderValue<Float_t> lp1(myReader, "lep_ID_1");
   TTreeReaderValue<Float_t> lp2(myReader, "lep_ID_2");
   TTreeReaderValue<Float_t> lp3(myReader, "lep_ID_3");

   TTreeReaderValue<Float_t> lpPHI0(myReader, "lep_Phi_0");
   TTreeReaderValue<Float_t> lpPHI1(myReader, "lep_Phi_1");
   TTreeReaderValue<Float_t> lpPHI2(myReader, "lep_Phi_2");
   TTreeReaderValue<Float_t> lpPHI3(myReader, "lep_Phi_3");

   TTreeReaderValue<Float_t> lpETA0(myReader, "lep_Eta_0");
   TTreeReaderValue<Float_t> lpETA1(myReader, "lep_Eta_1");
   TTreeReaderValue<Float_t> lpETA2(myReader, "lep_Eta_2");
   TTreeReaderValue<Float_t> lpETA3(myReader, "lep_Eta_3");

   TTreeReaderValue<Float_t> lpE0(myReader, "lep_E_0");
   TTreeReaderValue<Float_t> lpE1(myReader, "lep_E_1");
   TTreeReaderValue<Float_t> lpE2(myReader, "lep_E_2");
   TTreeReaderValue<Float_t> lpE3(myReader, "lep_E_3");

   TTreeReaderValue<Float_t> lpPT0(myReader, "lep_Pt_0");
   TTreeReaderValue<Float_t> lpPT1(myReader, "lep_Pt_1");
   TTreeReaderValue<Float_t> lpPT2(myReader, "lep_Pt_2");
   TTreeReaderValue<Float_t> lpPT3(myReader, "lep_Pt_3");

   TLorentzVector Lead;
   TLorentzVector SubLead;

   float M01, M02, M03, M12, M13, M23;

   // Loop over all entries of the TTree
   while (myReader.Next()) {

      if( abs((*lp0)) == 13 && abs((*lp1)) == 13 ){
         if( (*lp0)*(*lp1) < 0 ){
	    Lead.SetPtEtaPhiE((*lpPT0),(*lpETA0),(*lpPHI0),(*lpE0));	
            SubLead.SetPtEtaPhiE((*lpPT1),(*lpETA1),(*lpPHI1),(*lpE1));

	    M01 = (Lead+SubLead).M();
	    if((M01)>80000  && (M01)<102000 ){
               myHist->Fill(M01);
          }
         }            
      }

      if( abs((*lp0)) == 13 && abs((*lp2)) == 13 ){
         if( (*lp0)*(*lp2) < 0 ){
            Lead.SetPtEtaPhiE((*lpPT0),(*lpETA0),(*lpPHI0),(*lpE0));
            SubLead.SetPtEtaPhiE((*lpPT2),(*lpETA2),(*lpPHI2),(*lpE2));
   
            M02 = (Lead+SubLead).M();
            if((M02)>80000  && (M02)<102000 ){
               myHist->Fill(M02);
          }
         }
      }

      if( abs((*lp0)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp0)*(*lp3) < 0 ){
            Lead.SetPtEtaPhiE((*lpPT0),(*lpETA0),(*lpPHI0),(*lpE0));
            SubLead.SetPtEtaPhiE((*lpPT3),(*lpETA3),(*lpPHI3),(*lpE3));
   
            M03 = (Lead+SubLead).M();
            if((M03)>80000  && (M03)<102000 ){
               myHist->Fill(M03);
          }
         }
      }

      if( abs((*lp1)) == 13 && abs((*lp2)) == 13 ){
         if( (*lp1)*(*lp2) < 0 ){
            Lead.SetPtEtaPhiE((*lpPT1),(*lpETA1),(*lpPHI1),(*lpE1));
            SubLead.SetPtEtaPhiE((*lpPT2),(*lpETA2),(*lpPHI2),(*lpE2));
   
            M12 = (Lead+SubLead).M();
            if((M12)>80000  && (M12)<102000 ){
               myHist->Fill(M12);
          }
         }
      }

      if( abs((*lp1)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp1)*(*lp3) < 0 ){
            Lead.SetPtEtaPhiE((*lpPT1),(*lpETA1),(*lpPHI1),(*lpE1));
            SubLead.SetPtEtaPhiE((*lpPT3),(*lpETA3),(*lpPHI3),(*lpE3));
   
            M13 = (Lead+SubLead).M();
            if((M13)>80000  && (M13)<102000 ){
               myHist->Fill(M13);
          }
         }
      }

      if( abs((*lp2)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp2)*(*lp3) < 0 ){
            Lead.SetPtEtaPhiE((*lpPT2),(*lpETA2),(*lpPHI2),(*lpE2));
            SubLead.SetPtEtaPhiE((*lpPT3),(*lpETA3),(*lpPHI3),(*lpE3));
   
            M23 = (Lead+SubLead).M();
            if((M23)>80000  && (M23)<102000 ){
               myHist->Fill(M23);
          }
         }
      }
   }
 
   // Output invariant mass distribution
   myHist->Draw();
}
