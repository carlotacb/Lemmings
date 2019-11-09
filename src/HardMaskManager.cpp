#include "HardMaskManager.h"
#include "Level.h"
#include "LevelManager.h"

#define SEC_TO_REAPPEAR 10

void HardMaskManager::init()
{
	int levelHeight = Level::currentLevel().getLevelAttributes()->levelSize.y;
	int levelWidth = Level::currentLevel().getLevelAttributes()->levelSize.x;
	timeWhenDissapear = std::vector<std::vector<int>>(levelWidth, std::vector<int>(levelHeight, -1));
	timeToAppear = std::vector<std::vector<int>>(levelWidth, std::vector<int>(levelHeight, -1));

}

void HardMaskManager::update()
{
	int currentTime = LevelManager::getInstance().getCurrentTime() * 10;

	int levelHeight = Level::currentLevel().getLevelAttributes()->levelSize.y;
	int levelWidth = Level::currentLevel().getLevelAttributes()->levelSize.x;

	for (int i = 0; i < levelWidth; ++i) {
		for (int j = 0; j < levelHeight; ++j) {
			int currentTimeWhenDisappear = timeWhenDissapear[i][j];
			int currentTimeToAppear = timeToAppear[i][j];

			if (currentTimeWhenDisappear != -1 && currentTime  >= currentTimeToAppear) {
				regenerateMask(i, j);
			}
		}
	}
}

void HardMaskManager::eraseMask(int x, int y)
{
	if (getPixel(x, y) != 200) {
		int currentTime = LevelManager::getInstance().getCurrentTime() * 10;
		timeWhenDissapear[x][y] = currentTime;
		timeToAppear[x][y] = currentTime + rand() % 6 + (SEC_TO_REAPPEAR + rand() % 3)*10;

		Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 0);
	}
}

void HardMaskManager::applyMask(int x, int y)
{
	timeWhenDissapear[x][y] = -1;
	timeToAppear[x][y] = -1;

	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 255);

}

void HardMaskManager::eraseSpecialMask(int x, int y)
{
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 0);

}

void HardMaskManager::applySpecialMask(int x, int y)
{
	Level::currentLevel().getLevelAttributes()->maskedMap.setPixel(x, y, 200);
}

char HardMaskManager::getPixel(int x, int y) {
	return Level::currentLevel().getLevelAttributes()->maskedMap.pixel(x, y);
}

void HardMaskManager::regenerateMask(int x, int y)
{
	applyMask(x, y);
}





