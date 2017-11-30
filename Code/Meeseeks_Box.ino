// Made by Toglefritz

// Description:  This sketch controls the Particle Photon inside the Meeseeks Box IoT
// controller project. The hardware consists of a button connected to the D5 pin. The
// button is wired with a pull-down resistor to GND and a connection to 3.3V following
// the same design used in the Arduino state change detection tutorial. The sketch waits
// for the button to be pressed. Once pressed, the sketch counts the total number of button
// until there is a half second delay. The Particle Photon publishes an event to the Particle
// cloud depending upon the total number of button presses. This event can be used in an
// IFTTT applet to control many different connected home products.

const int button = 3;

int buttonPushCounter = 0;   // Counter for the number of button presses
int buttonState = 0;         // Current state of the button
int lastButtonState = 0;     // Previous state of the button
int previousTime = 0;        // The time the button was last pressed

void setup() {
    pinMode(button, INPUT);
}

void loop() {
    // If more than half a second has passed since the last time the
    // button was pressed, assume the user is done with the pattern and
    // sed a message to the cloud based on the number of times the button
    // was pressed.

    if(millis() - previousTime > 500 && buttonPushCounter != 0) {

        // If the button was pressed once, send a message to the cloud
        if(buttonPushCounter == 1) {
            Particle.publish("MeeseeksCount1");
        }
        else if(buttonPushCounter == 2) {
            Particle.publish("MeeseeksCount2");
        }
        else if(buttonPushCounter == 3) {
            Particle.publish("MeeseeksCount3");
        }
        else if(buttonPushCounter == 4) {
            Particle.publish("MeeseeksCount4");
        }
        else if(buttonPushCounter == 5) {
            Particle.publish("MeeseeksCount5");
        }
        else if(buttonPushCounter > 5) {
            Particle.publish("MeeseeksCount5+");
        }

        // After sending the message to the cloud, reset the counter and
        // the time
        buttonPushCounter = 0;
        previousTime = millis();
    }

    // Read the button state
    buttonState = digitalRead(button);

    // Compare the buttonState to its previous state. If the two are
    // different, a change as occured.
    if (buttonState != lastButtonState) {
        // If the current state is HIGH then the button went from off to on.
        if (buttonState == HIGH) {
            // Count the button press
            buttonPushCounter++;

            // Record the time of the button press
            previousTime = millis();
        }
    }

    // Delay a little bit to avoid bouncing
    delay(50);

    // Save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;
}
