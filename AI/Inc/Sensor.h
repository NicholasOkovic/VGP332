#pragma once


#include "MemoryRecord.h"

namespace AI
{
	class Agent;

	class Sensor
	{
	public:
		Sensor();
		virtual ~Sensor() = default;
		virtual void Update(Agent& agent, MemoryRecord memory, float deltaTime) = 0;

	private:

	};





}




