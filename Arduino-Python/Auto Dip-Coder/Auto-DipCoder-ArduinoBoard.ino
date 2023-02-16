#include <SparkFunAutoDriver.h>
#include <SPI.h>
const int sensorA = A0; //  Sensor near motor, horizontal
const int sensorB = A1; //  Sensor far from motor, horizontal

int SBV;
int SNH;

String readString;
String readString2;
String firstVarIdentifier; //data String
String t1;
String t2;
String t3;
String t4;
String t5;
String t6;
String t7;
String t8;

String h1;
String h2;
String h3;
String h4;
String h5;
String h6;
String h7;

bool busy = false;
bool started = false;

int t1i; //int variables
int t2i;
int t3i;
int t4i;
int t5i;
int t6i;
int t7i;

int h1i;
int h2i;
int h3i;
int h4i;
int h5i;
int h6i;
int h7i;
const int hmaxi = 100; //in mL

float dp; //int variables
int p1;
int p2;
int p3;
int p4;
int p5;
int p6;
int p7;
int p8;

int ind1; // , locations of indexes
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;
int ind9;
int ind10;
int ind11;
int ind12;
int ind13;
int ind14;

AutoDriver boardA(1, 53, 8, 7); 
AutoDriver boardB(0, 53, 8, 6); 

