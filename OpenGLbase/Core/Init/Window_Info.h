#pragma once
#include <string>

namespace Core
{
	struct Window_Info
	{
		std::string name;
		int width, height;
		int position_x, position_y;
		bool is_reshapable;

		Window_Info()
		{
			name = "OpenGL tutorial";
			width = 800; height = 600;
			position_x = 300;
			position_y = 300;
			is_reshapable = true;
		}

		Window_Info(std::string name,
			int start_position_x, int start_position_y,
			int width, int height,
			bool is_reshapable)
		{

			this->name = name;
			this->position_x = start_position_x;
			this->position_y = start_position_y;

			this->width = width;
			this->height = height;
			this->is_reshapable = is_reshapable;
		}

		//copy constructor
		Window_Info(const Window_Info& windowInfo)
		{
			name = windowInfo.name;
			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;

			width = windowInfo.width;
			height = windowInfo.height;
			is_reshapable = windowInfo.is_reshapable;
		}

		void operator=(const Window_Info& windowInfo)
		{

			name = windowInfo.name;

			position_x = windowInfo.position_x;
			position_y = windowInfo.position_y;

			width = windowInfo.width;
			height = windowInfo.height;
			is_reshapable = windowInfo.is_reshapable;
		}
	};
}
