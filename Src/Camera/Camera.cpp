#include "Camera.h"


glm::mat4 camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void camera::process_key_board(camera_data_define::camera_movement direction, float delta_time)
{
	float velocity = movement_speed * delta_time;
	if (direction == camera_data_define::camera_movement::FORWARD)
		position += front * velocity;
	if (direction == camera_data_define::camera_movement::BACKWARD)
		position -= front * velocity;
	if (direction == camera_data_define::camera_movement::LEFT)
		position -= right * velocity;
	if (direction == camera_data_define::camera_movement::RIGHT)
		position += right * velocity;
}

void camera::process_mouse_movement(float x_offset, float y_offset, GLboolean constrain_pitch)
{
	x_offset *= mouse_sensitivity;
	y_offset *= mouse_sensitivity;

	yaw += x_offset;
	pitch += y_offset;

	if (constrain_pitch)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	update_camera_vectors();
}

void camera::process_mouse_scroll(float y_offset)
{
	zoom -= (float)y_offset;
	if (zoom < camera_data_define::ZOOMMIN)
		zoom = camera_data_define::ZOOMMIN;
	if (zoom > camera_data_define::ZOOMMAX)
		zoom = camera_data_define::ZOOMMAX;
}

void camera::update_camera_vectors()
{
	glm::vec3 temp_front;
	temp_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	temp_front.y = sin(glm::radians(pitch));
	temp_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(temp_front);
	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));

}

camera::camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	:front(glm::vec3(0.0f, 0.0f, -1.0f)),
	movement_speed(camera_data_define::SPEED),
	mouse_sensitivity(camera_data_define::SENSITIVITY),
	zoom(camera_data_define::ZOOM)
{
	this->position = position;
	this->world_up = up;
	this->yaw = yaw;
	this->pitch = pitch;
	update_camera_vectors();
}
