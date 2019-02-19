#ifndef SHAPE_INC
#define SHAPE_INC

//GML libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

//OpenGL Libraries
#include <GL/glew.h>
#include <GL/gl.h>

#include "Geometry.h"
#include "logger.h"
#include <SOIL2/SOIL2.h>

#include <vector>


class Shape
{
public:
	Shape(std::vector<glm::vec3>, std::vector<glm::vec3>, std::vector<glm::vec2>);
	~Shape();
	Shape();
	Shape(const Shape& rhs) { vertices = rhs.vertices; normals = rhs.normals; uvs = rhs.uvs; }
	void init();
	void load_texture(const char*, const int);
	void show(int);
	

	std::vector<glm::vec3> getVertcies() { return vertices; }
	std::vector<glm::vec3> getNormals() { return normals; }
	std::vector<glm::vec2> getUvs() { return uvs; }

private:
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	GLuint vBuffer, uvBuffer, texture, textureID;

};


#endif // !SHAPE_INC
