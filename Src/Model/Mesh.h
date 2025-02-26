#pragma once

#include "glm/glm.hpp"
#include <string>
#include <vector>
#include "glad/glad.h"
#include "../ShaderCompiler/Shader.h"

#define MAX_BONE_INFLUENCE 4

namespace model_loader {
	struct vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texture_coords;
		glm::vec3 tangent;
		glm::vec3 bitangent;

		int bone_ids[MAX_BONE_INFLUENCE];
		float weights[MAX_BONE_INFLUENCE];
	};

	struct texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class mesh
	{
	public:
		unsigned int VAO;

		std::vector<vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<texture> textures;


		mesh(std::vector<vertex> vertices,std::vector<unsigned int> indices,std::vector<texture> textures);

		void draw(shader& shader);
	private:
		unsigned int VBO, EBO;

		void setup_mesh();
	};
}