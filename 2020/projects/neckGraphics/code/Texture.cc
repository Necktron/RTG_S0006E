#include "Texture.h"

Texture::Texture()
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::TextureFilepath(std::shared_ptr<Texture> ref)
{
	switch (int(ref->textureImage))
	{
		case -1:
			std::cout << "No texture chosen!" << std::endl;
			break;

		case 0:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/YellowBrickWall.jpg";
			break;

		case 1:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/TurquoiseWoodWall.jpg";
			break;

		case 2:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/KoreanFlag.png";
			break;

		case 3:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/Blueberries.jpg";
			break;

		case 4:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/OpenGLLogo.png";
			break;

		case 5:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/InstaTransparent.png";
			break;

		case 6:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/cat_diff.tga";
			break;

		case 7:
			ref->m_FilePath = "../../../projects/neckGraphics/code/resources/textures/IKEA.jpg";
			break;
	}
}

void Texture::SetupTexture(const std::string& filepath)
{
	stbi_set_flip_vertically_on_load(1);
	m_TextureData = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, STBI_rgb_alpha);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_TextureData)
		stbi_image_free(m_TextureData);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}