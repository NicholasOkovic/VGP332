#pragma once

#include <Ai.h>

#include "Crow.h"

class GoalArriveAtPositionCrow :public AI::Goal<Crow>
{
public:
	using Status = AI::Goal<Crow>::Status;

	GoalArriveAtPositionCrow();


	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;

	void SetDestination(const X::Math::Vector2& destination);

private:
	X::Math::Vector2 mDestination;
};

