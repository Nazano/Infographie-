#include "Cube.h"

Cube::Cube() : Geometry()
{
    m_vertices = (float*)malloc(sizeof(float)*3*36);
    m_normals  = (float*)malloc(sizeof(float)*3*36);
    m_uvs      = (float*)malloc(sizeof(float)*2*36);

    float vertices[3*36] = {
                            //Front
                            -0.5, -0.5, -0.5,
                             0.5, -0.5, -0.5,
                             0.5,  0.5, -0.5,
                            -0.5, -0.5, -0.5,
                             0.5,  0.5, -0.5,
                            -0.5,  0.5, -0.5,

                            //Back
                            -0.5, -0.5,  0.5,
                             0.5,  0.5,  0.5,
                             0.5, -0.5,  0.5,
                            -0.5, -0.5,  0.5,
                            -0.5,  0.5,  0.5,
                             0.5,  0.5,  0.5,

                            //Left
                            -0.5, -0.5,  0.5,
                            -0.5, -0.5, -0.5,
                            -0.5,  0.5, -0.5,
                            -0.5, -0.5,  0.5,
                            -0.5,  0.5, -0.5,
                            -0.5,  0.5,  0.5,

                            //Right
                             0.5, -0.5,  0.5,
                             0.5,  0.5, -0.5,
                             0.5, -0.5, -0.5,
                             0.5, -0.5,  0.5,
                             0.5,  0.5,  0.5,
                             0.5,  0.5, -0.5,

                            //Top
                             0.5,  0.5, -0.5,
                            -0.5,  0.5, -0.5,
                            -0.5,  0.5,  0.5,
                             0.5,  0.5, -0.5,
                            -0.5,  0.5,  0.5,
                             0.5,  0.5,  0.5,

                            //Bottom
                             0.5, -0.5, -0.5,
                            -0.5, -0.5,  0.5,
                            -0.5, -0.5, -0.5,
                             0.5, -0.5, -0.5,
                             0.5, -0.5,  0.5,
                            -0.5, -0.5,  0.5};

    float uvs[2*36] = {
                            //Front
                            0.0, 0.0,
                             1.0, 0.0,
                             1.0,  1.0,
                            0.0, 0.0,
                             1.0,  1.0,
                            0.0,  1.0,

                            //Back
                            0.0, 0.0,
                             1.0,  1.0,
                             1.0, 0.0,
                            0.0, 0.0,
                            0.0,  1.0,
                             1.0,  1.0,

                            //Left
                            0.0,  1.0,
                            0.0, 0.0,
                             1.0, 0.0,
                            0.0,  1.0,
                             1.0, 0.0,
                             1.0,  1.0,

                            //Right
                            0.0,  1.0,
                             1.0, 0.0,
                            0.0, 0.0,
                            0.0,  1.0,
                             1.0,  1.0,
                             1.0, 0.0,

                            //Top
                             1.0, 0.0,
                            0.0, 0.0,
                            0.0,  1.0,
                             1.0, 0.0,
                            0.0,  1.0,
                             1.0,  1.0,

                            //Bottom
                             1.0, 0.0,
                            0.0,  1.0,
                            0.0, 0.0,
                             1.0, 0.0,
                             1.0,  1.0,
                            0.0,  1.0};

    float normals[3*36] = {//Front
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0,
                           0.0, 0.0, -1.0,

                           //Back
                           0.0, 0.0, 1.0,
                           0.0, 0.0, 1.0,
                           0.0, 0.0, 1.0,
                           0.0, 0.0, 1.0,
                           0.0, 0.0, 1.0,
                           0.0, 0.0, 1.0,

                           //Left
                           -1.0, 0.0, 0.0,
                           -1.0, 0.0, 0.0,
                           -1.0, 0.0, 0.0,
                           -1.0, 0.0, 0.0,
                           -1.0, 0.0, 0.0,
                           -1.0, 0.0, 0.0,

                           //Right
                            1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,
                            1.0, 0.0, 0.0,

                           //Top
                            0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 1.0, 0.0,

                           //Bottom
                            0.0, -1.0, 0.0,
                            0.0, -1.0, 0.0,
                            0.0, -1.0, 0.0,
                            0.0, -1.0, 0.0,
                            0.0, -1.0, 0.0,
                            0.0, -1.0, 0.0};

    for(uint32_t i = 0; i < 3*36; i++)
    {
        m_vertices[i] = vertices[i];
        m_normals[i] = normals[i];
    }
    for(uint32_t i = 0; i < 2*36; i++)
        m_uvs[i] = uvs[i];
    m_nbVertices = 36;
}

Cube::~Cube() {
	glUseProgram(0);
	glDeleteBuffers(1, &buffer);
	delete shader;
}

void Cube::init() {

	//Affectation du VBO

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * this->getNbVertices(), this->getVertices(), GL_DYNAMIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Chargement du shader

	FILE* vertFile = fopen("bin\\Shaders\\color.vert", "r");
	FILE* fragFile = fopen("bin\\Shaders\\color.frag", "r");

	if (vertFile == NULL) { ERROR("Erreur vertex file"); }
	if (fragFile == NULL) { ERROR("Erreur fragment file"); }

	shader = Shader::loadFromFiles(vertFile, fragFile);

	fclose(vertFile);
	fclose(fragFile);
}

void Cube::show() {
	glUseProgram(shader->getProgramID());
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	GLint v = glGetAttribLocation(shader->getProgramID(), "vPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(v);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}