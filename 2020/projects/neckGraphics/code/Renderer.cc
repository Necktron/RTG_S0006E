#define LMB 0x0001
#define RMB 0x0002

#include "Renderer.h"

//Init all components
void Renderer::Init(float resX, float resY)
{
	meshPTR = std::make_shared<Mesh>();
	shaderPTR = std::make_shared<Shader>();
	texturePTR = std::make_shared<Texture>();

	rot = 0.0f;
	rotSpeed = 1.0f;
	angleOfRot = 0.0f;
	incrementRGB = 0.0f;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	moveX = 0.0f;
	moveY = 0.0f;
	moveZ = 0.0f;
	r = 1.1f;
	g = 0.0f;
	b = 0.0f;
	initPosX = 0.0f;
	initPosY = 0.0f;
	initPosZ = 0.0f;
	initScaleX = 0.0f;
	initScaleY = 0.0f;
	initScaleZ = 0.0f;
	initRotX = 0.0f;
	initRotY = 0.0f;
	initRotZ = 0.0f;
	zoomCam = 4.0f;

	window_Width = resX;
	window_Height = resY;

	transform = matrix3D();
	view = matrix3D();
	projection = matrix3D();
	MVP = matrix3D();

	rotation = vector3D();

	meshPTR->m_DEBUG = false;
	shaderPTR->m_DEBUG = false;
}

