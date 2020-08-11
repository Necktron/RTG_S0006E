#include "Rasterizer.h"

void Rasterizer::Init(float x, float y)
{
	frameBufferToggle = false;
	window_Width = x;
	window_Height = y;
}

//DONE
void Rasterizer::SetupRasterizerBuffer()
{
	float pos[] =
	{
		//( x, y, z, R, G, B, A, normX, normY, normZ )
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int index[] =
	{
		0, 1, 2
	};

	//Vertex Array
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//Vertex Buffer Object, VBO
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	//Vertex Assosiation Object, VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 10, (GLvoid*)(sizeof(float) * 7));

	//Index Buffer Object, IBO
	glGenBuffers(1, &this->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
}

//DONE
void Rasterizer::SetupFrameBuffer()
{
	glGenFramebuffers(1, &this->fbo);

	//Create a color attachment texture
	glGenTextures(1, &this->tcb);
	glBindTexture(GL_TEXTURE_2D, this->tcb);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_Width, window_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Create a renderbuffer object for depth and stencil attachment ( we won't be sampling these )
	glGenRenderbuffers(1, &this->rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, this->rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_Width, window_Height);

	//Attach the texture and renderbuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo); //DRAW (Write ops), READ (Read ops), GL_FRAMEBUFFER (Both)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->tcb, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);

	//Verify if it's complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "FRAMEBUFFER ERROR: Not completed!" << endl;
}

//DONE
unsigned int* Rasterizer::GetFrameBufferPointer()
{
	unsigned int* fboPTR = &this->fbo;
	return fboPTR;
}

//DONE
string Rasterizer::GetFrameBufferSize()
{
	string widthHeight;
	GLint dims[4] = { 0 };

	glGetIntegerv(GL_VIEWPORT, dims);
	widthHeight = to_string(dims[2]) + "x" + to_string(dims[3]);

	return widthHeight;
}

//DONE
void Rasterizer::SetVertexShader(const function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)>& func)
{
	this->vertexShader = func;
}

//DONE
void Rasterizer::SetPixelShader(const function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)>& func)
{
	this->pixelShader = func;
}

//DONE
void Rasterizer::SetupMVP()
{
	//Setup the vital parts for MVP, Model + View + Projection
	this->view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
	this->transform = matrix3D::translate(vector3D(0.0f, 0.0f, 0.0f)) * matrix3D::scale(vector3D(1.0f, 1.0f, 1.0f)) * matrix3D::mxRotX(0.0f) * matrix3D::mxRotY(0.0f) * matrix3D::mxRotZ(0.0f);
	this->projection = matrix3D::perspectiveProj(90.0f, this->window_Width, this->window_Height, 0.1f, 100.0f).transpose();

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
}

//DONE
void Rasterizer::SetupTexture(Texture::TextureImage texture)
{
	switch (int(texture))
	{
	case -1:
		std::cout << "No texture assigned!" << std::endl;
		break;

	case 0:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/YellowBrickWall.jpg");
		break;

	case 1:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/TurquoiseWoodWall.jpg");
		break;

	case 2:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/KoreanFlag.png");
		break;

	case 3:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Blueberries.jpg");
		break;

	case 4:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/OpenGLLogo.png");
		break;

	case 5:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/InstaTransparent.png");
		break;

		//CAT
	case 6:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/cat_diff.tga");
		break;

	case 7:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/IKEA.jpg");
		break;

	case 8:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Richard.jpg");
		break;

	case 9:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Micke.jpg");
		break;

		//BOX
	case 10:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/cubeLow.jpg");
		break;

		//WINDMILL
	case 11:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/windmill.jpg");
		break;

		//PENGUIN
	case 12:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Penguin.png");
		break;
	}

	this->texturePTR->textureImage = texture;
}

//WIP
void Rasterizer::IndexToFrame()
{

}

//WIP
void Rasterizer::Rasterize()
{

}

//Not requiered! Testing
bool Rasterizer::ToggleFrameBuffer()
{
	//If it's toggled, switch back
	if (frameBufferToggle)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		frameBufferToggle = false;
	}

	//If it's not, switch it on
	else
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fbo);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		frameBufferToggle = true;
	}

	return frameBufferToggle;
}

void Rasterizer::Draw()
{
}

void Rasterizer::Flush()
{
	//memset(&pixels[0], 0, sizeof(pixels[0]) * pixels.size());
	//zDepth.assign(width * height, 0);
}