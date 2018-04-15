#include <fstream>
#include <sstream>
#include "Level.h"
#include "DoorFactory.h"
#include "TrapdoorFactory.h"

void Level::createFromFile(string file)
{
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

				mapTexturePath = "images/levels/" + levelType;
				mapTexturePath += to_string(levelNum);;
				mapTexturePath += ".png";

				mapMaskPath = "images/levels/" + levelType;
				mapMaskPath += to_string(levelNum);
				mapMaskPath += "_mask.png";
				break;
			}

			case 1: // NUM_LEMMINGS GOAL_LEMMINGS TIME(secs) 
				iss >> levelAttributes.numLemmings >> levelAttributes.goalLemmings >> levelAttributes.time;
				break;

			case 2: //  RELEASE_RATE JOB_COUNT [CLIMBER, FLOATER, EXPLODER, BLOCKER, BUILDER, BASHER, MINER, DIGGER] 
				iss >> levelAttributes.releaseRate;
				levelAttributes.minReleaseRate = levelAttributes.releaseRate;
				for (int i = 0; i < 8; ++i) {
					iss >> levelAttributes.jobCount[i];
				}
				break;

			case 3: // TRAPDOOR_POS TRAPDOOR_TYPE(standard, hell)
			{
				int trapdoorPosX, trapdoorPosY;
				string trapdoorType;
				iss >> trapdoorPosX >> trapdoorPosY >> trapdoorType;

				trapdoorPos = glm::vec2(trapdoorPosX, trapdoorPosY);
				levelAttributes.trapdoor = TrapdoorFactory::instance().createTrapdoor(trapdoorType);
				break;
			}
			case 4: // DOOR_POS DOOR_TYPE(standard, egypt, maya, hell)
			{
				int doorPosX, doorPosY;
				string doorType;
				iss >> doorPosX >> doorPosY >> doorType;

				doorPos = glm::vec2(doorPosX, doorPosY);
				levelAttributes.door = DoorFactory::instance().createDoor(doorType);
				break;
			}
			case 5: //LEVEL OFFSET 
				int offsetX, offsetY;
				iss >> offsetX >> offsetY;
				levelAttributes.offset = glm::vec2(offsetX, offsetY);
				break;
			default:
				break;
		}
		++lineCount;

	}
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


	levelAttributes.trapdoor->init();
	levelAttributes.trapdoor->setPosition(trapdoorPos);

	levelAttributes.door->init();
	levelAttributes.door->setPosition(doorPos);
}
