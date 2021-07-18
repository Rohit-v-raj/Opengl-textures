#pragma once
#include "Renderer.h"

class Texture
{
private:

	string m_FilePath;
	unsigned int m_RendererID;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_BPP;

public:
	Texture(const string& path);
	~Texture();

	void Bind(unsigned int slot) const;
	void Unbind() const;

	inline int GetHeught() const { return m_height; }

	inline int GetWidth() const { return m_width; }



};