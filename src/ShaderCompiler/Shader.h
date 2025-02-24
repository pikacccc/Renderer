#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderCompiler.h"
#include "glm/glm.hpp"

class shader
{
public:
	unsigned int id;

	shader(const std::string& vertex_path, const std::string& fragment_path);
	~shader();

	void use();

	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	void set_vec2(const std::string& name, const glm::vec2& value) const;
	void set_vec3(const std::string& name, const glm::vec3& value) const;
	void set_vec4(const std::string& name, const glm::vec4& value) const;
};
#endif