#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);											// Generate buffer ID
	glBindBuffer(GL_ARRAY_BUFFER, ID);								// Bind buffer as an array buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);	// Copy vertex data 
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID); 
}