#ifndef ANDROMEDA_SHADER_H
#define ANDROMEDA_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

class Shader {
public:
	// shader IDs
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	// Use shader
	void useProgram();
	// Free memory
	void cleanup();

	// Read a GLSL shader file
	std::string readGLSLFile(std::string file);

	// Constructor
	Shader(std::string vs, std::string fs);
};

#endif
