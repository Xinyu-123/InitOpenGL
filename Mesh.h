#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Accessors
	glm::vec3& GetPosition() { return m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	void SetLightPosition(glm::vec3 _lightPosition) { m_lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightColor) { m_lightColor = _lightColor; }
	
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }
	// Methods
	void Create(Shader* _shader, string _file);
	void Cleanup();
	void Render(glm::mat4 _vp);
	void CalculateTransform();
	
	// Members
	static vector<Mesh> Lights;
	glm::vec3 m_rotation;

private:
	// Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
private:
	Shader* m_shader;
	Texture m_texture;
	Texture m_texture2;
	GLuint m_vertexBuffer; // GPU Buffer
	GLuint m_indexBuffer; // GPU Buffer
	vector<GLfloat> m_vertexData;
	vector<GLubyte> m_indexData;

	// Transform
	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::mat4 m_world;

	// Lights
	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;

	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;
};


#endif //MESH_H
