#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	m_texture = {};
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f);
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
}

Mesh:: ~Mesh() {

}

// Methods
void Mesh::Create(Shader* _shader){
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("C:/Users/dongxiny/Desktop/Graphics and Animation/InitOpenGL/Assets/Textures/Wood.jpg");

	// Colors values take from
	// https://web.archive.org/web/20180301041827/https://prideout.net/archive/colors.php
	//float a = 26.0f;
	//float b = 42.0f;
	//m_vertexData = {
	//	/* Position //    REGA Color    */
	//	-a, 0.0f, b,    1.0f, 0.0f, 0.0f, 1.0f, // Red
	//	a, 0.0f, b,        1.0f, 0.549f, 0.0f, 1.0f, // Orange
	//	-a, 0.0f, -b,    1.0f, 1.0f, 0.0f, 1.0f, // Yellow
	//	a, 0.0f, -b,    1.0f, 1.0f, 0.0f, 1.0f, // Green
	//	0.0f, b, a,        0.0f, 0.0f, 1.0f, 1.0f, // Blue
	//	0.0f, b, -a,    0.249f, 0.0f, 0.51f, 1.0f, // Indigo
	//	0.0f, -b, a,    0.502f, 0.0f, 0.502f, 1.0f, // Purple
	//	0.0f, -b, -a,    1.0f, 1.0f, 1.0f, 1.0f, // White
	//	b, a, 0.0f,        0.0f, 1.0f, 1.0f, 1.0f, // Cyan
	//	-b, a, 0.0f,    0.0f, 0.0f, 0.0f, 1.0f, // Black
	//	b, -a, 0.0f,    0.118f, 0.565f, 1.0f, 1.0f, // Dodger blue
	//	-b, -a, 0.0f,    0.863f, 0.078f, 0.235f, 1.0f, // Crimson
	//};

	//glGenBuffers(1, &m_vertexBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	/*m_indexData = {
		0, 6, 1, 0, 11, 6, 1, 4, 0, 1, 8, 4,
		1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
		3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
		5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
		7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
	};*/

	m_vertexData = {
		/* Position */			/* RBGA COlors */		/* Texture Coords */
		50.0f, 50.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 1.0f, // top-right
		50.0f, -50.0f, 0.0f,	0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // bottom-right
		-50.0f, -50.0f, 0.0f,	0.0f, 0.0f, 1.0f,		0.0f, 0.0f, // bottom-left
		-50.0f, 50.0f, 0.0f,	1.0f, 1.0f, 1.0f,		0.0f, 1.0f // top-left
		/* Position */			/* RGBA Color */
		0.2f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.9f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f,		1.0f, 0.0f, 0.0f, 0.0f,
		0.8f, 0.4f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	m_indexData = {
		2, 0, 3, 
		2, 1, 0
	};

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup(){
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
}

void Mesh::Render(glm::mat4 _wvp){
	glUseProgram(m_shader->GetProgramID());

	// 1st attribute : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)0
	);

	// 2nd attribute : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(
		m_shader->GetAttrColors(),
		3,
		GL_FLOAT,
		GL_FALSE,
		7 * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	_wvp *= m_world;
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() * 0.14285714285f);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}