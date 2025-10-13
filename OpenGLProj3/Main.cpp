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

using namespace std; 


const unsigned int width = 800;
const unsigned int height = 800; 


//Vertices coordinates: Each vertex has 3 position floats (x, y, z) + 3 color floats (r, g, b)
GLfloat vertices[] =
{
	// Positions			// Colors (R, G, B)     //TexCoord
	-0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,		0.0f, 0.0f,  		// Lower left corner
	-0.5f, 0.0f,  -0.5f,	0.83f, 0.70f, 0.44f,		1.0f, 0.0f,		// Upper left corner
	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,		1.0f, 1.0f,		// Upper right corner
	 0.5f, 0.0f, 0.5f,		0.83f, 0.70f, 0.44f,		1.0f, 0.0f,			// Lower right corner
	 0.0f, 0.8f, 0.0f,		0.82f, 0.86f, 0.44f,		0.5f, 1.0f

};


// Index buffer — defines which vertices make each triangle
GLuint indices[] =
{
	0, 1, 2,	//Upper triangle
	0, 2, 3,     //Lower triangle
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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

	//Create a GLFWwindow* object of 800 by 800 pixels, naming it "OpenGL-Project1"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL-Project1", NULL, NULL); 

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);							// position
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));		// color
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));		//texture

	// Unbind all buffers to avoid accidental modification
	VAO1.Unbind();
	VBO1.Unbind();

	//Uniform: Scale Factor
	GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale"); 

	//Texture

	Texture woodenTex("wooden-texture.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	woodenTex.texUnit(ShaderProgram, "tex0", 0);

	float rotation = 0.0f;
	double prevTime = glfwGetTime(); 

	glEnable(GL_DEPTH_TEST);

	//Main while/Render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);							// Background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// Clear frame buffer

		//Tell OpenGL which Shader Program we want to use 
		ShaderProgram.Activate(); 

		double crntTime = glfwGetTime(); 

		if (crntTime - prevTime >= 1.0f / 60.0f)
		{
			rotation += 0.5f;
			prevTime = crntTime; 
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f)); 

		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f); 

		int modelLoc = glGetUniformLocation(ShaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 

		int viewLoc = glGetUniformLocation(ShaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(ShaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// Set scale value
		glUniform1f(uniID, 0.2f); 


		glActiveTexture(GL_TEXTURE0);
		// Binds texture so that is appears in rendering
		woodenTex.Bind();

		//Bind the VAO so OpenGL knows how to use it
		VAO1.Bind(); 

		//Draw the triangle using the GL_TRIANGLES primitive 
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);				// Display the rendered frame

		//Take care of all GLFW events
		glfwPollEvents(); 
	}

	//Delete all the objects we've created 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	woodenTex.Delete(); 
	ShaderProgram.Delete(); 

	//Destroy window before ending the program
	glfwDestroyWindow(window); 

	//Terminate the GLFW before ending the program
	glfwTerminate(); 

	return 0; 
}