#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV; 
};

// VBO (Vertex Buffer Object) holds raw vertex data (positions, colors, etc.)
class VBO
{
	public:
		GLuint ID;
		VBO(std::vector<Vertex> &vertices);	// Constructor uploads data to GPU

		void Bind();
		void Unbind(); 
		void Delete(); 
};

#endif // !VBO_CLASS_H