//Update values for color anim, rot, etc
void Renderer::Update()
{
	//COLOR ANIM
	if (this->r > 1.0f)
		incrementRGB = -0.02f;
	else if (this->r < -1.0f)
		incrementRGB = 0.02f;

	this->r += incrementRGB;

	//ROT MOVE
	if (this->angleOfRot > 360.0f)
		this->angleOfRot = 0.0f;

	this->angleOfRot += 1.0f;

	this->rot = this->angleOfRot * this->rotSpeed;

	//Print out matrix values per frame
	if (meshPTR->m_DEBUG)
	{
		std::cout << "MATRIX VALUES" << std::endl;
		std::cout << MVP.mxOrigin[0][0] << " " << MVP.mxOrigin[0][1] << " " << MVP.mxOrigin[0][2] << " " << MVP.mxOrigin[0][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[1][0] << " " << MVP.mxOrigin[1][1] << " " << MVP.mxOrigin[1][2] << " " << MVP.mxOrigin[1][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[2][0] << " " << MVP.mxOrigin[2][1] << " " << MVP.mxOrigin[2][2] << " " << MVP.mxOrigin[2][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[3][0] << " " << MVP.mxOrigin[3][1] << " " << MVP.mxOrigin[3][2] << " " << MVP.mxOrigin[3][3] << std::endl;
		std::cout << "                " << std::endl;
	}

	//Setup the vital parts for MVP, Model + View + Projection
	SetView(vector3D(0.0f, 0.0f, zoomCam), vector3D(0.0f, 0.0f, 0.0f));
	SetTransform(vector3D(initPosX + moveX, initPosY + moveY, initPosZ + moveZ), vector3D(initScaleX, initScaleY, initScaleZ), vector3D(initRotX + rotX, initRotY + rotY, initRotZ + rotZ));
	SetProjection(90.0f);

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
}

//Check for keyboard / mouse input
void Renderer::InputScan()
{
	KeyboardScan();
	MouseScan();
}

//Set a mesh from the pre-defined types, triangle / quad / cube
void Renderer::SetMesh(int meshType)
{
	//WIP
	switch (meshType)
	{
		//Triangle
		case 0:
			meshPTR->Triangle();
			break;

		//Quad
		case 1:
			meshPTR->Quad();
			break;

		//Cube
		case 2:
			meshPTR->Cube();
			break;
	}
}

//Set a mesh from file path, load OBJ, next assignment
void Renderer::SetMesh(const char* filepath)
{
	//meshPTR->MeshFile(filepath);
}

//Set texture from a specific path
void Renderer::SetTexture(Texture::TextureImage texture)
{
	switch (int(texture))
	{
		case -1:
			std::cout << "No texture chosen!" << std::endl;
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

		case 6:
			texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/cat_diff.tga");
			break;

		case 7:
			texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/IKEA.jpg");
			break;
	}

	this->texturePTR->textureImage = texture;
}

//Set shader from a specific path
void Renderer::SetShader(Shader::ShaderEffect shader)
{
	switch (int(shader))
	{
		//Rainbow Static
		case 0:
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/StaticRainbow.shader");
			break;

		//Pulse Color
		case 1:
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/PulseColor.shader");
			break;

		//Texture from file
		case 2:
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/ImageTexture.shader");
			break;
	}

	if(int(texturePTR->textureImage) != -1)
	{
		shaderPTR->SetUniform1i("u_Texture", 0);
	}
}

//Set the initial transform of the model with Position / Scale / Rotation directions
void Renderer::SetStartTransform(vector3D pos, vector3D scale, vector3D rot)
{
	this->transform = matrix3D::translate(pos) * matrix3D::scale(scale) * matrix3D::mxRotAroundVec(rot, 0);

	initPosX = pos.vecGet(0);
	initPosY = pos.vecGet(1);
	initPosZ = pos.vecGet(2);

	initScaleX = scale.vecGet(0);
	initScaleY = scale.vecGet(1);
	initScaleZ = scale.vecGet(2);
	
	initRotX = rot.vecGet(0);
	initRotY = rot.vecGet(1);
	initRotZ = rot.vecGet(2);
}

//Set the transform of the model with Position / Scale / Rotation directions
void Renderer::SetTransform(vector3D pos, vector3D scale, vector3D rot)
{
	this->transform = matrix3D::translate(pos) * matrix3D::scale(scale) * matrix3D::mxRotX(rot.vecOrigin[0]) * matrix3D::mxRotY(rot.vecOrigin[1]) * matrix3D::mxRotZ(rot.vecOrigin[2]);
}

//Set the position and target location of the camera
void Renderer::SetView(vector3D origin, vector3D target)
{
	this->view = matrix3D::LookAt(origin, target, vector3D(0.0f, 1.0f, 0.0f));
}

//Set the FOV
void Renderer::SetProjection(float FOV)
{
	this->projection = matrix3D::perspectiveProj(FOV, this->window_Width, this->window_Height, 0.1f, 100.0f).transpose();
}

//Draw all data to the screen
void Renderer::Draw()
{
	Bind();

	Update();

	//if(int(shaderPTR->shaderEFK) = )
	//shaderPTR->SetUniform4f("u_Color", r, g, b, 1.0f);

	shaderPTR->SetUniformMat4fv("u_MVP", MVP);
	shaderPTR->SetUniform4f("u_Move", 0.0f, 0.0f, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 36 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	Unbind();
}

//Clear the screen from previous data
void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

//Bind buffers for render
void Renderer::Bind()
{
	shaderPTR->Bind();
	meshPTR->Bind();

	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}
}

//Unbind data so other Renderers can Bind their data and spare memory
void Renderer::Unbind()
{
	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}

	meshPTR->Unbind();
	shaderPTR->Unbind();
}

//WIP -->
//Return current Mesh data
Mesh Renderer::GetMesh()
{
	return Mesh();
}

//Return current Texture data
Texture Renderer::GetTexture()
{
	return Texture();
}

//Return current Shader data
Shader Renderer::GetShader()
{
	return Shader();
}

//Return current Transform
matrix3D Renderer::GetTransform()
{
	return transform;
}

//Handle input for mouse
void Renderer::MouseScan()
{
	if (GetAsyncKeyState(LMB) & 0x8000)
	{
		//CHECK FOR CHANGES IN POSITION

		// MOVE X AXIS = ROT X AXIS
		// MOVE Y AXIS = ROT Y AXIS
	}
}

//Handle input for keyboard
void Renderer::KeyboardScan()
{
	if (GetAsyncKeyState('W') & 0x8000)
		moveY += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000)
		moveX -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000)
		moveY -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000)
		moveX += 0.1f;
}