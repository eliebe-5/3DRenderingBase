#include "Quad.h"
using namespace Rendering;
using namespace Models;

Quad::Quad()
{}

Quad::~Quad()
{}

void Quad::create()
{
	GLuint vao;
	GLuint vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<Vertex_Format> vertices;
	vertices.push_back(Vertex_Format(glm::vec3(-0.25, 0.5, 0.0),//pos
		glm::vec2(1, 0)));   //color
	vertices.push_back(Vertex_Format(glm::vec3(-0.25, 0.75, 0.0),//pos
		glm::vec2(0, 0)));   //color
	vertices.push_back(Vertex_Format(glm::vec3(0.25, 0.5, 0.0),  //pos
		glm::vec2(0, 1)));   //color
	vertices.push_back(Vertex_Format(glm::vec3(0.25, 0.75, 0.0),//pos
		glm::vec2(0, 0)));   //color
								   
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);            
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_Format) * 4, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex_Format), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex_Format),
		(void*)(offsetof(Vertex_Format, Vertex_Format::uv)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

}

void Quad::update()
{
	//nothing here for the moment
}

void Quad::draw()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}