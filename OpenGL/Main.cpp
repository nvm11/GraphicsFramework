#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//use gl float as float may differ in size
// Vertices coordinates
GLfloat vertices[] =
{
	//test triforce for shaders
	////coordinates										    colors
	//-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	0.8f, 0.3f, 0.02f,	// Lower left corner
	//0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f,	// Lower right corner
	//0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.6f, 0.32f,	// Upper corner
	//-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	0.9f, 0.45f, 0.17f,	// Inner left
	//0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	0.9f, 0.45f, 0.17f,	// Inner right
	//0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f	// Inner down

	//square for textures
	//coords				//colors			
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, //lower left corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, //upper left corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, //upper right corner
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f, //lower right corner

};

GLuint indices[] =
{
	//triforce test
	//0,3,5, //lower left tri
	//3,2,4, //lower right tri
	//5,4,1 //upper right tri

	//square test
	0,2,1, //upper triangle
	0,3,2 //lower triangle
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//obtain reference ot the scale uniform value
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//texture
	Texture globe("globe.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	globe.texUnit(shaderProgram, "tex0", 0);


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
		//set scale of the uniform variable to 0.5f
		glUniform1f(uniID, 0.5f);
		globe.Bind();
		// bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// draw primitives, number of indices, 
		// datatype of indices, index of indices
		//9 for triforce, 6 for square
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// handle ecebts
		glfwPollEvents();
	}

	// delete all objects created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	globe.Delete();
	shaderProgram.Delete();
	// delete window before ending program
	glfwDestroyWindow(window);
	// terminate GLFW before ending program
	glfwTerminate();
	return 0;
}