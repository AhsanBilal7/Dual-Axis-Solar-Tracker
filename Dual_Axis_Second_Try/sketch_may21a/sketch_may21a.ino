#include <Servo.h> 


Servo horizontal; // horizontal servo
int servoh = 90; 
int servohLimitHigh = 175;
int servohLimitLow = 5;
// 65 degrees MAX

Servo vertical; // vertical servo
int servov = 90; 
int servovLimitHigh = 180;
int servovLimitLow = 5;

// LDR pin connections
// name = analogpin;
int ldrlt = A0; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = A3; //LDR top rigt - BOTTOM RIGHT
int ldrld = A1; //LDR down left - TOP LEFT
int ldrrd = A2; //ldr down rigt - TOP RIGHT

void setup(){
  Serial.begin(9600);
horizontal.attach(9,1000,2000);
vertical.attach(10 , 0 ,2000);
horizontal.write(45);
vertical.write(180);
delay(100);
}
void loop() {
int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right
int dtime = 10; int tol = 100; // dtime=diffirence time, tol=toleransi
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt

if (-1*tol > dvert || dvert > tol) 
 {
     if (avt > avd)
       {
       servov = (servov +5);
       if (servov > servovLimitHigh)
       {servov = servovLimitHigh;}
       }
     else if (avt < avd)
       {servov= (servov - 5);
       if (servov < servovLimitLow)
       { servov = servovLimitLow;}
       }
     // else if (avt == avd)
      // {
     //  delay(100);
     //  }
     vertical.write(servov);
 }

if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
 {
   if (avl > avr)
     {
     servoh = (servoh - 5);
     if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
     }  
   else if (avl < avr)
     {
     servoh = (servoh + 5);
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
     }
 //  else if (avl == avr)
  //   {
   //  delay(100);
  //   }
   horizontal.write(servoh);
 }

 delay(dtime);
 Serial.println("top Value is : ");
 Serial.print(avt);
 Serial.println("down Value is : ");
 Serial.print(avd);
 Serial.print("Servo Vertical : ");
 Serial.println(servov);
 Serial.print(" Servo Horizontal : ");
 Serial.println(servoh);
 
}
