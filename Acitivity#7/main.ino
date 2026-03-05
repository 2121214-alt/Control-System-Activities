#include <Servo.h>

// Create a servo object
Servo myServo;

const int servoPin = 9;

void setup() {
  // Attach the servo on pin 9 to the servo object
  myServo.attach(servoPin);
  
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  
  // Set initial position to 0
  myServo.write(0);
}

void loop() {
  // Check if data is available in the serial buffer
  if (Serial.available() > 0) {
    // Read the incoming integer
    int angle = Serial.parseInt();

    // Look for the newline character to clear the buffer
    if (Serial.read() == '\n') {
      // Final hardware-level safety check: constrain value
      angle = constrain(angle, 0, 180);
      
      // Move the servo to the specified angle
      myServo.write(angle);
      
      // Send confirmation back to Python
      Serial.print("Servo moved to: ");
      Serial.println(angle);
    }
  }
}
