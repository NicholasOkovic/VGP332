#pragma once

#include "AI.h"
#include "TileMap.h"
class VisualSensor;

class Raven : public AI::Agent
{
public:
	Raven(AI::AIWorld& world);

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ShowDebug(bool debug);

	void SetSeek(bool active);
	void SetArrive(bool active);
	//void SetWander(bool active);
	void setTargetDestination(const X::Math::Vector2& targetdestination);

	const AI::PerceptionModule* GetPerception() const { return mPerceptionModule.get(); }

	void SetTileMap(TileMap* tileMap) { mTileMap = tileMap; }
	TileMap GetTileMap() { return *mTileMap; }

	void SetMineral(bool hasMineral) { mHasMineral = hasMineral; }
	bool HasMineral() const { return mHasMineral; }

private:
	std::unique_ptr<AI::PerceptionModule> mPerceptionModule;
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::unique_ptr<AI::DecisionModule<Raven>> mDecisionModule;

	VisualSensor* mVisualSensor = nullptr;

	AI::SeekBehavior* mSeekBehavior = nullptr;
	//AI::WanderingBehavior* mWanderBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;


	std::array<X::TextureId, 32> mTexturesIds;

	TileMap* mTileMap = nullptr;

	bool mHasMineral = true;
};