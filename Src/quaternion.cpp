#include "quaternion.h"

//Mahony mahony;

// Helper function to convert degrees to radians
static inline float radians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

// Create a Quaternion with specified values
Quaternion quaternion_create(float w, float x, float y, float z) {
    Quaternion q;
    q.w = w;
    q.x = x;
    q.y = y;
    q.z = z;
    return q;
}

// Calculate the derivative of the quaternion
Quaternion quaternion_get_derivative(Quaternion q, float gx, float gy, float gz) {
    Quaternion qDot;
    qDot.w = -q.x * gx - q.y * gy - q.z * gz;
    qDot.x = q.w * gx + q.y * gz - q.z * gy;
    qDot.y = q.w * gy - q.x * gz + q.z * gx;
    qDot.z = q.w * gz + q.x * gy - q.y * gx;
    return qDot;
}

// Normalize the quaternion
void quaternion_normalize(Quaternion *q) {
    float norm = sqrt(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
    if (norm > 0.0f) {
        float invNorm = 1.0f / norm;
        q->w *= invNorm;
        q->x *= invNorm;
        q->y *= invNorm;
        q->z *= invNorm;
    }
}



// Global quaternion instance
Quaternion q = {1, 0, 0, 0};

/*bool initialFlag = 1;

void initialQuaternion(float gx, float gy, float gz, float ax, float ay, float az){
  if(initialFlag){
      for (int i = 0; i < 300; i++) {
        mahony.updateIMU(gx, gy, gz, ax, ay, az);
      }
      q = quaternion_create(mahony.getQ0(), mahony.getQ1(), mahony.getQ2(), mahony.getQ3());
      initialFlag = 0;
  }
}*/

// Update the global quaternion with new gyroscope data
void updateQuaternion(float gx, float gy, float gz, float dt) {
    // Convert gyroscope data from degrees/sec to radians/sec
    gx = radians(gx);
    gy = radians(gy);
    gz = radians(gz);

    // Calculate the quaternion derivative
    Quaternion qDot = quaternion_get_derivative(q, gx, gy, gz);

    // Integrate the quaternion derivative to get the new quaternion
    q.w += qDot.w * dt * 0.5f;
    q.x += qDot.x * dt * 0.5f;
    q.y += qDot.y * dt * 0.5f;
    q.z += qDot.z * dt * 0.5f;

    // Normalize the quaternion to avoid drift
    quaternion_normalize(&q);
}


void quaternionToTheta(float* theta){
  float r13 = 2 * q.x * q.z + 2 * q.y * q.w;
  float r23 = 2 * q.y * q.z - 2 * q.x * q.w;
  float r33 = 1 - 2 * q.x * q.x - 2 * q.y * q.y;

  float z_x = r13;
  float z_y = r23;
  float z_z = r33;
  
  float dotProduct = z_z;
  float magnitude = sqrt(z_x * z_x + z_y * z_y + z_z * z_z);

  *theta = acos(dotProduct / magnitude) * 180.0 / 3.14;
}
