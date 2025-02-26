#pragma once

#include <string>
#include <vector>

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glm/glm.hpp"
#include "../../Include/stb_image/stb_image.h"

namespace model_loader {
	using namespace std;
	unsigned int texture_from_file(const char* path, const std::string& directory, bool gamma = false);

	class model
	{
	public:
		std::vector<texture> textures_loaded;
		std::vector<mesh> meshes;
		std::string directory;
		bool gamma_correction;

		model(const std::string& path, bool gamma = false);

		void draw(shader& shader);
	private:
		void load_model(const std::string& path);
		void process_node(aiNode* node, const aiScene* scene);
		mesh process_mesh(aiMesh* mesh, const aiScene* scene);
		std::vector<texture> load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name);
	};
}