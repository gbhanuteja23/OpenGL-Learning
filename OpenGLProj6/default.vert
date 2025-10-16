//Vertex Shader source code

#version 330 core

layout (location = 0) in vec3 aPos;				// Vertex position

layout (location = 1) in vec3 aNormal;			//Normals

layout (location = 2) in vec3 aColor;			// Vertex color

layout (location = 3) in vec2 aTex;				//Texture coordinates


out vec3 crntPos;								//Outputs the current position for the Fragment Shader

out vec3 Normal;								//Outputs the Normal for the Fragment Shader

out vec3 Color;							 // Output the color to fragment shader

out vec2 texCoord;								//Outputs the texture coordinates to the Fragment Shader

	
uniform mat4 camMatrix;							//Imports the camera matrix from the main function
uniform mat4 model;								//Imports the model matrix from the main function
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	//Calculates current position
	crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f)); 

	Normal = aNormal;										// Assigns the normal from the Vertex Data to "Normal"

	Color = aColor;									// Assigns the colors from Vertex Data to "color"
	texCoord = mat2(0.0f, -1.0f, 1.0, 0.0f) * aTex;										// Assigns the texture coordintaes from the Vertex Data to "texCoord"

	gl_Position = camMatrix * vec4(crntPos, 1.0);			// Outputs the positions/coordinates of all vertices
	
}
