#include "model.h"

unsigned int model_loader::texture_from_file(const char* path, const std::string& directory, bool gamma)
{
	std::string file_name = std::string(path);
	file_name = directory + '/' + file_name;

	unsigned int texture_id;

	glGenTextures(1, &texture_id);

	int width, height, nr_components;
	unsigned char* data = stbi_load(file_name.c_str(), &width, &height, &nr_components, 0);

	if (data) {
		GLenum format;

		if (nr_components == 1)
			format = GL_RED;
		else if (nr_components == 3)
			format = GL_RGB;
		else if (nr_components == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return texture_id;
}

model_loader::model::model(const std::string& path, bool gamma) :gamma_correction(gamma)
{
	load_model(path);
}

void model_loader::model::draw(shader& shader)
{
	for (unsigned int i = 0; i < meshes.size(); ++i) {
		meshes[i].draw(shader);
	}
}

void model_loader::model::load_model(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	process_node(scene->mRootNode, scene);
}

void model_loader::model::process_node(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(process_mesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i) {
		process_node(node->mChildren[i], scene);
	}
}

model_loader::mesh model_loader::model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		vertex temp_vertex;
		glm::vec3 temp_vector;

		temp_vector.x = mesh->mVertices[i].x;
		temp_vector.y = mesh->mVertices[i].y;
		temp_vector.z = mesh->mVertices[i].z;
		temp_vertex.position = temp_vector;

		if (mesh->HasNormals()) {
			temp_vector.x = mesh->mNormals[i].x;
			temp_vector.y = mesh->mNormals[i].y;
			temp_vector.z = mesh->mNormals[i].z;
			temp_vertex.normal = temp_vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			temp_vertex.texture_coords = vec;

			temp_vector.x = mesh->mTangents[i].x;
			temp_vector.y = mesh->mTangents[i].y;
			temp_vector.z = mesh->mTangents[i].z;
			temp_vertex.tangent = temp_vector;

			temp_vector.x = mesh->mBitangents[i].x;
			temp_vector.y = mesh->mBitangents[i].y;
			temp_vector.z = mesh->mBitangents[i].z;
			temp_vertex.bitangent = temp_vector;
		}
		else
		{
			temp_vertex.texture_coords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(temp_vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<texture> diffuse_maps = load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

	std::vector<texture> specular_maps = load_material_textures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

	std::vector<texture> normal_maps = load_material_textures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

	std::vector<texture> height_maps = load_material_textures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), height_maps.begin(), height_maps.end());

	return model_loader::mesh(vertices, indices, textures);
}

std::vector<model_loader::texture> model_loader::model::load_material_textures(aiMaterial* mat, aiTextureType type, std::string type_name)
{
	std::vector<texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
		aiString str;
		mat->GetTexture(type, i, &str);

		bool loaded = false;
		for (unsigned int j = 0; j < textures_loaded.size(); ++j) {
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0) {
				textures.push_back(textures_loaded[j]);
				loaded = true;
				break;
			}
		}

		if (!loaded) {
			texture temp_texture;

			temp_texture.id = texture_from_file(str.C_Str(), this->directory);
			temp_texture.type = type_name;
			temp_texture.path = str.C_Str();
			textures.push_back(temp_texture);
			textures_loaded.push_back(temp_texture);
		}
	}

	return textures;
}
