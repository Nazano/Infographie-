#ifndef  CAMERA_INC
#define  CAMERA_INC

//OpenGL Libraries
#include <GL/glew.h>
#include <GL/gl.h>

//GML libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(GLint);
	~Camera();
	void move(float);
	GLuint getMatrixID() { return MatrixID; }
	glm::mat4 getViewMat() { return view; }

private:
	GLuint MatrixID;
	int programId;
	glm::mat4 MVP, view, projection, model;
};



#endif