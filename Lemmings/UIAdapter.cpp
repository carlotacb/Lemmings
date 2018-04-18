#include "UIAdapter.h"
#include "JobAssigner.h"
#include "Scene.h"
#include "Lemming.h"

void UIAdapter::changeFocusedLemming(int lemmingIndex)
{
	string lemmingJobName;
	if (lemmingIndex == -1) {
		lemmingJobName = "";
	}
	else {
		Lemming lemming = Scene::getInstance().getLemming(lemmingIndex);
		lemmingJobName = lemming.getJob()->getName();
	}
	UI::getInstance().changeDisplayedJob(lemmingJobName);
}
	
void UIAdapter::changeSelectedButton(int buttonIndex)
{
	UI::getInstance().changeSelectedButton(buttonIndex);

	if (buttonIndex == -1) {
		return;
	}

	activateButton(buttonIndex);
}


void UIAdapter::activateButton(int buttonIndex)
{
	JobAssigner::getInstance().deleteJobToAssign();

	switch (buttonIndex)
	{
	case Button::MINUS_BUTTON:
		if (Level::currentLevel().getLevelAttributes()->releaseRate > Level::currentLevel().getLevelAttributes()->minReleaseRate) {
			--Level::currentLevel().getLevelAttributes()->releaseRate;
		}
		break;
	case Button::PLUS_BUTTON:
		if (Level::currentLevel().getLevelAttributes()->releaseRate < 99) {
			++Level::currentLevel().getLevelAttributes()->releaseRate;
		}
		break;
	case Button::CLIMBER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::CLIMBER);
		}
		break;
	case Button::FLOATER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::FLOATER);
		}
		break;
	case Button::EXPLODER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::BOMBER);
		}
		break;
	case Button::BLOCKER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::BLOCKER);
		}
		break;
	case Button::BUILDER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::BUILDER);
		}
		break;
	case Button::BASHER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::BASHER);
		}
		break;
	case Button::MINER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::MINER);
		}
		break;
	case Button::DIGGER_BUTTON:
		if (UI::getInstance().getSelectedButtonJobCount() > 0) {
			JobAssigner::getInstance().offerJob(JobAssigner::JobNames::DIGGER);
		}
		break;
	case Button::PAUSE_BUTTON:
		Scene::getInstance().changePauseStatus();
		if (!Scene::getInstance().isPaused()) {
			UI::getInstance().changeSelectedButton(-1);
		}
		break;
	case Button::NUKE_BUTTON:

		break;
	case Button::SPEED_BUTTON:
		Scene::getInstance().changeSpeedUpStatus();
		if (!Scene::getInstance().isSpeedUp()) {
			UI::getInstance().changeSelectedButton(-1);
		}
		break;
	default:
		break;
	}

}