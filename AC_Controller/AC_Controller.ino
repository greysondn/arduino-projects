/**
 * AC Controller
 *
 * This would have been impossible without the work of the following people:
 * - Ken Shariff (IR library and original ir testing/example code)
 */

#include <IRremote.h>

IRsend irsend;

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
    if (Serial.read() != -1)
    {
        // this is the timer button on my AC, which works as a good test
        // that doesn't require any configuration changes to the AC itself.
        irsend.sendNEC(0x8166F906, 32);
    }
}
