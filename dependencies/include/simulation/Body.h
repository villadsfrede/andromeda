#ifndef ANDROMEDA_BODY_H
#define ANDROMEDA_BODY_H

#include <iostream>
#include <glm/glm.hpp>

class Body {
public:
	float mass;
	
	glm::vec3 position;
	glm::vec3 velocity;

	Body(float m, glm::vec3 p, glm::vec3 v);
};

#endif