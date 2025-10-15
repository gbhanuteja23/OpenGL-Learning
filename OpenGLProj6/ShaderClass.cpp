#include "ShaderClass.h"

// Reads an entire text file into a string
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);    // Open file in binary mode

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);					// Move to end to get file size
		contents.resize(in.tellg());				// Allocate string size
		in.seekg(0, std::ios::beg);					// Move back to start
		in.read(&contents[0], contents.size());		// Read entire file
		in.close();
		return(contents);							// Return file as a string
	}
	throw(errno); 
}

//Constructor: loads, compiles, and links vertex + fragment shaders
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

	CompileErrors(vertexShader, "VERTEX");

	//Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the Fragment Shader into the machine code 
	glCompileShader(fragmentShader);

	CompileErrors(fragmentShader, "FRAGMENT"); 

	//Create Shader Program Object and get its reference
	ID = glCreateProgram();

	//Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	//Warp-up/Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	CompileErrors(ID, "PROGRAM"); 

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

//Checks for shader compile and program link errors and logs them
void Shader::CompileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		// Check shader compilation
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	else
	{	
		// Check program linking
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << infoLog << std::endl;
		}
	}
}