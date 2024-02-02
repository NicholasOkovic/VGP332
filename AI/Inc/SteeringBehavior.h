#pragma once

#include <Xengine.h>

namespace AI
{
	class Agent;
	
	class SteeringBehavior
	{
	public:
		SteeringBehavior();
		virtual ~SteeringBehavior() = default;

		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;

		void SetWeight(float weight) { mWeight = weight; }
		float GetWeight(float weight) { return mWeight; }

		void SetActive(bool active) { active = true; }	///////
		bool IsActive() const { return mActive; }

		void ShowDebug(bool debug) { mDebug = debug; }
		bool IsDebug() const { return mDebug; }

	private:
		float mWeight = 1.0f;
		bool mActive = false;
		bool mDebug = false;
	};

	
}
