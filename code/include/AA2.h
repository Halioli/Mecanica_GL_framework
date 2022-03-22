#pragma once
#include "Simulator.h"
#include "ParticleSystem.h"

class AA2 : public Simulator
{
public:
	AA2();
	~AA2();

	void Update(float dt);
	void RenderUpdate();
	void RenderGui();

private:
	ParticleSystem* particles;
	int numParticles;
};

