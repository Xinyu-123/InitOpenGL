#include "Mesh.h"
#include "Shader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh() {
	m_shader = nullptr;
	m_texture = {};
	m_texture2 = {};
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f);
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_lightPosition = { 0, 0, 0 };
	m_lightColor = { 1, 1, 1 };
	m_cameraPosition = { 0, 0, 0 };
}

Mesh:: ~Mesh() {

}

// Methods
void Mesh::Create(Shader* _shader){
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("Assets/Textures/MetalFrameWood.jpg");
	m_texture2 = Texture();
	m_texture2.LoadTexture("Assets/Textures/MetalFrame.jpg");

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
		/*    Position    *//*    Normals    *//* Texture Coords */
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
	m_texture2.Cleanup();
}

void Mesh::Render(glm::mat4 _vp){
	glUseProgram(m_shader->GetProgramID());

	m_rotation.y += 0.001f;

	CalculateTransform();
	SetShaderVariables(_vp);
	BindAttributes();


	//glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size());
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);



	// Configure Light
	for (size_t i = 0; i < Lights.size(); ++i)
	{
		m_shader->SetVec3(Concat("light[", i, "].position").c_str(), Lights[i].GetPosition());
		m_shader->SetVec3(Concat("light[", i, "].color").c_str(), Lights[i].GetColor());

		m_shader->SetFloat(Concat("light[", i, "].constant").c_str(), 1.0f);
		m_shader->SetFloat(Concat("light[", i, "].linear").c_str(), 0.09f);
		m_shader->SetFloat(Concat("light[", i, "].quadradic").c_str(), 0.032f);
		m_shader->SetVec3(Concat("light[", i, "].ambientLight").c_str(), { 0.3f, 0.3f, 0.3f });
		m_shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), { 1.0f, 1.0f, 1.0f });
		m_shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), { 3.0f, 3.0f, 3.0f });

		m_shader->SetVec3(Concat("light[", i, "].direction").c_str(), glm::normalize(glm::vec3({ 0.0f + i * 0.1f, 0, 0.0f + i * 0.1f }) - Lights[i].GetPosition()));
		m_shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(5.0f));
		m_shader->SetFloat(Concat("light[", i, "].falloff").c_str(), 100);


		// Configure Material
		m_shader->SetFloat("material.specularStrength", 4);
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_texture.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_texture2.GetTexture());
	}
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

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

	// 2nd attribute : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(
		m_shader->GetAttrNormals(),
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	// 3rd attribute : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(
		m_shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*)(6 * sizeof(float))
	);

}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return(_s1 + index + _s2);
}
