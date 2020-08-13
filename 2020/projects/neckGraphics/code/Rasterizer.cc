#define LMB 0x0001
#define RMB 0x0002
#define MMB 0x0004

#include "Rasterizer.h"

//DONE
void Rasterizer::Init(float x, float y, string name)
{
	rasterizerName = name;
	frameBufferToggle = false;
	window_Width = x;
	window_Height = y;
	meshPTR = make_shared<Mesh>();
	shaderPTR = make_shared<Shader>();
	texturePTR = make_shared<Texture>();
	lightPTR = make_shared<Light>();
	fboPTR = make_shared<unsigned int>();

	r = 1.1f;
	g = 0.0f;
	b = 0.0f;
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

	//MODEL
	initPosX = 0.0f;
	initPosY = 0.0f;
	initPosZ = 0.0f;

	initScaleX = 0.0f;
	initScaleY = 0.0f;
	initScaleZ = 0.0f;

	initRotX = 0.0f;
	initRotY = 0.0f;
	initRotZ = 0.0f;

	//CAMERA
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

	//LIGHT
	//Pos
	lightX = 0.0f;
	lightY = 0.0f;
	lightZ = 0.0f;

	//Intensity
	lightAmbientIntensity = 0.0f;
	lightDiffuseIntensity = 0.0f;

	//Color related
	colorCounter = 0;

	transform = matrix3D();
	view = matrix3D();
	projection = matrix3D();
	MVP = matrix3D();

	rotation = vector3D();

	meshPTR->m_DEBUG = false;
	shaderPTR->m_DEBUG = false;
	LMB_DOWN = false;
	MMB_DOWN = false;
	RMB_DOWN = false;
	C_DOWN = false;
}

//DONE
void Rasterizer::Update()
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

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::BLINN_PHONG && lightPTR->lightSource == Light::LightSource::POINT_LIGHT)
	{
		shaderPTR->SetUniform3f("u_LightPos", lightPTR->currentLight.Position.vecOrigin[0], lightPTR->currentLight.Position.vecOrigin[1], lightPTR->currentLight.Position.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_CamPos", camX, camY, camZ);
		shaderPTR->SetUniform3f("u_AmbientColor", lightPTR->currentLight.Ambient.vecOrigin[0], lightPTR->currentLight.Ambient.vecOrigin[1], lightPTR->currentLight.Ambient.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_DiffuseColor", lightPTR->currentLight.Diffuse.vecOrigin[0], lightPTR->currentLight.Diffuse.vecOrigin[1], lightPTR->currentLight.Diffuse.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_SpecularColor", lightPTR->currentLight.Specular.vecOrigin[0], lightPTR->currentLight.Specular.vecOrigin[1], lightPTR->currentLight.Specular.vecOrigin[2]);
		shaderPTR->SetUniform1f("u_AmbientIntensity", lightPTR->currentLight.AmbientIntensity);
		shaderPTR->SetUniform1f("u_DiffuseIntensity", lightPTR->currentLight.DiffuseIntensity);
		shaderPTR->SetUniform1f("u_SpecularIntensity", lightPTR->currentLight.SpecularIntensity);
	}

	//Setup the vital parts for MVP, Model + View + Projection
	SetView(vector3D(camX, camY, camZ), vector3D(camX - camTargetX, camY - camTargetY, camZ - camTargetZ));
	SetTransform(vector3D(initPosX + moveX, initPosX + moveY, initPosZ + moveZ), vector3D(initScaleX, initScaleY, initScaleZ), vector3D(initRotX + rotX, initRotY + rotY, initRotZ + rotZ));
	SetProjection(90.0f);

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
}

//DONE
void Rasterizer::InputScan()
{
	MouseScan();
	KeyboardScan();
}

