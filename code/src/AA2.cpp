#include <glm\glm.hpp>
#include "EulerIntegrator.h";
#include "AA2.h"


namespace Sphere
{
	extern void setupSphere(glm::vec3 pos = glm::vec3(0.f, 1.f, 0.f), float radius = 1.f);
	extern void cleanupSphere();
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	extern void drawSphere();
}

// Auxiliar methods
#pragma region auxiliar
glm::vec3 GetParticleInitialPositionAA2(int id, int numParticles)
{
	float margin = 0.1f;
	float available_length = 2 * (5.f - margin);
	float offset = available_length / (numParticles - 1);

	float x, y, z;
	x = z = -5.f + margin + id * offset;
	y = 9.9f;

	return glm::vec3(x, y, z);
}

bool CheckHasTravessedFloorAA2(glm::vec3 particle)
{
	// This should be done with:
	// (n * p + d) * (n * p' + d) * n
	if (particle[1] <= 0.0f)
	{
		return true;
	}

	return false;
}

#pragma endregion

#pragma region class
AA2::AA2()
{
	numParticles = 40;
	particles = new ParticleSystem(numParticles);

	for (int i = 0; i < numParticles; i++)
	{
		particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
	}

	// Enable the rendering of particles in the framework 
	extern bool renderParticles; renderParticles = true;

	
}

AA2::~AA2()
{
	delete particles;
}

void AA2::Update(float dt)
{
	EulerIntegrator eulerInt;

	eulerInt.Step(particles, dt);

	// Check if a particle travessed the floor plane. Restart its position if it had
	for (int i = 0; i < numParticles; i++)
	{
		if (CheckHasTravessedFloorAA2(particles->GetParticlePosition(i)))
		{
			particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
		}
	}

	Sphere::updateSphere(glm::vec3 (5, 5, 5), 40.f);
}

void AA2::RenderUpdate()
{
	particles->Render();
}

void AA2::RenderGui() {};

#pragma endregion

