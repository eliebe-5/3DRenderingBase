#pragma once

#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <map>

namespace Managers
{
	class Shader_Manager
	{
	private:
		std::string read_shader(const std::string&);
		GLuint create_shader(GLenum, const std::string&, const std::string&);

		static std::map<std::string, GLuint> programs;
	public:
		Shader_Manager(void);
		~Shader_Manager(void);
		void create_program(const std::string&, const std::string&, const std::string&);
		static const GLuint get_shader(const std::string&);
	};
}