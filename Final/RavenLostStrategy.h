#include <AI.h>

#include "Raven.h"

class RavenLostStrategy :public AI::Strategy<Raven>
{
public:
	float CalculateDesirability(Raven& agent) const override;
	std::unique_ptr<AI::Goal<Raven>> CreateGoal() const override;

private:

};