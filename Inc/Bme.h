#include <stdint.h>
#ifndef BME_H
#define BME_H

#include <BME280I2C.h>

typedef struct BME280_struct
{
  float temperature;
	float pressure;
	uint8_t humidity;
	float height;
	volatile float altitude;
	volatile float baseAltitude;
  uint8_t isUpdated;

}BME_280_t;

void setupbme(BME_280_t*	BME_);
void bme280_update();



#endif