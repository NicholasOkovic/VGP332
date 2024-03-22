#include "Mineral.h"
#include "TypeId.h"



Mineral::Mineral(AI::AIWorld& world)
	: Entity(world, static_cast<uint32_t>(AgentType::Mineral))
{
}

void Mineral::Initialize()
{
	const float screenWidth = X::GetScreenWidth();
	const float screenHeight = X::GetScreenHeight();
	mTextureId = X::LoadTexture("mushroom.png");
	//position = X::RandomVector2({ 500.0f, 100.0f }, { 780.0f, 710.0f });
	position = X::RandomVector2({ screenWidth / 2.75f, screenHeight / 2.25f }, { screenWidth / 1.5f, screenHeight / 1.25f });
	//position.x += X::Random(0, 1) == 0 ? -300.0f : 300.0f;
}

void Mineral::Render()
{
	if (mHealth > 0)
	{
		X::DrawSprite(mTextureId, position);
		mTimer = 0;
	}
	
}

void Mineral::Update(float deltaTime)
{
	if (mHealth <= 0)
	{
		mTimer += deltaTime;
		if (mTimer >= 50)
		{
			mHealth = 100;
		}
	}

}
