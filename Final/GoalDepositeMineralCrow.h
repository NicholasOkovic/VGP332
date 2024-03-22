#pragma once
#include <AI.h>

#include "Crow.h"


class GoalDepositeMineralCrow :public AI::Goal<Crow>
{
public:

	using Status = AI::Goal<Crow>::Status;

	GoalDepositeMineralCrow();

	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;



private:
	float mStartTime = 0.0f;
	float mDepositeTime = 5.0f;
	X::Math::Vector2 mTargetBase;


};