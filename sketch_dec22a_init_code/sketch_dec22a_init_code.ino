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
    boolean getDeltaState(){ return delta_state;}  // in case you missed the return of process, use this function to check again..
  /// MANIPULATE
    void brtUp(){
      brtns = brtns >= zLimits.MAXbrt ? zLimits.MAXbrt : brtns+1;
    }
    void brtDown(){
      brtns = brtns <= zLimits.MINbrt ? zLimits.MINbrt : brtns-1;
    }
    boolean setGoal(boolean to){
      if(to) brtUp();
      else   brtDown();
    }
    boolean setState(boolean to){  // returns true when a change occured
     if(state)if(!to)         // change ON -> OFF
          brtDown();
     else     if(to)          // change OFF -> ON
          brtUp();
     delta_state = false; 
     return false;
    }
};


class z6bitDigit{
private:
  zLED mleds[6];
  
 public:
 
  z6bitDigit(int from=2, int to = 7){setDouts(from,to);}
  boolean setDouts(int from=2, int to=7){
    //if(from<1 || from>600) return false;
    //if(to<2 || to >600) return false;
    for(int i=from ; i<=to ; i++){
      pinMode(i, OUTPUT);
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
    if(val>zPow(2,6)) return false; 
    if(val<0) return false;
    int v =val;
    for(int i=0; i<6; i ++){
     mleds[i].setState(v%2==0);
     v/=2;
    }
    return true;
  }
};

class zSecond : public z6bitDigit{
 };

// Global Object Declares:
z6bitDigit seconds_out;
//zLED leds[6];
// Global vars
int S = 0;
//boolean st;
//boolean leds_ds[6];
 
void setup(){
// Bits
 for(int i=0; i<6; i++){
  //leds[i].setPin(i+2);
  //leds_ds[i] = false;
 }
/* leds[0].setPin(2);
 leds[1].setPin(3);
 leds[2].setPin(4);
 leds[3].setPin(5);
 leds[4].setPin(6);
 leds[5].setPin(7);*/
 
 st = true;

// Second
 S=0;
 
 randomSeed(0);
} 

void loop(){
 //second.showNum(S);
 S++;
 S%= 64;

 for(int i=0;i<7; i++){
 // leds[i].setState(random(i+2)==i+1%(i)); 
  leds[i].setGoal(random(3)==1); 
//  leds_ds[i] = leds[i].process();
  leds[i].process();
 }
 
  //if( leds_ds[0] )st = st? false : true;
  
 delay(random(10));    // ONLY LOOP DELAY

} 

