#define LMB 0x0001
#define RMB 0x0002
#define MMB 0x0004
#define JOBS_DONE ShellExecute(NULL, "open", "https://www.youtube.com/watch?v=5r06heQ5HsI", NULL, NULL, SW_SHOWNORMAL);

//Testing
#include <iostream>
#include <chrono>

#include "Rasterizer.h"

//Default constructor
Rasterizer::Rasterizer()
{
	window_Width = 256;
	window_Height = 256;

	meshPTR = make_shared<Mesh>();
	texturePTR = make_shared<Texture>();
	controlAccess = false;

	PixelColor col;
	col.r = 0;
	col.g = 0;
	col.b = 0;

	this->view = matrix3D::LookAt(vector3D(0, 0, 5), vector3D(0, 0, 0), vector3D(0.0f, 1.0f, 0.0f));
	this->projection = matrix3D::perspectiveProj(90, 256, 256, 0.1f, 100.0f).transpose();

	//W = window_Width;
	//H = window_Height;
	//N = 4;

	pixels.assign(256 * 256, col);
	zDepth.assign(256 * 256, 0.0f);
}

Rasterizer::Rasterizer(unsigned int width, unsigned int height)
{
	window_Width = width;
	window_Height = height;

	meshPTR = make_shared<Mesh>();
	texturePTR = make_shared<Texture>();
	controlAccess = false;

	PixelColor col;
	col.r = 0;
	col.g = 0;
	col.b = 0;

	this->view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
	this->projection = matrix3D::perspectiveProj(90, window_Width, window_Height, 0.1f, 100.0f).transpose();

	W = window_Width;
	H = window_Height;
	//N = 4;

	pixels.assign(window_Width * window_Height, col);
	zDepth.assign(window_Width * window_Height, 0.0f);
}

Rasterizer::~Rasterizer()
{

}

//DONE
void Rasterizer::Update()
{
	//ROT MOVE
	if (this->angleOfRot > 360.0f)
		this->angleOfRot = 0.0f;

	this->angleOfRot += 1.0f;

	this->rotFloat = this->angleOfRot * this->rotSpeed;

	SetTransform(this->pos, this->scale, this->rotVec);

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
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
		meshPTR->CustomMesh("resources/meshes/cat.obj");
		break;

		//Stool
	case 5:
		meshPTR->CustomMesh("resources/meshes/Stool.obj");
		break;

		//CUBE
	case 6:
		meshPTR->CustomMesh("resources/meshes/cubeLow.obj");
		break;

		//WINDMILL
	case 7:
		meshPTR->CustomMesh("resources/meshes/windmill.obj");
		break;

		//PENGUIN
	case 8:
		meshPTR->CustomMesh("resources/meshes/Penguin.obj");
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
		texturePTR->SetupTexture("resources/textures/YellowBrickWall.jpg");
		this->image = stbi_load("resources/textures/YellowBrickWall.jpg", &W, &H, &N, 0);
		break;

	case 1:
		texturePTR->SetupTexture("resources/textures/TurquoiseWoodWall.jpg");
		this->image = stbi_load("resources/textures/TurquoiseWoodWall.jpg", &W, &H, &N, 0);
		break;

	case 2:
		texturePTR->SetupTexture("resources/textures/KoreanFlag.png");
		this->image = stbi_load("resources/textures/KoreanFlag.png", &W, &H, &N, 0);
		break;

	case 3:
		texturePTR->SetupTexture("resources/textures/Blueberries.jpg");
		this->image = stbi_load("resources/textures/Blueberries.jpg", &W, &H, &N, 0);
		break;

	case 4:
		texturePTR->SetupTexture("resources/textures/OpenGLLogo.png");
		this->image = stbi_load("resources/textures/OpenGLLogo.png", &W, &H, &N, 0);
		break;

	case 5:
		texturePTR->SetupTexture("resources/textures/InstaTransparent.png");
		this->image = stbi_load("resources/textures/InstaTransparent.png", &W, &H, &N, 0);
		break;

		//CAT
	case 6:
		texturePTR->SetupTexture("resources/textures/cat_diff.tga");
		this->image = stbi_load("resources/textures/cat_diff.tga", &W, &H, &N, 0);
		break;

	case 7:
		texturePTR->SetupTexture("resources/textures/IKEA.jpg");
		this->image = stbi_load("resources/textures/IKEA.jpg", &W, &H, &N, 0);
		break;

	case 8:
		texturePTR->SetupTexture("resources/textures/Richard.jpg");
		this->image = stbi_load("resources/textures/Richard.jpg", &W, &H, &N, 0);
		break;

	case 9:
		texturePTR->SetupTexture("resources/textures/Micke.jpg");
		this->image = stbi_load("resources/textures/Micke.jpg", &W, &H, &N, 0);
		break;

		//BOX
	case 10:
		texturePTR->SetupTexture("resources/textures/cubeLow.jpg");
		this->image = stbi_load("resources/textures/cubeLow.jpg", &W, &H, &N, 0);
		break;

		//WINDMILL
	case 11:
		texturePTR->SetupTexture("resources/textures/windmill.jpg");
		this->image = stbi_load("resources/textures/windmill.jpg", &W, &H, &N, 0);
		break;

		//WINDMILL
	case 12:
		texturePTR->SetupTexture("resources/textures/Penguin.png");
		this->image = stbi_load("resources/textures/Penguin.png", &W, &H, &N, 0);
		break;
	}

	this->texturePTR->textureImage = texture;
}

//Set the transform of the model with Position / Scale / Rotation directions
void Rasterizer::SetTransform(vector3D pos, vector3D scale, vector3D rot)
{
	this->pos = pos;
	this->scale = scale;
	this->rotVec = rot;

	this->transform = matrix3D::translate(this->pos) * matrix3D::scale(this->scale) * matrix3D::mxRotX(this->rotVec.vecOrigin[0]) * matrix3D::mxRotY(this->rotVec.vecOrigin[1]) * matrix3D::mxRotZ(this->rotVec.vecOrigin[2]);
}

//WIP
void Rasterizer::SetupFrameBuffer()
{
	renderTarget = new FrameBuffer(256, 256);
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

	//INVESTIGATE THIS
	while (edges[EdgeL].y < edges[EdgeL].ye)
	{
		//printf("%i : ", edges[EdgeL].y);
		//printf("%i \n", edges[EdgeL].ye);

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

		PixelColor col = pixelShader({ texture.vecOrigin[0], 1 - texture.vecOrigin[1] }, normal, image, 256, 256, 3);

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
		else if ((scan.Y * window_Height + x) >= window_Width * window_Height)
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
void Rasterizer::Barycentric(vector2D p, vector2D a, vector2D b, vector2D c, float &u, float &v, float &w)
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

	auto start = chrono::steady_clock::now();

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

		vertexOne = projection * transform * vOne;
		vertexTwo = projection * transform * vTwo;
		vertexThree = projection * transform * vThree;

		//INVESTIGATE

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

		Rasterize(vertexOne, vertexTwo, vertexThree);
	}

	//TODO: Check so rasterization actually works 100%
	auto end = chrono::steady_clock::now();
	chrono::duration<double> totalTime = end - start;
	printf("Total time: %d", totalTime.count());
	JOBS_DONE;
	printf("Jesus... that's a lot of time!");
	printf("");

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
	renderTarget->Bind();
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
	renderTarget->Unbind();
}

//WIP
void Rasterizer::Flush()
{
	memset(&pixels[0], 0, sizeof(pixels[0]) * pixels.size());
	zDepth.assign(window_Width * window_Height, 0);
}