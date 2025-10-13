#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

// VBO (Vertex Buffer Object) holds raw vertex data (positions, colors, etc.)
class VBO
{
	public:
		GLuint ID;
		VBO(GLfloat* vertices, GLsizeiptr size);	// Constructor uploads data to GPU

		void Bind();
		void Unbind(); 
		void Delete(); 
};

#endif // !VBO_CLASS_H
