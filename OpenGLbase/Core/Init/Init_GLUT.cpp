#include "Init_GLUT.h"

using namespace Core::Init;

Core::I_Listener* Init_GLUT::listener = NULL;
Core::Window_Info Init_GLUT::window_information;

void Init_GLUT::init(const Core::Window_Info& window_info, const Core::Context_Info& context_info, const Core::Framebuffer_Info& framebuffer_info)
{
	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { (char*)"fake", NULL };
	glutInit(&fakeargc, fakeargv);

	window_information = window_info;

	if (context_info.core)
	{
		glutInitContextVersion(context_info.major_version, context_info.minor_version);
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebuffer_info.flags);
	glutInitWindowPosition(window_info.position_x, window_info.position_y);
	glutInitWindowSize(window_info.width, window_info.height);

	glutCreateWindow(window_info.name.c_str());

	std::cout << "GLUT: initialized" << std::endl;
	glEnable(GL_DEBUG_OUTPUT);
	//these callbacks are used for rendering
	glutIdleFunc(idle_callback);
	glutCloseFunc(close_callback);
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(keyboard_callback);
	glutKeyboardUpFunc(key_up_callback);
	glutMouseFunc(mouse_callback);
	glutMotionFunc(mouse_active_move_callback);
	glutPassiveMotionFunc(mouse_passive_move_callback);

	//init GLEW, this can be called in main.cpp
	Init::Init_GLEW::init();

	glDebugMessageCallback((GLDEBUGPROC)Debug_Output::my_callback, NULL);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
		GL_DONT_CARE, 0, NULL, GL_TRUE);

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	print_openGL_info(window_info, context_info);

}

//starts the rendering Loop
void Init_GLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idle_callback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::display_callback()
{
	if (listener) {
		listener->notify_begin_frame();
		listener->notify_display_frame();

		glutSwapBuffers();
		
		listener->notify_end_frame();
	}
}

void Init_GLUT::reshape_callback(int width, int height)
{
	if (window_information.is_reshapable == true)
	{
		if (listener)
		{
			listener->notify_reshape(width, height, window_information.width, window_information.height);
		}
		window_information.width = width;
		window_information.height = height;
	}
}

void Init_GLUT::close_callback()
{
	close();
}

void Init_GLUT::keyboard_callback(unsigned char key, int x, int y)
{
	listener->keyboard_callback(key, x, y);
}

void Init_GLUT::key_up_callback(unsigned char key, int x, int y)
{
	listener->key_up_callback(key, x, y);
}

void Init_GLUT::mouse_callback(int button, int state, int x, int y)
{
	listener->mouse_callback(button, state, x, y);
}

void Init_GLUT::mouse_active_move_callback(int x, int y)
{
	listener->mouse_active_move_callback(x, y);
}

void Init_GLUT::mouse_passive_move_callback(int x, int y)
{
	listener->mouse_passive_move_callback(x, y);
}

void Init_GLUT::enter_fullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exit_fullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::print_openGL_info(const Core::Window_Info& windowInfo, const Core::Context_Info& contextInfo) 
{

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************************************" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}

void Init_GLUT::set_listener(Core::I_Listener*& iListener)
{
	listener = iListener;
}