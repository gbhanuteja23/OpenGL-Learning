
//Fragment Shader source code 

#version 330 core
in vec3 vertexColor;				// Input color from vertex shader
out vec4 FragColor;					// Final pixel color output

void main()
{
	FragColor = vec4(vertexColor, 1.0f);			// Set pixel color
}