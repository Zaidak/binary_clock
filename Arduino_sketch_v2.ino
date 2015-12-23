//#include "custom_library.h"
class zLED{
  private:
    boolean state, delta_state;
    int pin, brtns;
    const struct Limits{
        int MAXbrt, MINbrt, minDtus;
        Limits(){MAXbrt = 255; MINbrt = 0; minDtus=2;}
    }zLimits;
  public:
  /// SETUP
    enum { fail, success };
    zLED(){pin =0; state = false; brtns = 0; delta_state = false;}    // DONE  - update
    boolean setPin(int a){ this->pin =  (a>0 && a<600)?  a : 0;  }    // DONE
  /// PROCESS
    boolean  process(  ){                                             // DONE 
     analogWrite(pin, brtns); 
     return true; 
    }
  /// MANIPULATE
//    void brtUp(){       brtns = brtns >= zLimits.MAXbrt ? zLimits.MAXbrt : brtns+1;}
//    void brtDown(){     brtns = brtns <= zLimits.MINbrt ? zLimits.MINbrt : brtns-1;}
    void brtUp(){     /*  brtns = brtns >= 255 ? 255 : brtns+1;*/ 
      if(brtns >= 255) {brtns = 255; return;}
      if(brtns <= 0)   {brtns = 1; return;}
      brtns++;
    }
    void brtDown(){    // brtns = brtns <= 0 ? 0 : brtns-1;}
      if(brtns >= 255) {brtns = 254; return;}
      if(brtns <= 0)   {brtns = 0; return;}
      brtns--;
    }
    boolean getDeltaState(){ return delta_state;}  // in case you missed the return of process, use this function to check again..
    int getPin(){return this->pin;}
    int getBrtns(){return this->brtns;}
    boolean getState(){ return this->state;}
    boolean setGoal(boolean to){    if(to) brtUp(); else   brtDown(); }
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
  zLED mleds[6];
  z6bitDigit(int from=2, int to = 7){setDouts(from,to);}
  boolean setDouts(int from=2, int to=7){
    //if(from<1 || from>600) return false;
    //if(to<2 || to >600) return false;
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
     v/=2;
     mleds[i].process();
    }
    //Serial.println(showNum);
    return true;
  }
};


// Global Object Declares:
z6bitDigit seconds_out;
//zLED leds[6];
// Global vars
int S = 0;
//boolean st;
//boolean leds_ds[6];
int clk; 
void setup(){
// Bits
 for(int i=0; i<6; i++){
//  leds[i].setPin(i+2);
  //leds_ds[i] = false;
 }
/* leds[0].setPin(2);
 for(int i=0; i<6; i++){
  //leds[i].setPin(i+2);
  //leds_ds[i] = false;
 }
/* leds[0].setPin(2);
 leds[5].setPin(7);*/
 
 //st = true;

// Second
 S=0;
 clk=0;
 
 //randomSeed(0);
 //Debug stuff:
 Serial.begin(9600);
 while(!Serial){}
/* Serial.println(seconds_out.mleds[0].getPin());
  Serial.println(seconds_out.mleds[1].getPin());
   Serial.println(seconds_out.mleds[2].getPin());
    Serial.println(seconds_out.mleds[3].getPin());
     Serial.println(seconds_out.mleds[4].getPin());
      Serial.println(seconds_out.mleds[5].getPin());
*/
} 

void loop(){
 clk++;
 if(clk >= 300){
   S++;
   S%= 64;
   clk = 0;
   Serial.println(S);
 }
 seconds_out.showNum(S);
    

 // Serial.println(S);
// for(int i=0;i<6; i++){
//  if(leds[i].getState()){ leds[i].setGoal(false); /*Serial.print("TRUE");*/}
//  else                  { leds[i].setGoal(true); /*Serial.print("FALSE");*/}
  //leds[i].setGoal(random(3)==1); 
//  leds_ds[i] = leds[i].process();
//  leds[i].process();
//  Serial.println(leds[i].getBrtns());
// }
  //if( leds_ds[0] )st = st? false : true;
                     
                     // seconds_out.showNum(S);
 /* for(int i=0;i<6;i++){                    
    seconds_out.mleds[i].setState(true);
    seconds_out.mleds[i].process();
  }*/
// delay(random(10));    // ONLY LOOP DELAY
delay(8);

} 

