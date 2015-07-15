/**
 * AC Controller
 */

#include <IRremote.h>
#include <dht.h>

// Analog input pin for DHT11
#define DHT11_PIN A0

// codes for remote controller
#define RM_POWER      0x8166817E
#define RM_TEMP_DOWN  0x816651AE
#define RM_TEMP_UP    0x8166A15E
#define RM_FAN_SPEED  0x81669966
#define RM_TIMER      0x8166F906
#define RM_MODE       0x8166D926

// whether or not the AC is on
int ac_on = false;

// temperature and humidity
float temperature = -1.0;
float humidity    = -1.0;

IRsend irsend;
dht DHT;

/**
 * Gets temp and humidity from DHT11 and stashes them in globals
 */
void getDHT()
{
      DHT.read11(DHT11_PIN);
      humidity = DHT.humidity;
      temperature = DHT.temperature;
}

/**
 * fires a controller code for power
 */
void flipPower()
{
    irsend.sendNEC(RM_POWER, 32);
    ac_on = !ac_on;
}


/**
 * Initial program setup.
 * Runs once at boot.
 */
void setup()
{
    // use this to show power status
    pinMode(13, OUTPUT);
}

/**
 * Program loop.
 * This is functionally the main program lifecycle.
 */
void loop()
{
    // so... let's begin!
    getDHT();
    
    // if it's too hot and the AC is off
    if ((temperature > 25) && (!ac_on))
    {
          // turn the AC on!
          flipPower();
          
          // turn LED on so we know the AC should be on
          digitalWrite(13, HIGH);
    }
    
    // if it's too cold and the AC is on
    if ((temperature < 21) && (ac_on))
    {
        // turn the AC off!
        flipPower();
        
        // turn LED on so we know the AC should be on
        digitalWrite(13, LOW);
    }
    
    // we can only read the DHT so fast, so a delay here.
    delay(2000);
}
