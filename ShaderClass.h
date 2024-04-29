#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <String.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);


class Shader {
	public:
		GLuint ID;
		Shader(const char* VertexFile, const char* FragFile);

		void Activate();
		void Delete();

};





#endif // !ShaderClass

