#ifndef ANDROMEDA_BODY_H
#define ANDROMEDA_BODY_H

#include <glm/glm.hpp>

class Body {
public:
	float mass;
	
	glm::vec3 position;
	glm::vec3 velocity;
};

#endif