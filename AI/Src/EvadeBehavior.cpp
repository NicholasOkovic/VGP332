#include "Precompiled.h"
#include "EvadeBehavior.h"

#include "Agent.h"


X::Math::Vector2 AI::EvadeBehavior::Calculate(Agent& agent)
{
	if (agent.target == nullptr)
	{
		return X::Math::Vector2();
	}


	X::Math::Vector2 agentToTarget = agent.target->position - agent.position;
	float distanceToTarget = X::Math::Magnitude(agentToTarget);

	if (distanceToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}

	const float timeToTarget = distanceToTarget / agent.maxSpeed;
	const X::Math::Vector2& targetVelocity = agent.target->velocity;
	const X::Math::Vector2& targetPosition = agent.target->position;
	const X::Math::Vector2 predictedPosition = agent.target->position + targetVelocity * timeToTarget;



	agentToTarget = predictedPosition - agent.position;
	distanceToTarget = X::Math::Magnitude(agentToTarget);

	if (distanceToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}
	X::Math::Vector2 desiredVelocity = X::Math::Vector2::Zero();

	if (X::Math::MagnitudeSqr(agentToTarget) <= panicDistance * panicDistance)
	{
		desiredVelocity = -(agentToTarget / distanceToTarget) * agent.maxSpeed;
	}

	
	const X::Math::Vector2 evadeForce = desiredVelocity - agent.velocity;


	if (IsDebug())
	{
		X::DrawScreenCircle(targetPosition, 20.0f, X::Colors::Red);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Yellow);
		X::DrawScreenCircle(agent.position, panicDistance, X::Colors::Pink);
	}


	return evadeForce;
}
