#include "Scene_Manager.h"
#include "../Rendering/Texture/Texture_Loader.h"
#include <random>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm\gtx\transform.hpp"
using namespace Managers;

Scene_Manager::Scene_Manager()
{
	glEnable(GL_DEPTH_TEST);

	eye = glm::vec3(0, 0, -10);

	view_matrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);

	last_point = glm::vec2(0, 0);
	move_speed = 0.005f;
	x_acc = 0.f;
	z_acc = 0.f;
	move_multiplier = 1.f;
}

Scene_Manager::~Scene_Manager()
{
	delete shader_manager;
	delete models_manager;
}

void Scene_Manager::notify_begin_frame()
{
	models_manager->update();
	glm::vec3 rot = glm::vec3((float)active_dt[1] * 0.0001f, (float)active_dt[0] * 0.0001f, 0);
	models_manager->get_model("cube").rotate(rot);
}

void Scene_Manager::notify_display_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	models_manager->draw();
	models_manager->draw(projection_matrix, view_matrix);
}

void Scene_Manager::notify_end_frame()
{
	glm::mat4 mat = view_matrix;

	glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
	glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

	eye += (-z_acc * forward + x_acc * strafe) * move_speed;
	update_view();
}

void Scene_Manager::notify_reshape(int width,
	int height,
	int previous_width,
	int previous_height)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) /
		(float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, near1 = 0.1f, far1 = 2000.0f;

	projection_matrix[0][0] = 1.0f / (ar * tan(angle / 2.0f));
	projection_matrix[1][1] = 1.0f / tan(angle / 2.0f);
	projection_matrix[2][2] = (-near1 - far1) / (near1 - far1);
	projection_matrix[2][3] = 1.0f;
	projection_matrix[3][2] = 2.0f * near1 * far1 / (near1 - far1);
}

void Scene_Manager::update_view()
{
	glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
	glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix
	

	//printf("yaw: %f;\tpitch: %f\n", yaw, pitch);

	matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 rotate = matPitch * matYaw;

	glm::mat4 translate = glm::mat4(1.0f);
	
	translate = glm::translate(translate, -eye);

	view_matrix = rotate * translate;
}

void Scene_Manager::keyboard_callback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case(27):
		glutExit();
		break;
	case('w'):
		z_acc += -1.f * move_multiplier;
		break;
	case('a'):
		x_acc += -1.f * move_multiplier;
		break;
	case('s'):
		z_acc += 1.f * move_multiplier;
		break;
	case('d'):
		x_acc += 1.f * move_multiplier;
		break;
	default:
		printf("KEY_DOWN\n");
		break;
	}

}

void Scene_Manager::key_up_callback(unsigned char key, int x, int y)
{
	int mod = glutGetModifiers();
	switch (key)
	{
	case(27):
		glutExit();
		break;
	case('w'):
		z_acc -= -1.f;
		break;
	case('a'):
		x_acc -= -1.f;
		break;
	case('s'):
		z_acc -= 1.f;
		break;
	case('d'):
		x_acc -= 1.f;
		break;
	default:
		printf("KEY_UP\n");
		break;
	}
}

void Scene_Manager::mouse_callback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		clicked_point = glm::vec2(x, y);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		clicked_point = glm::vec2(0, 0);
		active_dt = glm::vec2(0, 0);
	}
}

void Scene_Manager::mouse_active_move_callback(int x, int y)
{
	active_dt = glm::vec2(x, y) - clicked_point;
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void Scene_Manager::mouse_passive_move_callback(int x, int y)
{
	passive_dt = glm::vec2(x, y) - last_point;

	const float mouseX_Sensitivity = 0.003f;
	const float mouseY_Sensitivity = 0.003f;

	yaw -= mouseX_Sensitivity * passive_dt.x;
	pitch -= mouseY_Sensitivity * passive_dt.y;

	if (yaw > 3.14) yaw = -3.139;
	if (yaw < -3.14) yaw = 3.139;
	if (pitch > 3.14/2) pitch = 3.14/2;
	if (pitch < -3.14/2) pitch = -3.14/2;

	last_point = glm::vec2(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}