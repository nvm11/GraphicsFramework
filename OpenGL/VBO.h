#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* verticies, GLsizeiptr size);

	//binds the vbo
	void Bind();
	//unbinds the vbo
	void Unbind();
	//deletes the vbo
	void Delete();
};

#endif