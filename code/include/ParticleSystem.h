#pragma once

#include <glm\glm.hpp>

class ParticleSystem {
public:
	ParticleSystem(int maxParticles);
	~ParticleSystem();
	int GetNumberOfParticles();

	void Render();
	void SetParticlePosition(int particleId, glm::vec3 position);
	glm::vec3 GetParticlePosition(int particleId);
	void SetParticleVelocity(int particleId, glm::vec3 velocity);
	glm::vec3 GetParticleVelocity(int particleId);
private:
	int maxParticles;
	glm::vec3 *positions;
	glm::vec3 *velocities;
};