#ifndef QUATERNION_H
#define QUATERNION_H

#include <math.h> 
//#include "MahonyAHRS.h"

typedef struct {
  float w, x, y, z;
} Quaternion;

Quaternion quaternion_create(float w, float x, float y, float z);
Quaternion quaternion_get_derivative(Quaternion q, float gx, float gy, float gz);
void quaternion_normalize(Quaternion *q);

void quaternionToTheta(float* theta);
void updateQuaternion(float gx, float gy, float gz, float dt);
//void initialQuaternion(float gx, float gy, float gz, float ax, float ay, float az);

#endif // QUATERNION_H