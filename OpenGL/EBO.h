#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);

	// binds the EBO
	void Bind();
	// unbinds the EBO
	void Unbind();
	// deletes the EBO
	void Delete();
};

#endif