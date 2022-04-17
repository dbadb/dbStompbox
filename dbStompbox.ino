/* a simple MIDI pedal-board inplementation
 *
 */
#include <Arduino.h>
#include <Bounce2.h>


// device-name found in midiName.c

/* ---------------------------------------------------------------------- */
enum Pins
{
    kSwitch0 = 0,
    kSwitch1 = 1,
    kSwitch2 = 2,
    kSwitch3 = 3,
    kSwitch4 = 4,
    kSwitch5 = 5,

    kLED = 13,

    kExpression0 = A9, // aka 23
    kExpression1 = A8, // aka 22
};

enum SwitchCCs
{
    kSCC0 = 64, // damperpedal 0/1
    kSCC1 = 65, // portamento 0/1
    kSCC2 = 66, // sostenuto 0/1
    kSCC3 = 67, // softpedal 0/1
    kSCC4 = 68, // legato 0/1
    kSCC5 = 69, // hold2 0/1
};

enum ExpCCs
{
    kExpCC0 = 8, // continuous controller 1  (CC 8-31)
    kExpCC1 = 9, // continuous controller 2
};

const int midiChannel = 1;
const int debounceTime = 5; // ms

Bounce button0 = Bounce(kSwitch0, debounceTime);
Bounce button1 = Bounce(kSwitch1, debounceTime);
Bounce button2 = Bounce(kSwitch2, debounceTime);
Bounce button3 = Bounce(kSwitch3, debounceTime);
Bounce button4 = Bounce(kSwitch4, debounceTime);
Bounce button5 = Bounce(kSwitch5, debounceTime);

void setup() 
{
    // Configure the pins for input mode with pullup resistors.
    // The pushbuttons connect from each pin to ground.  When
    // the button is pressed, the pin reads LOW because the button
    // shorts it to ground.  When released, the pin reads HIGH
    // because the pullup resistor connects to  VCC inside
    // the chip.  LOW for "on", and HIGH for "off" may seem
    // backwards, but using the on-chip pullup resistors is very
    // convenient.  The scheme is called "active low".

    pinMode(kSwitch0, INPUT_PULLUP);
    pinMode(kSwitch1, INPUT_PULLUP);
    pinMode(kSwitch2, INPUT_PULLUP);
    pinMode(kSwitch3, INPUT_PULLUP);
    pinMode(kSwitch4, INPUT_PULLUP);
    pinMode(kSwitch5, INPUT_PULLUP);

    pinMode(kLED, OUTPUT);

    pinMode(kExpression0, INPUT); // no pullup for analog read
    pinMode(kExpression1, INPUT); // no pullup for analog read
}

void loop() 
{
    // Update all the buttons.  There should not be any long
    // delays in loop(), so this runs repetitively at a rate
    // faster than the buttons could be pressed and released.
    static int sLastExp0 = 0;
    static int sLastExp1 = 0;
    static int sLoopCounter = 0;

    button0.update();
    button1.update();
    button2.update();
    button3.update();
    button4.update();
    button5.update();

    if(button0.fallingEdge())
        usbMIDI.sendControlChange(kSCC0, 127, midiChannel); // pressed
    else
    if(button0.risingEdge())
        usbMIDI.sendControlChange(kSCC0, 0, midiChannel); // released

    if(button1.fallingEdge())
        usbMIDI.sendControlChange(kSCC1, 127, midiChannel); // pressed
    else
    if(button1.risingEdge())
        usbMIDI.sendControlChange(kSCC1, 0, midiChannel); // released
    
    if(button2.fallingEdge())
        usbMIDI.sendControlChange(kSCC2, 127, midiChannel); // pressed
    else
    if(button2.risingEdge())
        usbMIDI.sendControlChange(kSCC2, 0, midiChannel); // released
    
    if(button3.fallingEdge())
        usbMIDI.sendControlChange(kSCC3, 127, midiChannel); // pressed
    else
    if(button3.risingEdge())
        usbMIDI.sendControlChange(kSCC3, 0, midiChannel); // released

    if(button4.fallingEdge())
        usbMIDI.sendControlChange(kSCC4, 127, midiChannel); // pressed
    else
    if(button4.risingEdge())
        usbMIDI.sendControlChange(kSCC4, 0, midiChannel); // released

    if(button5.fallingEdge())
        usbMIDI.sendControlChange(kSCC5, 127, midiChannel); // pressed
    else
    if(button5.risingEdge())
        usbMIDI.sendControlChange(kSCC5, 0, midiChannel); // released
    
    // if we want more resolution, we can employ 
    // setPitchBend(int value, int channel)
    // where values is [-8192, 8191]
    int exp0 = analogRead(kExpression0) >> 3; // take top 9 bits (from 12)
    int delta = exp0 - sLastExp0;
    if(delta < 0) delta = -delta;
    // bottom bit is noisy
    if(delta > 2)
    {
        usbMIDI.sendControlChange(kExpCC0, exp0, midiChannel);
        sLastExp0 = exp0;
    }

    int exp1 = analogRead(kExpression1) >> 3; // take top 9 bits (from 12)
    delta = exp1 - sLastExp1;
    if(delta < 0) delta = -delta;
    // bottom bit is noisy
    if(delta > 2)
    {
        usbMIDI.sendControlChange(kExpCC1, exp1, midiChannel);
        sLastExp1 = exp1;
    }
    
    // MIDI Controllers should discard incoming MIDI messages.
    // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
    while (usbMIDI.read()) {
        // ignore incoming messages
    }

    if(sLoopCounter++ == 100000)
    {
        sLoopCounter = 0;
        digitalWrite(kLED, HIGH);
    }
    else
    if(sLoopCounter == 50000)
    {
        digitalWrite(kLED, LOW);
    }
}
