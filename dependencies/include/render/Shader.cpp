#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

std::string Shader::readGLSLFile(std::string file)
{
	std::string content;

	std::ifstream s;
	
	s.open(file);

	if (s.is_open())
	{
		std::stringstream buffer;

		buffer << s.rdbuf();

		content = buffer.str();
	}
	else
	{
		std::cout << "Failed to open file: " << file << std::endl;
	}

	s.close();

	return content;
}

void Shader::useProgram()
{
	glUseProgram(shaderProgram);
}

void Shader::cleanup()
{
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader);
	glDeleteProgram(shaderProgram);
}

Shader::Shader(std::string vs, std::string fs)
{
	std::string vertexData = readGLSLFile(vs);
	std::string fragmentData = readGLSLFile(fs);

	const char* vertexSource = vertexData.c_str();
	const char* fragmentSource = fragmentData.c_str();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	int status = 0;

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	std::cout << "VERTEX STATUS: " << status << std::endl;
	
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	std::cout << "FRAGMENT STATUS: " << status << std::endl;

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	std::cout << "LINKING STATUS: " << status << std::endl;
}