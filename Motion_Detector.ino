const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 7;
const int buzzerPin = 8;

long duration;
int distance;

const int maxDistance = 50;

unsigned long lastBeepMillis = 0;
const unsigned long beepOnMs = 200;
const unsigned long beepOffMs = 200;
bool buzzerState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000UL);
  if (duration == 0) {
    distance = 999;
  } else {
    distance = (duration * 0.034) / 2;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < maxDistance) {
    digitalWrite(ledPin, HIGH);
    handleBuzzerBeep();
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    buzzerState = false;
    lastBeepMillis = millis();
  }

  delay(100);
}

void handleBuzzerBeep() {
  unsigned long now = millis();
  if (buzzerState) {
    if (now - lastBeepMillis >= beepOnMs) {
      buzzerState = false;
      digitalWrite(buzzerPin, LOW);
      lastBeepMillis = now;
    }
  } else {
    if (now - lastBeepMillis >= beepOffMs) {
      buzzerState = true;
      digitalWrite(buzzerPin, HIGH);
      lastBeepMillis = now;
    }
  }
}