//Set a mesh from the pre-defined types, triangle / quad / cube
void Rasterizer::SetMesh(Mesh::OBJ obj)
{
	//WIP
	switch (int(obj))
	{
	case -1:
		std::cout << "No OBJ selected" << std::endl;
		break;

		//Rast Triangle
	case 0:
		meshPTR->RastTriangle();
		break;

		//Triangle
	case 1:
		meshPTR->Triangle();
		break;

		//Quad
	case 2:
		meshPTR->Quad();
		break;

		//Cube
	case 3:
		meshPTR->Cube();
		break;

		//Cat
	case 4:
		meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/cat.obj");
		break;

		//Stool
	case 5:
		meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/Stool.obj");
		break;

		//CUBE
	case 6:
		meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/cubeLow.obj");
		break;

		//WINDMILL
	case 7:
		meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/windmill.obj");
		break;

		//PENGUIN
	case 8:
		meshPTR->CustomMesh("../../../projects/neckGraphics/code/resources/meshes/Penguin.obj");
		break;
	}

	this->meshPTR->meshOBJ = obj;
}

//Set texture from a specific path
void Rasterizer::SetTexture(Texture::TextureImage texture)
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

		//WINDMILL
	case 12:
		texturePTR->SetupTexture("../../../projects/neckGraphics/code/resources/textures/Penguin.png");
		break;
	}

	this->texturePTR->textureImage = texture;
}

//Set shader from a specific path
void Rasterizer::SetShader(Shader::ShaderEffect shader)
{
	std::cout << "[ SHADER FOR RENDER: " << rasterizerName << " ]" << std::endl;

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

	if (int(texturePTR->textureImage) != -1)
	{
		shaderPTR->SetUniform1i("u_Texture", 0);
	}

	this->shaderPTR->shaderEFK = shader;
}

//Set a light source
void Rasterizer::SetLight(Light::LightSource lightsource)
{
	switch (int(lightsource))
	{
		//No light source
	case -1:
		std::cout << "No light source assigned!" << std::endl;
		break;

		//Point Light
	case 0:
		lightPTR->PointLight();
		break;
	}
}

//Set the initial transform of the model with Position / Scale / Rotation directions
void Rasterizer::SetStartTransform(vector3D pos, vector3D scale, vector3D rot)
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
void Rasterizer::SetTransform(vector3D pos, vector3D scale, vector3D rot)
{
	this->transform = matrix3D::translate(pos) * matrix3D::scale(scale) * matrix3D::mxRotX(rot.vecOrigin[0]) * matrix3D::mxRotY(rot.vecOrigin[1]) * matrix3D::mxRotZ(rot.vecOrigin[2]);
}

//Set the position and target location of the camera
void Rasterizer::SetView(vector3D origin, vector3D target)
{
	this->view = matrix3D::LookAt(origin, target, vector3D(0.0f, 1.0f, 0.0f));
}

