#include "ParticleSystem.h"

/////////Forward declarations
namespace LilSpheres
{
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}

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
ParticleSystem::ParticleSystem(int numParticles) : maxParticles(numParticles)
{
	currentNumParticles = maxParticles;
	currentPositions = new glm::vec3[maxParticles];
	currentVelocities = new glm::vec3[maxParticles];

	previousPositions = new glm::vec3[maxParticles];
	previousVelocities = new glm::vec3[maxParticles];

	startingPositions = new glm::vec3[maxParticles];
	startingVelocities = new glm::vec3[maxParticles];

	currentLifespan = new float[maxParticles];
	maxParticleLifetime = 80.f;

	for (int i = 0; i < maxParticles; i++)
	{
		currentPositions[i] = glm::vec3(0.f, 0.f, 0.f);
		currentVelocities[i] = glm::vec3(0.f, 0.f, 0.f);

		previousPositions[i] = glm::vec3(0.f, 0.f, 0.f);
		previousVelocities[i] = glm::vec3(0.f, 0.f, 0.f);

		startingPositions[i] = currentPositions[i];
		startingVelocities[i] = currentVelocities[i];

		currentLifespan[i] = 0.f;
	}
};

ParticleSystem::~ParticleSystem()
{
	printf("Destruct the particle system\n");
	delete currentPositions;
	delete currentVelocities;
	delete previousPositions;
	delete previousVelocities;
	delete startingPositions;
	delete startingVelocities;
	delete currentLifespan;
};

int ParticleSystem::GetNumberOfParticles()
{
	return currentNumParticles;
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

float ParticleSystem::GetCurrentLifespan(int particleId)
{
	return currentLifespan[particleId];
}

bool ParticleSystem::CheckParticleLifespan(int particleId)
{
	return currentLifespan[particleId] >= maxParticleLifetime;
}

void ParticleSystem::IncrementCurrentLifespan(int particleId)
{
	++currentLifespan[particleId];
}

void ParticleSystem::SetMaxLifetime(int newVal)
{
	maxParticleLifetime = newVal;
}

void ParticleSystem::ResetParticle(int particleId)
{
	SetParticlePosition(particleId, GetParticleInitialPositionAA2(particleId, currentNumParticles));
	SetParticleVelocity(particleId, startingVelocities[particleId]);
	currentLifespan[particleId] = 0.f;
}

void ParticleSystem::SetNumParticles(int newVal)
{
	currentNumParticles = newVal;
}