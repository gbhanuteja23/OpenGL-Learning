//Vertex Shader source code

#version 330 core

layout (location = 0) in vec3 aPos;				// Vertex position
layout (location = 1) in vec3 aColor;			// Vertex color
out vec3 vertexColor;							 // Output to fragment shader

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);		// Final position of vertex
	vertexColor = aColor;									// Pass color to fragment shader
}
