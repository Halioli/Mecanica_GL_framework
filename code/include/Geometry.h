#pragma once
#pragma once

#include <glm/glm.hpp>

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

class SphereCreated {

public:
    SphereCreated();
    ~SphereCreated();

    void ChechCollisionSphere();
private:
    SphereCreated* sphereC;
};

