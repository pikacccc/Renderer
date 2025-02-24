#include "Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	id = shader_compiler::create_shader_by_path(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use() {
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}
