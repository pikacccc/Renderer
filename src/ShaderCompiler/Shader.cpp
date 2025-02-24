#include "Shader.h"

shader::shader(const std::string& vertexPath, const std::string& fragmentPath)
{
	id = shader_compiler::create_shader_by_path(vertexPath, fragmentPath);
}

shader::~shader()
{
	glDeleteProgram(id);
}

void shader::use()
{
	glUseProgram(id);
}

void shader::set_bool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void shader::set_int(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void shader::set_float(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void shader::set_vec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void shader::set_vec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void shader::set_mat2(const std::string& name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void shader::set_mat3(const std::string& name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void shader::set_mat4(const std::string& name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
