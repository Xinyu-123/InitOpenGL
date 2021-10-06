#include "Shader.h"

Shader::Shader()
{
	m_programID = 0;
	m_attrVertices = 0;
	m_attrWVP = {};
	m_result = GL_FALSE;
	m_infoLength = 0;
}

Shader::~Shader()
{
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}

void Shader::Cleanup()
{
	glDeleteProgram(m_programID);
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	m_programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &m_result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &m_infoLength);
	EvaluateShader(m_infoLength, m_programID);

	glDetachShader(m_programID, vertexShaderID);
	glDetachShader(m_programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type)
{
	GLuint shaderID = glCreateShader(_type);

	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), ("Impossible to open %s. Are you in the right directory? \n", _filePath));
	std::string Line = "";
	while (getline(shaderStream, Line))
		shaderCode += "\n" + Line;
	shaderStream.close();

	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, nullptr);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_infoLength);
	EvaluateShader(m_infoLength, shaderID);

	glAttachShader(m_programID, shaderID);

	return shaderID;
}

void Shader::LoadAttributes()
{
	m_attrVertices = glGetAttribLocation(m_programID, "vertices");
	m_attrWVP = glGetUniformLocation(m_programID, "WVP");
}

void Shader::EvaluateShader(int _infoLength, GLuint _id)
{
	if (_infoLength > 0) {
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, nullptr, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}
