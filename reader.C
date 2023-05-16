#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
 
void hsimpleReader() {

   // Create a histogram
   auto myHist = new TH1F("h1","ntuple",500,75000,125000);
 
   // Open the file containing the tree.
   auto myFile = TFile::Open("test_ntuple.root");
   //if (!myFile || myFile->IsZombie()) {
   //   return;
   //}

   // Create a TTreeReader
   TTreeReader myReader("nominal", myFile);
 
   TTreeReaderValue<Float_t> lp0(myReader, "lep_ID_0");
   TTreeReaderValue<Float_t> lp1(myReader, "lep_ID_1");
   TTreeReaderValue<Float_t> lp2(myReader, "lep_ID_2");
   TTreeReaderValue<Float_t> lp3(myReader, "lep_ID_3");

   TTreeReaderValue<Float_t> M01(myReader, "Mll01");
   TTreeReaderValue<Float_t> M02(myReader, "Mll02");
   TTreeReaderValue<Float_t> M03(myReader, "Mll03");
   TTreeReaderValue<Float_t> M12(myReader, "Mll12");
   TTreeReaderValue<Float_t> M13(myReader, "Mll13");
   TTreeReaderValue<Float_t> M23(myReader, "Mll23");

   // Loop over all entries of the TTree
   while (myReader.Next()) {

      if( abs((*lp0)) == 13 && abs((*lp1)) == 13 ){
         if( (*lp0)*(*lp1) < 0 ){
	  if((*M01)>80000  && (*M01)<102000 ){
            myHist->Fill(*M01);
          }
         }            
      }

      if( abs((*lp0)) == 13 && abs((*lp2)) == 13 ){
         if( (*lp0)*(*lp2) < 0 ){
          if((*M02)>80000  && (*M02)<102000 ){
            myHist->Fill(*M02);
          }
         }
      }

      if( abs((*lp0)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp0)*(*lp3) < 0 ){
          if((*M03)>80000  && (*M03)<102000 ){
            myHist->Fill(*M03);
          }
         }
      }

      if( abs((*lp1)) == 13 && abs((*lp2)) == 13 ){
         if( (*lp1)*(*lp2) < 0 ){
          if((*M12)>80000  && (*M12)<102000 ){
            myHist->Fill(*M12);
          }
         }
      }

      if( abs((*lp1)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp1)*(*lp3) < 0 ){
          if((*M13)>80000  && (*M13)<102000 ){
            myHist->Fill(*M13);
          }
         }
      }

      if( abs((*lp2)) == 13 && abs((*lp3)) == 13 ){
         if( (*lp2)*(*lp3) < 0 ){
          if((*M23)>80000  && (*M23)<102000 ){
            myHist->Fill(*M23);
          }
         }
      }
   }
 
   myHist->Draw();
}
