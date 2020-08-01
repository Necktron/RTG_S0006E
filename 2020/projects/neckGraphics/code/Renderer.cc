#define LMB 0x0001
#define RMB 0x0002

#include "Renderer.h"

//Init all components
void Renderer::Init(float resX, float resY, string name)
{
	renderName = name;

	meshPTR = std::make_shared<Mesh>();
	shaderPTR = std::make_shared<Shader>();
	texturePTR = std::make_shared<Texture>();
	lightPTR = std::make_shared<Light>();

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

	camX = 0.0f;
	camY = 0.0f;
	camZ = 4.0f;

	camTargetX = 0.0f;
	camTargetY = 0.0f;
	camTargetZ = 1.0f;

	oldRotX = 0.0f;
	oldRotY = 0.0f;

	oldCamTargetX = 0.0f;
	oldCamTargetY = 0.0f;
	oldCamTargetZ = 0.0f;

	window_Width = resX;
	window_Height = resY;

	transform = matrix3D();
	view = matrix3D();
	projection = matrix3D();
	MVP = matrix3D();

	rotation = vector3D();

	meshPTR->m_DEBUG = false;
	shaderPTR->m_DEBUG = false;
	LMB_DOWN = false;
	RMB_DOWN = false;
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

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::PULSE_COLOR)
		shaderPTR->SetUniform4f("u_Color", r, 0.0f, 0.0f, 1.0f);

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::BLINN_PHONG)
	{
		g += 0.1f;

		shaderPTR->SetUniform3f("u_LightOrigin", 0.0f, 0.0f, 0.0f);
		shaderPTR->SetUniform3f("u_AmbientColor", 0.1f, 0.1f, 0.1f);
		shaderPTR->SetUniform3f("u_DiffuseColor", 0.1f, 0.1f, 0.1f);
		shaderPTR->SetUniform3f("u_SpecColor", 0.3f, 0.3f, 0.3f);
	}

	//Setup the vital parts for MVP, Model + View + Projection
	SetView(vector3D(camX, camY, camZ), vector3D(camX - camTargetX, camY - camTargetY, camZ - camTargetZ));
	SetTransform(vector3D(initPosX + moveX, initPosY + moveY, initPosZ + moveZ), vector3D(initScaleX, initScaleY, initScaleZ), vector3D(initRotX + rotX, initRotY + rotY, initRotZ + rotZ));
	SetProjection(90.0f);

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
}

//Check for keyboard / mouse input overall
void Renderer::InputScan()
{
	MouseScan();
	KeyboardScan();
}

//Check for keyboard / mouse input, specifically for camera commands
void Renderer::InputScanOnlyCamera()
{
	MouseScanCam();
	KeyboardScanCam();
}

//Set a mesh from the pre-defined types, triangle / quad / cube
void Renderer::SetMesh(Mesh::OBJ obj)
{
	//WIP
	switch (int(obj))
	{
		case -1:
			std::cout << "No OBJ selected" << std::endl;
			break;

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

		//Cat
		case 3:
			meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/cat.obj");
			break;

		//Stool
		case 4:
			meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/Stool.obj");
			break;

		//CUBE
		case 5:
			meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/cubeLow.obj");
			break;

		//SARA CUBE
		case 6:
			meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/saraCube.obj");
			break;
	}

	this->meshPTR->meshOBJ = obj;
}

//Set texture from a specific path
void Renderer::SetTexture(Texture::TextureImage texture)
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

		//SARACUBE
		case 11:
			texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/saraCubeUV2.tga");
			break;
	}

	this->texturePTR->textureImage = texture;
}

//Set shader from a specific path
void Renderer::SetShader(Shader::ShaderEffect shader)
{
	std::cout << "[ SHADER FOR RENDER: " << renderName << " ]" << std::endl;

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

		//Bling bling!
		case 3:
			shaderPTR->SetupShader("../../../projects/neckGraphics/code/resources/shaders/BlinnPhong.shader");
			break;
	}

	if(int(texturePTR->textureImage) != -1)
	{
		shaderPTR->SetUniform1i("u_Texture", 0);
	}

	this->shaderPTR->shaderEFK = shader;
}

