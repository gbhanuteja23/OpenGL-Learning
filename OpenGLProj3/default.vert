//Vertex Shader source code

#version 330 core

layout (location = 0) in vec3 aPos;				// Vertex position
layout (location = 1) in vec3 aColor;			// Vertex color

layout (location = 2) in vec2 aTex; 

out vec3 vertexColor;							 // Output to fragment shader

out vec2 texCoord; 

uniform float scale;							// Uniform: controls vertex scaling

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);		// Final position of vertex
	vertexColor = aColor;									// Pass color to fragment shader
	texCoord = aTex; 
}
