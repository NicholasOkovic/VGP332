#pragma once

#include "AI.h"
#include "TileMap.h"
class VisualSensor;


enum class CrowState
{
	GoHome,
	ChaseRaven,
	Deposite,
	Wander,
	Steal
};


class Crow : public AI::Agent
{
public:
	Crow(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active);
	void SetArrive(bool active);
	void SetWander(bool active);
	void SetTargetDestination(const X::Math::Vector2& targetdestination);
	X::Math::Vector2& GetTargetDestination() { return mDestination; }

	const AI::PerceptionModule* GetPerception() const { return mPerceptionModule.get(); }

	void SetTileMap(TileMap* tileMap) { mTileMap = tileMap; }
	TileMap* GetTileMap() { return mTileMap; }
	void SetMineral(bool hasMineral) { mHasMineral = hasMineral; }
	bool HasMineral() const { return mHasMineral; }


	//states & stuff
	void ChangeState(CrowState newState);
	CrowState GetState() { return mCrowState; }

	void SetMaxSpeed(int speed) { maxSpeed = speed; }

private:
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr<AI::DecisionModule<Crow>> mDecisionModule;

	VisualSensor* mVisualSensor = nullptr;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::WanderingBehavior* mWanderBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;

	X::Math::Vector2 mDestination;

	std::array<X::TextureId, 32> mTexturesIds;

	TileMap* mTileMap = nullptr;
	AI::StateMachine<Crow> mStateMachine;
	CrowState mCrowState;
	bool mHasMineral = false;

};