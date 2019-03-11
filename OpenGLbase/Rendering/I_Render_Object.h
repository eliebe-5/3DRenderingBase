#pragma once
#include <vector>
#include <iostream>
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "Vertex_Format.h"

namespace Rendering
{
	class I_Render_Object
	{
	public:
		virtual ~I_Render_Object() = 0;

		virtual void draw() = 0;
		virtual void draw(	const glm::mat4& projection_matrix,
							const glm::mat4& view_matrix) = 0;
		virtual void update() = 0;
		virtual void set_program(GLuint) = 0;
		virtual void destroy() = 0;

		virtual GLuint get_vao() const = 0;
		virtual const std::vector<GLuint>& get_vbos() const = 0;

		virtual void set_texture(std::string, GLuint) = 0;
		virtual const GLuint get_texture(std::string) const = 0;

		virtual void rotate(glm::vec3&) = 0;
	};
	
	inline I_Render_Object::~I_Render_Object()
	{
	}
}
