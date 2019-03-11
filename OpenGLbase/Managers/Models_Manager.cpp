#include "Models_Manager.h"

using namespace Managers;
using namespace Rendering;

Models_Manager::Models_Manager()
{
}

Models_Manager::~Models_Manager()
{
	//auto -it's a map iterator
	for (auto model : render_model_list)
	{
		delete model.second;
	}
	render_model_list.clear();
}

void Models_Manager::delete_model(const std::string& render_model_name)
{
	I_Render_Object* model = render_model_list[render_model_name];
	model->destroy();
	render_model_list.erase(render_model_name);
}

I_Render_Object& Models_Manager::get_model(const std::string& render_model_name) const
{
	return (*render_model_list.at(render_model_name));
}

void Models_Manager::update()
{
	//auto -it's a map iterator
	for (auto model : render_model_list)
	{
		model.second->update();
	}
}

void Models_Manager::set_model(const std::string& name, I_Render_Object* model)
{
	render_model_list[name.c_str()] = model;
}

void Models_Manager::draw()
{
	//auto -it's a map iterator
	for (auto model : render_model_list)
	{
		model.second->draw();
	}
}

void Models_Manager::draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	//auto -it's a map iterator
	for (auto model : render_model_list)
	{
		model.second->draw(projection_matrix, view_matrix);
	}
}