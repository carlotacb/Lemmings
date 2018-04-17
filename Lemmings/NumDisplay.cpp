#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "NumDisplay.h"


void NumDisplay::init() {
	setPosition(glm::vec2(0, 0));
}

void NumDisplay::displayNum(int num) {
	int firstDigit= num / 10;
	int secondDigit = num % 10;

	if (leftNum != NULL) {
		delete leftNum;
	}	
	if (rightNum != NULL) {
		delete rightNum;
	}
	displayNumAux(firstDigit, secondDigit);
}

void NumDisplay::render() {
	if (leftNum != NULL) {
		leftNum->render();
	}

	if (rightNum != NULL) {
		rightNum->render();
	}
}
