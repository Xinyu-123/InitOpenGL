#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_world = glm::mat4(1.0f);
}

Mesh:: ~Mesh() {

}

// Methods
void Mesh::Create(Shader* _shader){
	m_shader = _shader;
	m_vertexData = {
		/* Position */			/* RGBA Color */
		0.2f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.9f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f,
		0.4f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		0.7f, 0.8f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, 0.4f, 0.0f,		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.6f, 0.0f,		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.2f, 0.0f,		1.0f, 0.0f, 0.0f, 1.0f,
		1.5f, 0.6f, 0.0f,		0.0f, 1.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); 
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

}

void Mesh::Cleanup(){
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp){
	glUseProgram(m_shader->GetProgramID());

	// 1st attribute : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(
		m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		7 * sizeof(float),
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
}