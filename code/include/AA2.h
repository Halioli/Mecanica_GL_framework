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

private:
	ParticleSystem* particles;
	int numParticles;
	
	glm::vec3 sphereCenter;
	float sphereRadius;

	glm::vec3 capsuleA;
	glm::vec3 capsuleB;
	float capsuleRadius;
};

