/*
Dec 22 2017 updates: 
-

*/

//#include "custom_library.h"
class zLED{
  private:
    boolean state, delta_state;
    int pin, brtns, stepsize;
    const struct Limits{
        int MAXbrt, MINbrt, minDtus;
        Limits(){MAXbrt = 255; MINbrt = 0; minDtus=2;}
    }zLimits;
  public:
  /// SETUP
    enum { fail, success };
    zLED(){pin =0; state = false; brtns = 0; delta_state = false; stepsize = 5;}    // DONE  - update
    boolean setPin(int a){ this->pin =  (a>0 && a<600)?  a : 0;  }    // DONE
  /// PROCESS returns true is brithness is anything but zero
    boolean  process(  ){                                             // DONE 
     analogWrite(pin, brtns); 
     if (brtns ==0){
       return false;
     }
     else
       return true; 
    }
  /// MANIPULATE
//    void brtUp(){       brtns = brtns >= zLimits.MAXbrt ? zLimits.MAXbrt : brtns+1;}
//    void brtDown(){     brtns = brtns <= zLimits.MINbrt ? zLimits.MINbrt : brtns-1;}
    void brtUp(){     /*  brtns = brtns >= 255 ? 255 : brtns+1;*/ 
      if(brtns >= 255) {brtns = zLimits.MAXbrt; return;}//{brtns = 255; return;}
      if(brtns <= 0)   {brtns = 1; return;}//{brtns = 1; return;}
     // brtns++;
      brtns += stepsize;
    }
    void brtDown(){    // brtns = brtns <= 0 ? 0 : brtns-1;}
      if(brtns >= 255) {brtns = 254; return;}
      if(brtns <= 0)   {brtns = zLimits.MINbrt; return;}
     // brtns--;
      brtns -= stepsize;
    }
    boolean setStepSize(int s){ if(s >= 1 && s<= 254) {stepsize= s;return true;} else return false;}
    boolean getDeltaState(){ return delta_state;}  // in case you missed the return of process, use this function to check again..
    int getPin(){return this->pin;}
    int getBrtns(){return this->brtns;}
    boolean getState(){ return this->state;}
    boolean setGoal(boolean to){    if(to) brtDown() ; else  brtUp(); }//{    if(to) brtUp(); else   brtDown(); }
    boolean setState(boolean to){  // returns true when a change occured
     if(state)if(!to) brtDown();        // change ON -> OFF
     else     if(to)  brtUp();          // change OFF -> ON
     delta_state = false; 
     return false;
    }
};


class z6bitDigit{
private:
 public:
static const int ledCount = 6;
  zLED mleds[ledCount];
  z6bitDigit(int from=2, int to = 7){setDouts(from,to);}
  boolean setDouts(int from=2, int to=7){
    if(from<1 || from>600) return false;
    if(to<2 || to >600) return false;
    for(int i=from ; i<=to ; i++){
    //  pinMode(i, OUTPUT);
      mleds[i-from].setPin(i);
    }
    return true;
  }
  
  int zPow(int base, int pwr){
   int ret=1;
   for(int i=0; i<pwr; i++){
    ret *= base;
   } 
   return base;
  }
  
  boolean showNum(int val){
  //  if(val>zPow(2,6)) return false; 
  //  if(val<0) return false;
    int v =val;
    for(int i=0; i<6; i ++){
     mleds[i].setGoal(v%2==0);
  //   mleds[i].setState(v%2==0);
     v/=2;
     mleds[i].process();
    }
    //Serial.println(showNum);
    return true;
  }
  boolean setStepSize(int s){
    for(int i=0;i<6;i++){
      mleds[i].setStepSize(s);
    }
    return true; 
  }
  boolean setStepSizeFor(int s, int p){
    
    
    return true;
  }
};

// Global Object Declares:
z6bitDigit seconds_out;
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

// Global vars
int S = 0;
int clk; 
int clkT;
void setup(){
 S=0;
 clk=0;
 clkT=300;    //300 is about one second. with delay 8
 Serial.begin(9600);
 while(!Serial){}
 seconds_out.setStepSize(8);
} 

void loop(){
 clk++;
 if(clk >= clkT){
   S++;
   S%= 64;
   clk = 0;
//   Serial.println(S);
  // read the analog in value:
 }
 seconds_out.showNum(S);
 seconds_out.setStepSize(S);
  sensorValue = analogRead(analogInPin);            
  // map it to the range of the analog out:
//  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
//  analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);      
//  Serial.print("\t output = ");      
//  Serial.println(outputValue);   
   
 delay(8);
} 
