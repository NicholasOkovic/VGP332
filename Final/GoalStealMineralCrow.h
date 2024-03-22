#pragma once

#include <AI.h>

#include "Raven.h"
#include "Crow.h"

class GoalStealMineralCrow :public AI::Goal<Crow>
{
public:

	using Status = AI::Goal<Crow>::Status;

	GoalStealMineralCrow();

	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;



private:
	float mStartTime = 0.0f;
	float mHarvestTime = 5.0f;
	Raven* mTargetRaven = nullptr;


};
