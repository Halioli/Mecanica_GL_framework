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
	positions = new glm::vec3[maxParticles];
	velocities = new glm::vec3[maxParticles];

	for (int i = 0; i < maxParticles; i++) 
	{
		positions[i] = glm::vec3(0.f, 0.f, 0.f);
		velocities[i] = glm::vec3(0.f, 0.f, 0.f);
	}
};

ParticleSystem::~ParticleSystem() 
{
	printf("Destruct the particle system\n");
	delete positions;
	delete velocities;
};

int ParticleSystem::GetNumberOfParticles() 
{
	return maxParticles;
};

void ParticleSystem::Render() 
{
	LilSpheres::firstParticleIdx = 0;
	LilSpheres::particleCount = GetNumberOfParticles();

	LilSpheres::updateParticles(0, GetNumberOfParticles(), &(positions[0].x));
}

void ParticleSystem::SetParticlePosition(int particleId, glm::vec3 position) 
{
	positions[particleId] = position;
}

glm::vec3 ParticleSystem::GetParticlePosition(int particleId) 
{
	return positions[particleId];
}

void ParticleSystem::SetParticleVelocity(int particleId, glm::vec3 velocity)
{
	velocities[particleId] = velocity;
}

glm::vec3 ParticleSystem::GetParticleVelocity(int particleId)
{
	return velocities[particleId];
}