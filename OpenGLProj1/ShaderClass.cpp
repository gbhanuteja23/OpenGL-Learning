#include "ShaderClass.h"

// Reads an entire text file into a string
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno); 
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Load shader source code
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile); 

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str(); 

	//Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the Vertex Shader into the machine code 
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the Fragment Shader into the machine code 
	glCompileShader(fragmentShader);

	//Create Shader Program Object and get its reference
	ID = glCreateProgram();

	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//Warp-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	//Delete the now useless Vertex and Fragment Shader Objects 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID); 
}

void Shader::Delete()
{
	glDeleteProgram(ID); 
}