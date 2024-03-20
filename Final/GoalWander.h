#pragma once


#include "AI.h"

#include "Crow.h"

class GoalWander : public AI::Goal<Crow>
{
public:
	using Status = AI::Goal<Crow>::Status;

	GoalWander();


	void Activate(Crow& agent) override;
	Status Process(Crow& agent) override;
	void Terminate(Crow& agent) override;

private:

};

