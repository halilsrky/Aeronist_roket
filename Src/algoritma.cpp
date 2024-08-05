#include "Arduino.h"
#include "algoritma.h"

bool thetaKontrol = true;
bool ucusKontrol = true;
bool bekleKontrol = false;
bool armingKontrol = false;
bool parasutBirKontrol = false;
bool parasutIkiKontrol = false;


const int buzzerPin = 16;
bool buzzerActive = false;
unsigned long buzzerStartTime = 0;
unsigned long ucusStartTime = 0;
const unsigned long buzzerDuration = 1000;
float oncekiIrtifa = 0;
int sayac = 0;

void buzzerControl() {
  unsigned long currentMillis = millis();
  if (buzzerActive) {
    if (currentMillis - buzzerStartTime <= 200) {
      digitalWrite(buzzerPin, HIGH);  
    }else {
      digitalWrite(buzzerPin, LOW);  
      buzzerActive = false;  
    }
  }
}

/*void buzzerControl() {
  unsigned long currentMillis = millis();
  if (buzzerActive) {
    if (currentMillis - buzzerStartTime <= 500) {
      digitalWrite(buzzerPin, HIGH);  
    }
    else if (currentMillis - buzzerStartTime <= 800) {
      digitalWrite(buzzerPin, LOW);  
    }
    else if (currentMillis - buzzerStartTime <= 1300) {
      digitalWrite(buzzerPin, HIGH);  
    }
    else if (currentMillis - buzzerStartTime <= 1600) {
      digitalWrite(buzzerPin, LOW);  
    }
    else if (currentMillis - buzzerStartTime <= 2600) {
      digitalWrite(buzzerPin, HIGH);  
    } else {
      digitalWrite(buzzerPin, LOW);  
      buzzerActive = false;  
    }
  }
}*/


void algoritma1(BME_280_t* BME, dso32_struct_t* DSO) {
pinMode(16, OUTPUT);
DSO->durum = 1;
float GForce = sqrt(DSO->acc_x * DSO->acc_x + DSO->acc_y * DSO->acc_y + DSO->acc_z * DSO->acc_z) / 9.81;
unsigned long currentMillis = millis();

if(GForce > 3 && ucusKontrol){

 /* Serial.println("                        ");
  Serial.println("*******************************************");
  Serial.println("*******************************************");
  Serial.print("UCUS BASLADI        G KUVVETI: ");
  Serial.println(GForce);
  Serial.println("*******************************************");
  Serial.println("*******************************************");
  Serial.println("                        ");*/
  DSO->durum = 2;
  buzzerActive = true;
  buzzerStartTime = millis();
  ucusKontrol = false;
  ucusStartTime = millis();
}

if(((int)currentMillis - (int)ucusStartTime) > 7000 && !ucusKontrol && !bekleKontrol){
 /* Serial.println("                        ");
  Serial.println("*******************************************");
  Serial.println("*******************************************");
  Serial.println("7 SANIYE GECTI");
  Serial.println("*******************************************");
  Serial.println("*******************************************");
  Serial.println("                        ");*/
  bekleKontrol = true;
}


if (BME->altitude > 10 && bekleKontrol) {
  armingKontrol = true;
}


if ((DSO->theta > 70) && thetaKontrol && armingKontrol) {
 /* Serial.println("                        ");
  Serial.println("*******************************************");  
  Serial.println("*******************************************");
  Serial.println("THETA > 70 DERECE      1.PARASUT ACILDI");
  Serial.println("*******************************************");
  Serial.println("*******************************************");
  Serial.println("                        ");*/
  DSO->durum = 4;
  buzzerActive = true;
  buzzerStartTime = millis();
  parasutBirKontrol = true;
  thetaKontrol = false;
}

/*if(armingKontrol && ((BME->altitude + 0.5) < oncekiIrtifa) && !parasutBirKontrol){
  sayac++;
  if(armingKontrol && (sayac > 5)){
  Serial.println("                        ");
  Serial.println("*******************************************");  
  Serial.println("*******************************************");
  Serial.println("IRTIFA AZAZLIYOR       1.PARASUT ACILDI");
  Serial.println("*******************************************");
  Serial.println("*******************************************"); 
  Serial.println("                        "); 
  buzzerActive = true;
  buzzerStartTime = millis();
  parasutBirKontrol = true;
  armingKontrol = 0;
  }
}else{
  sayac = 0;
}*/

if(parasutBirKontrol && BME->altitude < 10 && !parasutIkiKontrol){
 /* Serial.println("                        ");
  Serial.println("*******************************************");  
  Serial.println("*******************************************");
  Serial.println("IRTIFA < 500       2.PARASUT ACILDI");
  Serial.println("*******************************************");
  Serial.println("*******************************************"); */
  buzzerActive = true;
  buzzerStartTime = millis();
  parasutIkiKontrol = true;
}

buzzerControl();

oncekiIrtifa = BME->altitude;


}