#pragma once
#include <AI.h>

#include "Raven.h"


class GoalDepositeMineral :public AI::Goal<Raven>
{
public:

	using Status = AI::Goal<Raven>::Status;

	GoalDepositeMineral();

	void Activate(Raven& agent) override;
	Status Process(Raven& agent) override;
	void Terminate(Raven& agent) override;



private:
	float mStartTime = 0.0f;
	float mDepositeTime = 5.0f;
	X::Math::Vector2 mTargetBase;


};