#ifndef ANDROMEDA_ROCKET_H
#define ANDROMEDA_ROCKET_H
#include "Body.h"
#include "render/Shader.h"

class Rocket : public Body {
public:

	glm::vec3 Pos = {0, 0, 0};

	unsigned int VBO, VAO;


	//Rocket
	float vertices[9*6] = {

	 -0.5f,  -0.5f, -0.5f,  
	 0.5f, -0.5f, -0.5f,  
	0.0f,  0.5f, 0.0f,  

	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.0f, 0.5f, 0.0f,

	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.0f, 0.5f, 0.0f,

	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.0f, 0.5f, 0.0f,

	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	0.0f, 0.5f, 0.0f,

	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f,
	0.0f, 0.5f, 0.0f,


	};





	Rocket(float m, glm::vec3 p, glm::vec3 v);

	void move(glm::vec3 mov, Shader& shader);
};


#endif 
