#include "Math.h"

Plane::Plane() {
	//planeNormal * planePoint + planeD;
	
}

Plane::~Plane() {

}

void Plane::CheckColision(glm::vec3 point){
	if (point.z <= planePoint.z) {

	}
}

