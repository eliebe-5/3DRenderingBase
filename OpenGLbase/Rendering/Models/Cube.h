#pragma once
#include "Model.h"
#include<time.h>
#include<stdarg.h>
namespace Rendering
{
	namespace Models
	{
		class Cube : public Model
		{
		public:
			Cube();
			~Cube();

			void create(float, float, float, float);
			virtual void draw(	const glm::mat4& projection_matrix,
								const glm::mat4& view_matrix)
								override final;
			virtual void update() override final;
			void rotate(glm::vec3&);

		private:
			glm::vec3 rotation, rotation_sin, rotation_speed;
			time_t timer;
		};
	}
}
