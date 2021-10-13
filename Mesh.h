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

	// Methods
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);

private:
	Shader* m_shader;
	Texture m_texture;
	GLuint m_vertexBuffer; // GPU Buffer
	GLuint m_indexBuffer; // GPU Buffer
	vector<GLfloat> m_vertexData;
	vector<GLubyte> m_indexData;
	glm::mat4 m_world;
	glm::vec3 m_position;
	glm::vec3 m_rotation;
};


#endif //MESH_H
