#include <Wire.h>
#include "Adafruit_TCS34725.h"

int CoAbs(int x)
{
  if (x<0)
  {
    x = -x;
  }
  return x;
}

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
int time = 2.4;
int gain = 1;
Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
//Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) { 
  Serial.begin(9600);
   Serial.println("Color Sensor v0.4");
   Serial.println(tcs.begin());
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
  
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
   //colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  //Standard Color Settings
  int RedRGB[] = {3, 62, 25, 25, 110};
  int BlueRGB[] = {15, 20, 48, 74, 145};
  int GreenRGB[] = {38, 21, 55, 25, 88};
  int WhiteRGB[] = {108, 140, 165, 145, 459};
  int BlackRGB[] = {9, 12, 14, 12, 38};
  int BrownRGB[] = {24, 44, 37, 27, 109};
  int GrayRGB[] = {47, 53, 77, 72, 211};
  int PinkRGB[] = {9, 115, 61, 67, 242};
  int OrangeRGB[] = {64, 118, 77, 52, 249};
  int YellowRGB[] = {103, 125, 141, 71, 341};
  int PurpleRGB[] = {6, 37, 28, 30, 94};

  //Color Proximity to Standards Variables
  int CRL,CRR,CRG,CRB,CRC,CRT;

  int CBL,CBR,CBG,CBB,CBC,CBT;

  int CPL,CPR,CPG,CPB,CPC,CPT;

  int CGL,CGR,CGG,CGB,CGC,CGT;

  int CBrL,CBrR,CBrG,CBrB,CBrC,CBrT;

  int COL,COR,COG,COB,COC,COT;

  int CYL,CYR,CYG,CYB,CYC,CYT;

  int CWL,CWR,CWG,CWB,CWC,CWT;

  int CPiL,CPiR,CPiG,CPiB,CPiC,CPiT;

  int CGrL,CGrR,CGrG,CGrB,CGrC,CGrT;

  //Check if Color is Already Detected to Not Repeat Output Variables
  bool Bla = false;
  bool Pur = false;
  bool Blu = false;
  bool Bro = false;
  bool Gre = false;
  bool Gra = false;
  bool Yel = false;
  bool Red = false;
  bool Pin = false;
  bool Ora = false;
  bool Whi = false;

  //Black Color Range
  if (r <= 13 && g <= 14 && b <= 13 && c <= 40 && lux <= 10)
  {
    //Serial.print("Black//");
    Serial.println("Black Color Detected");
    Bla = true;
  }

  //Blue Color Range
   if (r >= 5 && r <= 29 && g >= 9 && g <= 59 && b >= 14 && b <= 100 && c >= 28 && lux >= 2 && lux <= 19 && Bla == false)
  {
    //Serial.print("Blue//");
     //Get Blue Color Proximity to Blue
     CBR = CoAbs(BlueRGB[1] - r);
     CBG = CoAbs(BlueRGB[2] - g);
     CBB = CoAbs(BlueRGB[3] - b);
     CBC = CoAbs(BlueRGB[4] - c);

     CBT = CBR + CBG + CBB + CBC - 15;

     //Get Purple Color Proximity to Blue
     CPR = CoAbs(PurpleRGB[1] - r);
     CPG = CoAbs(PurpleRGB[2] - g);
     CPB = CoAbs(PurpleRGB[3] - b);
     CPC = CoAbs(PurpleRGB[4] - c);

     CPT = CPR + CPG + CPB + CPC + 24;

     //Get Green Color Proximity to Blue
     CGR = CoAbs(GreenRGB[1] - r);
     CGG = CoAbs(GreenRGB[2] - g);
     CGB = CoAbs(GreenRGB[3] - b);
     CGC = CoAbs(GreenRGB[4] - c);

     CGT = CGR + CGG + CGB + CGC + 20;

     //Check to see if the color is Blue
     if(CBT < CPT && CBT < CGT)
     {
       Serial.println("Blue Color Detected");
       Blu = true;
     }

     //Check to see if the color is Purple
     if(CPT < CBT && CPT < CGT)
     {
       Serial.println("Purple Color Detected");
       Pur = true;
     }

     //Check to see if the color is Green
     if(CGT < CPT && CGT < CBT)
     {
       Serial.println("Green Color Detected");
       Gre = true;
     }
  }

  //Red Color Range
  if (r >= 30 && r <= 100 && g >= 8 && g <= 41 && b >= 8 && b <= 37 && c >= 50 && c <= 166 && lux <= 8
  && Bla == false && Pur == false && Blu == false)
  {
    //Serial.println("Red//");
    //Get Orange Color Proximity to Red
     COR = CoAbs(OrangeRGB[1] - r);
     COG = CoAbs(OrangeRGB[2] - g);
     COB = CoAbs(OrangeRGB[3] - b);
     COC = CoAbs(OrangeRGB[4] - c);

     COT = COR + COG + COB + COC + 5;

     //Get Blue Color Proximity to Red
     CBR = CoAbs(BlueRGB[1] - r);
     CBG = CoAbs(BlueRGB[2] - g);
     CBB = CoAbs(BlueRGB[3] - b);
     CBC = CoAbs(BlueRGB[4] - c);

     CBT = CBR + CBG + CBB + CBC + 10;

     //Get Red Color Proximity to Red
     CRR = CoAbs(RedRGB[1] - r);
     CRG = CoAbs(RedRGB[2] - g);
     CRB = CoAbs(RedRGB[3] - b);
     CRC = CoAbs(RedRGB[4] - c);

     CRT = CRR + CRG + CRB + CRC - 15;

     //Get Purple Color Proximity to Red
     CPR = CoAbs(PurpleRGB[1] - r);
     CPG = CoAbs(PurpleRGB[2] - g);
     CPB = CoAbs(PurpleRGB[3] - b);
     CPC = CoAbs(PurpleRGB[4] - c);

     CPT = CPR + CPG + CPB + CPC + 15;

     //Get Green Color Proximity to Red
     CGR = CoAbs(GreenRGB[1] - r);
     CGG = CoAbs(GreenRGB[2] - g);
     CGB = CoAbs(GreenRGB[3] - b);
     CGC = CoAbs(GreenRGB[4] - c);

     CGT = CGR + CGG + CGB + CGC + 20;

     //Get Brown Color Proximity to Red
     CBrR = CoAbs(BrownRGB[1] - r);
     CBrG = CoAbs(BrownRGB[2] - g);
     CBrB = CoAbs(BrownRGB[3] - b);
     CBrC = CoAbs(BrownRGB[4] - c);

     CBrT = CBrR + CBrG + CBrB + CBrC + 25;

     //Get Pink Color Proximity to Red
     CPiR = CoAbs(PinkRGB[1] - r);
     CPiG = CoAbs(PinkRGB[2] - g);
     CPiB = CoAbs(PinkRGB[3] - b);
     CPiC = CoAbs(PinkRGB[4] - c);

     CPiT = CPiR + CPiG + CPiB + CPiC;

     //Check to see if the color is Blue
     if(CBT < CPT && CBT < CGT && CBT < CRT && CBT < CBrT && CBT < COT && CBT < CPiT)
     {
       Serial.println("Blue Color Detected");
       Blu = true;
     }

     //Check to see if the color is Red
     if(CRT < CPT && CRT < CBT && CRT < CGT && CRT < CBrT && CRT < COT && CRT < CPiT)
     {
       Serial.println("Red Color Detected");
       Red = true;
     }

     //Check to see if the color is Purple
     if(CPT < CBT && CPT < CGT && CPT < CRT && CPT < CBrT && CPT < COT && CPT < CPiT)
     {
       Serial.println("Purple Color Detected");
       Pur = true;
     }

     //Check to see if the color is Green
     if(CGT < CPT && CGT < CBT  && CGT < CRT && CGT < CBrT && CGT < COT && CGT < CPiT)
     {
       Serial.println("Green Color Detected");
       Gre = true;
     }

     //Check to see if the color is Brown
     if(CBrT < CPT && CBrT < CBT  && CBrT < CRT && CBrT < CGT && CBrT < COT && CBrT < CPiT)
     {
       Serial.println("Brown Color Detected");
       Bro = true;
     }

     if(COT < CPT && COT < CBT  && COT < CRT && COT < CGT && COT < CBrT && COT < CPiT)
     {
       Serial.println("Orange Color Detected");
       Ora = true;
     }

     //Check to see if the color is Pink
     if(CPiT < CPT && CPiT < CBT  && CPiT < CRT && CPiT < CGT && CPiT < CBrT && CPiT < COT)
     {
       Serial.println("Pink Color Detected");
       Pin = true;
     }
  }

  //Brown Color Range
  if (r >= 10 && r <= 50 && g >= 8 && g <= 50 && b >= 5 && b <= 31 && c <= 130 && lux >= 4 && lux <= 64 
  && Bla == false && Bro == false && Pur == false && Blu == false && Red == false && Bro == false 
  && Ora == false && Gre == false)
  {
     //Serial.println("Brown//");
     //Get Orange Color Proximity to Brown
     COR = CoAbs(OrangeRGB[1] - r);
     COG = CoAbs(OrangeRGB[2] - g);
     COB = CoAbs(OrangeRGB[3] - b);
     COC = CoAbs(OrangeRGB[4] - c);

     COT = COR + COG + COB + COC + 18;

     //Get Blue Color Proximity to Brown
     CBR = CoAbs(BlueRGB[1] - r);
     CBG = CoAbs(BlueRGB[2] - g);
     CBB = CoAbs(BlueRGB[3] - b);
     CBC = CoAbs(BlueRGB[4] - c);

     CBT = CBR + CBG + CBB + CBC + 20;

     //Get Red Color Proximity to Brown
     CRR = CoAbs(RedRGB[1] - r);
     CRG = CoAbs(RedRGB[2] - g);
     CRB = CoAbs(RedRGB[3] - b);
     CRC = CoAbs(RedRGB[4] - c);

     CRT = CRR + CRG + CRB + CRC + 30;

     //Get Purple Color Proximity to Brown
     CPR = CoAbs(PurpleRGB[1] - r);
     CPG = CoAbs(PurpleRGB[2] - g);
     CPB = CoAbs(PurpleRGB[3] - b);
     CPC = CoAbs(PurpleRGB[4] - c);

     CPT = CPR + CPG + CPB + CPC + 35;

     //Get Green Color Proximity to Brown
     CGR = CoAbs(GreenRGB[1] - r);
     CGG = CoAbs(GreenRGB[2] - g);
     CGB = CoAbs(GreenRGB[3] - b);
     CGC = CoAbs(GreenRGB[4] - c);

     CGT = CGR + CGG + CGB + CGC + 10;

     //Get Brown Color Proximity to Brown
     CBrR = CoAbs(BrownRGB[1] - r);
     CBrG = CoAbs(BrownRGB[2] - g);
     CBrB = CoAbs(BrownRGB[3] - b);
     CBrC = CoAbs(BrownRGB[4] - c);

     CBrT = CBrR + CBrG + CBrB + CBrC - 15;

     //Get Pink Color Proximity to Red
     CPiR = CoAbs(PinkRGB[1] - r);
     CPiG = CoAbs(PinkRGB[2] - g);
     CPiB = CoAbs(PinkRGB[3] - b);
     CPiC = CoAbs(PinkRGB[4] - c);

     CPiT = CPiR + CPiG + CPiB + CPiC;

     //Check to see if the color is Blue
     if(CBT < CPT && CBT < CGT && CBT < CRT && CBT < CBrT && CBT < COT && CBT < CPiT)
     {
       Serial.println("Blue Color Detected");
       Blu = true;
     }

     //Check to see if the color is Red
     if(CRT < CPT && CRT < CBT && CRT < CGT && CRT < CBrT && CRT < COT && CRT < CPiT)
     {
       Serial.println("Red Color Detected");
       Red = true;
     }

     //Check to see if the color is Purple
     if(CPT < CBT && CPT < CGT && CPT < CRT && CPT < CBrT && CPT < COT && CPT < CPiT)
     {
       Serial.println("Purple Color Detected");
       Pur = true;
     }

     //Check to see if the color is Green
     if(CGT < CPT && CGT < CBT && CGT < CRT && CGT < CBrT && CGT < COT && CGT < CPiT)
     {
       Serial.println("Green Color Detected");
       Gre = true;
     }

     //Check to see if the color is Brown
     if(CBrT < CPT && CBrT < CBT  && CBrT < CRT && CBrT < CGT && CBrT < COT && CBrT < CPiT)
     {
       Serial.println("Brown Color Detected");
       Bro = true;
     }

     //Check to see if the color is Orange
     if(COT < CPT && COT < CBT && COT < CRT && COT < CGT && COT < CBrT && COT < CPiT)
     {
       Serial.println("Orange Color Detected");
       Ora = true;
     }

     //Check to see if the color is Pink
     if(CPiT < CPT && CPiT < CBT  && CPiT < CRT && CPiT < CGT && CPiT < CBrT && CPiT < COT)
     {
       Serial.println("Pink Color Detected");
       Pin = true;
     }
  }

  //Purple Color Range
   if (r >= 10 && r <= 39 && g >= 9 && g <=39 && b >= 10 && b <= 53 && c >= 37 && lux <= 11 
   && c <= 128 && Bla == false && Blu == false && Red == false && Bro == false && Pur == false && Gre == false)
  {
    //Serial.println("Purple//");
    //Get Blue Color Proximity to Purple
     CBR = CoAbs(BlueRGB[1] - r);
     CBG = CoAbs(BlueRGB[2] - g);
     CBB = CoAbs(BlueRGB[3] - b);
     CBC = CoAbs(BlueRGB[4] - c);

     CBT = CBR + CBG + CBB + CBC + 10;

     //Get Red Color Proximity to Purple
     CRR = CoAbs(RedRGB[1] - r);
     CRG = CoAbs(RedRGB[2] - g);
     CRB = CoAbs(RedRGB[3] - b);
     CRC = CoAbs(RedRGB[4] - c);

     CRT = CRR + CRG + CRB + CRC + 20;

     //Get Purple Color Proximity to Purple
     CPR = CoAbs(PurpleRGB[1] - r);
     CPG = CoAbs(PurpleRGB[2] - g);
     CPB = CoAbs(PurpleRGB[3] - b);
     CPC = CoAbs(PurpleRGB[4] - c);

     CPT = CPR + CPG + CPB + CPC - 15;

     //Get Green Color Proximity to Purple
     CGR = CoAbs(GreenRGB[1] - r);
     CGG = CoAbs(GreenRGB[2] - g);
     CGB = CoAbs(GreenRGB[3] - b);
     CGC = CoAbs(GreenRGB[4] - c);

     CGT = CGR + CGG + CGB + CGC;

     //Get Brown Color Proximity to Purple
     CBrR = CoAbs(BrownRGB[1] - r);
     CBrG = CoAbs(BrownRGB[2] - g);
     CBrB = CoAbs(BrownRGB[2] - b);
     CBrC = CoAbs(BrownRGB[4] - c);

     CBrT = CBrR + CBrG + CBrB + CBrC + 35;

     //Check to see if the color is Blue
     if(CBT < CPT && CBT < CGT && CBT < CRT && CBT < CBrT)
     {
       Serial.println("Blue Color Detected");
       Blu = true;
     }

     //Check to see if the color is Red
     if(CRT < CPT && CRT < CBT && CRT < CGT && CRT < CBrT)
     {
       Serial.println("Red Color Detected");
       Red = true;
     }

     //Check to see if the color is Purple
     if(CPT < CBT && CPT < CGT && CPT < CRT && CPT < CBrT)
     {
       Serial.println("Purple Color Detected");
       Pur = true;
     }

     //Check to see if the color is Green
     if(CGT < CPT && CGT < CBT && CGT < CRT && CGT < CBrT)
     {
       Serial.println("Green Color Detected");
       Gre = true;
     }

     //Check to see if the color is Brown
     if(CBrT < CPT && CBrT < CBT  && CBrT < CRT && CBrT < CGT)
     {
       Serial.println("Brown Color Detected");
       Bro = true;
     }
  }
  
  //Green Color Range
   if (r >= 6 && r <= 30 && g >= 9 && g <= 100 && b >= 6 && b <= 46 && c >= 21 && lux >= 7 && lux <= 55 
   && Bla == false && Pur == false && Blu == false && Red == false && Bro == false && Gre == false)
  {
     //Serial.println("Green//");
     //Get Blue Color Proximity to Green
     CBR = CoAbs(BlueRGB[1] - r);
     CBG = CoAbs(BlueRGB[2] - g);
     CBB = CoAbs(BlueRGB[3] - b);
     CBC = CoAbs(BlueRGB[4] - c);

     CBT = CBR + CBG + CBB + CBC + 20;

     //Get Purple Color Proximity to Green
     CPR = CoAbs(PurpleRGB[1] - r);
     CPG = CoAbs(PurpleRGB[2] - g);
     CPB = CoAbs(PurpleRGB[3] - b);
     CPC = CoAbs(PurpleRGB[4] - c);

     CPT = CPR + CPG + CPB + CPC + 11;

     //Get Green Color Proximity to Green
     CGR = CoAbs(GreenRGB[1] - r);
     CGG = CoAbs(GreenRGB[2] - g);
     CGB = CoAbs(GreenRGB[3] - b);
     CGC = CoAbs(GreenRGB[4] - c);

     CGT = CGR + CGG + CGB + CGC -10;

     //Check to see if the color is Blue
     if((CBT < CPT) && (CBT < CGT))
     {
       Serial.println("Blue Color Detected");
       Blu = true;
     }

     //Check to see if the color is Purple
     if((CPT < CBT) && (CPT < CGT))
     {
       Serial.println("Purple Color Detected");
       Pur = true;
     }

     //Check to see if the color is Green
     if((CGT < CPT) && (CGT < CBT))
     {
       Serial.println("Green Color Detected");
       Gre = true;
     }
  }

  //Gray Color Range
  if (r >= 28 && r <= 86 && g >= 32 && g <= 119 && b >= 29 && b <= 108 && lux >= 8 && lux <= 61 
  && c >= 80 && c <= 323 && Pur == false && Bla == false && Pur == false
  && Blu == false && Red == false && Bro == false && Gre == false && Gra == false)
  {
     //Serial.println("Gray//");
     //Get Yellow Color Proximity to Gray
     CYR = CoAbs(YellowRGB[1] - r);
     CYG = CoAbs(YellowRGB[2] - g);
     CYB = CoAbs(YellowRGB[3] - b);
     CYC = CoAbs(YellowRGB[4] - c);

     CYT = CYR + CYG + CYB + CYC + 26;

     //Get White Color Proximity to Gray
     CWR = CoAbs(WhiteRGB[1] - r);
     CWG = CoAbs(WhiteRGB[2] - g);
     CWB = CoAbs(WhiteRGB[3] - b);
     CWC = CoAbs(WhiteRGB[4] - c);

     CWT = CWR + CWG + CWB + CWC + 40;

     //Get Pink Color Proximity to Gray
     CPiR = CoAbs(PinkRGB[1] - r);
     CPiG = CoAbs(PinkRGB[2] - g);
     CPiB = CoAbs(PinkRGB[3] - b);
     CPiC = CoAbs(PinkRGB[4] - c);

     CPiT = CPiR + CPiG + CPiB + CPiC + 15;

     //Get Orange Color Proximity to Gray
     COR = CoAbs(OrangeRGB[1] - r);
     COG = CoAbs(OrangeRGB[2] - g);
     COB = CoAbs(OrangeRGB[3] - b);
     COC = CoAbs(OrangeRGB[4] - c);

     COT = COR + COG + COB + COC + 30;

     //Get Gray Color Proximity to Gray
     CGrR = CoAbs(GrayRGB[1] - r);
     CGrG = CoAbs(GrayRGB[2] - g);
     CGrB = CoAbs(GrayRGB[3] - b);
     CGrC = CoAbs(GrayRGB[4] - c);

     CGrT = CGrR + CGrG + CGrB + CGrC - 35;

     //Check to see if the color is Yellow
     if((CYT < CWT) && CYT < CPiT && CYT < COT && CYT < CGrT)
     {
       Serial.println("Yellow Color Detected");
       Yel = true;
     }

     //Check to see if the color is White
     if((CWT < CYT) && CWT < CPiT && CWT < COT && CWT < CGrT)
     {
       Serial.println("White Color Detected");
       Whi = true;
     }

     //Check to see if the color is Pink
     if((CPiT < CWT) && CPiT < CYT && CPiT < COT && CPiT < CGrT)
     {
       Serial.println("Pink Color Detected");
       Pin = true;
     }

     //Check to see if the color is Orange
      if((COT < CWT) && COT < CYT && COT < CPiT && COT < CGrT)
     {
       Serial.println("Orange Color Detected");
       Ora = true;
     }
     
     //Check to see if the color is Gray
      if((CGrT < CWT) && CGrT < CYT && CGrT < CPiT && CGrT < COT)
     {
       Serial.println("Gray Color Detected");
       Gra = true;
     }
  }

  //Orange Color Range
  if (r >= 40 && r <= 138 && g >= 24 && g <= 99 && b >= 15 && b <= 58 && c >= 80 
  && lux >= 14 && lux <= 69 && Pur == false && Bla == false && Pur == false && Blu == false && Red == false 
  && Bro == false && Gre == false && Gra == false && Yel == false && Pin == false)
  {
     //Serial.println("Orange//");
     //Get Orange Color Proximity to Orange
     COR = CoAbs(OrangeRGB[1] - r);
     COG = CoAbs(OrangeRGB[2] - g);
     COB = CoAbs(OrangeRGB[3] - b);
     COC = CoAbs(OrangeRGB[4] - c);

     COT = COR + COG + COB + COC - 20;

     //Get Red Color Proximity to Orange
     CRR = CoAbs(RedRGB[1] - r);
     CRG = CoAbs(RedRGB[2] - g);
     CRB = CoAbs(RedRGB[3] - b);
     CRC = CoAbs(RedRGB[4] - c);

     CRT = CRR + CRG + CRB + CRC + 38;

     //Get Brown Color Proximity to Orange
     CBrR = CoAbs(BrownRGB[1] - r);
     CBrG = CoAbs(BrownRGB[2] - g);
     CBrB = CoAbs(BrownRGB[3] - b);
     CBrC = CoAbs(BrownRGB[4] - c);

     CBrT = CBrR + CBrG + CBrB + CBrC + 25;

     //Get Pink Color Proximity to Orange
     CPiR = CoAbs(PinkRGB[1] - r);
     CPiG = CoAbs(PinkRGB[2] - g);
     CPiB = CoAbs(PinkRGB[3] - b);
     CPiC = CoAbs(PinkRGB[4] - c);

     CPiT = CPiR + CPiG + CPiB + CPiC;

     //Check to see if the color is Orange
     if(COT < CRT && COT < CBrT && COT < CPiT)
     {
       Serial.println("Orange Color Detected");
       Ora = true;
     }

     //Check to see if the color is Red
     if(CRT < COT && CRT < CBrT && CRT < CPiT)
     {
       Serial.println("Red Color Detected");
       Red = true;
     }

     //Check to see if the color is Brown
     if(CBrT < COT && CBrT < CRT && CBrT < CPiT)
     {
       Serial.println("Brown Color Detected");
       Bro = true;
     }

     //Check to see if the color is Pink
     if(CPiT < COT && CPiT < CRT && CPiT < CBrT)
     {
       Serial.println("Pink Color Detected");
       Pin = true;
     }
  }

  //Yellow Color Range
  if (r >= 47 && r <= 190 && g >= 53 && g <= 173 && b >= 17 && b <= 85 && lux >= 92 && lux <= 163 
  && Pur == false && Bla == false && Pur == false
  && Blu == false && Red == false && Bro == false && Gre == false && Gra == false && Ora == false && Pin == false)
  {
     //Serial.println("Yellow//");
     //Get Yellow Color Proximity to Yellow
     CYR = CoAbs(YellowRGB[1] - r);
     CYG = CoAbs(YellowRGB[2] - g);
     CYB = CoAbs(YellowRGB[3] - b);
     CYC = CoAbs(YellowRGB[4] - c);

     CYT = CYR + CYG + CYB + CYC - 10;

     //Get White Color Proximity to Yellow
     CWR = CoAbs(WhiteRGB[1] - r);
     CWG = CoAbs(WhiteRGB[2] - g);
     CWB = CoAbs(WhiteRGB[3] - b);
     CWC = CoAbs(WhiteRGB[4] - c);

     CWT = CWR + CWG + CWB + CWC + 40;

     //Get Pink Color Proximity to Yellow
     CPiR = CoAbs(PinkRGB[1] - r);
     CPiG = CoAbs(PinkRGB[2] - g);
     CPiB = CoAbs(PinkRGB[3] - b);
     CPiC = CoAbs(PinkRGB[4] - c);

     CPiT = CPiR + CPiG + CPiB + CPiC + 10;

     //Get Orange Color Proximity to Yellow
     COR = CoAbs(OrangeRGB[1] - r);
     COG = CoAbs(OrangeRGB[2] - g);
     COB = CoAbs(OrangeRGB[3] - b);
     COC = CoAbs(OrangeRGB[4] - c);

     COT = COR + COG + COB + COC + 15;

     //Check to see if the color is Yellow
     if((CYT < CWT) && CYT < CPiT && CYT < COT)
     {
       Serial.println("Yellow Color Detected");
       Yel = true;
     }

     //Check to see if the color is White
     if((CWT < CYT) && CWT < CPiT && CWT < COT)
     {
       Serial.println("White Color Detected");
       Whi = true;
     }

     //Check to see if the color is Pink
     if((CPiT < CWT) && CPiT < CYT && CPiT < COT)
     {
       Serial.println("Pink Color Detected");
       Pin = true;
     }

     //Check to see if the color is Orange
      if((COT < CWT) && COT < CYT && COT < CPiT)
     {
       Serial.println("Orange Color Detected");
       Ora = true;
     }
  }

  //Pink Color Range
  if (r >= 64 && r <= 122 && g >= 30 && g <= 63 && b >= 35 && b <= 69 && c >= 89 && lux <= 12
  && Pur == false && Bla == false 
  && Ora ==false && Pur == false && Blu == false && Red == false && Bro == false && Gre == false 
  && Gra == false && Yel == false && Pin == false)
  {
    //Serial.println("Pink//");
    //Color is Pink
    Serial.println("Pink Color Detected");
    Pin = true;
  }

  

  //White Color Range
  if (r >= 70  && g >= 70 && b >= 70 && lux >= 73 && lux <= 175 && Pur == false && Bla == false && Pur == false
  && Blu == false && Red == false && Bro == false && Gre == false && Gra == false 
  && Yel == false && Pin == false && Ora == false)
  {
    //Serial.println("White//");
    //Color is White
    Serial.println("White Color Detected");
    Whi = true;
  }
  delay(600);
}
