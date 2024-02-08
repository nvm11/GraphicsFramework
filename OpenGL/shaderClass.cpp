#include"shaderClass.h"

//reads a text file and outputs a string with everything in the text file
//(serialization)
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

/// <summary>
/// creates a shader program with the specified shaders
/// </summary>
/// <param name="vertexFile">vertex shader</param>
/// <param name="fragmentFile">fragment shader</param>
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	//read files and store as strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//convert shader strings into arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader object
	//obtain its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach vertex shader to vert shader obj
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile into machine code
	glCompileShader(vertexShader);
	//check for successful compilation
	compileErrors(vertexShader, "VERTEX");

	//create fragment shader obj
	//get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//attach frag shader source to frag shader obj
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile into machine code
	glCompileShader(fragmentShader);
	//check for successful compilation
	compileErrors(fragmentShader, "FRAGMENT");

	//create program and obtain a reference to it
	ID = glCreateProgram();

	//attach vertex and fragment shaders to the program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//link shaders together
	glLinkProgram(ID);

	//already in program, so delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/// <summary>
/// acivates shader program
/// </summary>
void Shader::Activate()
{
	glUseProgram(ID);
}

/// <summary>
/// deletes shader program
/// </summary>
void Shader::Delete()
{
	glDeleteProgram(ID);
}

/// <summary>
/// checks if shader program has already compiled
/// </summary>
/// <param name="shader">shader program to check</param>
/// <param name="type">type of program (vertex, frag, shader)</param>
void Shader::compileErrors(unsigned int shader, const char* type)
{
	//stores compilation status
	GLint hasCompiled;
	//error message array
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER COMPILATION ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}