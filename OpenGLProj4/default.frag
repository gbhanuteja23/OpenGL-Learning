
//Fragment Shader source code 

#version 330 core
in vec3 vertexColor;				// Input color from vertex shader
out vec4 FragColor;					// Outputs colors in RGBA

in vec2 texCoord;					// Imports the texture coordinates from the Vertex Shader

in vec3 Normal;						// Imports the normal from the Vertex Shader
in vec3 crntPos;					// Imports the current position from the Vertex Shader

uniform sampler2D tex0;				// Gets the Texture Unit from the main function 

uniform vec4 lightColor;			// Gets the color of the light from the main function
uniform vec3 lightPos;				// Gets the color of the light from the main function
uniform vec3 camPos;				// Gets the position of the camera from the main function

void main()
{
	float ambient = 0.20f;												// ambient lighting 

	//diffuse lighting
	vec3 normal = normalize(Normal);									
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f); 

	//Specular lighting
	float specularLight = 0.50f; 
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect( -lightDirection, normal); 
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8); 
	float specular = specAmount * specularLight; 

	//Outputs final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);			// Set pixel color
}