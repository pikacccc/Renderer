#pragma once
#include "TextureLoader.h"

class texture2d
{
public:
	unsigned int id;
	int width; 
	int height;
	int nr_channels;

	texture2d(const std::string& source_path);
	~texture2d();

	void use();
};
