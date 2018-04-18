#include <GL/glew.h>
#include <GL/glut.h>
#include "Cursor.h"
#include "Game.h"
#include "Scene.h"
#include "ShaderManager.h"

enum CursorStates {
	CROSS,
	FOCUS,
	LEFT,
	RIGHT
};

void Cursor::init() {
	glutSetCursor(GLUT_CURSOR_NONE);

	cursorSprite = Sprite::createSprite(glm::ivec2(12, 12), glm::vec2(29. / 32, 29. / 128), &ShaderManager::getInstance().getShaderProgram(), &Game::spriteSheets().cursorSprites);
	cursorSprite->setNumberAnimations(4);

	cursorSprite->setAnimationSpeed(CROSS, 12);
	cursorSprite->addKeyframe(CROSS, glm::vec2(0, 87. / 128));
	
	cursorSprite->setAnimationSpeed(FOCUS, 12);
	cursorSprite->addKeyframe(FOCUS, glm::vec2(0, 58. / 128));
	
	cursorSprite->setAnimationSpeed(LEFT, 12);
	cursorSprite->addKeyframe(LEFT, glm::vec2(0, 0));
	
	cursorSprite->setAnimationSpeed(RIGHT, 12);
	cursorSprite->addKeyframe(RIGHT, glm::vec2(0, 29. / 128));

	cursorSprite->changeAnimation(CROSS);
}

void Cursor::render() {
	cursorSprite->render();
}

void Cursor::setScrollLeftCursor() {
	cursorSprite->changeAnimation(LEFT);
}

void Cursor::setScrollRightCursor() {
	cursorSprite->changeAnimation(RIGHT);
}

void Cursor::setFocusCursor() {
	cursorSprite->changeAnimation(FOCUS);
}

void Cursor::setCrossCursor() {
	cursorSprite->changeAnimation(CROSS);
}

void Cursor::setPosition(glm::vec2 position) {
	cursorSprite->setPosition(position);
}
