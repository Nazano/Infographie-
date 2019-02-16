#include "Camera.h"

Camera::Camera(GLint programId)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	MVP = Projection * View * Model;
	MatrixID = glGetUniformLocation(programId, "MVP");
}

void Camera::move() {
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
}

Camera::~Camera()
{
}