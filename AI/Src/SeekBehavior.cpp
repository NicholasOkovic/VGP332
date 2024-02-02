#include "Precompiled.h"
#include "SeekBehavior.h"
#include "Agent.h"

using namespace AI;

X::MathVector2 SeekBehavior::Calculate(Agent& agent)
{
	const X::Math::Vector2 agentToDest = agent.destiniation - agent.position;
	if (X::Math::MagnitudeSqr(agentToDest) <= 1.0)
	{
		return X::Math::Vector2::Zero();
	}


	const X::Math::Vector2 desiredVelocity = X::Math::Normalize(agentToDest) * agent.maxSpeed);
	const X::Math::Vector2 seekForce =

	if (IsDebug)
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenCircle(agent.destiniation, 20.0f, X::Colors::Red);
	}

}
