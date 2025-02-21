#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderCompiler.h"
#include "../Math/Vector.h"

class Shader
{
public:
	unsigned int id;

	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const vector::vec2& value) const;
	void setVec3(const std::string& name, const vector::vec3& value) const;
	void setVec4(const std::string& name, const vector::vec4& value) const;
};
#endif