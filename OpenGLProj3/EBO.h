#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

// EBO (Element Buffer Object) stores indices for reusing vertices efficiently
class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);		// Constructor uploads index data

	void Bind();
	void Unbind();
	void Delete();
};

#endif // !EBO_CLASS_H
