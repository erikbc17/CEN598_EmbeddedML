#include <Arduino_LSM9DS1.h>

int ledPin = LED_BUILTIN;  // Built-in LED on the Arduino Nano 33 BLE Sense is used in the system
// BOOLS DEFINE OUR CONDITIONS FOR EACH VARIABLE IN OUR ALGORITHM
bool isFaceDown(float accelMagnitude, float gyro_x, float gyro_y, float gyro_z) { // defines the conditions for a facedown posture
    // Define thresholds for Face Down posture using both acceleration and gyroscope data
    return (accelMagnitude < 1.0184 && gyro_x < 2.5942 && gyro_y < -0.69634 && gyro_z < 0.248);// analysis in Google Colab for means for treshholds
}

bool isFaceUp(float accelMagnitude, float gyro_x, float gyro_y, float gyro_z) { // defines the conditions for a faceup posture
    // Define thresholds for Face Up posture using both acceleration and gyroscope data
    return (accelMagnitude > 0.99 && gyro_x > 1.378 && gyro_y > 0.4639 && gyro_z > 0.4941);// analysis in Google Colab for means for treshholds
}

bool isFaceSide(float accelMagnitude, float gyro_x, float gyro_y, float gyro_z) { // defines the conditions for a face sideways posture
    // Define thresholds for Face Side posture using both acceleration and gyroscope data
    return (accelMagnitude > 1.011 && gyro_x > 2.3595 && gyro_y < 0.373 && gyro_z < 0.5271); // analysis in Google Colab for means for treshholds
}

void setup() {
    // Start serial communication and set LED pin as output
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);

    // Initialize the IMU sensor
    if (!IMU.begin()) {
        Serial.println("Failed to initialize the IMU!");
        while (1);  // fail safe if sensor isnt detected
    }
}
// IF STATEMENTS RUN THROUGH THE CONDITIONING OF EACH SCENARIO TO SEE WHICH LABEL IS BEST SUITED
void loop() {
    // Check if accelerometer and gyroscope data are available
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
        float accelX, accelY, accelZ;
        float gyro_x, gyro_y, gyro_z;

        // Read accelerometer and gyroscope data
        IMU.readAcceleration(accelX, accelY, accelZ);
        IMU.readGyroscope(gyro_x, gyro_y, gyro_z);

        // Calculate the magnitude of acceleration
        float accelerationMagnitude = sqrt(pow(accelX, 2) + pow(accelY, 2) + pow(accelZ, 2));

        // Check the posture based on sensor data
        if (isFaceDown(accelerationMagnitude, gyro_x, gyro_y, gyro_z)) { // checking for the conditions in each scenario
            setLEDState("Face Down");
        } else if (isFaceUp(accelerationMagnitude, gyro_x, gyro_y, gyro_z)) { // checking for the conditions in each scenario
            setLEDState("Face Up");
        } else if (isFaceSide(accelerationMagnitude, gyro_x, gyro_y, gyro_z)) { // checking for the conditions in each scenario
            setLEDState("Face Side");
        } else {
            setLEDState("UNKNOWN"); // checking for the conditions in each scenario
        }
    }
}

void setLEDState(const char* postureName) {
    // Print the detected posture based on the information below
    Serial.print("Posture detected: ");
    Serial.println(postureName);

    // Set LED state based on the detected posture name
    if (strcmp(postureName, "Face Down") == 0) {
        digitalWrite(ledPin, HIGH);  // Turn on LED for Face Down posture
        delay(2000);  // Blink once
        digitalWrite(ledPin, LOW);
        delay(5000);
    } else if (strcmp(postureName, "Face Up") == 0) {
        digitalWrite(ledPin, HIGH);  // Turn on LED for Face Up posture
        delay(2000);  // Blink twice; 2-second hold
        digitalWrite(ledPin, LOW);
        delay(500);
        digitalWrite(ledPin, HIGH);
        delay(2000);
        digitalWrite(ledPin, LOW);
        delay(500);
    } else if (strcmp(postureName, "Face Side") == 0) {
        digitalWrite(ledPin, HIGH);  // Turn on LED for Face Side posture
        delay(2000);  // Blink three times; 2-second hold
        digitalWrite(ledPin, LOW);
        delay(500);
        digitalWrite(ledPin, HIGH);
        delay(2000);
        digitalWrite(ledPin, LOW);
        delay(500);
        digitalWrite(ledPin, HIGH);
        delay(2000);
        digitalWrite(ledPin, LOW);
    } else {
        digitalWrite(ledPin, LOW);  // NO LED FOR UNKNOWN
    }
}
