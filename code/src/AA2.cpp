#include <glm\glm.hpp>
#include "EulerIntegrator.h";
#include "AA2.h"
#include "Geometry.h"
#include <imgui/imgui.h>


namespace Planes
{
	Plane bottomPlane(glm::vec3(1.f, 0.f, 1.f), glm::vec3(), 1.f);

	Plane topPlane(glm::vec3(), glm::vec3(), 0.f);
	Plane leftPlane(glm::vec3(), glm::vec3(), 0.f);
	Plane rightlane(glm::vec3(), glm::vec3(), 0.f);
	Plane frontPlane(glm::vec3(), glm::vec3(), 0.f);
	Plane backPlane(glm::vec3(), glm::vec3(), 0.f);
}

namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	CustomSphere customSphere(1.f, glm::vec3(0.f, 2.f, 0.f));
}

namespace LilSpheres {
	extern const int maxParticles;
	extern int firstParticleIdx, particleCount;
	extern void updateParticles(int startIdx, int count, float* array_data);
}
//namespace Capsule 
//{
//	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius);
//}

// Auxiliar methods
#pragma region auxiliar
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

bool CheckHasTravessedFloorAA2(glm::vec3 particle)
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
		particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
	}

	/*capsuleA = glm::vec3(2.f, 3.f, 0.f);
	capsuleB = glm::vec3(4.f, 4.f, 0.f);
	capsuleRadius = 1.f;*/

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

	// Check if a particle travessed the floor plane. Restart its position if it had
	for (int i = 0; i < numParticles; i++)
	{
		particles->IncrementCurrentLifespan(i);
		if (particles->CheckParticleLifespan(i))
		{
			particles->ResetParticle(i);
		}

		if (CheckHasTravessedFloorAA2(particles->GetCurrentParticlePosition(i)))
		{
			particles->SetParticlePosition(i, GetParticleInitialPositionAA2(i, numParticles));
		}

		if (Sphere::customSphere.CheckCollisionSphere(particles->GetCurrentParticlePosition(i)))
		{
			mirrorRes = Sphere::customSphere.CalculateParticleMirror(particles->GetPreviousParticlePosition(i), 
							particles->GetCurrentParticlePosition(i), particles->GetCurrentParticleVelocity(i));

			particles->SetMirrorParticlePosition(i, mirrorRes[0]);
			particles->SetMirrorParticleVelocity(i, mirrorRes[1]);
		}
	}

	Sphere::customSphere.SphereMovement(renderSphere);
}

void AA2::RenderUpdate()
{
	particles->Render();
	Sphere::updateSphere(Sphere::customSphere.sphereCenter, Sphere::customSphere.sphereRadius);
	//Capsule::updateCapsule(capsuleA, capsuleB, capsuleRadius);
}

void AA2::RenderGui() 
{
	ImGui::Checkbox("Show particles", &renderParticles);
	ImGui::Checkbox("Show sphere", &renderSphere);
	//guiCapsuleChanged |= ImGui::Checkbox("Show capsule", &renderCapsule);

	if (!renderSphere)
	{
		Sphere::customSphere.sphereRadius = 0.f;
	}


	if (renderParticles) {
		ImGui::SliderInt(
			"First particle", //label
			&LilSpheres::firstParticleIdx, // where the value exists
			0, // min
			numParticles // max
		);
		ImGui::DragInt(
			"Number of particles", //label
			&LilSpheres::particleCount, // where the value exists
			1.f, // drag speed
			0, // min
			LilSpheres::maxParticles // max
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

		if (ImGui::Button("Reset sphere")) {
			Sphere::customSphere.sphereCenter = glm::vec3(0.f, 1.f, 0.f);
		}

		/*if (renderCapsule) {
			guiCapsuleChanged |= ImGui::SliderFloat3(
				"Capsule A",
				&capsuleA.x,
				-5.f,
				10.f
			);
		}*/
	}
};

#pragma endregion

