#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std; 


//Vertices coordinates: Each vertex has 3 position floats (x, y, z) + 3 color floats (r, g, b)
GLfloat vertices[] =
{
	// Positions								   // Colors (R, G, B)
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       1.0f, 0.0f, 0.0f,			// Lower Left - red
	 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       0.0f, 1.0f, 0.0f,			// Lower Right - green
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   0.0f, 0.0f, 1.0f,		// Upper - blue
	-0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,   1.0f, 1.0f, 0.0f,		// Inner Left - yellow
	 0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,   1.0f, 0.0f, 1.0f,		// Inner Right - magenta
	 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,       0.0f, 1.0f, 1.0f				// Inner Down - cyan
};


// Index buffer — defines which vertices make each triangle
GLuint indices[] =
{
	0, 3, 5,	//Lower left triangle
	3, 2, 4,	//Lower right triangle
	5, 4, 1		//Upper triangle
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
	glViewport(0, 0, 800, 800); 

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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);							// position
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));		// color

	// Unbind all buffers to avoid accidental modification
	VAO1.Unbind();
	VBO1.Unbind();

	//Uniform: Scale Factor
	GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");

	//Main while/Render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);		// Background color
		glClear(GL_COLOR_BUFFER_BIT);					// Clear frame buffer

		//Tell OpenGL which Shader Program we want to use 
		ShaderProgram.Activate(); 

		// Set scale value
		glUniform1f(uniID, 0.5f); 

		//Bind the VAO so OpenGL knows how to use it
		VAO1.Bind(); 

		//Draw the triangle using the GL_TRIANGLES primitive 
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); 
		glfwSwapBuffers(window);				// Display the rendered frame

		//Take care of all GLFW events
		glfwPollEvents(); 
	}

	//Delete all the objects we've created 
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ShaderProgram.Delete(); 

	//Destroy window before ending the program
	glfwDestroyWindow(window); 

	//Terminate the GLFW before ending the program
	glfwTerminate(); 

	return 0; 
}