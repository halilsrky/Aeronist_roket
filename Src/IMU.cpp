#include "IMU.h"
#include <Arduino.h>
#include "math.h"

Adafruit_LSM6DSO32 dso32;

static dso32_struct_t* DSO;

double yenigyrox = 0.0;
double yenigyroz = 0.0;
double yenigyroy = 0.0;
unsigned long deltaTime = 0;
unsigned long lastTime = 0;
sensors_event_t accel;
sensors_event_t gyro;
sensors_event_t temp;
float Theta;
float Theta_;
float currentTime;
unsigned long prevTime;
int numSamples = 1000;
float sumX = 0.0, sumY = 0.0, sumZ = 0.0;
float sumAccelX = 0.0, sumAccelY = 0.0, sumAccelZ = 0.0;
float gyroBiasX = 0.0, gyroBiasY = 0.0, gyroBiasZ = 0.0;
int sayac1 = 0;

Mahony ahrs;

void setupimu(dso32_struct_t* DSO_){
  Serial.begin(115200);
    while (!Serial)
      delay(10); 

    if (!dso32.begin_I2C()) {
    }

    dso32.setAccelRange(LSM6DSO32_ACCEL_RANGE_8_G);
    dso32.getAccelRange();
    dso32.getGyroRange();
    dso32.setAccelDataRate(LSM6DS_RATE_12_5_HZ);
    dso32.getAccelDataRate();
    dso32.setGyroDataRate(LSM6DS_RATE_12_5_HZ);
    dso32.getGyroDataRate();
    

    DSO = DSO_;
}

void dso32_update(){

  if(dso32.getEvent(&accel, &gyro, &temp)){
    currentTime = (float)micros() / 1000.0f;
    float dt = (currentTime - prevTime) / 1000.0f;
    prevTime = currentTime;

    DSO->acc_x = accel.acceleration.x;
    DSO->acc_y = accel.acceleration.y;
    DSO->acc_z = accel.acceleration.z;
    DSO->gyro_x = gyro.gyro.x - gyroBiasX;
    DSO->gyro_y = gyro.gyro.y - gyroBiasY;
    DSO->gyro_z = gyro.gyro.z - gyroBiasZ;

    yenigyrox = (gyro.gyro.x - gyroBiasX);
    yenigyroy = (gyro.gyro.y - gyroBiasY);
    yenigyroz = (gyro.gyro.z - gyroBiasZ);

   // initialQuaternion(yenigyroy, yenigyroz, yenigyrox, -accel.acceleration.y, -accel.acceleration.z, -accel.acceleration.x);
    updateQuaternion(yenigyroy*180/PI, yenigyroz*180/PI, yenigyrox*180/PI, dt);
    quaternionToTheta(&Theta_);
   // ahrs.updateIMU(yenigyroy, yenigyroz, yenigyrox, -accel.acceleration.y, -accel.acceleration.z, -accel.acceleration.x);
  //  DSO->MahonyTheta = ahrs.getMahonyTheta();
    DSO->theta = Theta_;
    sayac1++;
  }
}
 

void calculateOffset(){
  delay(1000);
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  dso32.getEvent(&accel, &gyro, &temp);

  for(int a = 0; a < 1000; a++) {
    while(!dso32.getEvent(&accel, &gyro, &temp));
    sumX += gyro.gyro.x;
    sumY += gyro.gyro.y;
    sumZ += gyro.gyro.z;
  }
   
  gyroBiasX = sumX / 1000.0f;
  gyroBiasY = sumY / 1000.0f;
  gyroBiasZ = sumZ / 1000.0f;
  
}
unsigned long startMillis;

float CurrentTime, prevTime3 = 0;

void measureFrequency() {
  unsigned long CurrentMillis = millis();
  if (CurrentMillis - startMillis >= 1000) {
    Serial.print("Frequency: ");
    Serial.print(sayac1);
    Serial.println(" Hz");
    sayac1 = 0;
    startMillis = CurrentMillis;
  }
}