//Set the FOV
void Rasterizer::SetProjection(float FOV)
{
	this->projection = matrix3D::perspectiveProj(FOV, this->window_Width, this->window_Height, 0.1f, 100.0f).transpose();
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
unsigned char* Rasterizer::GetFrameBufferPointer()
{
	return this->image;
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

vector<Rasterizer::PixelColor> Rasterizer::GetPixel()
{
	return this->pixels;
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

//WIP - Set IBO to FrameBuffer
void Rasterizer::IndexToFrame()
{
	//TODO: Fix this
}

//WIP
void Rasterizer::Increment(Edge& edge)
{
	if (edge.oct == OctantOne)
	{
		edge.x++;

		if (edge.d < 0)
		{
			edge.d += edge.e;
		}
		else
		{
			edge.d += edge.ne;
			edge.y++;
		}
	}
	else if (edge.oct == OctantTwo)
	{
		edge.y++;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}
		else
		{
			edge.d += edge.ne;
			edge.x++;
		}
	}
	else if (edge.oct == OctantThree)
	{
		edge.y++;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}
		else
		{
			edge.d += edge.ne;
			edge.x--;
		}
	}
	else if (edge.oct == OctantFour)
	{
		edge.x--;
		if (edge.d < 0)
		{
			edge.d += edge.e;
		}
		else
		{
			edge.d += edge.ne;
			edge.y++;
		}
	}
}

//WIP
void Rasterizer::Rasterize(vector3D vOne, vector3D vTwo, vector3D vThree)
{
	Edge edges[3] =
	{
		Edge(vOne, vTwo),
		Edge(vOne, vThree),
		Edge(vThree, vTwo)
	};

	int maxLength = 0, EdgeL = 0;

	for (int i = 0; i < 3; i++)
	{
		int length = edges[i].ye - edges[i].yb;
		if (length > maxLength)
		{
			maxLength = length;
			EdgeL = i;
		}
	}

	int EdgeOneS, EdgeTwoS;

	if (edges[(EdgeL + 1) % 3].yb > edges[(EdgeL + 2) % 3].yb)
	{
		EdgeTwoS = (EdgeL + 1) % 3;
		EdgeOneS = (EdgeL + 2) % 3;
	}

	else
	{
		EdgeOneS = (EdgeL + 1) % 3;
		EdgeTwoS = (EdgeL + 2) % 3;
	}

	while (edges[EdgeL].y < edges[EdgeL].ye)
	{
		int obsoleteY = edges[EdgeL].y;

		while (edges[EdgeL].y == obsoleteY)
		{
			Increment(edges[EdgeL]);
		}

		if (edges[EdgeL].y <= edges[EdgeOneS].ye)
		{
			while (edges[EdgeL].y > edges[EdgeOneS].y)
			{
				Increment(edges[EdgeOneS]);
			}

			scanline(Scanline(edges[EdgeOneS].x, edges[EdgeL].x, edges[EdgeL].y));
		}
		else
		{
			while (edges[EdgeL].y > edges[EdgeTwoS].y)
			{
				Increment(edges[EdgeTwoS]);
			}

			scanline(Scanline(edges[EdgeTwoS].x, edges[EdgeL].x, edges[EdgeL].y));
		}
	}
}

//WIP
void Rasterizer::Perspective(vector3D &vOne, vector3D &vTwo, vector3D &vThree)
{
	wOne = 1 / vOne.vecOrigin[3];
	wTwo = 1 / vTwo.vecOrigin[3];
	wThree = 1 / vThree.vecOrigin[3];

	vOne.vecOrigin[0] = ((vOne.vecOrigin[0] * wOne + 1) / 2) * window_Width;
	vOne.vecOrigin[1] = ((vOne.vecOrigin[1] * wOne + 1) / 2) * window_Height;
	vOne.vecOrigin[2] = vOne.vecOrigin[2] * wOne;

	vTwo.vecOrigin[0] = ((vTwo.vecOrigin[0] * wTwo + 1) / 2) * window_Width;
	vTwo.vecOrigin[1] = ((vTwo.vecOrigin[1] * wTwo + 1) / 2) * window_Height;
	vTwo.vecOrigin[2] = vTwo.vecOrigin[2] * wTwo;

	vThree.vecOrigin[0] = ((vThree.vecOrigin[0] * wThree + 1) / 2) * window_Width;
	vThree.vecOrigin[1] = ((vThree.vecOrigin[1] * wThree + 1) / 2) * window_Height;
	vThree.vecOrigin[2] = vThree.vecOrigin[2] * wThree;
}

//WIP
void Rasterizer::Barycentric(vector2D p, vector2D a, vector2D b, vector2D c, float& u, float& v, float& w)
{
	vector2D vZero = b - a;
	vector2D vOne = c - a;
	vector2D vTwo = p - a;

	float D00 = vZero.dotProd(vZero);
	float D01 = vZero.dotProd(vOne);
	float D11 = vOne.dotProd(vOne);
	float D20 = vTwo.dotProd(vZero);
	float D21 = vTwo.dotProd(vOne);
	float denom = D00 * D11 - D01 * D01;
	v = (D11 * D20 - D01 * D21) / denom;
	w = (D00 * D21 - D01 * D20) / denom;
	u = 1.0f - v - w;
}

//WIP
void Rasterizer::scanline(const Scanline& scan)
{
	int diffX = scan.xEnd - scan.xBegin;

	if (diffX == 0)
	{
		return;
	}

	for (int x = scan.xBegin; x <= scan.xEnd; x++)
	{
		float u, v, w;
		Barycentric(vector2D(x, scan.Y), vector2D(rastVertexOne.vecOrigin[0], rastVertexOne.vecOrigin[1]), vector2D(rastVertexTwo.vecOrigin[0], rastVertexTwo.vecOrigin[1]), vector2D(rastVertexThree.vecOrigin[0], rastVertexThree.vecOrigin[1]), u, v, w);
		float corrW = (u * wOne + v * wTwo + w * wThree);
		float zPixel = ((rastVertexOne.vecOrigin[2] * u) + (rastVertexTwo.vecOrigin[2] * v) + (rastVertexThree.vecOrigin[2] * w));

		int index = (scan.Y * window_Width + x);

		if (index < 0 || index >= (window_Width * window_Height))
		{
			continue;
		}

		if (zDepth[index] > zPixel)
		{
			continue;
		}

		zDepth[index] = zPixel;

		//TEST VERSION
		vector2D texture = (((rastUVOne * u) * wOne), ((rastUVTwo * v) * wTwo) / corrW);
		vector3D normal = ((rastNormOne * u) * wOne + (rastNormTwo * v) * wTwo + (rastNormThree * w) * wThree) / corrW;
		vector3D diff = ((rastDiffColorOne * u) * wOne + (rastDiffColorTwo * v) * wTwo + (rastDiffColorThree * w) * wThree) / corrW;

		//ORIGINAL
		/*vector2D texture = ((uvOne * u) * wOne + (uvTwo * v) * wTwo + (uvThree * w) * wThree) / corrW;
		vector3D normal = ((normOne * u) * wOne + (normTwo * v) * wTwo + (normThree * w) * wThree) / corrW;
		vector3D diff = ((diffColorOne * u) * wOne + (diffColorTwo * v) * wTwo + (diffColorThree * w) * wThree) / corrW;*/

		PixelColor col = pixelShader({ texture.vecOrigin[0], 1 - texture.vecOrigin[1] }, normal, image, this->w, this->h, n);

		//PixelColor col = fragments(texture, normal, image, this->w, this->h, n);

		/* ALL WHITE */
		/*col.r = std::min(255.0f, 255.0f);
		col.g = std::min(255.0f, 255.0f);
		col.b = std::min(255.0f, 255.0f);*/

		/* Some blue */
		/*col.r = texture.vecOrigin[0] * 255;
		col.g = texture.vecOrigin[1] * 255;
		col.b = 255;*/

		/* USE THIS AS FINAL */
		col.r = ((col.r * diff.vecOrigin[0]), (col.r * diff.vecOrigin[0]));
		col.g = ((col.g * diff.vecOrigin[1]), (col.g * diff.vecOrigin[1]));
		col.b = ((col.b * diff.vecOrigin[2]), (col.b * diff.vecOrigin[2]));

		if ((scan.Y * window_Width + x) < 0)
		{
			continue;
		}
		else if ((scan.Y * window_Width + x) >= window_Width * window_Height)
		{
			continue;
		}

		if (x > 0 && x < window_Width)
		{
			this->pixels[index] = col;
		}
	}
}

//WIP
Rasterizer::Scanline::Scanline(int xOne, int xTwo, int y)
{
	if (xOne > xTwo)
	{
		xBegin = xTwo, xEnd = xOne;
	}
	else
	{
		xBegin = xOne, xEnd = xTwo;
	}

	Y = y;
}

//WIP
Rasterizer::Edge::Edge(vector3D vOne, vector3D vTwo)
{
	if (vOne.vecOrigin[1] < vTwo.vecOrigin[1])
	{
		xb = vOne.vecOrigin[0];
		yb = vOne.vecOrigin[1];
		xe = vTwo.vecOrigin[0];
		ye = vTwo.vecOrigin[1];
	}
	else
	{
		xb = vTwo.vecOrigin[0];
		yb = vTwo.vecOrigin[1];
		xe = vOne.vecOrigin[0];
		ye = vOne.vecOrigin[1];
	}

	dx = (xe - xb);
	dy = (ye - yb);

	if (dx >= 0)
	{
		if (dy > dx)
		{
			oct = OctantTwo;
			std::swap(dx, dy);
		}
		else
		{
			oct = OctantOne;
		}
	}
	else
	{
		if (dy > -dx)
		{
			oct = OctantThree;
			std::swap(dx, dy);
		}
		else
		{
			oct = OctantFour;
		}
	}

	dx = abs(dx);
	dy = abs(dy);

	d = 2 * dy - dx;
	e = 2 * dy;
	ne = 2 * (dy - dx);

	x = xb;
	y = yb;
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

//WIP
void Rasterizer::Draw()
{
	const vector<Mesh::Vertex>& meshData = this->meshPTR->vertices;

	for (int i = 0; i < this->meshPTR->indices.size(); i += 3)
	{
		vector3D vOne(meshData[this->meshPTR->indices[i]].pos.vecOrigin[0], meshData[this->meshPTR->indices[i]].pos.vecOrigin[1], meshData[this->meshPTR->indices[i]].pos.vecOrigin[2]);
		vector3D vTwo(meshData[this->meshPTR->indices[i + 1]].pos.vecOrigin[0], meshData[this->meshPTR->indices[i + 1]].pos.vecOrigin[1], meshData[this->meshPTR->indices[i + 1]].pos.vecOrigin[2]);
		vector3D vThree(meshData[this->meshPTR->indices[i + 2]].pos.vecOrigin[0], meshData[this->meshPTR->indices[i + 2]].pos.vecOrigin[1], meshData[this->meshPTR->indices[i + 2]].pos.vecOrigin[2]);

		vector2D uOne(meshData[this->meshPTR->indices[i]].texCoord.vecOrigin[0], meshData[this->meshPTR->indices[i]].texCoord.vecOrigin[1]);
		vector2D uTwo(meshData[this->meshPTR->indices[i + 1]].texCoord.vecOrigin[0], meshData[this->meshPTR->indices[i + 1]].texCoord.vecOrigin[1]);
		vector2D uThree(meshData[this->meshPTR->indices[i + 2]].texCoord.vecOrigin[0], meshData[this->meshPTR->indices[i + 2]].texCoord.vecOrigin[1]);

		vector3D nOne(meshData[this->meshPTR->indices[i]].norm.vecOrigin[0], meshData[this->meshPTR->indices[i]].norm.vecOrigin[1], meshData[this->meshPTR->indices[i]].norm.vecOrigin[2]);
		vector3D nTwo(meshData[this->meshPTR->indices[i + 1]].norm.vecOrigin[0], meshData[this->meshPTR->indices[i + 1]].norm.vecOrigin[1], meshData[this->meshPTR->indices[i + 1]].norm.vecOrigin[2]);
		vector3D nThree(meshData[this->meshPTR->indices[i + 2]].norm.vecOrigin[0], meshData[this->meshPTR->indices[i + 2]].norm.vecOrigin[1], meshData[this->meshPTR->indices[i + 2]].norm.vecOrigin[2]);

		rastVertexOne = projection * transform * vOne;
		rastVertexTwo = projection * transform * vTwo;
		rastVertexThree = projection * transform * vThree;

		Perspective(rastVertexOne, rastVertexTwo, rastVertexThree);

		rastUVOne = uOne;
		rastUVTwo = uTwo;

		rastNormOne = nOne;
		rastNormTwo = nTwo;
		rastNormThree = nThree;

		rastDiffColorOne = vertexShader(meshData[this->meshPTR->indices[i]].pos, meshData[this->meshPTR->indices[i]].norm, transform);
		rastDiffColorTwo = vertexShader(meshData[this->meshPTR->indices[i + 1]].pos, meshData[this->meshPTR->indices[i + 1]].norm, transform);
		rastDiffColorThree = vertexShader(meshData[this->meshPTR->indices[i + 2]].pos, meshData[this->meshPTR->indices[i + 2]].norm, transform);

		Rasterize(rastVertexOne, rastVertexTwo, rastVertexThree);
	}
}

//Clear the screen from previous data
void Rasterizer::Clear() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//DONE
void Rasterizer::Bind()
{
	shaderPTR->Bind();
	meshPTR->Bind();

	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}
}

//DONE
void Rasterizer::Unbind()
{
	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}

	meshPTR->Unbind();
	shaderPTR->Unbind();
}

