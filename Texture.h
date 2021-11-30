#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "StandardIncludes.h"

class Texture
{
public:
	// Constructors / Destructors
	Texture();
	virtual ~Texture() {};

	// Accessors
	GLuint GetTexture() { return m_texture; }

	// methods
	void LoadTexture(string _filename);
	void LoadCubeMap(vector<std::string> _faces);
	void Cleanup();
private:
	// Members
	int m_width;
	int m_height;
	int m_channels;
	GLuint m_texture;
	GLuint m_texture2;

	// Method
	bool EndsWith(const std::string& _str, const std::string& _suffix);
};

#endif

