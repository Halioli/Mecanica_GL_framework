#include "Geometry.h"

Plane::Plane()
{

}

Plane::~Plane()
{

}

void Plane::CheckColision(glm::vec3 pointPos, glm::vec3 pointVel)
{
    if (pointPos.z <= planePoint.z)
    {
        // Colision happened
        glm::vec3 vector = { pointPos.x - planePoint.x, pointPos.y - planePoint.y, pointPos.z - planePoint.z };

        float result = pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2);
        float vectorModule = sqrt(result);

        //planeNormal.x * pointPos.x + planeNormal.y * pointPos.y + planeNormal.z * pointPos.z + D = 0
        float dValue = -(pointPos.x * planeNormal.x + pointPos.y * planeNormal.y + pointPos.z * planeNormal.z);

        // == Mirror ==
        //p = p' -2(n * p' + d) * n
        //glm::vec3 mirrorPosition = pointPos - 2 * (planeNormal * pointPos + dValue) * planeNormal;
        //v = v' -2(n * v') * n
        //glm::vec3 mirrorVelocity = pointVel - 2 * (planeNormal * pointVel) * planeNormal;
    }
}