#include"VBO.h"
//vertex buffer object that stores vertex data and 
//info of geometry of objects to be rendered
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

//bind vbo
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

//unbind vbo
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//deletes the vbo
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}