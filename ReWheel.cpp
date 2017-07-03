// Do not remove the include below
#include "ReWheel.h"

#define PinA 3
#define PinB 4
#define PinRelayLeft 8  //left
#define PinRelayRight 9  //right
#define PinRelayDown 11 //down
#define PinRelayUp 12 //up




volatile long timeOfLastSwitch = 0;
volatile long count = 0;
long num = 0;
volatile long detaTsum = 0;
long rotationThreshold = 100;
long stopThreshold = 500;
long deltaA = 0;
long deltaB = 0;
long timeOfLastEvent = 0;
long interruptCounter = 0;
//long interruptCounter = 0;

void AChanged()
{
  if ((millis() - timeOfLastSwitch) >3 ){
        count ++;
        deltaA++;
        interruptCounter = 0;

        detaTsum += 10000/(millis() - timeOfLastSwitch);
        if(detaTsum >rotationThreshold){
        	//digitalWrite(PinRelayLeft,HIGH);

        	digitalWrite(PinRelayUp,LOW);
        }

  }
  if (interruptCounter > 2000000000)interruptCounter=0;
  interruptCounter++;
  timeOfLastSwitch = millis();
  if(interruptCounter > 30000)
  	  { Serial.println("A:off"); digitalWrite(PinRelayUp,HIGH);digitalWrite(PinRelayDown,HIGH);detaTsum=0;}


}

void BChanged()
{
  if ((millis() - timeOfLastSwitch) >3){
      count --;
      deltaB++;
      interruptCounter = 0;

      detaTsum -= 10000/(millis() - timeOfLastSwitch);
      if(detaTsum < -rotationThreshold){
      	//digitalWrite(PinRelayRight,HIGH);

          digitalWrite(PinRelayDown,LOW);
      }

}
  if (interruptCounter > 2000000000)interruptCounter=0;
  interruptCounter++;

  timeOfLastSwitch = millis();
  if(interruptCounter > 30000) { Serial.println("B:off");digitalWrite(PinRelayDown,HIGH);digitalWrite(PinRelayUp,HIGH);detaTsum=0;}



}


void setup()
{
  Serial.begin(9600);

  pinMode(PinA,INPUT);
  pinMode(PinB,INPUT);
	  pinMode(PinRelayDown,OUTPUT);
	  delay(1000);



  pinMode(PinRelayLeft,OUTPUT);
  pinMode(PinRelayRight,OUTPUT);
  pinMode(PinRelayDown,OUTPUT);
  pinMode(PinRelayUp,OUTPUT);

  for(int i=0;i<5;i++){
	  delay(1000);
	  digitalWrite(PinRelayDown,LOW);
	  delay(150);
	  digitalWrite(PinRelayDown,HIGH);
  }
  delay(1000);
  digitalWrite(PinRelayRight,LOW);
  delay(150);
  digitalWrite(PinRelayRight,HIGH);


  attachInterrupt(PinA, AChanged, LOW);
  //attachInterrupt(PinA, AChanged, HIGH);

  attachInterrupt(PinB, BChanged, LOW);
  //attachInterrupt(PinB, BChanged, HIGH);

  //delay(3000);

  timeOfLastSwitch = millis();

 // delay(1000);

  //digitalWrite(PinRelayRight,LOW);


}



void loop()
{

  if (num != count)
  {
	    Serial.println( detaTsum);
		Serial.print("A ");
		Serial.println(deltaA);
		Serial.print("B ");
		Serial.println(deltaB);
	 // if(num>count)
	//	  digitalWrite(PinRelayLeft,HIGH);
	 // else
	//	  digitalWrite(PinRelayLeft,LOW);

    num = count;
    Serial.println(num);
	Serial.println("________ ");
	 timeOfLastEvent = millis();
  }

  if(millis()-timeOfLastEvent > 500) {Serial.println("loop:off");digitalWrite(PinRelayDown,HIGH);digitalWrite(PinRelayUp,HIGH);detaTsum=0;}

}


