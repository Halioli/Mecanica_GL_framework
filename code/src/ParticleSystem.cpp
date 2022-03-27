#include "ParticleSystem.h"

/////////Forward declarations
namespace LilSpheres
{
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

ParticleSystem::ParticleSystem(int numParticles) : maxParticles(numParticles)
{
	currentPositions = new glm::vec3[maxParticles];
	currentVelocities = new glm::vec3[maxParticles];

	previousPositions = new glm::vec3[maxParticles];
	previousVelocities = new glm::vec3[maxParticles];

	for (int i = 0; i < maxParticles; i++)
	{
		currentPositions[i] = glm::vec3(0.f, 0.f, 0.f);
		currentVelocities[i] = glm::vec3(0.f, 0.f, 0.f);

		previousPositions[i] = glm::vec3(0.f, 0.f, 0.f);
		previousVelocities[i] = glm::vec3(0.f, 0.f, 0.f);
	}
};

ParticleSystem::~ParticleSystem()
{
	printf("Destruct the particle system\n");
	delete currentPositions;
	delete currentVelocities;
	delete previousPositions;
	delete previousVelocities;
};

int ParticleSystem::GetNumberOfParticles()
{
	return maxParticles;
};

void ParticleSystem::Render()
{
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = GetNumberOfParticles();

	LilSpheres::updateParticles(0, GetNumberOfParticles(), &(currentPositions[0].x));
}

void ParticleSystem::SetParticlePosition(int particleId, glm::vec3 position)
{
	SetPreviousParticlePosition(particleId);
	currentPositions[particleId] = position;
}

glm::vec3 ParticleSystem::GetCurrentParticlePosition(int particleId)
{
	return currentPositions[particleId];
}

void ParticleSystem::SetParticleVelocity(int particleId, glm::vec3 velocity)
{
	SetPreviousParticleVelocity(particleId);
	currentVelocities[particleId] = velocity;
}

glm::vec3 ParticleSystem::GetCurrentParticleVelocity(int particleId)
{
	return currentVelocities[particleId];
}

void ParticleSystem::SetPreviousParticlePosition(int particleId)
{
	previousPositions[particleId] = GetCurrentParticlePosition(particleId);
}

glm::vec3 ParticleSystem::GetPreviousParticlePosition(int particleId)
{
	return previousPositions[particleId];
}

void ParticleSystem::SetPreviousParticleVelocity(int particleId)
{
	previousVelocities[particleId] = GetCurrentParticleVelocity(particleId);
}

glm::vec3 ParticleSystem::GetPreviousParticleVelocity(int particleId)
{
	return previousVelocities[particleId];
}

void ParticleSystem::SetMirrorParticlePosition(int particleId, glm::vec3 position)
{
	currentPositions[particleId] = position;
}

void ParticleSystem::SetMirrorParticleVelocity(int particleId, glm::vec3 velocity)
{
	currentVelocities[particleId] = velocity;
}