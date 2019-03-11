#pragma once
#include "Model.h"

namespace Rendering
{
	namespace Models
	{
		class Quad: public Model
		{
		public:
			Quad();
			~Quad();

			void create();
			virtual void update() override final;
			virtual void draw() override final;
		};
	}
}
