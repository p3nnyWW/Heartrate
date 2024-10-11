// Pin definitions for Traffic Light
const int redLED = 13;     // Red LED connected to D13

// KY-039 Heartbeat Monitor pin
const int heartbeatPin = 34; // Analog input for heartbeat signal

unsigned long interval = 1000;   // Default interval for LED blink (in milliseconds)
unsigned long lastBeatTime = 0;  // Time of the last heartbeat
int heartbeatThreshold = 500;    // Adjust based on your module's sensitivity
int heartRate = 60;              // Placeholder for heart rate (in beats per minute)

void setup() {
  // Setup the red LED pin
  pinMode(redLED, OUTPUT);

  // Setup serial for debugging
  Serial.begin(115200);
}

// Main loop
void loop() {
  // Read the KY-039 heartbeat sensor
  int heartbeatValue = analogRead(heartbeatPin);

  // Check if the signal exceeds the threshold (indicating a heartbeat)
  if (heartbeatValue > heartbeatThreshold && millis() - lastBeatTime > 500) {
    // Calculate heart rate based on the time between beats
    unsigned long currentTime = millis();
    unsigned long beatInterval = currentTime - lastBeatTime;
    heartRate = 60000 / beatInterval;  // Convert time between beats to beats per minute (BPM)
    lastBeatTime = currentTime;

    // Print the heart rate for debugging
    Serial.print("Heart Rate: ");
    Serial.println(heartRate);

    // Adjust the blinking interval based on the heart rate
    interval = 60000 / heartRate; // Set interval to match heart rate
  }

  // Blink the red LED in sync with the heartbeat
  blinkRedLED();
}

// Function to blink the red LED based on the interval
void blinkRedLED() {
  // Turn the red LED on
  digitalWrite(redLED, HIGH);
  delay(interval / 2);  // Keep it on for half of the heartbeat interval

  // Turn the red LED off
  digitalWrite(redLED, LOW);
  delay(interval / 2);  // Keep it off for the remaining half of the interval
}
