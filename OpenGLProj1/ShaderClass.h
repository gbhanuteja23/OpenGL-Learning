#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

// Helper function to read shader source code from a file
std::string get_file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;		// Shader program ID

		// Constructor: creates a shader program from vertex and fragment shader files
		Shader(const char* vertexFile, const char* fragmentFile);

		// Activates the shader program for rendering
		void Activate();

		// Deletes the shader program when no longer needed
		void Delete(); 
};

#endif // !SHADER_CLASS_H

