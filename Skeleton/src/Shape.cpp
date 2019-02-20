#include "Shape.h"

Shape::Shape(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs) {

	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
}

Shape::Shape() {
	
}

Shape::~Shape() {
	glDeleteBuffers(1, &vBuffer);
	glDeleteTextures(1, &texture);
}

void Shape::init(const int programId) {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vBuffer);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3) + uvs.size() * sizeof(glm::vec2), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), uvs.size() * sizeof(glm::vec2), &uvs[0]);
	

	GLuint vertIndice = glGetAttribLocation(programId, "vPosition");
	glVertexAttribPointer(vertIndice, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)0);
	glEnableVertexAttribArray(vertIndice);
	
	GLuint uvIndice = glGetAttribLocation(programId, "texCoord");
	glVertexAttribPointer(uvIndice, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (const GLvoid*)(vertices.size() * sizeof(glm::vec3)));
	glEnableVertexAttribArray(uvIndice);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertIndice);
	glDisableVertexAttribArray(uvIndice);
}

void Shape::load_texture(const char* tex_path, const int programID) {

	int width, height;
	auto img = SOIL_load_image(tex_path, &width, &height, 0, SOIL_LOAD_RGBA);
	if (img == NULL)
		ERROR("Cannot load texture: %s", tex_path);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (!texture)
		ERROR("glGenTextures error %d", texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(img);
}

void Shape::show() {

	if (texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size()+uvs.size());
}