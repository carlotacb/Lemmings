#include <fstream>
#include <sstream>
#include "Level.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"

Level *Level::createFromFile(string file)
{
	Level *level = new Level();

	ifstream infile(file);

	int lineCount = 0;
	string line;
	while (getline(infile, line))
	{
		istringstream iss(line);
		switch (lineCount) {

			case 0: // LEVEL_TYPE(fun, tricky, taxing, mayhem) LEVEL_NUM
			{
				string levelType;
				int levelNum;
				iss >> levelType >> levelNum;

				level->mapTexturePath = "images/levels/" + levelType;
				level->mapTexturePath += to_string(levelNum);;
				level->mapTexturePath += ".png";

				level->mapMaskPath = "images/levels/" + levelType;
				level->mapMaskPath += to_string(levelNum);
				level->mapMaskPath += "_mask.png";
				break;
			}

			case 1: // NUM_LEMMINGS GOAL_LEMMINGS TIME(secs) 
				iss >> level->levelAttributes.numLemmings >> level->levelAttributes.goalLemmings >> level->levelAttributes.time;
				break;

			case 2: //  RELEASE_RATE JOB_COUNT [CLIMBER, FLOATER, EXPLODER, BLOCKER, BUILDER, BASHER, MINER, DIGGER] 
				iss >> level->levelAttributes.releaseRate;

				for (int i = 0; i < 8; ++i) {
					iss >> level->levelAttributes.jobCount[i];
				}
				break;

			case 3: // TRAPDOOR_POS DOOR_POS
				int trapdoorPosX, trapdoorPosY, doorPosX, doorPosY;
				iss >> trapdoorPosX >> trapdoorPosY >> doorPosX >> doorPosY;

				level->trapdoorPos = glm::vec2(trapdoorPosX, trapdoorPosY);
				level->doorPos = glm::vec2(doorPosX, doorPosY);
				break;
			case 4:
				int lemmingSpawnPosX, lemmingSpawnPosY, lemmingGoalPosX, lemmingGoalPosY;
				iss >> lemmingSpawnPosX >> lemmingSpawnPosY >> lemmingGoalPosX >> lemmingGoalPosY;

				level->levelAttributes.lemmingSpawnPos = glm::vec2(lemmingSpawnPosX, lemmingSpawnPosY);
				level->levelAttributes.lemmingGoalPos = glm::vec2(lemmingGoalPosX, lemmingGoalPosY);
				break;

			default:
				break;
		}
		++lineCount;

	}

	return level;
}

Level::LevelAttributes* Level::getLevelAttributes() {
	return &levelAttributes;
}

void Level::init()
{
	levelAttributes.colorTexture.loadFromFile(mapTexturePath, TEXTURE_PIXEL_FORMAT_RGBA);
	levelAttributes.colorTexture.setMinFilter(GL_NEAREST);
	levelAttributes.colorTexture.setMagFilter(GL_NEAREST);

	levelAttributes.maskedMap.loadFromFile(mapMaskPath, TEXTURE_PIXEL_FORMAT_L);
	levelAttributes.maskedMap.setMinFilter(GL_NEAREST);
	levelAttributes.maskedMap.setMagFilter(GL_NEAREST);


	levelAttributes.trapdoor = TrapdoorFactory::instance().createFunTrapdoor();
	levelAttributes.trapdoor->setPosition(trapdoorPos);

	levelAttributes.door = DoorFactory::instance().createFunDoor();
	levelAttributes.door->setPosition(doorPos);
}
