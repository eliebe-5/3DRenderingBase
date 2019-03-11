#pragma once

#include "Context_Info.h"
#include "Framebuffer_Info.h"
#include "Window_Info.h"
#include <iostream>
#include "Init_GLEW.h"
#include "I_Listener.h"
#include "Debug_Output.h"

namespace Core {
	namespace Init {
		class Init_GLUT {
		public:
			static void init(const Core::Window_Info&, const Core::Context_Info&, const Core::Framebuffer_Info&);
			static void run();//called from outside
			static void close();

			static void set_listener(Core::I_Listener*& iListener);

			void enter_fullscreen();
			void exit_fullscreen();

			//used to print info about GL
			static void print_openGL_info(const Core::Window_Info&, const Core::Context_Info&);
		private:
			static Core::I_Listener* listener;
			static Core::Window_Info window_information;
			static void idle_callback(void);
			static void display_callback(void);
			static void reshape_callback(int, int);
			static void close_callback();
			static void keyboard_callback(unsigned char key, int x, int y);
			static void key_up_callback(unsigned char key, int x, int y);
			static void mouse_callback(int button, int state, int x, int y);
			static void mouse_active_move_callback(int x, int y);
			static void mouse_passive_move_callback(int x, int y);

		};
	}
}