#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

using namespace std; 


const unsigned int width = 800;
const unsigned int height = 800; 


//Vertices coordinates: Each vertex has 3 position floats (x, y, z) + 3 color floats (r, g, b)
GLfloat vertices[] =
{
	// Positions			// Colors (R, G, B)     //TexCoord		  //Normals
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f

};


// Indices for vertices order 
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{	// Coordinates //
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, 0.1f,
	 -0.1f, 0.1f, 0.1f,
	 -0.1f, 0.1f, -0.1f,
	  0.1f, 0.1f, -0.1f,
	  0.1f, 0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
}; 

int main()
{
	//Initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGL are we using
	//In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Tell GLFW we are using the CORE Profile
	//So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	//Create a GLFWwindow* object of 800 by 800 pixels, naming it "OpenGL-Project4"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL-Project4", NULL, NULL); 

	//Error check if the window fails to create
	if (window == NULL)
	{
		cout << "Failed to create GLFW Widow" << endl;
		glfwTerminate();
		return -1; 

	}
	//Introduce the window into the current context
	glfwMakeContextCurrent(window); 

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGL in the window
	//In this case the viewport goes from x=0, y=0, to x=800, y=800
	glViewport(0, 0, width, height); 

	// Create the shader program using vertex and fragment shaders
	Shader ShaderProgram("default.vert", "default.frag"); 

	// Create and bind a Vertex Array Object (VAO)
	VAO VAO1;
	VAO1.Bind();

	// Create a Vertex Buffer Object (VBO) and copy vertex data into it
	VBO VBO1(vertices, sizeof(vertices));

	// Create an Element Buffer Object (EBO) and copy index data into it
	EBO EBO1(indices, sizeof(indices));

	// Link vertex attributes (position and color) to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);							// position
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));		// color
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));		//texture
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));		//Normals

	// Unbind all buffers to avoid accidental modification
	VAO1.Unbind();
	VBO1.Unbind();

	//Shader for light cube
	Shader lightShader("light.vert", "light.frag");

	//Generate Vertex Array Object and bind it 
	VAO lightVAO;
	lightVAO.Bind();

	//Generate Vertex Buffer Object and link it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	//Generate Element(Index) Buffer Object and link it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	//Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	//Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind(); 

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 

	glm::vec3 lightPos = glm::vec3(0.5, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos); 

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel)); 
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	ShaderProgram.Activate(); 
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//Texture
	Texture planksTex("planks.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	planksTex.texUnit(ShaderProgram, "tex0", 0);

	Texture planksSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE); 
	planksSpec.texUnit(ShaderProgram, "tex1", 1); 

	//Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	//Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f)); 

	double prevTime = glfwGetTime();

	//Main while/Render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);							// Background color
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// Clean the back buffer and depth buffer

		double crntTime = glfwGetTime();

		if (crntTime - prevTime >= 1.0f / 60.0f)
		{
			float deltaTime = crntTime - prevTime; 

			// Handles camera inputs
			camera.Inputs(window, deltaTime);
			prevTime = crntTime;
		}		

		//Updates and exports the camera matrix to the Vertex Shader 
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f); 

		//Tell OpenGL which Shader Program we want to use 
		ShaderProgram.Activate();
		
		//Export the camera Position to the fragment Shader for specular lighting 
		glUniform3f(glGetUniformLocation(ShaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		
		//Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(ShaderProgram, "camMatrix"); 

		glActiveTexture(GL_TEXTURE0);
		// Binds texture so that is appears in rendering
		planksTex.Bind();
		planksSpec.Bind(); 

		//Bind the VAO so OpenGL knows how to use it
		VAO1.Bind(); 

		//Draw the triangle using the GL_TRIANGLES primitive 
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);		


		lightShader.Activate();
		
		//Export the camMatrix to the Vertex Shader of the light cube 
		camera.Matrix(lightShader, "camMatrix");

		//Bind the VAO so OpenGL knows to use it 
		lightVAO.Bind();

		//Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		

		glfwSwapBuffers(window);				// Display the rendered frame

		//Take care of all GLFW events
		glfwPollEvents(); 
	}

	//Delete all the objects we've created 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	planksTex.Delete(); 
	ShaderProgram.Delete(); 
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete(); 

	//Destroy window before ending the program
	glfwDestroyWindow(window); 

	//Terminate the GLFW before ending the program
	glfwTerminate(); 

	return 0; 
}