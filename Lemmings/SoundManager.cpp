#include "SoundManager.h"
#include <stdio.h>
#include <fmod_errors.h>

FMOD::Sound * SoundManager::loadSound(const std::string & file, FMOD_MODE mode) const {
	FMOD::Sound* pSound;
	lowLevelSystem->createSound(file.c_str(), mode, nullptr, &pSound);
	return pSound;
}

FMOD::Channel* SoundManager::playSound(FMOD::Sound * sound) const {
	FMOD::Channel* channel;
	lowLevelSystem->playSound(sound, nullptr, false, &channel);
	return channel;
}

void SoundManager::update() {
	system->update();
	lowLevelSystem->update();
}

SoundManager::SoundManager() : system(NULL) {
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&system); // Create the Studio System object.
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	// Initialize FMOD Studio, which will also initialize FMOD Low Level
	result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}
	system->getLowLevelSystem(&lowLevelSystem);
}


SoundManager::~SoundManager() {
	system->unloadAll();
	system->release();
}
