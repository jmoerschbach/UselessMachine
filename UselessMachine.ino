#include <Servo.h>

#define LEVER_PIN 9
#define HATCH_PIN 8
#define SWITCH_PIN 3
Servo leverServo;
Servo hatchServo;

constexpr int HATCH_CLOSE = 30;
constexpr int HATCH_OPEN = 90;
constexpr int LEVER_BACK = 130;
constexpr int LEVER_FORTH = 40;

void setup() {
	pinMode(SWITCH_PIN, INPUT_PULLUP);
	leverServo.attach(LEVER_PIN);
	hatchServo.attach(HATCH_PIN);

	setHatch(0);
	setLever(0);

}
//#################### Helper functions ##################################
void openHatch(uint8_t startPos, uint8_t endPos, uint16_t delayBetweenSteps) {
	setHatch(startPos);
	for (uint8_t i = startPos; i < endPos; i += 1) {
		setHatch(i);
		delay(delayBetweenSteps / 10);
	}
}

void closeHatch(uint8_t startPos, uint8_t endPos, uint16_t delayBetweenSteps) {
	setHatch(startPos);
	for (uint8_t i = startPos; i > endPos; i -= 1) {
		setHatch(i);
		delay(delayBetweenSteps / 10);
	}
}

void setHatch(uint8_t percent) {
	if (percent > 100) {
		return;
	}

	hatchServo.write(((percent / 100.0) * HATCH_OPEN) + HATCH_CLOSE);
}

void moveLever(uint8_t startPos, uint8_t endPos, uint16_t delayBetweenSteps) {
	setLever(startPos);
	for (uint8_t i = startPos; i < endPos; i += 1) {
		setLever(i);
		delay(delayBetweenSteps / 10);
	}
}

void moveLeverBackwards(uint8_t startPos, uint8_t endPos,
		uint16_t delayBetweenSteps) {
	setLever(startPos);
	for (uint8_t i = startPos; i >= endPos; i -= 1) {
		setLever(i);
		delay(delayBetweenSteps / 10);
	}
}

void setLever(uint8_t percent) {
	if (percent > 100) {
		return;
	}
	percent = 100 - percent;
	leverServo.write(
			((percent / 100.0) * (LEVER_BACK - LEVER_FORTH)) + LEVER_FORTH);
}

//############################ Animations ###########################

void cautious() {
	openHatch(0, 70, 200);
	moveLever(0, 30, 0);
	delay(1000);
	moveLever(30, 100, 0);
	delay(500);
	setLever(0);
	delay(300);
	setHatch(0);
	delay(100);
}

void fastest() {
	openHatch(0, 80, 10);
	setLever(100);
	delay(350);
	setLever(0);
	delay(200);
	setHatch(0);
	delay(100);
}

void provoking() {
	openHatch(0, 90, 200);
	setLever(70);
	delay(random(1000, 3000));
	setLever(100);
	delay(150);
	setLever(0);
	delay(300);
	setHatch(0);
	delay(500);
}

void makingSure() {
	openHatch(0, 90, 100);
	moveLever(0, 100, 0);
	delay(2000);
	moveLeverBackwards(100, 30, 50);
	closeHatch(90, 60, 200);
	delay(1000);
	openHatch(60, 90, 100);
	setLever(80);
	delay(1000);
	setLever(0);
	delay(150);
	setHatch(0);
	delay(100);
}

void deking() {
	long numberOfDisguises = random(2, 6);
	for (uint8_t i = 0; i < numberOfDisguises; i++) {
		openHatch(0, 70, 100);
//		setHatch(70);
		delay(400);
		setHatch(0);
		delay(200);
		delay(random(100, 1000));
	}
	openHatch(0, 80, 30);
	setLever(100);
	delay(400);
	setLever(0);
	delay(200);
	setHatch(0);
	delay(200);
}
void scouting() {
	openHatch(0, 50, 50);
	delay(random(500, 2500));
	closeHatch(50, 0, 50);
	delay(random(2000));
	delay(2000);
	fastest();

}
void slowFast() {
	openHatch(0, 80, 50);
	moveLever(30, 70, 500);
	delay(400);
	setLever(100);
	delay(100);
	setLever(0);
	delay(200);
	setHatch(0);
	delay(100);
}

void slowFastSlow() {
	openHatch(0, 80, 200);
	moveLever(30, 70, 500);
	delay(400);
	setLever(100);
	delay(300);
	moveLeverBackwards(100, 10, 500);
	setHatch(0);
	setLever(0);
	delay(100);
}

void simpleTurnOff() {
	leverServo.write(LEVER_FORTH);
}
void simpleTurnOn() {
	leverServo.write(LEVER_BACK);
}

void slowTurnOnFastOff() {
	hatchServo.write(HATCH_OPEN);
	leverServo.write(((LEVER_BACK - LEVER_FORTH) / 2) + LEVER_FORTH);
	delay(500);
	for (uint8_t step = ((LEVER_BACK - LEVER_FORTH) / 2) + LEVER_FORTH;
			step > LEVER_FORTH; step -= 5) {
		leverServo.write(step);
		delay(50);
	}
	delay(500);
	leverServo.write(LEVER_BACK);
	delay(200);
	hatchServo.write(HATCH_CLOSE);
	delay(1000);
}

void (*ALL_ANIMATIONS[])() = {cautious, fastest, provoking, makingSure, deking, scouting, slowFast, slowFastSlow};

void loop() {

	if (digitalRead(SWITCH_PIN) == LOW) {
		delay(random(1000));
		long CURRENT_ANIMATION = random(8);
		ALL_ANIMATIONS[CURRENT_ANIMATION]();
	}

}
