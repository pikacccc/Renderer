#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "glad/glad.h"

namespace shader_compiler {
	static unsigned int compile_shader(unsigned int shader_type,std::string& source);
	unsigned int create_shader(std::string& vs_source_code, std::string& fs_source_code);
	unsigned int create_shader(std::string& vs_path, std::string& fs_path);
}