#include "Shader_Manager.h" 
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace Managers;

std::map<std::string, GLuint> Shader_Manager::programs;

Shader_Manager::Shader_Manager(void) {}
Shader_Manager::~Shader_Manager(void) {
	std::map<std::string, GLuint>::iterator i;
	for (i = programs.begin(); i != programs.end(); ++i)
	{
		GLuint pr = i->second;
		glDeleteProgram(pr);
	}
	programs.clear();
}

std::string Shader_Manager::read_shader(const std::string& filename) {
	std::string shader_code;
	std::ifstream file(filename, std::ios::in);
	assert(file.good());
	file.seekg(0, std::ios::end);
	shader_code.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shader_code[0], shader_code.size());
	file.close();
	return shader_code;
}

GLuint Shader_Manager::create_shader(GLenum shader_type, const std::string& source, const std::string& shader_name) {
	int compile_result = 0;

	GLuint shader = glCreateShader(shader_type);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shader_name.c_str() << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

void Shader_Manager::create_program(const std::string& shader_name, const std::string& v_shader_filename, const std::string& f_shader_filename) {
	//read the shader files and save the code
	std::string vertex_shader_code = read_shader(v_shader_filename);
	std::string fragment_shader_code = read_shader(f_shader_filename);

	GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;
	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	//check for link errors
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
		return;
	}
	programs.insert(std::pair<std::string, GLuint>(shader_name, program));
}

const GLuint Shader_Manager::get_shader(const std::string& shader_name) {
	return programs.at(shader_name);
}