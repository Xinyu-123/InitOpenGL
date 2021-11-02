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
	GLuint GetProgramID() { return m_programID; }
	GLuint GetAttrVertices() { return m_attrVertices; }
	GLuint GetAttrColors() { return m_attrColors;  }
	GLuint GetAttrNormals() { return m_attrNormals;  }
	GLuint GetAttrTexCoords() { return m_attrTexCoords;  }
	GLuint GetSampler1() { return m_sampler1;  }
	GLuint GetSampler2() { return m_sampler2;  }

	// Methods
	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();
	GLuint GetAttrWVP() { return m_attrWVP; }
	void SetVec3(const char* _name, glm::vec3 _value);
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
	GLuint m_attrPOL;
	GLuint m_attrColors;
	GLuint m_attrNormals;
	GLuint m_attrTexCoords;
	GLuint m_sampler1;
	GLuint m_sampler2;
	GLint m_result = GL_FALSE;
	int m_infoLength;
};

#endif