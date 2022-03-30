#pragma once

#include <glm\glm.hpp>
#include "Geometry.h"

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
	void DecrementDelayTime(int particleId);
	bool CheckParticleDelay(int particleId);
	void ResetDelay(int particleId);

	void SetCascadePoints(glm::vec3 startingP, glm::vec3 endingP);
	enum ParticleMode {
		NORMAL,
		CASCADE,
		FOUNTAIN,
	};

	int particleMode;

	glm::vec3 cascadeStartingPoint;
	glm::vec3 cascadeEndingPoint;

	float* delayTime;

private:
	int currentNumParticles;
	int maxParticles;
	glm::vec3* currentPositions;
	glm::vec3* currentVelocities;

	glm::vec3* previousPositions;
	glm::vec3* previousVelocities;

	glm::vec3* startingPositions;
	glm::vec3* startingVelocities;

	int delayRange;
	
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