#pragma once
#pragma once

#include <glm/glm.hpp>
#include "ParticleSystem.h"

class Plane
{
public:
    Plane();
    ~Plane();

    glm::vec3 planePoint;
    glm::vec3 planeNormal;
    float planeD;

    void CheckColision(glm::vec3 pointPos, glm::vec3 pointVel);


private:
    Plane* plane;
};

class CustomSphere {

public:
    CustomSphere(float radiusS, glm::vec3 centerS);
    ~CustomSphere();

    bool CheckCollisionSphere(glm::vec3 particlePos);
    glm::vec3* CalculateParticleMirror(glm::vec3 previousPos, glm::vec3 currentPos, glm::vec3 currentVel);
    glm::vec3 CalculatePointOfCollision(glm::vec3 particlePos);

    glm::vec3 sphereCenter;
    float sphereRadius;

private:
    CustomSphere* sphereC;

};

