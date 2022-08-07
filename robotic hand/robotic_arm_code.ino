
#include<Servo.h>
#define numOfValsRec 5 //5 values
#define digitsPerValRec 1 // analog in

Servo servoThumb;
Servo servoIndex;
Servo servoMid;
Servo servoRing;
Servo servoSmall;


int valsRec[numOfValsRec];

//$00000

int stringLength=numOfValsRec * digitsPerValRec +1;
int counter = 0;
bool counterStart = false;
String recivedString;


void setup() {
  Serial.begin(9600);

  servoThumb.attach(7);
  servoIndex.attach(9);
  servoMid.attach(11);
  servoRing.attach(8);
  servoSmall.attach(10);

}

void recieveData() {
  while(Serial.available())
  {
    char c = Serial.read();
    if(c=='$'){
      counterStart=true;
      
    }
    if(counterStart){
      if(counter < stringLength){
        recivedString = String(recivedString + c);
        counter++;
      }
      if(counter >=stringLength){
        for(int i = 0; i<numOfValsRec; i++)
        {
          int num= (i*digitsPerValRec)+1;
        
        valsRec[i] = recivedString.substring(num,num+digitsPerValRec).toInt();
        }
        recivedString = "";
        counter=0;
        counterStart = false;
      }
    }



    
    
  }
}

void loop() {
  
recieveData();
if (valsRec[0] ==1){servoThumb.write(80);} else{servoThumb.write(0);}
if (valsRec[1] ==1){servoIndex.write(90);} else{servoIndex.write(0);}
if (valsRec[2] ==1){servoMid.write(90);} else{servoMid.write(0);}
if (valsRec[3] ==1){servoRing.write(90);} else{servoRing.write(0);}
if (valsRec[4] ==1){servoSmall.write(90);} else{servoSmall.write(0);}
}
