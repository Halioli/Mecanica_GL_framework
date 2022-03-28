#pragma once
#include "Simulator.h"
#include "ParticleSystem.h"

namespace Sphere {
	extern void updateSphere(glm::vec3 pos, float radius);
}

extern bool renderSphere, renderCapsule, renderParticles;

class AA2 : public Simulator
{
public:
	AA2();
	~AA2();

	void Update(float dt);
	void RenderUpdate();
	void RenderGui();

	int numParticles;
private:
	ParticleSystem* particles;
	


	glm::vec3 capsuleA;
	glm::vec3 capsuleB;
	float capsuleRadius;
};

