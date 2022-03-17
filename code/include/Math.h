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

	void CheckColision(glm::vec3 point);
	

private:
	Plane* plane;


};

