#pragma once
#include "stb_image.h"
#include "core/app.h"
#include <iostream>
#include <memory>
#include <string>

class Texture
{
public:

	Texture();
	~Texture();

	enum class TextureImage
	{
		NONE = -1,
		YELLOW_BRICKS = 0,
		TURQUOISE_WOOD = 1,
		KOREAN_FLAG = 2,
		BLUEBERRIES = 3,
		OPENGL_LOGO = 4,
		INSTAGRAM = 5,
		CAT = 6,
		IKEA = 7,
		LAGER = 8,
		MICKE = 9
	};

	TextureImage textureImage = TextureImage::NONE;

	void SetupTexture(const std::string& filepath); //Scan and setup texture
	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWitdh() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	unsigned char* m_TextureData;
	int m_Width, m_Height, m_BPP;
};