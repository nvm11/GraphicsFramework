#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	//open GLFW
	glfwInit();

	//GLFW doesnt know its version, we specify
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	//again, use open gl uint to avoid differences

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//link shaders together
	glLinkProgram(shaderProgram);

	//already in program, so delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	GLuint VAO, VBO, EBO;

	//always generate VAO before VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Make VAO current Vertex Array Object by Binding it
	glBindVertexArray(VAO);

	//look at OpenGL docs for different 
	//types of buffers and what they do
	//using array buffer here
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//create object with vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//inputs: position of vertex attrib, number of values for the vertex attrib, type of value, if we use ints for our values, amount of data between each vertex, pointer to verticies beginnning our array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	//rgba specify color
	glClearColor(0.31f, 0.10f, 0.19f, 1.0f);
	//assign new color
	glClear(GL_COLOR_BUFFER_BIT);
	//swap back buffer with front buffer
	glfwSwapBuffers(window);

	//main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.31f, 0.10f, 0.19f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//draw the triangle using the GL TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		//take care of events
		glfwPollEvents();
	}
	//delete all objects wevee created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	//destroy window
	glfwDestroyWindow(window);
	//close GLFW
	glfwTerminate();
	return 0;
}