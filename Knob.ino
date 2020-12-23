#include <Servo.h>

#define LEVER_PIN 9
#define HATCH_PIN 8
#define SWITCH_PIN 3
Servo leverServo;
Servo hatchServo;

constexpr int HATCH_CLOSE = 0;
constexpr int HATCH_OPEN = 90;
constexpr int MIN = 130;
constexpr int MAX = 50;
int val;    // variable to read the value from the analog pin

void setup() {
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	leverServo.attach(LEVER_PIN);
	hatchServo.attach(HATCH_PIN);
	leverServo.write(MIN);
	hatchServo.write(HATCH_CLOSE);
}

void loop() {
	if (digitalRead(SWITCH_PIN) == LOW) {
		slowTurnOnFastOff();

	}

}
void simpleTurnOff() {
	leverServo.write(MIN);
}
void simpleTurnOn() {
	leverServo.write(MAX);
}

void slowTurnOnFastOff() {
	hatchServo.write(HATCH_OPEN);
	leverServo.write(((MIN - MAX) / 2) + MAX);
	delay(500);
	for (uint8_t step = ((MIN - MAX) / 2) + MAX; step > MAX; step -= 5) {
		leverServo.write(step);
		delay(50);
	}
	delay(500);
	leverServo.write(MIN);
	delay(200);
	hatchServo.write(HATCH_CLOSE);
	delay(1000);
}
