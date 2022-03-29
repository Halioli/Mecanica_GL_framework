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

	void SetMirrorParticlePosition(int particleId, glm::vec3 position);
	void SetMirrorParticleVelocity(int particleId, glm::vec3 velocity);

	float GetCurrentLifespan(int particleId);
	bool CheckParticleLifespan(int particleId);
	void IncrementCurrentLifespan(int particleId);
	void SetMaxLifetime(int newVal);
	void ResetParticle(int particleId);
	void ResetParticleCascade(int particleId);
	void SetNumParticles(int newVal);
	void CascadeMode(int particleId);
	void SetStartingValues();
	void FountainMode(int particleId);
	void ResetParticleFountain(int particleId);

	enum ParticleMode {
		NORMAL,
		CASCADE,
		FOUNTAIN,
	};

	int particleMode;

	glm::vec3 cascadeStartingPoint;
	glm::vec3 cascadeEndingPoint;

private:
	int currentNumParticles;
	int maxParticles;
	glm::vec3* currentPositions;
	glm::vec3* currentVelocities;

	glm::vec3* previousPositions;
	glm::vec3* previousVelocities;

	glm::vec3* startingPositions;
	glm::vec3* startingVelocities;

	
	glm::vec3 cascadeStartingVelocity;
	int cascadeRotationAngle;
	float cascadeStartingVelocityMag;

	glm::vec3 fountainDirection;
	glm::vec3 fountainPosition;
	int fountainAngle;
	glm::vec3 fountainStartingVelocity;
	float fountainStartingVelocityMag;
	
	float* currentLifespan;
	float maxParticleLifetime;
};