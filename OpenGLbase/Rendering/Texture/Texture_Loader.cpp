#include "GL\glew.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Texture_Loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Rendering;

Texture_Loader::Texture_Loader()
{

}

Texture_Loader::~Texture_Loader()
{

}

unsigned int Texture_Loader::load_texture(const std::string& filename, unsigned int w, unsigned int h) {

	unsigned char* data;
	load_image_file(filename, w, h, data);

	unsigned int gl_texture_object;
	glGenTextures(1, &gl_texture_object);
	glBindTexture(GL_TEXTURE_2D, gl_texture_object);

	//filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float max_anisotropy;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_anisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);

	//Align pixels
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//Gen texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete data;
	return gl_texture_object;
}

void Texture_Loader::load_image_file(const std::string& filename, unsigned int w, unsigned int h, unsigned char*& data) {
	int x, y, n;
	data = stbi_load(filename.c_str(), &x, &y, &n, 0);
	w = x;
	h = y;
}
	