void setup()
{
  Serial.begin(19200);
  Serial.println("Hello world");  
  // Start by setting up the SPI port and pins. The
  //  Autodriver library does not do this for you!
  pinMode(8, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  pinMode(52, OUTPUT);
  pinMode(53, OUTPUT);
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);       // This low/high is a reset of the L6470 chip on the
  digitalWrite(8, HIGH);      //  Autodriver board, and is a good thing to do at
                              //  the start of any Autodriver sketch, to be sure
                              //  you're starting the Autodriver from a known state.
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  dSPINConfig();  
}
// loop() waits for data
void loop()
{
  while (!Serial.available()) 
  {
      delay(100); //time for the buffer to fill up
      Serial.println("Waiting for Data");
  }
  if (Serial.available() >0)
    {

        while (Serial.available())
        {
          delay(100);
          char c = Serial.read();  //gets one byte from serial buffer
          if (c =='*') 
            {
  //            Serial.println();
  //            Serial.print("Captured String is : ");
  //            Serial.println(readString); //prints string to serial port out
  
              ind1 = readString.indexOf(',');  //finds location of first ,
              firstVarIdentifier = readString.substring(0, ind1);   //captures first data String
              ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
              t2 = readString.substring(ind1+1, ind2);   //captures second data String
              ind3 = readString.indexOf(',', ind2+1 );  //finds location of thirC:\Programming Projects\Arduino-Python-L6470-Autodriver\Dave's Clean Serial Reader\Pythonside\TKwithSerialReading.pyd ,
              t3 = readString.substring(ind2+1, ind3);  //captures third data String
              ind4 = readString.indexOf(',', ind3+1 );  // finds location of fourth ,
              t4 = readString.substring(ind3+1, ind4); //captures fourth data String
              ind5 = readString.indexOf(',', ind4+1 );  // finds location of fifth ,
              t5 = readString.substring(ind4+1, ind5); //captures fifth data String
              ind6 = readString.indexOf(',', ind5+1 );  // finds location of sixth ,
              t6 = readString.substring(ind5+1, ind6); //captures sixth data String
              ind7 = readString.indexOf(',', ind6+1 );  // finds location of seventh ,
              t7 = readString.substring(ind6+1, ind7); //captures seventh data String
              ind8 = readString.indexOf('*', ind7+1);  //finds location of *
              t8 = readString.substring(ind7+1, ind8);   //captures eigth data String
  
              if (firstVarIdentifier == "runH" && started == false) //run set height function with the following variables from python
              {
                Serial.println("Height Program Started"); 
                //setHeight();
                boardA.goTo(50000); 
                delay(100);
              }
              else if (firstVarIdentifier == "runPos" && started == false) //run set position function with the following variables from python
              {
                Serial.println("Position Program Started"); 
                //setPosition();
                vertReset();
                horReset();
                runPositiontest6();
                delay(100);
              }
              else if (firstVarIdentifier == "sendD" && started == false) //load data with the following variables from python
              {
                started == true;
                Serial.println("Dipcoder Loading Height Data");
                h1i = (hmaxi-t2.toInt())*-25;
                h2i = (hmaxi-t3.toInt())*-25;
                h3i = (hmaxi-t4.toInt())*-25;
                h4i = (hmaxi-t5.toInt())*-25;
                h5i = (hmaxi-t6.toInt())*-25;
                h6i = (hmaxi-t7.toInt())*-25;
                h7i = (hmaxi-t8.toInt())*-25;
                Serial.println(h2i);
                delay(5000); //Wait for new data
                //loadData();
                t1="";
                t2="";
                t3="";
                t4="";
                t5="";
                t6="";
                t7="";
                h1="";
                h2="";
                h3="";
                h4="";
                h5="";
                h6="";
                h7="";
                Serial.println("Dipcoder Loading Time Data");
                ind1 = readString.indexOf(',');  //finds location of first ,
                firstVarIdentifier = readString.substring(0, ind1);   //captures first data String
                ind2 = readString.indexOf(',', ind1+1 );   //finds location of second ,
                t2 = readString.substring(ind1+1, ind2);   //captures second data String
                ind3 = readString.indexOf(',', ind2+1 );  //finds location of thirC:\Programming Projects\Arduino-Python-L6470-Autodriver\Dave's Clean Serial Reader\Pythonside\TKwithSerialReading.pyd ,
                t3 = readString.substring(ind2+1, ind3);  //captures third data String
                ind4 = readString.indexOf(',', ind3+1 );  // finds location of fourth ,
                t4 = readString.substring(ind3+1, ind4); //captures fourth data String
                ind5 = readString.indexOf(',', ind4+1 );  // finds location of fifth ,
                t5 = readString.substring(ind4+1, ind5); //captures fifth data String
                ind6 = readString.indexOf(',', ind5+1 );  // finds location of sixth ,
                t6 = readString.substring(ind5+1, ind6); //captures sixth data String
                ind7 = readString.indexOf(',', ind6+1 );  // finds location of seventh ,
                t7 = readString.substring(ind6+1, ind7); //captures seventh data String
                ind8 = readString.indexOf('*', ind7+1);  //finds location of *
                t8 = readString.substring(ind7+1, ind8);   //captures eigth data String
                delay(1000);
                t1i = t2.toInt();
                t2i = t3.toInt();
                t3i = t4.toInt();
                t4i = t5.toInt();
                t5i = t6.toInt();
                t6i = t7.toInt();
                t7i = t8.toInt();
                Serial.println(t2i);
                delay(5000);
                started == false;
              }
              else if (firstVarIdentifier == "startP" && started == false) //run program function
              {
                Serial.println("Dipcoder Program Started"); 
                //programStart();
                delay(100);
              }
              else if (firstVarIdentifier == "reset" && started == false) //run reset function
              {
                Serial.println("Resetting Dipcoder Values"); 
                //programReset();
                delay(100);
              }
              else if (firstVarIdentifier == "quit") //quit program
              {
                Serial.println("Quit Program"); 
                //programQuit();
                delay(100);
              }
              readString=""; //clears variable for new input

//            Serial.print("Identifier = ");
//            Serial.println(firstVarIdentifier);
//            Serial.print("t2 = ");
//            Serial.println(t2);
//            Serial.print("t3 = ");
//            Serial.println(t3);
//            Serial.print("t4 = ");
//            Serial.println(t4);
//            Serial.print("t5 = ");
//            Serial.println(t5);
//            Serial.print("t6 = ");
//            Serial.println(t6);
//            Serial.print("t7 = ");
//            Serial.println(t7); 
//            Serial.print("t8 = ");
//            Serial.println(t8);                                                                                                    
//            Serial.println();
//            Serial.println();
              
              t1="";
              t2="";
              t3="";
              t4="";
              t5="";
              t6="";
              t7="";
              h1="";
              h2="";
              h3="";
              h4="";
              h5="";
              h6="";
              h7="";
            } 
            else {     
              readString += c; //makes the string readString
                  }
                  //showTest();
        //Serial.println(readString); 
      }
  }  
//  readString = "";
  Serial.flush();  
}
  // This is the configuration function for the two dSPIN parts. Read the inline
  //  comments for more info.
  void dSPINConfig(void)
  {
    boardA.SPIPortConnect(&SPI);      // Before doing anything else, we need to
    boardB.SPIPortConnect(&SPI);      //  tell the object which SPI port to use.
                                      //  Some devices may have more than one.
  
    boardA.configSyncPin(BUSY_PIN, 0);// BUSY pin low during down time
                                      //  second paramter ignored.
    boardA.configStepMode(STEP_FS_32);   // 0 microsteps per step
    boardA.setMaxSpeed(3000);        // 10000 steps/s max
    boardA.setFullSpeed(2000);       // microstep below 10000 steps/s
    boardA.setAcc(1000);             // accelerate at 10000 steps/s/s
    boardA.setDec(1000);
  
    boardA.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
    boardA.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
    boardA.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
    boardA.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
    boardA.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
    boardA.setSwitchMode(SW_USER);    // Switch is not hard stop
    boardA.setOscMode(INT_16MHZ_OSCOUT_16MHZ); // for boardA, we want 16MHz
                                      //  internal osc, 16MHz out.
                                      
    boardB.configSyncPin(BUSY_PIN, 0);// BUSY pin low during down time
                                      //  second paramter ignored.
    boardB.configStepMode(STEP_FS_64);   // 0 microsteps per step
    boardB.setMaxSpeed(100);        // 10000 steps/s max
    boardB.setFullSpeed(1000);       // microstep below 10000 steps/s
    boardB.setAcc(200);             // accelerate at 10000 steps/s/s
    boardB.setDec(200);
  
    boardB.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
    boardB.setOCThreshold(OC_3750mA);  // OC threshold 3750mA
    boardB.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
    boardB.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
    boardB.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
    boardB.setSwitchMode(SW_USER);    // Switch is not hard stop
    boardB.setOscMode(EXT_16MHZ_OSCOUT_INVERT); // for boardA, we want 16MHz
                                      //  internal osc, 16MHz out.
  
  }
