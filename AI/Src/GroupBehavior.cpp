#include "Precompiled.h"
#include "GroupBehavior.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 SeparationBehavior::Calculate(Agent& agent)
{
	const float forcedMulitiplier = 5.0f;
	X::Math::Vector2 seperationForce = X::Math::Vector2::Zero();
	for (auto& n : agent.neighbors)
	{
		if (n != agent.target)
		{
			X::Math::Vector2 dirToNeighbor = n->position - agent.position;
			float distance = X::Math::Magnitude(dirToNeighbor);
			float overlapDistance = (n->radius + agent.radius) - distance;
			if (overlapDistance > 0.0f)
			{
				dirToNeighbor /= distance;
				if (X::Math::Dot(dirToNeighbor, agent.heading) > 0.0f)
				{
					float disiredSpeed = (overlapDistance / agent.radius) * forcedMulitiplier * agent.maxSpeed;
					disiredSpeed = X::Math::Min(disiredSpeed, agent.maxSpeed);
					seperationForce += (-dirToNeighbor * disiredSpeed);
				}

			}
		}
	}

	seperationForce = seperationForce - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenCircle(agent.position, agent.radius, X::Colors::Honeydew);
	}
	return seperationForce;
}
