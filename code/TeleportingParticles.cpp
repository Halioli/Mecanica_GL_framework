#include <glm\glm.hpp>
#include "TeleportingParticles.h";
#include "EulerIntegration.h"

// Auxiliar methods
#pragma region auxiliar
glm::vec3 GetParticleInitialPosition(int id, int numParticles) 
{
	float margin = 0.1f;
	float available_length = 2 * (5.f - margin);
	float offset = available_length / (numParticles-1);

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
TeleportingParticles::TeleportingParticles() 
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

TeleportingParticles::~TeleportingParticles() 
{
	delete particles;
}

void TeleportingParticles::Update(float dt) 
{
	// THIS IS DONE AT EULER_INTEGRATION
	glm::vec3 previousPosition;
	glm::vec3 currentPosition;
	glm::vec3 previousVelocity;
	glm::vec3 currentVelocity;
	glm::vec3 acceleration = { 0.0f, -9.81f, 0.0f };

	// Logic to make particles fall down
	for (int i = 0; i < particles->GetNumberOfParticles(); i++)
	{
		// Update previous position & velocity
		previousPosition = particles->GetParticlePosition(i);
		previousVelocity = particles->GetParticleVelocity(i);

		// Update position
		currentPosition[0] = previousPosition[0] + dt * previousVelocity[0];
		currentPosition[1] = previousPosition[1] + dt * previousVelocity[1];
		currentPosition[2] = previousPosition[2] + dt * previousVelocity[2];

		// Update velocity
		currentVelocity[0] = previousVelocity[0] + dt * acceleration[0];
		currentVelocity[1] = previousVelocity[1] + dt * acceleration[1];
		currentVelocity[2] = previousVelocity[2] + dt * acceleration[2];

		// Update the paricle's position
		particles->SetParticlePosition(i, currentPosition);
		particles->SetParticleVelocity(i, currentVelocity);
	}
	// //

	// Check if a particle travessed the floor plane. Restart its position if it had
	for (int i = 0; i < numParticles; i++) 
	{
		if (CheckHasTravessedFloor(particles->GetParticlePosition(i))) 
		{
			particles->SetParticlePosition(i, GetParticleInitialPosition(i, numParticles));
		}
	}
}

void TeleportingParticles::RenderUpdate() 
{
	particles->Render();
}

void TeleportingParticles::RenderGui() {};

#pragma endregion