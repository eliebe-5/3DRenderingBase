#pragma once
#include "Model.h"

namespace Rendering
{
	namespace Models
	{
		class Triangle : public Model
		{
		public:
			Triangle();
			~Triangle();

			void create();
			virtual void update() override final;
			virtual void draw() override final;
		};
	}
}