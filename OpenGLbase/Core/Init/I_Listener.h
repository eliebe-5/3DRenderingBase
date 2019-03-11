#pragma once

namespace Core {

	class I_Listener
	{
	public:
		virtual ~I_Listener() = 0;

		//drawing functions
		virtual void notify_begin_frame() = 0;
		virtual void notify_display_frame() = 0;
		virtual void notify_end_frame() = 0;
		virtual void notify_reshape(int width, int height, int previous_width, int previous_height) = 0;
		virtual void keyboard_callback(unsigned char key, int x, int y) = 0;
		virtual void key_up_callback(unsigned char key, int x, int y) = 0;
		virtual void mouse_callback(int button, int state, int x, int y) = 0;
		virtual void mouse_active_move_callback(int x, int y) = 0;
		virtual void mouse_passive_move_callback(int x, int y) = 0;
	};

	inline I_Listener::~I_Listener() {
		//implementation of pure virtual destructor
	}
}