#ifndef PAKET_H
#define PAKET_H

#include "Bme.h"
#include "IMU.h"
#include "gps.h"

typedef union{
	float           sayi;
	unsigned char   array[4];
}FLOAT32_UINT8_DONUSTURUCU;

unsigned char check_sum_hesapla();

void addDataPacket(BME_280_t* BME, dso32_struct_t* DSO);//, GPS_t* GPS);


#endif
