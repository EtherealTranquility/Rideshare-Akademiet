#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>

// Opprett objekt for MPU6050
MPU6050 mpu;

// Definer SD-kort pin (ikke i bruk akkurat nå)
const int chipSelect = 4;

// Initialiserer MPU6050-sensoren
void initializeMPU()
{
    Wire.begin();
    mpu.initialize();
    
    if (mpu.testConnection())
    {
        Serial.println("MPU6050 tilkoblet!");
    }
    else
    {
        Serial.println("Kunne ikke koble til MPU6050!");
    }
}

/* SD-kort er ikke tilgjengelig for nå, denne delen er kommentert ut
bool initializeSD()
{
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD-kortet kunne ikke initialiseres!");
        return false;
    }
    Serial.println("SD-kortet er initialisert.");
    return true;
}

// Oppretter CSV-header hvis filen er ny
void createCSVHeader()
{
    File dataFile = SD.open("sensor_data.csv", FILE_WRITE);
    if (dataFile)
    {
        dataFile.println("Time(ms),Accel_X,Accel_Y,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z");
        dataFile.close();
    }
    else
    {
        Serial.println("Feil ved åpning av fil!");
    }
}
*/

// Leser akselerometer- og gyroskopdata fra MPU6050
void readSensorData(int16_t &ax, int16_t &ay, int16_t &az, int16_t &gx, int16_t &gy, int16_t &gz)
{
    mpu.getAcceleration(&ax, &ay, &az);
    mpu.getRotation(&gx, &gy, &gz);
}

// Skriver sensorverdier til Serial Monitor i CSV-format
void printSensorDataCSV(unsigned long currentTime, int16_t ax, int16_t ay, int16_t az, int16_t gx, int16_t gy, int16_t gz)
{
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

void setup()
{
    Serial.begin(115200); // Starter seriell kommunikasjon
    initializeMPU(); // Initialiserer MPU6050
    // if (initializeSD()) { createCSVHeader(); }  // SD-kort init er kommentert ut for nå
}

void loop()
{
    int16_t ax, ay, az, gx, gy, gz; // Variabler for sensorverdier
    
    readSensorData(ax, ay, az, gx, gy, gz); // Leser sensorverdier
    printSensorDataCSV(millis(), ax, ay, az, gx, gy, gz); // Skriver til Serial Monitor i CSV-format
    
    delay(500); // Vent 500 ms før neste måling
}
