#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>

// Konfigurerbare verdier
#define BAUD_RATE 9600 // Angir hastigheten på seriell kommunikasjon (baud, "bits per second"). Komponentene våre skal støtte opptil 1Mbps
#define CHIP_SELECT_PIN 10 // Chip select (CS) pin for SD-kortet
#define SD_MAX_RETRIES 20 // Antall ganger det skal forsøkes å initialisere SD-kortet før hard stopp
#define SAMPLE_DELAY 100 // 10ms = 100Hz
#define ACCEL_SENSITIVITY 2048.0 // Følsomhet for akselerometer (LSB/g)
#define GYRO_SENSITIVITY 131.0 // Følsomhet for gyroskop (LSB/°/s)
#define GRAVITY 9.819
#define DECIMALS 10 // Desimalpresisjon for utskrift og logging
#define ENABLE_SERIAL_OUTPUT true // Global bryter for å aktivere/deaktivere seriell utskrift (for debugging eller logging til PC)
#define LIFTOFF_THRESHOLD_G 1.5  // Antall g som kreves på Z-aksen for å starte logging
#define FILENAME "data.txt" 

// Opprett objekt for MPU6050
MPU6050 mpu;

// Globale verdier for akselerometer- og gyroskopdata
float ax, ay, az, gx, gy, gz;

// Tidspunktet loggingen starter
unsigned long startTime = 0; 

// Liftoff!
bool airborne = false;

File dataFile;

// setup() kjøres én gang når Arduino får strøm eller resettes, dette er "entry pointet" til programmet
void setup()
{
    Serial.begin(BAUD_RATE); // Starter seriell kommunikasjon med PC-en for debugging og dataoverføring
    initializeMPU();
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_16); // Setter akselerometerets måleområde til ±16g
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);  // Setter gyroskopets måleområde til ±250°/s
    setOffsets();
    initializeSD();
    createCSVHeader();
}

// Stopper programmet helt og skriver ut en feilmelding til Serial Monitor
void hardStop(const char* error_message)
{
    if (ENABLE_SERIAL_OUTPUT)
    {
        Serial.println(error_message);
    }
    while (true) // Fryser programmet
    {
        Serial.println("Kritisk feil!");
    }
}

// Setter opp I2C-kommunikasjon og sjekker at MPU6050 er riktig tilkoblet, gir feilmelding dersom det mislykkes
void initializeMPU()
{
    Wire.begin(); // Initialiserer I2C-kommunikasjon for å koble til sensorer og hente data
    mpu.initialize();
    if (mpu.testConnection())
    {
        if (ENABLE_SERIAL_OUTPUT)
        {
            Serial.println("MPU6050 tilkoblet!");
        }
    }
    else
    {
        hardStop("Kunne ikke koble til MPU6050!");
    }
}

// Setter offset-verdier for akselerometer og gyroskop for å kompensere for sensorfeil
// Verdiene er hentet fra "IMU_Zero.ino", som brukes til å kalibrere MPU6050-sensoren
void setOffsets()
{
    mpu.setXAccelOffset(-5147);
    mpu.setYAccelOffset(-2742);
    mpu.setZAccelOffset(1461);
    mpu.setXGyroOffset(6);
    mpu.setYGyroOffset(-14);
    mpu.setZGyroOffset(38);
}

// Denne funksjonen kobler til SD-kortet, og prøver å koble til flere ganger hvis tilkoblingen mislykkes
void initializeSD()
{
    /* ChatGPT foreslo og teste koden etter å kalle disse to funksjonene, har ikke fått prøvd enda.
    pinMode(CHIP_SELECT_PIN, OUTPUT); 
    digitalWrite(CHIP_SELECT_PIN, HIGH);
    */
    int attempts = SD_MAX_RETRIES;
    while (!SD.begin(CHIP_SELECT_PIN)) // Prøv flere ganger til SD-kortet er tilgjengelig
    {
        attempts--;
        if (!attempts)
        {
            hardStop("Kunne ikke initialisere SD-kortet etter flere forsøk.");
        }
        if (ENABLE_SERIAL_OUTPUT)
        {
            Serial.println("Feil ved initialisering av SD-kortet. Prøver på nytt...");
        }
        delay(1000); // Vent et sekund før nytt forsøk
    }
    if (ENABLE_SERIAL_OUTPUT)
    {
        Serial.println("SD-kortet er initialisert.");
    }
}

