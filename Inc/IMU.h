#include <stdint.h>
#ifndef IMU_H
#define IMU_H

// For SPI mode, we need a CS pin
#define LSM_CS 10
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK 13
#define LSM_MISO 12
#define LSM_MOSI 11

#include <Adafruit_LSM6DSO32.h>
#include "quaternion.h"
#include "MahonyAHRS.h"



typedef struct dso32_struct
{
	int16_t offsetData;
  uint8_t durum;
	double gyro_x, gyro_y, gyro_z;
	float delta_angle_x, delta_angle_y, delta_angle_z;
	float acc_x, acc_y, acc_z;
	float theta;
  float MahonyTheta;
	float currentTime, lastTime;
	float deltaTime, prevTime;

}dso32_struct_t;

void setupimu(dso32_struct_t* DSO_);
float getTheta();
void calculateOffset();
void dso32_update();
void measureFrequency();

#endif