//DONE
void Rasterizer::MouseScan()
{
	if (controlAccess)
	{
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
	}

	//ACTIVATE COMMANDS FOR CAMERA
	if (GetAsyncKeyState(RMB) & 0x8000 && !RMB_DOWN)
		RMB_DOWN = true;

	else if (GetAsyncKeyState(RMB) & 0x8000 && RMB_DOWN) {}

	else
		RMB_DOWN = false;

	//MMB
	if (GetAsyncKeyState(MMB) & 0x8000 && !MMB_DOWN)
		MMB_DOWN = true;

	else if (!(GetAsyncKeyState(MMB) & 0x8000) && MMB_DOWN)
		MMB_DOWN = false;
}

//DONE
void Rasterizer::KeyboardScan()
{
	if (controlAccess)
	{
		//MOVE MODEL IF LMB IS DOWN
		if (GetAsyncKeyState('W') & 0x8000 && LMB_DOWN)
			moveY += 0.15f;

		if (GetAsyncKeyState('A') & 0x8000 && LMB_DOWN)
			moveX -= 0.1f;

		if (GetAsyncKeyState('S') & 0x8000 && LMB_DOWN)
			moveY -= 0.15f;

		if (GetAsyncKeyState('D') & 0x8000 && LMB_DOWN)
			moveX += 0.1f;

		if (GetAsyncKeyState('Q') & 0x8000 && LMB_DOWN)
			moveZ -= 0.15f;

		if (GetAsyncKeyState('E') & 0x8000 && LMB_DOWN)
			moveZ += 0.1f;
	}

	//MOVE CAMERA IF RMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && RMB_DOWN)
		camY += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && RMB_DOWN)
		camX -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && RMB_DOWN)
		camY -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && RMB_DOWN)
		camX += 0.1f;

	if (GetAsyncKeyState('Q') & 0x8000 && RMB_DOWN)
		camZ -= 0.06f;

	if (GetAsyncKeyState('E') & 0x8000 && RMB_DOWN)
		camZ += 0.06f;

	//MOVE LIGHT IF MMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[1] += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[0] -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[1] -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[0] += 0.1f;

	if (GetAsyncKeyState('Q') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[2] -= 0.15f;

	if (GetAsyncKeyState('E') & 0x8000 && MMB_DOWN)
		lightPTR->currentLight.Position.vecOrigin[2] += 0.1f;

	//SET DIFFUSE AND AMBIENT INTENSITY
	if (GetAsyncKeyState('I') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.AmbientIntensity < 1.0f)
		{
			lightPTR->currentLight.AmbientIntensity += 0.01f;
			cout << "Ambient Intensity: " << lightPTR->currentLight.AmbientIntensity << endl;
		}
	}

	if (GetAsyncKeyState('J') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.DiffuseIntensity > 0.0f)
		{
			lightPTR->currentLight.DiffuseIntensity -= 0.01f;
			cout << "Diffusee Intensity: " << lightPTR->currentLight.DiffuseIntensity << endl;
		}
	}

	if (GetAsyncKeyState('K') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.AmbientIntensity > 0.0f)
		{
			lightPTR->currentLight.AmbientIntensity -= 0.01f;
			cout << "Ambient Intensity: " << lightPTR->currentLight.AmbientIntensity << endl;
		}
	}

	if (GetAsyncKeyState('L') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.DiffuseIntensity < 1.0f)
		{
			lightPTR->currentLight.DiffuseIntensity += 0.01f;
			cout << "Diffusee Intensity: " << lightPTR->currentLight.DiffuseIntensity << endl;
		}
	}

	//SET SPECULAR INTENSITY
	if (GetAsyncKeyState('Z') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.SpecularIntensity > 0.0f)
		{
			lightPTR->currentLight.SpecularIntensity -= 0.01f;
			cout << "Specular Intensity: " << lightPTR->currentLight.SpecularIntensity << endl;
		}
	}

	if (GetAsyncKeyState('X') & 0x8000 && MMB_DOWN)
	{
		if (lightPTR->currentLight.SpecularIntensity < 1.0f)
		{
			lightPTR->currentLight.SpecularIntensity += 0.01f;
			cout << "Specular Intensity: " << lightPTR->currentLight.SpecularIntensity << endl;
		}
	}

	//SWITCH COLOR
	if (GetAsyncKeyState('C') < 0 && MMB_DOWN && !C_DOWN)
	{
		switch (colorCounter)
		{
			//RED
		case 0:
			lightPTR->currentLight.Diffuse.vecOrigin[0] = 0.3f;
			lightPTR->currentLight.Diffuse.vecOrigin[1] = 0.0f;
			lightPTR->currentLight.Diffuse.vecOrigin[2] = 0.0f;

			lightPTR->currentLight.Specular.vecOrigin[0] = 0.5f;
			lightPTR->currentLight.Specular.vecOrigin[1] = 0.0f;
			lightPTR->currentLight.Specular.vecOrigin[2] = 0.0f;
			break;

			//GREEN
		case 1:
			lightPTR->currentLight.Diffuse.vecOrigin[0] = 0.0f;
			lightPTR->currentLight.Diffuse.vecOrigin[1] = 0.3f;
			lightPTR->currentLight.Diffuse.vecOrigin[2] = 0.0f;

			lightPTR->currentLight.Specular.vecOrigin[0] = 0.0f;
			lightPTR->currentLight.Specular.vecOrigin[1] = 0.5f;
			lightPTR->currentLight.Specular.vecOrigin[2] = 0.0f;
			break;

			//BLUE
		case 2:
			lightPTR->currentLight.Diffuse.vecOrigin[0] = 0.0f;
			lightPTR->currentLight.Diffuse.vecOrigin[1] = 0.0f;
			lightPTR->currentLight.Diffuse.vecOrigin[2] = 0.3f;

			lightPTR->currentLight.Specular.vecOrigin[0] = 0.0f;
			lightPTR->currentLight.Specular.vecOrigin[1] = 0.0f;
			lightPTR->currentLight.Specular.vecOrigin[2] = 0.5f;
			break;

			//WHITE
		case 3:
			lightPTR->currentLight.Diffuse.vecOrigin[0] = 0.3f;
			lightPTR->currentLight.Diffuse.vecOrigin[1] = 0.3f;
			lightPTR->currentLight.Diffuse.vecOrigin[2] = 0.3f;

			lightPTR->currentLight.Specular.vecOrigin[0] = 0.5f;
			lightPTR->currentLight.Specular.vecOrigin[1] = 0.5f;
			lightPTR->currentLight.Specular.vecOrigin[2] = 0.5f;
			break;
		}

		colorCounter++;

		if (colorCounter > 3)
			colorCounter = 0;

		C_DOWN = true;
	}

	if (GetAsyncKeyState('C') == 0 && C_DOWN)
		C_DOWN = false;
}

void Rasterizer::Flush()
{
	//memset(&pixels[0], 0, sizeof(pixels[0]) * pixels.size());
	//zDepth.assign(width * height, 0);
}