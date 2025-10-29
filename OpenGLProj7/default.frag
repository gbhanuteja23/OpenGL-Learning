
//Fragment Shader source code 

#version 330 core
out vec4 FragColor;					// Outputs colors in RGBA

in vec3 crntPos;					// Imports the current position from the Vertex Shader

in vec3 Normal;						// Imports the normal from the Vertex Shader

in vec3 Color;						// Input color from vertex shader

in vec2 texCoord;					// Imports the texture coordinates from the Vertex Shader



uniform sampler2D diffuse0;				// Gets the Texture Unit from the main function 

uniform sampler2D specular0; 

uniform vec4 lightColor;			// Gets the color of the light from the main function
uniform vec3 lightPos;				// Gets the position of the light from the main function
uniform vec3 camPos;				// Gets the position of the camera from the main function


vec4 PointLight()
{
	vec3 lightVec = lightPos - crntPos;

	//intensity of light wrt distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / ( a * dist * dist + b * dist + 1.0f); 

	float ambient = 0.20f;												// ambient lighting 

	//diffuse lighting
	vec3 normal = normalize(Normal);									
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f); 

	//Specular lighting
	float specularLight = 0.50f; 
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect( -lightDirection, normal); 
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16); 
	float specular = specAmount * specularLight; 

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor; 
}


vec4 DirectionalLight()
{
	//ambient light
	float ambient = 0.65f;												// ambient lighting 

	//diffuse lighting
	vec3 normal = normalize(Normal);									
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f); 

	//Specular lighting
	float specularLight = 2.0f; 
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect( -lightDirection, normal); 
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16); 
	float specular = specAmount * specularLight; 

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 SpotLight()
{

	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;

}

float nearPlane = 0.1f;
float farPlane  = 100.0f;

float linearizeDepth(float depth)
{
    return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - (depth * 2.0 - 1.0) * (farPlane - nearPlane));
}

float logisticDepth(float depth, float steepness, float offset)
{

	float zVal = linearizeDepth(depth);
	return (1.0 / (1.0 + exp(-steepness * (zVal - offset))));
}

void main()
{
	// outputs final color
	float depth = logisticDepth(gl_FragCoord.z, 0.5f, 0.5f);
	FragColor = DirectionalLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}