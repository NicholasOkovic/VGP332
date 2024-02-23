#pragma once
#include <AI.h>

#include "TypeId.h"

using namespace AI;

class VisualSensor : public AI::Sensor
{
public:

	virtual void Update(AI::Agent& agent, AI::MemoryRecords& memory, float deltatime) override;


private:
	AgentType targetType = AgentType::Invalid;
	float viewRange = 0.0f;
	float viewHalfAngle = 0.0f;
};

