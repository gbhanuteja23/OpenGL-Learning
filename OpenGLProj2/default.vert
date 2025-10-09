//Vertex Shader source code

#version 330 core

layout (location = 0) in vec3 aPos;				// Vertex position
layout (location = 1) in vec3 aColor;			// Vertex color

layout (location = 3) in vec2 aTex; 

out vec3 vertexColor;							 // Output to fragment shader

out vec2 texCoord; 

uniform float scale;							// Uniform: controls vertex scaling

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);		// Final position of vertex
	vertexColor = aColor;									// Pass color to fragment shader
	texCoord = aTex; 
}
