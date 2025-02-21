#include "Texture2d.h"

Texture2d::Texture2d(const std::string& source_path) : width(0) , height(0), nr_channels(0)
{
	id = texture_loader::load_texture_2d(source_path, width, height, nr_channels);
}

Texture2d::~Texture2d()
{
	glDeleteBuffers(1, &id);
}

void Texture2d::use()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
