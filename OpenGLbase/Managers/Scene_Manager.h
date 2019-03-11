#pragma once

#include "Shader_Manager.h"
#include "..\Core\Init\I_Listener.h"
#include "Models_Manager.h"

namespace Managers
{
	class Scene_Manager : public Core::I_Listener
	{
	public:
		Scene_Manager();
		~Scene_Manager();

		virtual void notify_begin_frame();
		virtual void notify_display_frame();
		virtual void notify_end_frame();
		virtual void notify_reshape(int width,
			int height,
			int previous_width,
			int previous_height);
		virtual void keyboard_callback(unsigned char key, int x, int y);
		virtual void key_up_callback(unsigned char key, int x, int y);
		virtual void mouse_callback(int button, int state, int x, int y);		
		virtual void mouse_active_move_callback(int x, int y);
		virtual void mouse_passive_move_callback(int x, int y);
		void update_view();

		Managers::Shader_Manager* shader_manager;
		Managers::Models_Manager* models_manager;
	private:
		glm::mat4 projection_matrix;
		glm::mat4 view_matrix;
		float roll, yaw, pitch, move_speed, x_acc, z_acc, move_multiplier;
		glm::vec3 eye;
		glm::vec2 active_dt, passive_dt, clicked_point, last_point;
	};
}