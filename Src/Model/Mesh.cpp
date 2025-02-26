#include "Mesh.h"

model_loader::mesh::mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setup_mesh();
}

void model_loader::mesh::draw(shader& shader)
{
	unsigned int diffuse_number = 1;
	unsigned int specular_number = 1;
	unsigned int normal_number = 1;
	unsigned int height_number = 1;

	for (unsigned int i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuse_number++);
		else if (name == "texture_specular")
			number = std::to_string(specular_number++);
		else if (name == "texture_normal")
			number = std::to_string(normal_number++);
		else if (name == "texture_height")
			number = std::to_string(height_number++);

		shader.set_int((name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void model_loader::mesh::setup_mesh()
{
	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texture_coords));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tangent));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, bitangent));
	glEnableVertexAttribArray(4);

	glVertexAttribIPointer(5, 4, GL_INT, sizeof(vertex), (void*)offsetof(vertex, bone_ids));
	glEnableVertexAttribArray(5);

	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, weights));
	glEnableVertexAttribArray(6);

	glBindVertexArray(0);
}
