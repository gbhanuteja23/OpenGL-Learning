
//Fragment Shader source code 

#version 330 core
in vec3 vertexColor;				// Input color from vertex shader
out vec4 FragColor;					// Final pixel color output

in vec2 texCoord;

uniform sampler2D tex0; 

void main()
{
	FragColor = texture(tex0, texCoord);			// Set pixel color
}