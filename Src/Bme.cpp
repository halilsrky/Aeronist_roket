#include <stdint.h>
#include "Bme.h"
#include <Arduino.h>
#include "math.h"
#include <Wire.h>

static BME_280_t*	BME;

// Sensor ayarlari seciliyor
BME280I2C::Settings settings(
BME280::OSR_X1,
BME280::OSR_X1,
BME280::OSR_X1,
BME280::Mode_Forced,
BME280::StandbyTime_1000ms,
BME280::Filter_16,
BME280::SpiEnable_False,
BME280I2C::I2CAddr_0x76
);

BME280I2C bme(settings); // Secilen ayarlar ataniyor

// Sensor baslatiliyor 
void setupbme(BME_280_t*	BME_){

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  bme.chipModel();
  BME = BME_;

}

// Sensoden veri aliniyor
void bme280_update(){

  float temp(NAN), hum(NAN), pres(NAN);

  BME280::TempUnit tempUnit(BME280::TempUnit_Celsius); // Sicaklik birimi seciliyor
  BME280::PresUnit presUnit(BME280::PresUnit_hPa); // Basinc birimi seciliyor

  bme.read(pres, temp, hum, tempUnit, presUnit);
  
  float p_seaLevel = 1013.25;		//hPa

  BME->temperature = temp;
  BME->humidity = (uint8_t)hum;
  BME->pressure = pres;
  BME->altitude = 44330.0 * (1.0 - pow((pres / p_seaLevel), (1.0 / 5.255))); //Irtifa hesaplaniyor
  
}