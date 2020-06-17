#include "TextureResource.h"
#include "config.h"
#include <string>
#include <memory>

TextureResource::TextureResource()
{

}

TextureResource::~TextureResource()
{

}

void TextureResource::loadFromRast(std::shared_ptr<Rasterizer> rastPTR)
{
	glGenTexturesEXT(1, &texBufferID);

	glBindTexture(GL_TEXTURE_2D, texBufferID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, rastPTR->width, rastPTR->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &rastPTR->pixelRetriver()[0]);
}

void TextureResource::loadFromFile(const char *filePath)
{
	int bitdepth;

	//OBS! These are tested: ( StrawHats.jpg, Ace.jpg, Corazon.jpg, cat_diff.tga )

	data = stbi_load(filePath, &width, &height, &bitdepth, STBI_rgb_alpha);

	glGenTextures(1, &texBufferID);

	glBindTexture(GL_TEXTURE_2D, texBufferID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

void TextureResource::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texBufferID);
}