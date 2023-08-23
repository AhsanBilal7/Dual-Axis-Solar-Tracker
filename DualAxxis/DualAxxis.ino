#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopl = A2; //top left LDR green
int ldrtopr = A1; //top right LDR yellow
int ldrbotl = A3; // bottom left LDR blue
int ldrbotr = A0; // bottom right LDR orange

 void setup () 
 {
  servohori.attach(10);
  servohori.write(90);
  servoverti.attach(9);
  servoverti.write(90);
  Serial.begin(9600);
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs
     Serial.print("AvgTop: ");

     Serial.print(avgtop);
      Serial.println("AvgBot: ");

     Serial.print(avgbot);
  if (avgtop < avgbot)
  {
    servov = servov +1;
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    servoverti.write(servov);
    delay(10);
    
  }
  else if (avgbot < avgtop)
  { 
  servov =  servov -1 ;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  servoverti.write(servov);
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servoh = servoh +1;
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    servohori.write(servoh);
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servoh =  servoh -1;
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    servohori.write(servoh);
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
}
