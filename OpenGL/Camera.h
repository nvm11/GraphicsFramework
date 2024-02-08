#ifndef  CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"


class Camera
{
public:
	//camera vectors
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	//prevents camera from jumping to a point on initial click
	bool firstClick = true;

	//size of window
	int width;
	int height;

	//speed and sensitivity of camera
	float speed = 0.1f;
	float sensitivity = 100.0f;

	//constructor to set initial values
	Camera(int width, int height, glm::vec3 position);

	//informs vertex shader of camera matrix updates
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	//exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	//input handler for fps controller
	void Inputs(GLFWwindow* window);
};
#endif