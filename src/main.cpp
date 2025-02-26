#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "ShaderCompiler/Shader.h"
#include "TextureLoader/Texture2d.h"
#include "glm/glm.hpp"
#include "Camera/Camera.h"
#include "Util/Util.h"
#include "Model/Model.h"

//callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
camera m_camera{ glm::vec3(0.0f,0.0f,3.0f) };
float last_x = SCR_WIDTH / 2.0f;
float last_y = SCR_HEIGHT / 2.0f;
bool first_mouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
	GLFWwindow* window;

	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "hello world", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);

	shader shader("Shader/shader-1.vs", "Shader/shader-1.fs");

	model_loader::model backpack("resource/object/cyborg/cyborg.obj");

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(m_camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = m_camera.get_view_matrix();

		shader.set_mat4("projection", projection);
		shader.set_mat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		shader.set_mat4("model", model);
		backpack.draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera.process_key_board(camera_data_define::camera_movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera.process_key_board(camera_data_define::camera_movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera.process_key_board(camera_data_define::camera_movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera.process_key_board(camera_data_define::camera_movement::RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double x_pos_in, double y_pos_in)
{
	float x_pos = static_cast<float>(x_pos_in);
	float y_pos = static_cast<float>(y_pos_in);

	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	float x_offset = x_pos - last_x;
	float y_offset = last_y - y_pos;

	last_x = x_pos;
	last_y = y_pos;

	m_camera.process_mouse_movement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	m_camera.process_mouse_scroll(static_cast<float>(y_offset));
}