#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "NumDisplay.h"
#include "NumFactory.h"



void NumDisplay::init() {

	backgroundTexture.loadFromFile("images/UI/black_frame.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgroundTexture.setMinFilter(GL_NEAREST);
	backgroundTexture.setMagFilter(GL_NEAREST);

	background = Sprite::createSprite(glm::vec2(15, 23), glm::vec2(1., 1.), &Scene::shaderProgram(), &backgroundTexture);
	setPosition(glm::vec2(0, 0));
}

void NumDisplay::displayNum(int num) {
	int firstDigit= num / 10;
	int secondDigit = num % 10;

	if (leftNum != NULL) {
		delete leftNum;
	}
	leftNum = NumFactory::instance().createNum(firstDigit);
	
	if (rightNum != NULL) {
		delete rightNum;
	}
	rightNum = NumFactory::instance().createNum(secondDigit);

	leftNum->setPosition(this->position + glm::vec2(4,1));
	rightNum->setPosition(this->position + glm::vec2(8, 1));
}

void NumDisplay::setPosition(glm::vec2 position) {
	this->position = position;

	background->setPosition(position);

	if (leftNum != NULL) {
		leftNum->setPosition(this->position + glm::vec2(4, 1));
	}

	if (rightNum != NULL) {
		rightNum->setPosition(this->position + glm::vec2(8, 1));
	}
}

void NumDisplay::render() {
	background->render();

	if (leftNum != NULL) {
		leftNum->render();
	}

	if (rightNum != NULL) {
		rightNum->render();
	}
}
