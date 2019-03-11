#include "Cube.h"
using namespace Rendering;
using namespace Models;

#define PI 3.14159265

Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::create(float x, float y, float z, float side)
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float halfside = side / 2;

	std::vector<Vertex_Format> vertices;
	std::vector<unsigned int>  indices = 
	  { 0,  1,  2,  0,  2,  3,   //front
		4,  5,  6,  4,  6,  7,   //right
		8,  9,  10, 8,  10, 11 ,  //back
		12, 13, 14, 12, 14, 15,  //left
		16, 17, 18, 16, 18, 19,  //upper
		20, 21, 22, 20, 22, 23 }; //bottom
	
	auto c = glm::vec3(x, y, z);

								  //front
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, halfside),
		glm::vec2(0, 1)));

	//right
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, -halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, -halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, halfside),
		glm::vec2(0, 1)));

	//back
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, -halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, -halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, -halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, -halfside),
		glm::vec2(0, 1)));

	//left
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, -halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, -halfside),
		glm::vec2(0, 1)));

	//upper
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, halfside, -halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, halfside, -halfside),
		glm::vec2(0, 1)));

	////bottom
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, -halfside),
		glm::vec2(0, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, -halfside),
		glm::vec2(1, 0)));
	vertices.push_back(Vertex_Format(c + glm::vec3(halfside, -halfside, halfside),
		glm::vec2(1, 1)));
	vertices.push_back(Vertex_Format(c + glm::vec3(-halfside, -halfside, halfside),
		glm::vec2(0, 1)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(Vertex_Format),
		&vertices[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(unsigned int),
		&indices[0],
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_Format), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex_Format),
		(void*)(offsetof(Vertex_Format, Vertex_Format::uv)));
	glBindVertexArray(0);

	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);

	rotation_speed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);

}

void Cube::update()
{
}

void Cube::rotate(glm::vec3& rotation)
{
	this->rotation = rotation + this->rotation;
}

void Cube::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->get_texture(texture_in_use));
	unsigned int textureLocation = glGetUniformLocation(program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(program, "rotation"),
		rotation.x, rotation.y, rotation.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"),
		1, false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"),
		1, false, &projection_matrix[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}