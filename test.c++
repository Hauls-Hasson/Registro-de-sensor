const int sensorPin = A0;
const float threshold = 500.0;

bool aboveThreshold = false;

unsigned long startMillis = 0;
unsigned long activationStart = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);

  activationStart = millis();

  Serial.println("=== SYSTEM START ===");
}

void loop() {
  unsigned long currentMillis = millis();

  float sensorValue = getFakeSensor();

  float fakeValue = 0;

  float getFakeSensor() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '1') {
            fakeValue = 600;
            Serial.println("Sensor ON");
        }
        if (c == '0') {
            fakeValue = 0;
            Serial.println("Sensor OFF");
        }
    }
    return fakeValue;
}

  unsigned long elapsed = currentMillis - activationStart;

  unsigned long totalSeconds = elapsed / 1000;
  unsigned long ms = elapsed % 1000;
  unsigned long seconds = totalSeconds % 60;
  unsigned long minutes = (totalSeconds / 60) % 60;
  unsigned long hours = (totalSeconds / 3600) % 24;
  unsigned long days = totalSeconds / 86400;

  if (sensorValue > threshold && !aboveThreshold) {
    aboveThreshold = true;
    startMillis = currentMillis;

    Serial.print("START | Day ");
    Serial.print(days);
    Serial.print(" | ");
    printTime(hours, minutes, seconds, ms);
    Serial.println();
  }

  if (sensorValue <= threshold && aboveThreshold) {
    aboveThreshold = false;

    unsigned long duration = currentMillis - startMillis;

    unsigned long d_ms = duration % 1000;
    unsigned long d_sec = (duration / 1000) % 60;
    unsigned long d_min = (duration / 60000) % 60;
    unsigned long d_hr = duration / 3600000;

    Serial.print("STOP  | Day ");
    Serial.print(days);
    Serial.print(" | ");
    printTime(hours, minutes, seconds, ms);

    Serial.print(" | Duration: ");
    Serial.print(d_hr); Serial.print("h ");
    Serial.print(d_min); Serial.print("m ");
    Serial.print(d_sec); Serial.print("s ");
    Serial.print(d_ms); Serial.print("ms");

    Serial.println();
  }

  delay(50); // evita flood
}

void printTime(unsigned long h, unsigned long m, unsigned long s, unsigned long ms) {
  if (h < 10) Serial.print("0");
  Serial.print(h); Serial.print(":");

  if (m < 10) Serial.print("0");
  Serial.print(m); Serial.print(":");

  if (s < 10) Serial.print("0");
  Serial.print(s); Serial.print(".");

  if (ms < 100) Serial.print("0");
  if (ms < 10) Serial.print("0");
  Serial.print(ms);
}