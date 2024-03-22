#include "Raven.h"
#include "RavenStates.h"

#include "TypeId.h"
#include "VisualSensor.h"
//#include "RavenStrategy.h"
#include "RavenHuntStrategy.h"
#include "RavenHarvestStrategy.h"
#include "RavenGoToMineralStrategy.h"
#include "RavenGoHomeStrategy.h"
#include "RavenDepositeStrategy.h"
#include "RavenLostStrategy.h"
using namespace AI;

extern float wanderJitter;
extern float wanderRadius;
extern float wanderDistance;
extern float viewRange;
extern float viewAngle;

namespace
{
	float ComputeImportance(const AI::Agent& agent, const AI::MemoryRecord& record)
	{
		float score = 0.0f;
		AgentType entityType = static_cast<AgentType>(record.GetProperty<int>("type"));
		switch (entityType)
		{
		case AgentType::Invalid:
			score = 0.0f;
			break;

		case AgentType::SCV:
		{
			score = 0.0f;
		}
		break;
		case AgentType::Mineral:
		{
			int health = record.GetProperty<int>("health", 0);
			if (health > 0 )
			{
				X::Math::Vector2 lastSeenPos = record.GetProperty<X::Math::Vector2>("lastSeenPosition");
				float distance = X::Math::Distance(agent.position, lastSeenPos);
				float distanceScore = std::max(1000.0f - distance, 0.0f);
				score = distanceScore;
			}
			else
			{
				score = 0.0f;
			}
			
		}
		break;

		default:
			break;
		}
		return score;
	}
}

Raven::Raven(AI::AIWorld& world)
	: Agent(world, static_cast<uint32_t>(AgentType::Raven))
{

}

void Raven::Load()
{
	//perception
	mPerceptionModule = std::make_unique<AI::PerceptionModule>(*this, ComputeImportance);
	mPerceptionModule->SetMemorySpan(3.0f);
	mVisualSensor = mPerceptionModule->AddSensor<VisualSensor>();
	mVisualSensor->targetType = AgentType::Mineral;

	//steering
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();
	//mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderingBehavior>();
	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();

	//decision & strat
	mDecisionModule = std::make_unique<AI::DecisionModule<Raven>>(*this);
	mDecisionModule->AddStrategy<RavenHuntStrategy>();
	mDecisionModule->AddStrategy<RavenHarvestStrategy>();
	mDecisionModule->AddStrategy<RavenGoHomeStrategy>();
	mDecisionModule->AddStrategy<RavenDepositeStrategy>();
	mDecisionModule->AddStrategy<RavenLostStrategy>();
	
	auto strategy = mDecisionModule->AddStrategy<RavenGoToMineralStrategy>();
	strategy->SetPerception(mPerceptionModule.get());

	//stateMachines
	mStateMachine.Initialize(this);
	mStateMachine.AddState<RavenGoHome>();
	mStateMachine.AddState<RavenHarvestMineral>();
	mStateMachine.AddState<RavenGoToMineral>();
	mStateMachine.AddState<RavenGoToGatherSpot>();
	mStateMachine.AddState<RavenDeposite>();
	//mStateMachine.AddState<RavenNoStrat>();

	ChangeState(RavenState::GoHome);

	SetMaxSpeed(50);

	for (int i = 0; i < mTexturesIds.size(); i++)
	{
		char name[128];
		sprintf_s(name, "interceptor_%02i.png", i + 1);
		mTexturesIds[i] = X::LoadTexture(name);
	}



}

void Raven::Unload()
{
}

void Raven::Update(float deltaTime)
{
	mVisualSensor->viewRange = viewRange;
	mVisualSensor->viewHalfAngle = viewAngle * X::Math::kDegToRad;

	mPerceptionModule->Update(deltaTime);
	mStateMachine.Update(deltaTime);
	mDecisionModule->Update();

	//mWanderBehavior->SetUp(wanderRadius, wanderDistance, wanderJitter);

	const X::Math::Vector2 force = mSteeringModule->Calculate();
	const X::Math::Vector2 Acceleration = force /mass;
	velocity += Acceleration * deltaTime;
	if (X::Math::MagnitudeSqr(velocity) > 1.0f)
	{
		heading = X::Math::Normalize(velocity);
	}
	position += velocity * deltaTime;


	const auto& memoryRecords = mPerceptionModule->GetMemoryRecords();
	for (auto& memory : memoryRecords)
	{
		X::Math::Vector2 pos = memory.GetProperty<X::Math::Vector2>("lastSeenPosition");
		X::DrawScreenLine(position, pos, X::Colors::Purple);

		std::string score = std::to_string(memory.importance);
		X::DrawScreenText(score.c_str(), pos.x, pos.y, 12.0f, X::Colors::Purple);
	}

}

void Raven::Render()
{
	const float angle = atan2(-heading.x, heading.y) + X::Math::kPi;
	const float percent = angle / X::Math::kTwoPi;
	const int frame = static_cast<int>(percent * mTexturesIds.size()) % mTexturesIds.size();
	X::DrawSprite(mTexturesIds[frame], position);
}

void Raven::ShowDebug(bool debug)
{
	mSeekBehavior->ShowDebug(debug);
	//mWanderBehavior->ShowDebug(debug);
}

void Raven::SetSeek(bool active)
{
	mSeekBehavior->SetActive(active);
}

void Raven::SetArrive(bool active)
{
	mArriveBehavior->SetActive(active);
}

//void Raven::SetWander(bool active)
//{
//	mWanderBehavior->SetActive(active);
//}


void Raven::SetTargetDestination(const X::Math::Vector2& targetdestination)
{
	//RavenStrategy* strategy = mDecisionModule->AddStrategy<RavenStrategy>();
	//strategy->SetTargetDestination(targetdestination);
	mDestination = targetdestination;
}

void Raven::ChangeState(RavenState newState)
{
	mStateMachine.ChangeState((int)newState);
	mRavenState = newState;
}
