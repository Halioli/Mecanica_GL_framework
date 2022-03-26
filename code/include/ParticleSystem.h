#pragma once

#include <glm\glm.hpp>

class ParticleSystem {
public:
	ParticleSystem(int maxParticles);
	~ParticleSystem();
	int GetNumberOfParticles();

	void Render();
	void SetParticlePosition(int particleId, glm::vec3 position);
	glm::vec3 GetCurrentParticlePosition(int particleId);
	void SetParticleVelocity(int particleId, glm::vec3 velocity);
	glm::vec3 GetCurrentParticleVelocity(int particleId);

	void SetPreviousParticlePosition(int particleId);
	glm::vec3 GetPreviousParticlePosition(int particleId);
	void SetPreviousParticleVelocity(int particleId);
	glm::vec3 GetPreviousParticleVelocity(int particleId);

private:
	int maxParticles;
	glm::vec3* currentPositions;
	glm::vec3* currentVelocities;

	glm::vec3* previousPositions;
	glm::vec3* previousVelocities;
};