#ifndef ANDROMEDA_ROCKET_H
#define ANDROMEDA_ROCKET_H
#include <Body.h>

class Rocket : public Body {
public:

	glm::vec3 Pos;

	Rocket(float m, glm::vec3 p, glm::vec3 v);

	void draw();
};


#endif 
