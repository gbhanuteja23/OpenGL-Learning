#include"Model.h"

using namespace std; 


const unsigned int width = 800;
const unsigned int height = 800; 


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
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL-Project6", NULL, NULL); 

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


	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	glm::vec3 lightPos = glm::vec3(0.5, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	ShaderProgram.Activate();
	glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	//Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	//Creates camera object
	Camera camera(width, height, glm::vec3(17.0f, 4.0f, 4.0f)); 

	glFrontFace(GL_CW); // Set winding order to Clockwise

	Model model("models/hal_tejas/scene.gltf");

	glFrontFace(GL_CCW); // Set winding order back to Counter-Clockwise

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

		// Draws different meshes
		model.Draw(ShaderProgram, camera); 
		

		glfwSwapBuffers(window);				// Display the rendered frame

		//Take care of all GLFW events
		glfwPollEvents(); 
	}

	// Delete all the objects we've created
	ShaderProgram.Delete();

	//Destroy window before ending the program
	glfwDestroyWindow(window); 

	//Terminate the GLFW before ending the program
	glfwTerminate(); 

	return 0; 
}