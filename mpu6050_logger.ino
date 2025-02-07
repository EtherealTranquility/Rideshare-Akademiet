#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

// Opprett objekt for MPU6050
MPU6050 mpu;

// Definer SD-kort pin
const int chipSelect = 4;

void initializeMPU() {
    Wire.begin();
    mpu.initialize();
    if (mpu.testConnection()) {
        Serial.println("MPU6050 tilkoblet!");
    } else {
        Serial.println("Kunne ikke koble til MPU6050!");
    }
}

/* SD-kort er ikke tilgjengelig for nå, denne delen er kommentert ut
bool initializeSD() {
    if (!SD.begin(chipSelect)) {
        Serial.println("SD-kortet kunne ikke initialiseres!");
        return false;
    }
    Serial.println("SD-kortet er initialisert.");
    return true;
}

void createCSVHeader() {
    File dataFile = SD.open("sensor_data.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println("Time(ms),Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z");
        dataFile.close();
    } else {
        Serial.println("Feil ved åpning av fil!");
    }
}
*/

void readSensorData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz) {
    mpu.getAcceleration(&ax, &ay, &az);
    mpu.getRotation(&gx, &gy, &gz);
}

void printSensorDataCSV(unsigned long currentTime, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz) {
    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(ax);
    Serial.print(",");
    Serial.print(ay);
    Serial.print(",");
    Serial.print(az);
    Serial.print(",");
    Serial.print(gx);
    Serial.print(",");
    Serial.print(gy);
    Serial.print(",");
    Serial.println(gz);
}

void setup() {
    Serial.begin(115200);
    initializeMPU();
    // if (initializeSD()) { createCSVHeader(); }  // SD-kort init er kommentert ut for nå
}

void loop() {
    int16_t ax, ay, az, gx, gy, gz;
    readSensorData(ax, ay, az, gx, gy, gz);
    printSensorDataCSV(millis(), ax, ay, az, gx, gy, gz);
    delay(500);
}
