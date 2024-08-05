#include <Adafruit_LSM6DSO32.h>
#include <SoftwareSerial.h>
#include "IMU.h"
#include "algoritma.h"
#include "Bme.h"
#include "packet.h"
#include "gps.h"


#define RX_PIN 9
#define TX_PIN 10

SoftwareSerial Telemetri(RX_PIN, TX_PIN);

extern unsigned char olusturalacak_paket[59];

static BME_280_t bme28;
static dso32_struct_t dso;
static GPS_t gps2;

void setup(void) {
  Serial.begin(115200);
  Telemetri.begin(115200);

  Wire.begin();
  while(!Serial) {}

 
 // setupgps(&gps2);
  setupimu(&dso);
  calculateOffset();
  setupbme(&bme28);

}



//Serial1 gps


void loop() {

  bme280_update();
  dso32_update();
  measureFrequency();
  //gps_verileri_al();

  
  addDataPacket(&bme28, &dso);// , &gps2);


  float currentTime = (float)millis();
  static float prevTime2;

  if (currentTime - prevTime2 >= 1000){
    prevTime2 = currentTime;
    algoritma1(&bme28, &dso);
    Serial.print("A:-90,B:90,");
    Serial.print("Theta:");
    Serial.print(dso.theta);
    Serial.print(",Mahony_Theta:");
    Serial.println(0);
   // Serial.write(olusturalacak_paket, sizeof(olusturalacak_paket));
}
}