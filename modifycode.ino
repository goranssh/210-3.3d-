const int ledPin = 13; // Replace with your actual LED pin number
bool isPatSignal = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Particle.subscribe("buddyPhotonSignal", signalHandler);
}

void loop() {

}

void signalHandler(const char *event, const char *data) {
  if (strcmp(data, "pat") == 0) {
    isPatSignal = true;
  } else if (strcmp(data, "wave") == 0) {
    isPatSignal = false;
  }
}

void flashLED() {
  if (isPatSignal) {
    // Flash the LED in a different way for "pat" signal
    digitalWrite(ledPin, HIGH);
    delay(100); // Adjust the delay for your desired flashing pattern
    digitalWrite(ledPin, LOW);
    delay(100);
  } else {

    digitalWrite(ledPin, HIGH);
    delay(500); // Adjust the delay for your desired flashing pattern
    digitalWrite(ledPin, LOW);
    delay(500);
  }
}
