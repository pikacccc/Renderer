#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	ID = shader_compiler::create_shader_by_path(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
