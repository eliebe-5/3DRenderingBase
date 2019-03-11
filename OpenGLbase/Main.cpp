#include "Core\Init\Init_GLUT.h";
#include "Managers\Scene_Manager.h"
#include "Rendering\Texture\Texture_Loader.h"

int main(int argc, char **argv)
{
	Core::Window_Info window(std::string("OpenGL Window"),
		400, 200,//position
		800, 600, //size
		true);//reshape

	Core::Context_Info context(4, 5, true);
	Core::Framebuffer_Info framebuffer_info(true, true, true, true);
	Core::Init::Init_GLUT::init(window, context, framebuffer_info);

	Core::I_Listener* scene = new Managers::Scene_Manager();
	((Managers::Scene_Manager*)scene)->shader_manager = new Managers::Shader_Manager();
	((Managers::Scene_Manager*)scene)->shader_manager->create_program("colorShader",
		"Shaders\\vs.glsl",  //Vertex Shader
		"Shaders\\fs.glsl"); //Fragment Shader
	((Managers::Scene_Manager*)scene)->models_manager = new Managers::Models_Manager();

	Models::Cube* cube = new Models::Cube();
	cube->set_program(Managers::Shader_Manager::get_shader("colorShader"));
	cube->create(0, 0, 0, 2);
	
	Models::Cube* cube1 = new Models::Cube();
	cube1->set_program(Managers::Shader_Manager::get_shader("colorShader"));
	cube1->create(0, 48, 0, 100);
	
	unsigned int texture = Texture_Loader::load_texture("Textures\\Crate.bmp", 256, 256);
	cube->set_texture("Create", texture);
	cube1->set_texture("Create", texture);
	
	((Managers::Scene_Manager*)scene)->models_manager->set_model("cube", cube);
	((Managers::Scene_Manager*)scene)->models_manager->set_model("cube1", cube1);
	
	Core::Init::Init_GLUT::set_listener(scene);
	Core::Init::Init_GLUT::run();

	delete scene;
	return 0;
}