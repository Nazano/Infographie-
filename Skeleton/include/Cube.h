#ifndef  CUBE_INC
#define  CUBE_INC

//OpenGL Libraries
#include <GL/glew.h>
#include <GL/gl.h>

//GML libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Geometry.h"
#include "Shader.h"

class Cube : public Geometry
{
	public:
		Cube();
		~Cube();
		void init();
		void show();
		Shader* getShader() { return shader; }

	private:
		Shader* shader;
		GLuint buffer;
};

#endif
