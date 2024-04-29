#ifndef ANDROMEDA_SHADER_H
#define ANDROMEDA_SHADER_H

#include <string>
#include <glad/glad.h>

class Shader {
public:
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint shaderProgram;

	void useProgram();
	void cleanup();

	std::string readGLSLFile(std::string file);

	Shader(std::string vs, std::string fs);
};

#endif
