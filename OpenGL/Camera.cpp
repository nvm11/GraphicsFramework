#include"Camera.h"

/// <summary>
/// instantiates the camera with the specified values
/// </summary>
/// <param name="width">width of window</param>
/// <param name="height">height of window</param>
/// <param name="position">starting position of the camera</param>
Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

/// <summary>
/// informs vertex shader of changes to the camera matrix
/// </summary>
/// <param name="FOVdeg">Field of View (in degrees)</param>
/// <param name="nearPlane">distance from camera to the near clipping plane
/// (closets dist at which objects are rendered). prevents objects from being too close to the camera</param>
/// <param name="farPlane">dist from camera to far clipping plane. 
/// anyhting beyond this dist is not rendered</param>
void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	//initialize matrix as identity matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//make camera look in the correct direction + position
	view = glm::lookAt(Position, Position + Orientation, Up);
	//add perspecitve to the scene. odd effect when left out
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	//export new camMatrix to vertex shader
	cameraMatrix = projection * view;
}

/// <summary>
/// exports the camera matrix to a shader
/// </summary>
/// <param name="shader">shader to export matrix to</param>
/// <param name="uniform">name of uniform variable to export the matrix to</param>
void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix to uniform value of a shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

/// <summary>
/// input handler of FPS Controller
/// </summary>
/// <param name="window">window to navigate</param>
void Camera::Inputs(GLFWwindow* window)
{
	//forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	//left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	//backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	//right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	//up
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	//down
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	//speed up
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.04f;
	}
	//normal speed
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}
	//rotate camera
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//hide cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//prevents jump on first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		//stores cursor coords
		double mouseX;
		double mouseY;

		//fetches coords of th cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//normalizes and shifts the coords of the cursor so they
		//begin from the center of the window. turns coord to degrees
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		//calculates vertical change in orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		//prevents barrell rolls
		if (!(glm::angle(newOrientation, Up) <= glm::radians(5.0f)
			|| glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))
		{
			Orientation = newOrientation;
		}

		//rotates the orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
		//sends mouse cursor to the middle of the screen
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		//shows cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//resets firstClick
		firstClick = true;
	}
}