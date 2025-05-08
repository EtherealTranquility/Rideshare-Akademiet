#include <SPI.h>
#include <SD.h>

// Konfigurerbare verdier
#define BAUD_RATE 115200 // Hastighet for seriell kommunikasjon
#define CHIP_SELECT_PIN 4 // Chip select (CS) pin for SD-kortet

void setup()
{
    Serial.begin(BAUD_RATE); // Starter seriell kommunikasjon
    while (!SD.begin(CHIP_SELECT_PIN)) // Forsøk å initialisere SD-kortet
    {
        Serial.println("Kunne ikke initialisere SD-kortet. Prøver igjen...");
        delay(1000);
    }
    Serial.println("SD-kortet er initialisert.");
    File dataFile = SD.open("sensor_data.csv");
    if (dataFile)
    {
        Serial.println("Innhold i 'sensor_data.csv':"); 
        while (dataFile.available()) // Sjekker om det er flere bytes som kan leses
        {
            Serial.write(dataFile.read()); // Leser en byte av gangen og skriver det til Serial Monitor
        }
        dataFile.close();
    }
    else
    {
        Serial.println("Kunne ikke åpne fil for lesing!");
    }
}

void loop() {}