void vertReset (void)
{
  Serial.println("Running command 'vertReset'");  //Print to serial monitor function being run
    delay(2000);
  SBV = analogRead(sensorB);   // Read the value from the limit sensor and set a variable to that value
  while(SBV > 1000) {            // While the switch is high(open ciruit) run this loop
    delay(100);           
    boardB.run(FWD, 250);       // Runs the motor at a slow speed (FWD: Gantry moves away from motor, Sample moves up)
    SBV = analogRead(sensorB); // Reads the bottom vertical(BV) sensor every loop, in this case, many times a second
  }
  if (SBV < 100) {              // If the sensor goes low(creates short) the program switches to this loop
    boardB.hardStop();          // Immediately stop the motor
    boardB.resetPos();          // Reset the position tracker for this motor (vertical)
    boardB.move(REV, 6500);     // Moves the sample a set distance low to release the limit switch 
  } 
}

void horReset (void)
{
  Serial.println("Running command 'horReset'");
    delay(2000);
    SNH = analogRead(sensorA);
  while(SNH > 1000) {
    delay(100);
    boardA.run(REV, 500);
    SNH = analogRead(sensorA);
  }
  if (SNH < 100) {
    boardA.hardStop();
    boardA.resetPos();
    boardA.move(FWD, 3500);
  } 
}

