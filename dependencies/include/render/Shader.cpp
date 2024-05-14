#include "Shader.h"

std::string Shader::readGLSLFile(std::string file)
{
	std::string content;

	std::ifstream s;
	
	s.open(file);

	if (s.is_open())
	{
		std::stringstream buffer;

		// Read input stream into buffer
		buffer << s.rdbuf();

		// Set content as string of buffer data
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
	// Free memory
	glDeleteProgram(vertexShader);
	glDeleteProgram(fragmentShader);
	glDeleteProgram(shaderProgram);
}

// Constructor
Shader::Shader(std::string vs, std::string fs)
{
	// Read vs and fs file
	std::string vertexData = readGLSLFile(vs);
	std::string fragmentData = readGLSLFile(fs);

	// Create vs and fs source
	const char* vertexSource = vertexData.c_str();
	const char* fragmentSource = fragmentData.c_str();

	// Create shader programs
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	// Set shader sources
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	int status = 0;

	// Compile vs
	glCompileShader(vertexShader);
	// Check vs compile status
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	std::cout << "VERTEX STATUS: " << status << std::endl;
	
	// Compile fs
	glCompileShader(fragmentShader);
	// Check fs compile status
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	std::cout << "FRAGMENT STATUS: " << status << std::endl;

	// Attach vs and fs to shaderprogam
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link shaderprogram
	glLinkProgram(shaderProgram);
	// Check shaderprogram linking
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	std::cout << "LINKING STATUS: " << status << std::endl;
}