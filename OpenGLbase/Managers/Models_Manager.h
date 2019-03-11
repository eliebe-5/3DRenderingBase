#pragma once
#include <map>
#include "Shader_Manager.h"
#include "..\Rendering\I_Render_Object.h"
#include "..\Rendering\Models\Quad.h"
#include "..\Rendering\Models\Triangle.h"
#include "..\Rendering\Models\Cube.h"

using namespace Rendering;
namespace Managers
{
	class Models_Manager
	{
	public:
		Models_Manager();
		~Models_Manager();

		void draw();
		void draw(	const glm::mat4& projection_matrix,
					const glm::mat4& view_matrix);
		void update();
		void set_model(const std::string&, I_Render_Object*);
		void delete_model(const std::string&);
		I_Render_Object& get_model(const std::string&) const;

	private:
		std::map<std::string, I_Render_Object*> render_model_list;
	};
}