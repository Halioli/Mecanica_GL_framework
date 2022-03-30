#include <glm\glm.hpp>
#include "EulerIntegrator.h";
#include "AA2.h"
#include "Geometry.h"
#include <imgui/imgui.h>
#include <time.h>


namespace Planes
{
	Plane bottomPlane(glm::vec3(1.f, 0.f, 1.f), glm::vec3(0.f, -1.f, 0.f));

	Plane topPlane(glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f, -1.f, 0.f));

	Plane leftPlane(glm::vec3(-5.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
	Plane rightPlane(glm::vec3(5.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));
	Plane frontPlane(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, 1.f));
	Plane backPlane(glm::vec3(0.f, 0.f, -5.f), glm::vec3(0.f, 0.f, 1.f));

}

namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	CustomSphere customSphere(1.f, glm::vec3(0.f, 2.f, 0.f));
}

namespace Capsule 
{
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
}

namespace LilSpheres 
{
	extern const int maxParticles;
	extern int firstParticleIdx;
	extern int particleCount;
	extern int maxLifetime = 40;
	extern void updateParticles(int startIdx, int count, float* array_data);

	extern enum ParticleMode {
		NORMAL,
		CASCADE,
		FOUNTAIN
	};

	//No ho agafa
	glm::vec3 cascadeStartingPoint = glm::vec3(-4.f, 4.f, -4.f);
	glm::vec3 cascadeEndingPoint = glm::vec3(-4.f, 4.f, 2.f);
}

int particleNum = 1500;

extern glm::vec3 GetParticleInitialPositionAA2(int id, int numParticles);

#pragma region class
AA2::AA2()
{
	srand(time(NULL));
	numParticles = 1500;
	particles = new ParticleSystem(numParticles);

	for (int i = 0; i < numParticles; i++)
	{
		switch (particles->particleMode) {
			case LilSpheres::NORMAL:
				particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
				break;

			case LilSpheres::CASCADE:
				particles->CascadeMode(i);
				break;

			case LilSpheres::FOUNTAIN:
				particles->FountainMode(i);
				break;

			default:
				particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
				break;
		}
	}

	capsuleA = glm::vec3(2.f, 3.f, 0.f);
	capsuleB = glm::vec3(4.f, 4.f, 0.f);
	capsuleRadius = 1.f;

	// Enable the rendering of particles in the framework 
	extern bool renderParticles; renderParticles = true;
	extern bool renderSphere; renderSphere = true;
	extern bool renderCapsule; renderCapsule = false;
}

AA2::~AA2()
{
	delete particles;
	renderSphere = false;
	renderCapsule = false;
}

void AA2::Update(float dt)
{
	EulerIntegrator eulerInt;
	glm::vec3* mirrorRes;

	eulerInt.Step(particles, dt);

	particles->SetMaxLifetime(LilSpheres::maxLifetime);
	particles->SetNumParticles(particleNum);
	particles->SetCascadePoints(LilSpheres::cascadeStartingPoint, LilSpheres::cascadeEndingPoint);

	for (int i = 0; i < numParticles; i++)
	{
		if(!particles->CheckParticleDelay(i)){
			particles->DecrementDelayTime(i);
		}
		else {
			particles->IncrementCurrentLifespan(i);

			if (particles->CheckParticleLifespan(i))
			{
				switch (particles->particleMode)
				{
				case LilSpheres::NORMAL:
					particles->ResetParticle(i);
					break;

				case LilSpheres::CASCADE:
					particles->ResetParticleCascade(i);
					break;

				case LilSpheres::FOUNTAIN:
					particles->ResetParticle(i);
					break;

				default:
					particles->ResetParticle(i);
					break;
				}
			}
			// === Check Plane Collisions ===
			if (Planes::bottomPlane.CheckBottomColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::bottomPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			if (Planes::topPlane.CheckTopColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::topPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			if (Planes::leftPlane.CheckLeftColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::leftPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			if (Planes::rightPlane.CheckRightColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::rightPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			if (Planes::frontPlane.CheckFrontColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::frontPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			if (Planes::backPlane.CheckBackColision(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Planes::backPlane.CalculateParticleMirror(particles->GetCurrentParticlePosition(i),
					particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}

			// === Check Sphere Collisions ===
			if (Sphere::customSphere.CheckCollisionSphere(particles->GetCurrentParticlePosition(i)))
			{
				mirrorRes = Sphere::customSphere.CalculateParticleMirror(particles->GetPreviousParticlePosition(i),
					particles->GetCurrentParticlePosition(i), particles->GetCurrentParticleVelocity(i));

				particles->SetMirrorParticlePosition(i, mirrorRes[0]);
				particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
			}
		}
		
	}

	Sphere::customSphere.SphereMovement(renderSphere);
}

void AA2::RenderUpdate()
{
	particles->Render();
	Sphere::updateSphere(Sphere::customSphere.sphereCenter, Sphere::customSphere.sphereRadius);
	Capsule::updateCapsule(capsuleA, capsuleB, capsuleRadius);
}

void AA2::RenderGui() 
{
	ImGui::Checkbox("Show particles", &renderParticles);
	ImGui::Checkbox("Show sphere", &renderSphere);
	ImGui::Checkbox("Show capsule", &renderCapsule);

	if (!renderSphere)
	{
		Sphere::customSphere.sphereRadius = 0.f;
	}

	if (renderParticles) 
	{
		ImGui::SliderInt(
			"Number of particles", //label
			&particleNum, // where the value exists
			0, // min
			40 // max
		);

		ImGui::SliderInt(
			"Particle lifetime", //label
			&LilSpheres::maxLifetime, // where the value exists
			0, // min
			360 // max
		);

		ImGui::RadioButton("Normal", &particles->particleMode, LilSpheres::NORMAL);
		ImGui::RadioButton("Cascade", &particles->particleMode, LilSpheres::CASCADE);
		ImGui::RadioButton("Fountain", &particles->particleMode, LilSpheres::FOUNTAIN);

		ImGui::InputFloat3(
			"Segment A",
			&LilSpheres::cascadeStartingPoint.x
		);

		ImGui::InputFloat3(
			"Segment B",
			&LilSpheres::cascadeEndingPoint.x
		);
	}

	if (renderSphere)
	{
		ImGui::InputFloat3(
			"Sphere center",
			&Sphere::customSphere.sphereCenter.x // pointer to an array of 3 floats
		);

		ImGui::InputFloat(
			"Sphere Radius",
			&Sphere::customSphere.sphereRadius
		);

		ImGui::RadioButton("Move left", &Sphere::customSphere.sphereMovement, Sphere::customSphere.LEFT);
		ImGui::RadioButton("STOP", &Sphere::customSphere.sphereMovement, Sphere::customSphere.STOP);
		ImGui::RadioButton("Move right", &Sphere::customSphere.sphereMovement, Sphere::customSphere.RIGHT);

		if (ImGui::Button("Reset sphere")) 
		{
			Sphere::customSphere.sphereCenter = glm::vec3(0.f, 1.f, 0.f);
		}
	}

	if (renderCapsule)
	{
		ImGui::SliderFloat3(
			"Capsule A",
			&capsuleA.x,
			-5.f,
			10.f
		);
	}
};

#pragma endregion

