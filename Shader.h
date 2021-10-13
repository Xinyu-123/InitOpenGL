#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"
class Shader
{
public:
	// Constructors / Destructors
	Shader();
	virtual ~Shader();

	// Accessors
	GLuint GetProgramID() {
		return m_programID;
	}
	GLuint GetAttrVertices() {
		return m_attrVertices;
	}
	GLuint GetAttrColors() { return m_attrColors;  }

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	GLuint GetAttrWVP() { return m_attrWVP; }
private:
	// Methods
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	// Members
	GLuint m_programID;
	GLuint m_attrVertices;
	GLuint m_attrWVP;
	GLuint m_attrColors;
	GLint m_result = GL_FALSE;
	int m_infoLength;
};

#endif