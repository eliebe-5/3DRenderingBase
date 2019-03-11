#pragma once
#include "GL\glew.h"
#include <fstream>
#include <iostream>
#include <string>

namespace Rendering
{
	class Texture_Loader
	{
	public:
		Texture_Loader();
		~Texture_Loader();

		static unsigned int load_texture(const std::string&, unsigned int, unsigned int);
	private:
		static void load_image_file(const std::string&, unsigned int, unsigned int, unsigned char*&);
	};
}