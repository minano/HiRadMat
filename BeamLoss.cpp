#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;


void BeamLoss(){


  FILE *fp = fopen("parameters.cfg","r");
  /*
    Space for reading the configuration file using a specific class
    Default: "basic file with parameter values in one column"
   */
 
  float val[10];
 
  
  int ncol=0;
  int i = 0;
   while(1){

    ncol=fscanf(fp,"%f",&val[i]);
    if(ncol<0) break;
    i++;      
  }
   cout<<""<<endl;
   cout<<"************ - HiRadMat - ************ "<<endl;
   cout<<"Beam conditions: "<<endl;
   //cout<<"SPS: 24GeV protons"<<endl;
   cout<<" Beam intensity = "<<val[1]<<" protons per bunch"<<endl;
   cout<<" Number of Bunchs = "<<val[2]<<""<<endl;
   cout<<""<<endl;
   cout<<"Sensor dimensions: "<<endl;
   cout<<" x_DUT = "<<val[3]<<" mm"<<endl;
   cout<<" y_DUT = "<<val[4]<<" mm"<<endl;
   cout<<" z_DUT = "<<val[5]<<" um"<<endl;
   const float SiDen = 2.33; //gr/cm3
   float vol_DUT = val[3]*val[4]*val[5]/1e4;//cm3
   float mass_DUT=vol_DUT*SiDen;
   cout<<"vol_DUT = "<<vol_DUT<<" cm3"<<endl;
   cout<<" mass_DUT ="<<mass_DUT<<" gr"<<endl;


   cout<<""<<endl;
   cout<<"Testing conditions: "<<endl;
   cout<<" Beam spot = "<<val[0]<<" mm"<<endl;
   cout<<" Beam intensity = "<<val[1]<<" protons"<<" crossing the module along "<<val[5]<<" um"<<endl;
  
   float SensorArea=val[3]*val[4];//mm
   cout<<" Sensor area perpendicular to beam: "<<SensorArea<<" cm2"<<endl;
   float BeamSpotcm=1E-2*(val[0]); //cm2
   float masaKg=mass_DUT*1E-3; //Kg


   /*
     Space for calling to fluence estimation 
     Return: 1. Fluence integrated in sensor area
             2. Max instantaneous fluence on sensor
    */
   
   const float CorrFactor = 0.7; //Bethe-Bloch Mean/ Landau MPV
   const float CarriersPerMicra = 108*CorrFactor; //Si (Bethe-Bloch)
   const float eVPerMicra = 388*CorrFactor; //Si (Bethe-Bloch)
   const float eV2J= 1.60217662E-19; //eV to Joules
   const float rad=0.01; //1rad = 0.01Gy
   const float Mrad2neq = 3E13; //1Mrad = 3E13 equivalent neutrons/cm2
   const float Factor = 0.6; //proton fluence should be multiplied by this factor to get equivalent neutrons 
   
   float carriers;
   float DepositedEnergy;
   float Edep;
   float Dose; //Gy = J/Kg
   float DoseMrad;
   float Fluxp,Fluxneq;
   
   for (int i=1;i< val[2]+1;i++){
     cout<<"*******************************************************"<<endl;
     cout<<"N BUNCH: "<<i<<endl;
     carriers =  (val[5]*CarriersPerMicra)*val[1]*i;
     cout<<"***** "<<carriers<<" carriers are generated on DUT"<<" *****"<<endl;
     DepositedEnergy = (val[5]*eVPerMicra)*val[1]*i;
     cout<<"***** "<<DepositedEnergy<<" eV is deposited on DUT"<<" *****"<<endl;
     Edep = DepositedEnergy*eV2J;
     cout<<""<<endl;
     Dose = (Edep/masaKg);
     DoseMrad = (Dose/rad)/1E+6;
     cout << "ABSORBED DOSE: "<<Dose<<" Gy ("<<DoseMrad<<" Mrad)"<<endl;
     Fluxp = val[1]*i/BeamSpotcm;
     cout<<"***Flux: "<<Fluxp<<" p/cm2"<<endl;
     //Fluxneq = (Fluxp*Factor)/Mrad2neq;
     //cout<<Fluxneq<<" Mrad"<<endl;
     
  cout<<"*******************************************************"<<endl;
  }
  
}   

