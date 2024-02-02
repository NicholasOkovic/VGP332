#pragma once

#include "AI.h"

class SCV : public AI::Agent
{
public:
	~SCV() override = default;

	SCV(AI::AIWorld& world);
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();


	void ShowDebug(bool debug);

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::array<X::TextureId, 16> mTextureIds;

};