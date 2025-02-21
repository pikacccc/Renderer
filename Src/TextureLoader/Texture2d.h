#pragma once
#include "texture_loader.h"

class Texture2d
{
public:
	unsigned int id;
	int width; 
	int height;
	int nr_channels;

	Texture2d(const std::string& source_path);
	~Texture2d();

	void use();
};
