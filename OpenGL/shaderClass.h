#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	//ID of the shader program
	GLuint ID;
	//constructor that builds the shader program from two 
	//shaders (fragment and vertex shaders)
	Shader(const char* vertexFile, const char* fragmentFile);

	//activates shader program
	void Activate();
	//deletes shader program
	void Delete();
private:
	//checks if shaders are already compiled
	void compileErrors(unsigned int shader, const char* type);
};

#endif
