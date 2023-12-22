#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//use gl float as float may differ in size
// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

GLuint indices[] =
{
	0,3,5, //lower left tri
	3,2,4, //lower right tri
	5,4,1 //upper right tri
};

int main()
{
	//open GLFW
	glfwInit();

	//GLFW doesnt know its version, we specify
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//name window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Program", NULL, NULL);
	//error check
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//introduce window to current context
	glfwMakeContextCurrent(window);
	//load GLADF so it configures OpenGL
	gladLoadGL();

	//specify viewport
	glViewport(0, 0, 800, 800);

	// generates shader obj using shaders files
	Shader shaderProgram("default.vert", "default.frag");


	// generates vertex array 
	// object and binds it
	VAO VAO1;
	VAO1.Bind();

	// generates vertex buffer object 
	// and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// generates element buffer object 
	// and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	// unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//main while loop
	while (!glfwWindowShouldClose(window))
	{
		// specify background color
		glClearColor(0.31f, 0.10f, 0.19f, 1.0f);
		// clear back buffer 
		// and assign the new color
		glClear(GL_COLOR_BUFFER_BIT);
		// tell OpenGL which shader
		// program we want to use
		shaderProgram.Activate();
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// draw primitives, number of indices, 
		// datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// handle ecebts
		glfwPollEvents();
	}

	// delete all objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// delete window before ending program
	glfwDestroyWindow(window);
	// terminate GLFW before ending program
	glfwTerminate();
	return 0;
}