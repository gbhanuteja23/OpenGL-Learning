//Vertex Shader source code

#version 330 core

layout (location = 0) in vec3 aPos;				// Vertex position
layout (location = 1) in vec3 aColor;			// Vertex color

layout (location = 2) in vec2 aTex;				//Texture coordinates

layout (location = 3) in vec3 aNormal;			//Normals

out vec3 vertexColor;							 // Output the color to fragment shader

out vec2 texCoord;								//Outputs the texture coordinates to the Fragment Shader

out vec3 Normal;								//Outputs the Normal for the Fragment Shader
out vec3 crntPos;								//Outputs the current position for the Fragment Shader
	
uniform mat4 camMatrix;							//Imports the camera matrix from the main function
uniform mat4 model;								//Imports the model matrix from the main function

void main()
{
	//Calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f)); 

	gl_Position = camMatrix * vec4(crntPos, 1.0);			// Outputs the positions/coordinates of all vertices
	vertexColor = aColor;									// Assigns the colors from Vertex Data to "color"
	texCoord = aTex;										// Assigns the texture coordintaes from the Vertex Data to "texCoord"
	Normal = aNormal;										// Assigns the normal from the Vertex Data to "Normal"
}
