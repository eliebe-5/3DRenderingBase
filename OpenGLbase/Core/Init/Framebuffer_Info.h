#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"

namespace Core {
	struct Framebuffer_Info {

		unsigned int flags;
		bool msaa;

		Framebuffer_Info()
		{
			flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			msaa = false;
		}

		Framebuffer_Info(bool color, bool depth, bool stencil, bool msaa)
		{
			flags = GLUT_DOUBLE;
			if (color)
				flags |= GLUT_RGBA | GLUT_ALPHA;
			if (depth)
				flags |= GLUT_DEPTH;
			if (stencil)
				flags |= GLUT_STENCIL;
			if (msaa)
				flags |= GLUT_MULTISAMPLE;
			this->msaa = msaa;
		}
	};
}