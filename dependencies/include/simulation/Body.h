#ifndef ANDROMEDA_BODY_H
#define ANDROMEDA_BODY_H

#include <iostream>
#include <glm/glm.hpp>

class Body {
public:
	float mass;
	
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	Body(float m, glm::vec3 p, glm::vec3 v, glm::vec3 a);
};

#endif