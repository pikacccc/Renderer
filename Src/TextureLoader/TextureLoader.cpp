#include "TextureLoader.h"

unsigned int texture_loader::load_texture_2d(const std::string& source_path, int& width, int& height, int& nr_channels)
{
	unsigned int texture2d;

	glGenBuffers(1, &texture2d);
	glBindTexture(GL_TEXTURE_2D, texture2d);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(source_path.c_str(), &width, &height, &nr_channels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 0;
	}
	stbi_image_free(data);
	return texture2d;
}
