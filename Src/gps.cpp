#include "gps.h"
#include <Arduino.h>

float gps_enlem;
float gps_boylam;
unsigned long gps_age;// enlem boylam hesabı icin gerekli
int gps_yil;
byte gps_ay, gps_gun, gps_saat, gps_dakika, gps_saniye, hundredths;
unsigned long gps_age2;
float previous_time;
static GPS_t*	GPS;
TinyGPS gps;
SoftwareSerial gps_serial(2,3);

void setupgps(GPS_t*	GPS_){
  gps_serial.begin(9600);
  gps_serial.listen();
  GPS = GPS_;
}

void gps_verileri_al(){
  float start = millis();
  if(start-previous_time<1000){
    
    while (gps_serial.available()){
      gps.encode(gps_serial.read());
    }
    previous_time = start;
    gps.f_get_position(&gps_enlem,&gps_boylam,&gps_age);
    gps.crack_datetime(&gps_yil, &gps_ay, &gps_gun, &gps_saat, &gps_dakika, &gps_saniye, &hundredths, &gps_age2);
    GPS->s_baglanilan_uydu_sayisi = gps.satellites();
    GPS->s_gps_irtifa = gps.f_altitude();
    GPS->s_gps_hiz = gps.f_speed_kmph();
    GPS->s_gps_istikamet_acisi = gps.f_course();
    gps_saat+=3;
    if(gps_saat>=24){
      gps_saat=gps_saat-24;
    }
  }
}
