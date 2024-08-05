#ifndef GPS_H
#define GPS_H
#include <SoftwareSerial.h>
#include <TinyGPS.h>

typedef struct GPS_struct
{
  uint8_t s_baglanilan_uydu_sayisi;
  float s_gps_enlem;
  float s_gps_boylam;
  unsigned long s_gps_age;// enlem boylam hesabı icin gerekli
  float s_gps_irtifa;
  float s_gps_hiz;
  float s_gps_istikamet_acisi;
  int s_gps_yil;
  byte s_gps_ay, s_gps_gun, s_gps_saat, s_gps_dakika, s_gps_saniye, s_hundredths;
  unsigned long s_gps_age2;
  float s_bitis_zamani;
}GPS_t;

void setupgps(GPS_t*	GPS_);
void gps_verileri_al();

#endif