#include "PursuitBehavior.h"
#include "Precompiled.h"

#include "Agent.h"


X::Math::Vector2 AI::PursuitBehavior::Calculate(Agent& agent)
{
	if (agent.target == nullptr)
	{
		return X::Math::Vector2();
	}




	X::Math::Vector2 agentToTarget = agent.target->position - agent.position;
	const float distanceToTarget = X::Math::Magnitude(agentToTarget);

	if (distanceToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}

	const float timeToTarget = distanceToTarget / agent.maxSpeed;
	const X::Math::Vector2& targetVelocity = agent.target->velocity;	/////
	const X::Math::Vector2& targetPosition = agent.target->velocity;
	const X::Math::Vector2 predictedPosition = agent.target->position + targetVelocity * timeToTarget;

	agentToTarget = predictedPosition - agent.position;
	distanceToTarget = X::Math::Magnitude(agentToTarget);

	if (distanceToTarget <= 10.0f)
	{
		return X::Math::Vector2();
	}

	const X::Math::Vector2 desiredVelocity = (agentToTarget / distanceToTarget) * agent.maxSpeed;
	const X::Math::Vector2 seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenCircle(targetPosition, 20.0f, X::Color::Red);
		X::DrawScreenLine(targetPosition, 20.0f, X::Color::Red);
		X::DrawScreenCircle(targetPosition, 20.0f, X::Color::Red);

	}



}
