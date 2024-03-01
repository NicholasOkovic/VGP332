#pragma once
#include <XEngine.h>

#include "AI.h"

class Mineral : public AI::Entity
{
public:
	Mineral(AI::AIWorld& world);

	void Initialize();
	void Render();
	const int GetHealth() { return mHealth; }			//////
	void SetHealth(int health) { mHealth = health; }


private:
	X::TextureId mTextureId;
	int mHealth = 100;
};