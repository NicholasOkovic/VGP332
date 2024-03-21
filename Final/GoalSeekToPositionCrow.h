#pragma once

#include <AI.h>

#include "Crow.h"

class GoalSeekToPositionCrow :public AI::Goal<Crow>
{
public:

	using Status = AI::Goal<Crow>::Status;

	GoalSeekToPositionCrow();

	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;

	void SetDestination(const X::Math::Vector2& destination);
	void SetDestinationRange(float range);

private:
	float mDestinationRange = 10.0f;
	X::Math::Vector2 mDestination;


};
