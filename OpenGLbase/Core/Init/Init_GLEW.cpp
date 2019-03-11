#include "Init_GLEW.h"
using namespace Core;
using namespace Core::Init;

void Init_GLEW::init() {
	glewExperimental = true;
	if (glewInit() == GLEW_OK)
	{
		std::cout << "GLEW: initialized" << std::endl;
	}
	
}