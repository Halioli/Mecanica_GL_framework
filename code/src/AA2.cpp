#include <glm\glm.hpp>
#include "EulerIntegrator.h";
#include "AA2.h"

// Auxiliar methods
#pragma region auxiliar
glm::vec3 GetParticleInitialPosition(int id, int numParticles)
{
	float margin = 0.1f;
	float available_length = 2 * (5.f - margin);
	float offset = available_length / (numParticles - 1);

	float x, y, z;
	x = z = -5.f + margin + id * offset;
	y = 9.9f;

	return glm::vec3(x, y, z);
}

bool CheckHasTravessedFloor(glm::vec3 particle)
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
		particles->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
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
		if (CheckHasTravessedFloor(particles->GetParticlePosition(i)))
		{
			particles->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
		}
	}
}

void AA2::RenderUpdate()
{
	particles->Render();
}

void AA2::RenderGui() {};

#pragma endregion