#include "Triangle.h"
using namespace Rendering;
using namespace Models;

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<Vertex_Format> vertices;
	vertices.push_back(Vertex_Format(glm::vec3(0.25, -0.25, 0.0),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(glm::vec3(-0.25, -0.25, 0.0),
		glm::vec2(0, 1)));
	vertices.push_back(Vertex_Format(glm::vec3(0.25, 0.25, 0.0),
		glm::vec2(0, 0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_Format) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_Format),
		(void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_Format),
		(void*)(offsetof(Vertex_Format, Vertex_Format::uv)));
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Triangle::update()
{
}

void Triangle::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}