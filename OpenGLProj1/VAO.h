#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "VBO.h"

// VAO (Vertex Array Object) stores vertex attribute configurations
class VAO
{
	public:
		GLuint ID;
		VAO();			// Constructor creates VAO

		// Links a VBO attribute (e.g., position or color) to this VAO
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		
		void Bind();
		void Unbind();
		void Delete(); 
};

#endif // !VAO_CLASS_H
