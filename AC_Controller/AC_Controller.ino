/**
 * AC Controller
 */

#include <IRremote.h>
#include <dht.h>

#define DHT11_PIN A0

IRsend irsend;
dht DHT;

/**
 * Initial program setup.
 * Runs once at boot.
 */
void setup()
{
    Serial.begin(9600);
}

/**
 * Program loop.
 * This is functionally the main program lifecycle.
 */
void loop()
{
    // ------------------------
    // IR LED logic
    // ------------------------
    if (Serial.read() != -1)
    {
        // this is the timer button on my AC, which works as a good test
        // that doesn't require any configuration changes to the AC itself.
        irsend.sendNEC(0x8166F906, 32);
    }
    
    // -------------------------
    // DHT 11 output
    // -------------------------
    int dhtStatus = DHT.read11(DHT11_PIN);
    
    if (dhtStatus == DHTLIB_OK)
    {
        Serial.print("Humidity: ");
        Serial.print(DHT.humidity, 2);
        Serial.println("");
        
        Serial.print("Temp Cel: ");
        Serial.print(DHT.temperature, 2);
        Serial.println("");
        
        Serial.print("---");
        Serial.println("");
    }
    else
    {
        Serial.print("Something's wrong.");
        Serial.println("");
        
        Serial.print("---");
        Serial.println("");
    }
    
    // we can only read the DHT so fast, so a delay here.
    delay(2000);
}
