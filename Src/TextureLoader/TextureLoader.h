#pragma once
#include <string>
#include <iostream>
#include "glad/glad.h"
#include "../../Include/stb_image/stb_image.h"

namespace texture_loader 
{
	unsigned int load_texture_2d(const std::string& source_path, int& width, int& height, int& nr_channels);
}