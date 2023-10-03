


#include <Arduino_LSM9DS1.h> // IMU Sensor Data Library

int RLED_pin = LEDR;  // Red LED for blinking response for the completion of a state

void setup() {
  Serial.begin(115200); // Retained from myreadimusensor (provided), 115200 baud is used to collect data faster
  while (!Serial);
  Serial.println("Started");
  
  pinMode(RLED_pin, OUTPUT);  // The red LED is collected that an output
  
  // Initialize the IMU sensor for input check. If the sensor does not end up working, we will have an output saying "Failed to initialize IMU!"
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
} //

void loop() {
  digitalWrite(RLED_pin, HIGH);  // Turn on the red LED
  Serial.print("Seconds:"); // prints Loop#"x", with X being the value of the amount of seconds passed
  Serial.println(millis() / 1000);  // Print elapsed seconds by converting milliseconds that have passed and prints them out (timestamp)

  float x, y, z;
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable() && IMU.magneticFieldAvailable()) { // operand reading all three sensors from the imu read sensor code from Canvas
    IMU.readAcceleration(x, y, z); // breaks down the metric
    Serial.print("Accelerometer: ");
    Serial.print(x);  Serial.print('\t'); // Prints out the conditions in order , taken from CANVAS
    Serial.print(y);  Serial.print('\t');// Prints out the conditions in order , taken from CANVAS
    Serial.println(z);// Prints out the conditions in order , taken from CANVAS

    IMU.readGyroscope(x, y, z);// Prints out the conditions in order , taken from CANVAS
    Serial.print("Gyroscope:");// Prints out the conditions in order , taken from CANVAS
    Serial.print(x);  Serial.print('\t');// Prints out the conditions in order , taken from CANVAS
    Serial.print(y);  Serial.print('\t');// Prints out the conditions in order , taken from CANVAS
    Serial.println(z);// Prints out the conditions in order , taken from CANVAS
            // REMOVED THE FOLLOWING BELOW BUT KEPT THE CODE TO SHOW THAT WE RECEIVED IT FROM THE CANVAS PAGE.
    //IMU.readMagneticField(x, y, z); // IRRELEVANT, taken from the sensor code from CANVAS
    //Serial.print("Magnetic Field: ");
    //Serial.print(x);  Serial.print('\t');
    //.print(y);  Serial.print('\t');
    //Serial.println(z);
  }
  
  digitalWrite(RLED_pin, LOW);  // Turn off the red LED
  delay(4000);  // Delay for 4 seconds to enable buffer for when I transition to another state
}

// All data is converted into an output in the serial monitor. upon collecting a statistically significant amount of samples for each 