// Oppretter CSV-header hvis filen er ny, eller sletter den eksisterende og skriver header på nytt, gir feilmelding dersom det mislykkes
void createCSVHeader()
{
    // SD.remove("sensor_data.csv"); // Sletter eksisterende fil hvis den finnes, for å starte med en tom fil
    dataFile = SD.open(FILENAME, FILE_WRITE); // Åpner filen i WRITE-modus, dette overskriver eksisterende innhold
    if (dataFile)
    {
        dataFile.println("time(ms),ax,ay,az,gx,gy,gz"); // Skriver header for CSV-filen
        dataFile.close();
        while (1)
        {
            Serial.print("FILEN ER LAGET!");
        }
    }
    else
    {
        while (true) {
            Serial.println("Feil ved åpning av fil!");
        }
    }
}

int i = 5000;

// Hovedløkken som kontinuerlig leser og skriver sensorverdier (kjører etter setup-funksjonen)
void loop()
{   
    readSensorData();
    if (ENABLE_SERIAL_OUTPUT) // Skriver data til Serial Monitor hvis aktivert
    {
        printSensorDataCSV();
    }
    /*
    logDataToSD();
    i--;
    if (i == 0)
    {
        return;
    }
    */
    
    /*
    float effective_az = az - 1.0; // Beregner effektiv akselerasjon på Z-aksen, justert for 1g
    if (effective_az > LIFTOFF_THRESHOLD_G)) // Sjekker om den effektive akselerasjonen er større enn terskelen for liftoff
    {
        startTime = millis();
        airborne = true;
        while (airborne)
        {
            readSensorData();
            logDataToSD();
            delay(SAMPLE_DELAY);
        }

    }
    */
    
    delay(SAMPLE_DELAY);
}

// Leser akselerometer- og gyroskopdata fra MPU6050
void readSensorData()
{
    int16_t ax_sensor, ay_sensor, az_sensor; // Rå akselerometerdata fra sensoren
    mpu.getAcceleration(&ax_sensor, &ay_sensor, &az_sensor);

    ax = (float)ax_sensor / ACCEL_SENSITIVITY; 
    ay = (float)ay_sensor / ACCEL_SENSITIVITY;
    az = (float)az_sensor / ACCEL_SENSITIVITY;

    int16_t gx_sensor, gy_sensor, gz_sensor; // Rå gyroskopdata fra sensoren
    mpu.getRotation(&gx_sensor, &gy_sensor, &gz_sensor);

    gx = (float)gx_sensor / GYRO_SENSITIVITY;
    gy = (float)gy_sensor / GYRO_SENSITIVITY;
    gz = (float)gz_sensor / GYRO_SENSITIVITY;
}

// Skriver sensorverdier til Serial Monitor (Merk, ikke CSV-format for lesbarhet)
void printSensorData()
{
    Serial.print("Tid: ");   Serial.print(millis() - startTime);
    Serial.print("   ax: "); Serial.print(ax, DECIMALS);
    Serial.print("   ay: "); Serial.print(ay, DECIMALS);
    Serial.print("   az: "); Serial.print(az, DECIMALS);
    Serial.print("   gx: "); Serial.print(gx, DECIMALS);
    Serial.print("   gy: "); Serial.print(gy, DECIMALS);
    Serial.print("   gz: "); Serial.print(gz, DECIMALS);
    Serial.print("\n");
}

// Skriver sensorverdier til Serial Monitor i CSV-format (for enkel eksport og videre behandling)
void printSensorDataCSV()
{
    Serial.print(millis() - startTime); Serial.print(",");
    Serial.print(ax, DECIMALS);         Serial.print(",");
    Serial.print(ay, DECIMALS);         Serial.print(",");
    Serial.print(az, DECIMALS);         Serial.print(",");
    Serial.print(gx, DECIMALS);         Serial.print(",");
    Serial.print(gy, DECIMALS);         Serial.print(",");
    Serial.print(gz, DECIMALS);         Serial.print("\n");
}

// Skriver sensorverdier til SD-kort i CSV-format
void logDataToSD()
{
    /*
    NB: Filen åpnes og lukkes hver gang, noe som gir lav ytelse og høyere risiko for datakorrupsjon.
    Potensiell løsning: Gjør `File dataFile` til en global variabel som åpnes én gang etter liftoff og lukkes etter landing. 
    */
    File dataFile = SD.open(FILENAME, FILE_WRITE);
    if (dataFile)
    {
        dataFile.print(millis() - startTime); dataFile.print(",");
        dataFile.print(ax, DECIMALS);         dataFile.print(",");
        dataFile.print(ay, DECIMALS);         dataFile.print(",");
        dataFile.print(az, DECIMALS);         dataFile.print(",");
        dataFile.print(gx, DECIMALS);         dataFile.print(",");
        dataFile.print(gy, DECIMALS);         dataFile.print(",");
        dataFile.print(gz, DECIMALS);         dataFile.print("\n");
        dataFile.close();
    }
    else
    {
        if (ENABLE_SERIAL_OUTPUT)
        {
            Serial.println("Feil ved åpning av fil for skriving!");
        }
    }
}