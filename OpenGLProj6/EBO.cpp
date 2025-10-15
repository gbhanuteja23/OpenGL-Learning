#include "EBO.h"

EBO::EBO(std::vector<GLuint> &indices)
{
	glGenBuffers(1, &ID);		// Generate buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);		// Bind as index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);		// Upload indices
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}