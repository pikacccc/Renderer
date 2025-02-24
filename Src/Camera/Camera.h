#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "CameraDataDefine.h"

class camera
{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 world_up;

	float yaw;
	float pitch;
	float movement_speed;
	float mouse_sensitivity;
	float zoom;

	camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = camera_data_define::YAW, float pitch = camera_data_define::PITCH);
	
	glm::mat4 get_view_matrix();
	
	void process_key_board(camera_data_define::camera_movement direction, float delta_time);

	void process_mouse_movement(float x_offset, float y_offset, GLboolean constrain_pitch = true);

	void process_mouse_scroll(float y_offset);

private:
	void update_camera_vectors();
};
