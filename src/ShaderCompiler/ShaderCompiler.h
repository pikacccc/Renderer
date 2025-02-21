#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "glad/glad.h"

namespace shader_compiler {
	static unsigned int compile_shader(unsigned int shader_type, const std::string& source);
	unsigned int create_shader(const std::string& vs_source_code, const std::string& fs_source_code);
	unsigned int create_shader_by_path(const std::string& vs_path, const std::string& fs_path);
}