#include "Mesh.h"

using namespace std; 


const unsigned int width = 800;
const unsigned int height = 800; 


//Vertices coordinates: Each vertex has 3 position floats (x, y, z) + 3 color floats (r, g, b)
Vertex vertices[] =
{
	// Positions							// Colors (R, G, B)				//TexCoord						//Normals
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),	glm::vec3(0.0f, 1.0f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f)}

};


// Indices for vertices order 
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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


	//Texture data
	Texture textures[]
	{
		Texture("planks.png", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};


	// Create the shader program using vertex and fragment shaders
	Shader ShaderProgram("default.vert", "default.frag"); 

	//Store mesh data in vectors for the mesh
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture)); 

	//Create floor mesh
	Mesh floor(verts, ind, tex); 

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));

	// Create light mesh
	Mesh light(lightVerts, lightInd, tex);



	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	glm::vec3 lightPos = glm::vec3(0.5, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos); 

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel)); 
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	ShaderProgram.Activate(); 
	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



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

		// Draws different meshes
		floor.Draw(ShaderProgram, camera);
		light.Draw(lightShader, camera);
		

		glfwSwapBuffers(window);				// Display the rendered frame

		//Take care of all GLFW events
		glfwPollEvents(); 
	}

	// Delete all the objects we've created
	ShaderProgram.Delete();
	lightShader.Delete();

	//Destroy window before ending the program
	glfwDestroyWindow(window); 

	//Terminate the GLFW before ending the program
	glfwTerminate(); 

	return 0; 
}