//Set a light source
void Renderer::SetLight(Light::LightSource lightsource)
{
	switch (int(lightsource))
	{
		//No light source
		case -1:
			std::cout << "No light source assigned!" << std::endl;
			break;

		//Point Light
		case 0:
			lightPTR->GetPointLight();
			break;
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

	//Custom mesh
	if(int(meshPTR->meshOBJ) == 3 || int(meshPTR->meshOBJ) == 4)
		glDrawElements(GL_TRIANGLES, meshPTR->indices.size(), GL_UNSIGNED_INT, NULL);

	//Anything else
	else
		glDrawElements(GL_TRIANGLES, 36 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	Unbind();
}

//Clear the screen from previous data
void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

//Return current Mesh data
std::shared_ptr<Mesh> Renderer::GetMesh()
{
	return meshPTR;
}

//Return current Texture data
std::shared_ptr<Texture> Renderer::GetTexture()
{
	return texturePTR;
}

//Return current Shader data
std::shared_ptr<Shader> Renderer::GetShader()
{
	return shaderPTR;
}

//Return current Transform
matrix3D Renderer::GetTransform()
{
	return transform;
}

// * * * PRIVATE FUNCTIONS * * *

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

//Handle input form mouse, Everything
void Renderer::MouseScan()
{
	//CAM Z MOVEMENT
	if (GetAsyncKeyState('E') & 0x8000)
		camZ += 0.06f;

	if (GetAsyncKeyState('Q') & 0x8000)
		camZ -= 0.06f;

	//ROTATION FOR MODEL
	if (GetAsyncKeyState(LMB) & 0x8000 && !LMB_DOWN)
	{
		GetCursorPos(&mousePosOrigin);
		oldRotX = rotX;
		oldRotY = rotY;
		LMB_DOWN = true;
	}

	else if (GetAsyncKeyState(LMB) & 0x8000 && LMB_DOWN)
	{
		GetCursorPos(&mousePosCurrent);

		float currX = mousePosCurrent.x - mousePosOrigin.x;
		float currY = mousePosCurrent.y - mousePosOrigin.y;

		rotX = -currY + oldRotX;
		rotY = -currX + oldRotY;
	}

	else
		LMB_DOWN = false;

	//ROTATION FOR CAMERA
	if (GetAsyncKeyState(RMB) & 0x8000 && !RMB_DOWN)
	{
		GetCursorPos(&mousePosOrigin);
		oldCamTargetX = camTargetX * 0.01f;
		oldCamTargetY = camTargetY * 0.01f;
		RMB_DOWN = true;
	}

	else if (GetAsyncKeyState(RMB) & 0x8000 && RMB_DOWN)
	{
		GetCursorPos(&mousePosCurrent);

		float currX = mousePosCurrent.x - mousePosOrigin.x;
		float currY = mousePosCurrent.y - mousePosOrigin.y;

		camTargetX = (-currY + oldCamTargetX) * 0.01f;
		camTargetY = (-currX + oldCamTargetY) * 0.01f;
	}

	else
		RMB_DOWN = false;
}

//Handle input form keyboard, Everything
void Renderer::KeyboardScan()
{
	//MOVE MODEL IF RMB IS NOT DOWN
	if (GetAsyncKeyState('W') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveY += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveX -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveY -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveX += 0.1f;

	if (GetAsyncKeyState('Q') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveZ -= 0.15f;

	if (GetAsyncKeyState('E') & 0x8000 && !(GetAsyncKeyState(RMB) & 0x8000))
		moveZ += 0.1f;

	//MOVE CAMERA IF RMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camY += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camX -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camY -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camX += 0.1f;
}

//Handle input form mouse to the camera
void Renderer::MouseScanCam()
{
	//CAM Z MOVEMENT
	if (GetAsyncKeyState('E') & 0x8000)
		camZ += 0.06f;

	if (GetAsyncKeyState('Q') & 0x8000)
		camZ -= 0.06f;

	//ROTATION FOR CAMERA
	if (GetAsyncKeyState(RMB) & 0x8000 && !RMB_DOWN)
	{
		GetCursorPos(&mousePosOrigin);
		oldCamTargetX = camTargetX * 0.01f;
		oldCamTargetY = camTargetY * 0.01f;
		RMB_DOWN = true;
	}

	else if (GetAsyncKeyState(RMB) & 0x8000 && RMB_DOWN)
	{
		GetCursorPos(&mousePosCurrent);

		float currX = mousePosCurrent.x - mousePosOrigin.x;
		float currY = mousePosCurrent.y - mousePosOrigin.y;

		camTargetX = (-currY + oldCamTargetX) * 0.01f;
		camTargetY = (-currX + oldCamTargetY) * 0.01f;
	}

	else
		RMB_DOWN = false;
}

//Handle input form keyboard to the camera
void Renderer::KeyboardScanCam()
{
	//MOVE CAMERA IF RMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camY += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camX -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camY -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && GetAsyncKeyState(RMB) & 0x8000)
		camX += 0.1f;
}