void runCoating6 (void)
{
  dp = 540000/6;
  p1=dp; 
  p2=dp*2;
  p3=dp*3;
  p4=dp*4;
  p5=dp*5;
  p6=dp*6;
  Serial.println("Running command 'runCoating6'");
  delay(1000);                
    boardB.goTo(h1i);      //  At to Position 1- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 1");
    delay(t1.toInt());            //Coating
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p2);    //  Moving to Position 2 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h2i);      //  At to Position 1- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 2");
    delay(t2.toInt());            //Washing
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p3);        //  Moving to Position 3 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h3i);      //  At to Position 3- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 3");
    delay(t3.toInt());            //Washing
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p4);                //  Move to Position 4 - Poly-elect. W/NP
  while(boardA.busyCheck()){}     //  Moving
    boardB.goTo(h4i);              //  At to Position 4- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 4");
    delay(t4.toInt());            //Coating
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p5);    //  Moving to Position 5 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h5i);      //  At to Position 6- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 5");
    delay(t5.toInt());            //Washing
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p6);    //  Moving to Position 6 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h6i);      //  At to Position 6- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At Position 6");
    delay(t6.toInt());            //Washing
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p1);    //  Moving to Position 1
  while(boardA.busyCheck()){}
  delay(50);            //Ready to run next coating
}

void runHeighttest6 (void)
{
  
  dp = 270000/6;
  p1=dp; 
  p2=dp*2;
  p3=dp*3;
  p4=dp*4;
  p5=dp*5;
  p6=dp*6;
  Serial.println("Running command 'runHeighttest'");
 delay(1000);                
    boardB.goTo(h1i);      //  At to Position 1- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H1");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p2);    //  Moving to Position 2 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h2i);      //  At to Position 1- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H2");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p3);        //  Moving to Position 3 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h3i);      //  At to Position 3- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H3");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p4);                //  Move to Position 4 - Poly-elect. W/NP
  while(boardA.busyCheck()){}     //  Moving
    boardB.goTo(h4i);              //  At to Position 4- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H4");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p5);    //  Moving to Position 5 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h5i);      //  At to Position 6- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H5");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p6);    //  Moving to Position 6 - Water
  while(boardA.busyCheck()){}
    boardB.goTo(h6i);      //  At to Position 6- Poly-elect. W/NP
    while(boardB.busyCheck()){}
    Serial.println("At H6");
    askForOK();           //Showing height
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p1);    //  Moving to Position 1
  while(boardA.busyCheck()){}
  delay(50);            //Ready to run next coating
}

void runPositiontest6 (void)
{
  dp = 250000/6;
  p1=0; 
  p2=dp;
  p3=dp*2;
  p4=dp*3;
  p5=dp*4;
  p6=dp*5;
   delay(1000);                
    boardB.goTo(h1i);      //  At to Position 1- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p2);    //  Moving to Position 2 - Water
  while(boardA.busyCheck()){}                
    boardB.goTo(h2i);      //  At to Position 2- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position 
   delay(1000);    
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p3);        //  Moving to Position 3 - Water
  while(boardA.busyCheck()){}                
    boardB.goTo(h3i);      //  At to Position 3- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position 
   delay(1000);    
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p4);                //  Move to Position 4 - Poly-elect. W/NP
  while(boardA.busyCheck()){}                
    boardB.goTo(h4i);      //  At to Position 4- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position
   delay(1000);    
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p5);    //  Moving to Position 5 - Water
  while(boardA.busyCheck()){}                
    boardB.goTo(h5i);      //  At to Position 5- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position 
   delay(1000);    
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p6);    //  Moving to Position 6 - Water
  while(boardA.busyCheck()){}                
    boardB.goTo(h6i);      //  At to Position 6- Poly-elect. W/NP
    while(boardB.busyCheck()){}//Dotting Position 
   delay(1000);    
    boardB.goHome();
    while(boardB.busyCheck()){}
  boardA.goTo(p1);    //  Moving to Position 1
  while(boardA.busyCheck()){}
  delay(5000);            //Ready to run next coating
}
void askForOK (void)
{

}
