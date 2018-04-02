#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE


#include <string.h>
#include "Texture.h"
#include "Sprite.h"
#include "VariableTexture.h"

class Level
{

public:

	static Level &currentLevel()
	{
		static Level currentLevel;

		return currentLevel;
	}

	struct LevelAttributes {
		int numLemmings;
		int goalLemmings;
		int time;

		int releaseRate;
		int minReleaseRate;
		int jobCount[8];

		Sprite *door;
		Sprite *trapdoor;

		glm::vec2 lemmingSpawnPos;
		glm::vec2 lemmingGoalPos;

		Texture colorTexture;
		VariableTexture maskedMap;
	};

	void createFromFile(string file);
	void init();

	LevelAttributes *getLevelAttributes();


private:
	void initDoors();

private:
	LevelAttributes levelAttributes;

	glm::vec2 doorPos;
	glm::vec2 trapdoorPos;
	
	string mapTexturePath;
	string mapMaskPath;
};
#endif // _LEVEL_INCLUDE

