#include "ShaderCompiler.h"

static unsigned int shader_compiler::compile_shader(unsigned int shader_type, const std::string& source)
{
	unsigned int id = glCreateShader(shader_type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int res;
	glGetShaderiv(id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE) {
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char* msg = (char*)alloca(len * sizeof(char));
		glGetShaderInfoLog(id, len, &len, msg);
		std::cout << "Failed to compile "
			<< (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader!"
			<< std::endl;
		std::cout << msg << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int shader_compiler::create_shader(const std::string& vs_source_code, const std::string& fs_source_code)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = shader_compiler::compile_shader(GL_VERTEX_SHADER, vs_source_code);
	unsigned int fs = shader_compiler::compile_shader(GL_FRAGMENT_SHADER, fs_source_code);

	if (vs == 0 || fs == 0) {
		std::cout << "Failed to compile shaders!" << std::endl;
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int shader_compiler::create_shader_by_path(const std::string& vs_path, const std::string& fs_path)
{
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;
	// ensure ifstream objects can throw exceptions:
	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		v_shader_file.open(vs_path);
		f_shader_file.open(fs_path);
		std::stringstream v_shader_stream, f_shader_stream;

		v_shader_stream << v_shader_file.rdbuf();
		f_shader_stream << f_shader_file.rdbuf();
		// close file handlers
		v_shader_file.close();
		f_shader_file.close();
		// convert stream into string
		vertex_code = std::move(v_shader_stream.str());
		fragment_code = std::move(f_shader_stream.str());
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		return 0;
	}

	return shader_compiler::create_shader(vertex_code, fragment_code);
}
