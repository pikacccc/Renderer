#include "ShanderCompiler.h"

static unsigned int shader_compiler::compile_shader(unsigned int shader_type, std::string& source)
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

unsigned int shader_compiler::create_shader(std::string& vs_source_code, std::string& fs_source_code)
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

unsigned int shader_compiler::create_shader(std::string& vs_path, std::string& fs_path)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vs_path);
		fShaderFile.open(fs_path);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = std::move(vShaderStream.str());
		fragmentCode = std::move(fShaderStream.str());
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
		return 0;
	}

	unsigned int program = glCreateProgram();
	unsigned int vs = shader_compiler::compile_shader(GL_VERTEX_SHADER, vertexCode);
	unsigned int fs = shader_compiler::compile_shader(GL_FRAGMENT_SHADER, fragmentCode);

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
