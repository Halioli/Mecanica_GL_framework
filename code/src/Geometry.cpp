#include "Geometry.h"

glm::vec3 CalculateVectorBetweenTwoPoints(glm::vec3 firstP, glm::vec3 secondP) {
    return firstP - secondP;
}

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

CustomSphere::CustomSphere(float radiusS, glm::vec3 centerS) {

    sphereRadius = radiusS;
    sphereCenter = centerS;
}

CustomSphere::~CustomSphere() {

}

bool CustomSphere::CheckCollisionSphere(glm::vec3 particlePos) 
{
    glm::vec3 vecRes = CalculateVectorBetweenTwoPoints(sphereCenter, particlePos);
    float magnitudeVector = glm::length(vecRes);

    return magnitudeVector <= sphereRadius;
}


void CustomSphere::CalculateParticleMirror(glm::vec3 previousParticlePos) 
{

    glm::vec3 pointOfCollision = CalculatePointOfCollision(previousParticlePos)
}

//Aixo es crida a CalculateParticleMirror()
glm::vec3 CustomSphere::CalculatePointOfCollision(glm::vec3 previousParticlePos) 
{
    float λRect[2];

    float a;
    float b;
    float c;
    glm::vec3 pointOfCollision;

    glm::vec3 vecRes = CalculateVectorBetweenTwoPoints(sphereCenter, previousParticlePos);

    
    //Ax + By + Cz + D = 0     
    //Pc = P + λV <--------------- Hem de trobar la lambda (ens donarà 2 res)
    // (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = r^2

    c = (pow(previousParticlePos.x - sphereCenter.x, 2) + 
        pow(previousParticlePos.y - sphereCenter.y, 2) + 
        pow(previousParticlePos.z - sphereCenter.z, 2)) - pow(sphereRadius, 2);

    b = (2 * previousParticlePos.x * vecRes.x) + 
        (2 * previousParticlePos.y * vecRes.y) + 
        (2 * previousParticlePos.z * vecRes.z);

    a = pow(vecRes.x, 2) +
        pow(vecRes.y, 2) +
        pow(vecRes.z, 2);

    λRect[0] = ( - (b) + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    λRect[1] = (-(b) - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;


    if (λRect[0] >= λRect[1])
    {
       pointOfCollision = previousParticlePos + λRect[1] * vecRes;
    }
    else
    {
        pointOfCollision = previousParticlePos + λRect[0] * vecRes;
    }
    return pointOfCollision;

}




