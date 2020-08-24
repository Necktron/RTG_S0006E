#define LMB 0x0001
#define RMB 0x0002
#define MMB 0x0004

#include "Rasterizer.h"

//DONE
void Rasterizer::Init(string name)
{
	rasterizerName = name;
	meshPTR = make_shared<Mesh>();
	texturePTR = make_shared<Texture>();
	lightPTR = make_shared<Light>();
	frameBufferPTR = make_shared<FrameBuffer>();

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
	FOV = 90.0f;
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
	LMB_DOWN = false;
	MMB_DOWN = false;
	RMB_DOWN = false;
	C_DOWN = false;

	PixelColor col;
	col.r = 0;
	col.g = 0;
	col.b = 0;

	pixels.assign(256 * 256, col);
	zDepth.assign(256 * 256, 0.0f);
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

	//Setup the vital parts for MVP, Model + View + Projection
	SetView(vector3D(camX, camY, camZ), vector3D(camX - camTargetX, camY - camTargetY, camZ - camTargetZ));
	SetTransform(vector3D(initPosX + moveX, initPosX + moveY, initPosZ + moveZ), vector3D(initScaleX, initScaleY, initScaleZ), vector3D(initRotX + rotX, initRotY + rotY, initRotZ + rotZ));
	SetProjection(FOV);

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

//WIP
void Rasterizer::SetupFrameBuffer(unsigned int x, unsigned int y)
{
	frameBufferPTR->CreateFrameBuffer(x, y);
}

//WIP
int* Rasterizer::GetFrameBufferPointer()
{
	int val = GL_VIEWPORT;
	int* pointer = &val;
	return pointer;
}

//WIP
string Rasterizer::GetFrameBufferSize()
{
	string widthHeight;
	GLint dims[4] = { 0 };

	glGetIntegerv(GL_VIEWPORT, dims);
	widthHeight = to_string(dims[2]) + "x" + to_string(dims[3]);

	return widthHeight;
}

//WIP
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

//DONT TOUCH - WORKS
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


//RASTERIZER AREA
//WIP
void Rasterizer::Rasterize(Mesh::Vertex vOne, Mesh::Vertex vTwo, Mesh::Vertex vThree)
{
	Edge edges[3] =
	{
		Edge(vOne.pos, vTwo.pos),
		Edge(vOne.pos, vThree.pos),
		Edge(vThree.pos, vTwo.pos)
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
			Increment(edges[EdgeL]);

		if (edges[EdgeL].y <= edges[EdgeOneS].ye)
		{
			while (edges[EdgeL].y > edges[EdgeOneS].y)
				Increment(edges[EdgeOneS]);

			scanline(Scanline(edges[EdgeOneS].x, edges[EdgeL].x, edges[EdgeL].y));
		}
		else
		{
			while (edges[EdgeL].y > edges[EdgeTwoS].y)
				Increment(edges[EdgeTwoS]);

			scanline(Scanline(edges[EdgeTwoS].x, edges[EdgeL].x, edges[EdgeL].y));
		}
	}
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
		Barycentric(vector2D(x, scan.Y), vector2D(vertexOne.vecOrigin[0], vertexOne.vecOrigin[1]), vector2D(vertexTwo.vecOrigin[0], vertexTwo.vecOrigin[1]), vector2D(vertexThree.vecOrigin[0], vertexThree.vecOrigin[1]), u, v, w);
		float corrW = (u * wOne + v * wTwo + w * wThree);
		float zPixel = ((vertexOne.vecOrigin[2] * u) + (vertexTwo.vecOrigin[2] * v) + (vertexThree.vecOrigin[2] * w));

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
		vector2D texture = (((uvOne * u) * wOne), ((uvTwo * v) * wTwo) / corrW);
		vector3D normal = ((normOne * u) * wOne + (normTwo * v) * wTwo + (normThree * w) * wThree) / corrW;
		vector3D diff = ((diffColorOne * u) * wOne + (diffColorTwo * v) * wTwo + (diffColorThree * w) * wThree) / corrW;

		//ORIGINAL
		/*vector2D texture = ((uvOne * u) * wOne + (uvTwo * v) * wTwo + (uvThree * w) * wThree) / corrW;
		vector3D normal = ((normOne * u) * wOne + (normTwo * v) * wTwo + (normThree * w) * wThree) / corrW;
		vector3D diff = ((diffColorOne * u) * wOne + (diffColorTwo * v) * wTwo + (diffColorThree * w) * wThree) / corrW;*/

		PixelColor col = pixelShader({ texture.vecOrigin[0], 1 - texture.vecOrigin[1] }, normal, image, this->W, this->H, N);

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

//DONT TOUCH - WORKS
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

//DONT TOUCH - WORKS
void Rasterizer::Perspective(vector3D& vOne, vector3D& vTwo, vector3D& vThree)
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
vector<Rasterizer::PixelColor> Rasterizer::PixelRetriver() { return this->pixels; }

//WIP
void Rasterizer::Draw()
{
	/*
		1. Get shape verticies, 3 vertices
		2. Get vertex pos relative to world space / screen space
		3. Examine edges, from A -> B, B -> C, C -> A
		4. Interpolate X(Y) = startPos + (distBetweenStartAndEnd) * (howFarWeTraveled) / (How far are we going to travel)
		5. Save all vertices along the edge
		6. Sort all vertices in vectors for each Y values, from lowest to highest
		
	*/

	Bind();

	const vector<Mesh::Vertex>& meshData = this->meshPTR->vertices;
	indices = this->meshPTR->indices;

	Update();

	for (int i = 0; i < indices.size(); i += 3)
	{
		vector3D vOne(meshData[indices[i]].pos.vecOrigin[0], meshData[indices[i]].pos.vecOrigin[1], meshData[indices[i]].pos.vecOrigin[2]);
		vector3D vTwo(meshData[indices[i + 1]].pos.vecOrigin[0], meshData[indices[i + 1]].pos.vecOrigin[1], meshData[indices[i + 1]].pos.vecOrigin[2]);
		vector3D vThree(meshData[indices[i + 2]].pos.vecOrigin[0], meshData[indices[i + 2]].pos.vecOrigin[1], meshData[indices[i + 2]].pos.vecOrigin[2]);

		vector2D uOne(meshData[indices[i]].texCoord.vecOrigin[0], meshData[indices[i]].texCoord.vecOrigin[1]);
		vector2D uTwo(meshData[indices[i + 1]].texCoord.vecOrigin[0], meshData[indices[i + 1]].texCoord.vecOrigin[1]);
		vector2D uThree(meshData[indices[i + 2]].texCoord.vecOrigin[0], meshData[indices[i + 2]].texCoord.vecOrigin[1]);

		vector3D nOne(meshData[indices[i]].norm.vecOrigin[0], meshData[indices[i]].norm.vecOrigin[1], meshData[indices[i]].norm.vecOrigin[2]);
		vector3D nTwo(meshData[indices[i + 1]].norm.vecOrigin[0], meshData[indices[i + 1]].norm.vecOrigin[1], meshData[indices[i + 1]].norm.vecOrigin[2]);
		vector3D nThree(meshData[indices[i + 2]].norm.vecOrigin[0], meshData[indices[i + 2]].norm.vecOrigin[1], meshData[indices[i + 2]].norm.vecOrigin[2]);

		vertexOne = (view * projection) * transform * vOne;
		vertexTwo = (view * projection) * transform * vTwo;
		vertexThree = (view * projection) * transform * vThree;

		Perspective(vertexOne, vertexTwo, vertexThree);

		uvOne = uOne;
		uvTwo = uTwo;
		uvThree = uThree;

		normOne = nOne;
		normTwo = nTwo;
		normThree = nThree;

		diffColorOne = vertexShader(meshData[indices[i]].pos, meshData[indices[i]].norm, transform);
		diffColorTwo = vertexShader(meshData[indices[i + 1]].pos, meshData[indices[i + 1]].norm, transform);
		diffColorThree = vertexShader(meshData[indices[i + 2]].pos, meshData[indices[i + 2]].norm, transform);

		Mesh::Vertex vA, vB, vC;

		vA.pos = vertexOne;
		vA.texCoord = uvOne;
		vA.norm = normOne;

		vB.pos = vertexTwo;
		vB.texCoord = uvTwo;
		vB.norm = normTwo;

		vC.pos = vertexThree;
		vC.texCoord = uvThree;
		vC.norm = normThree;

		Rasterize(vA, vB, vC);
	}

	Unbind();
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
	frameBufferPTR->Bind();
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
	frameBufferPTR->Unbind();
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

//WIP
void Rasterizer::Flush()
{
	memset(&pixels[0], 0, sizeof(pixels[0]) * pixels.size());
	zDepth.assign(window_Width * window_Height, 0);
}