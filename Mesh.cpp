#include "Mesh.h"
#include "Shader.h"
#include "OBJ_Loader.h"

vector<Mesh> Mesh::Lights;

Mesh::Mesh() {
	m_shader = nullptr;
	m_textureDiffuse = {};
	m_textureSpecular = {};
	m_textureNormal = {};
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
	m_enableNormalMap = false;

}

Mesh:: ~Mesh() {

}

// Methods
void Mesh::Create(Shader* _shader, string _file){
	m_shader = _shader;


	objl::Loader loader;
	M_ASSERT(loader.LoadFile(_file) == true, "Failed to load mesh.");

	for (size_t i = 0; i < loader.LoadedMeshes.size(); ++i)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[i];
		vector<objl::Vector3> tangents;
		vector<objl::Vector3> bitangents;
		vector<objl::Vertex> triangles;
		objl::Vector3 tangent;
		objl::Vector3 bitangent;
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j += 3)
		{
			triangles.clear();
			triangles.push_back(curMesh.Vertices[j]);
			triangles.push_back(curMesh.Vertices[j + 1]);
			triangles.push_back(curMesh.Vertices[j + 2]);
			CalculateTangents(triangles, tangent, bitangent);
			tangents.push_back(tangent);
			bitangents.push_back(bitangent);
		}
		for (size_t j = 0; j < curMesh.Vertices.size(); ++j)
		{
			m_vertexData.push_back(curMesh.Vertices[j].Position.X);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Position.Z);

			m_vertexData.push_back(curMesh.Vertices[j].Normal.X);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(curMesh.Vertices[j].Normal.Z);

			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(curMesh.Vertices[j].TextureCoordinate.Y);

			if (loader.LoadedMaterials[0].map_bump != "")
			{
				int index = j / 3;
				m_vertexData.push_back(tangents[index].X);
				m_vertexData.push_back(tangents[index].Y);
				m_vertexData.push_back(tangents[index].Z);
				
				m_vertexData.push_back(bitangents[index].X);
				m_vertexData.push_back(bitangents[index].Y);
				m_vertexData.push_back(bitangents[index].Z);
			}
		}
	}

	string diffuseMap = loader.LoadedMaterials[0].map_Kd;
	const size_t last_slash_idx = diffuseMap.find_last_of("\\");

	if (std::string::npos != last_slash_idx)
	{
		diffuseMap.erase(0, last_slash_idx);
	}

	m_textureDiffuse = Texture();
	m_textureDiffuse.LoadTexture("Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Kd));
	m_textureSpecular = Texture();

	if(loader.LoadedMaterials[0].map_Ks != "")
		m_textureSpecular.LoadTexture("Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_Ks));
	
	if (loader.LoadedMaterials[0].map_bump != "")
	{
		m_textureNormal.LoadTexture("Assets/Textures/" + RemoveFolder(loader.LoadedMaterials[0].map_bump));
		m_enableNormalMap = true;
	}

	

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
}

void Mesh::Cleanup(){
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_textureDiffuse.Cleanup();
	m_textureSpecular.Cleanup();
}

void Mesh::Render(glm::mat4 _vp){
	glUseProgram(m_shader->GetProgramID());

	m_rotation.x += 0.01f;

	CalculateTransform();
	SetShaderVariables(_vp);
	BindAttributes();


	//glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / elementSize);
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}

void Mesh::CalculateTransform()
{
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.x, glm::vec3(1, 0, 0));
	m_world = glm::scale(m_world, m_scale);
}

string Mesh::RemoveFolder(string _map)
{
	const size_t last_slash_idx = _map.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		_map.erase(0, last_slash_idx + 1);
	}

	return _map;
}

void Mesh::SetShaderVariables(glm::mat4 _pv)
{
	m_shader->SetMat4("World", m_world);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
	m_shader->SetInt("EnableNormalMap", m_enableNormalMap);


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
		m_shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, m_textureDiffuse.GetTexture());
		m_shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, m_textureSpecular.GetTexture());
		m_shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, m_textureNormal.GetTexture());
	}
}

void Mesh::BindAttributes()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

	int stride = 8;
	elementSize = 8;
	if (m_enableNormalMap)
	{
		stride += 6;
		elementSize += 6;
	}
	
	// 1st attribute : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(
		m_shader->GetAttrVertices(),
		3,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)0
	);

	// 2nd attribute : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(
		m_shader->GetAttrNormals(),
		3,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)(3 * sizeof(float))
	);

	// 3rd attribute : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(
		m_shader->GetAttrTexCoords(),
		2,
		GL_FLOAT,
		GL_FALSE,
		stride * sizeof(float),
		(void*)(6 * sizeof(float))
	);

	if (m_enableNormalMap)
	{
		// 4nd attribute : tangent
		glEnableVertexAttribArray(m_shader->GetAttrTangents());
		glVertexAttribPointer(
			m_shader->GetAttrTangents(),
			3,
			GL_FLOAT,
			GL_FALSE,
			stride * sizeof(float),
			(void*)(8 * sizeof(float))
		);

		// 5rd attribute : bitangent
		glEnableVertexAttribArray(m_shader->GetAttrBitangents());
		glVertexAttribPointer(
			m_shader->GetAttrBitangents(),
			3,
			GL_FLOAT,
			GL_FALSE,
			stride * sizeof(float),
			(void*)(11 * sizeof(float))
		);

	}
}

string Mesh::Concat(string _s1, int _index, string _s2)
{
	string index = to_string(_index);
	return(_s1 + index + _s2);
}

void Mesh::CalculateTangents(vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
	objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
	objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;

	objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
	objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

	float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

	_tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
	_tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
	_tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);	
	
	_bitangent.X = f * (-deltaUV2.Y * edge1.X + deltaUV1.X * edge2.X);
	_bitangent.X = f * (-deltaUV2.Y * edge1.Y + deltaUV1.X * edge2.Y);
	_bitangent.X = f * (-deltaUV2.Y * edge1.Z + deltaUV1.X * edge2.Z);
}
