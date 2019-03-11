#include "Model.h"
using namespace Rendering;
using namespace Models;

Model::Model() {}

Model::~Model()
{
	destroy();
}

void Model::draw()
{
	//this will be again overridden
}

void Model::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	//this will be again overridden
}

void Model::update()
{
	//this will be again overridden
}

void Model::set_program(GLuint program)
{
	this->program = program;
}

void Model::rotate(glm::vec3& rot)
{

}

GLuint Model::get_vao() const
{
	return vao;
}

const std::vector<GLuint>& Model::get_vbos() const
{
	return vbos;
}

const GLuint Model::get_texture(std::string textureName) const
{
	return textures.at(textureName);
}

void Model::use_texture(const std::string& texture)
{
	texture_in_use = texture.c_str();
}

void Model::set_texture(std::string textureName, GLuint texture)
{
	if (texture == 0) return;
	textures[textureName] = texture;
	texture_in_use = textureName.c_str();
}

void Model::destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}