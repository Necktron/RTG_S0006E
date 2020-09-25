#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Framebuffer.h"
#include <memory>
#include <string>
#include <sstream>
#include <iostream>
#include <functional>
#include <Windows.h>

/*
	SOURCES OF GUIDES AND INFO FOR RASTERIZER:
		- FBO: https://www.khronos.org/opengl/wiki/Framebuffer_Object
		- LAMBDA FUNCTIONS: https://www.youtube.com/watch?v=mWgmBBz0y8c
		- RASTERIZATION TUTORIAL: https://www.youtube.com/watch?v=t7Ztio8cwqM
		- BRESENHAM ALGORITHM: https://www.thecrazyprogrammer.com/2017/01/bresenhams-line-drawing-algorithm-c-c.html

*/

class Rasterizer
{
public:
	unsigned int window_Width, window_Height;
	matrix3D transform;
	shared_ptr<Mesh> meshPTR;
	shared_ptr<Texture> texturePTR;
	FrameBuffer* renderTarget;
	bool controlAccess;

	//Octant
	enum Octant
	{
		OctantOne,
		OctantTwo,
		OctantThree,
		OctantFour
	};

	//Pixel Color
	struct PixelColor
	{
		unsigned char r = 0;
		unsigned char g = 0;
		unsigned char b = 0;
	};

	//Scanline
	class Scanline
	{
	public:
		Scanline(int xOne, int xTwo, int y);
		int xBegin, xEnd, Y;
	};

	//Edge
	class Edge
	{
	public:
		Edge(vector3D vOne, vector3D vTwo);

		Octant oct;
		int x, y, xb, xe, yb, ye, d, dy, dx, e, ne;
	};

	Rasterizer();
	Rasterizer(unsigned int resX, unsigned int resY);
	~Rasterizer();

	void Update(); //Update values for color anim, rot, etc

	//Similar to Renderer functions
	void SetMesh(Mesh::OBJ obj); //Set a mesh from the pre-defined types, triangle / quad / cube
	void SetTexture(Texture::TextureImage texture); //Set texture from a specific path
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform

	//Rasterizer specific
	void SetupFrameBuffer(); // Setup FBO with arbitrary dimensions - DONE
	int* GetFrameBufferPointer(); //Retrieve a pointer to the FBO - DONE
	string GetFrameBufferSize(); //Retrieve the size of the FBO - DONE
	vector<Rasterizer::PixelColor> GetPixel(); //Get pixel value - WIP
	void SetVertexShader(const function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)>& func); //Set vertex shader by lambda function as argument - DONE
	void SetPixelShader(const function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)>& func); //Set pixel shader by lambda function as argument - DONE

	//Rasterizer logic
	void Rasterize(vector3D v1, vector3D v2, vector3D v3);
	void scanline(const Scanline& scan);
	void Increment(Edge& edge);
	void Barycentric(vector2D p, vector2D a, vector2D b, vector2D c, float& u, float& v, float& w);
	void Perspective(vector3D& vOne, vector3D& vTwo, vector3D& vThree);
	vector<Rasterizer::PixelColor> PixelRetriver();

	//Render
	void Draw(); //Draw to the FBO - WIP
	void Clear() const; //Clear the screen from previous data - WIP
	void Flush(); //WIP

	void Bind();
	void Unbind();

	//MODEL
	vector3D pos;
	vector3D scale;
	vector3D rotVec;
	vector3D oldRotVec;

private:
	float rotFloat;
	float rotSpeed;
	float angleOfRot;

	matrix3D view;
	matrix3D projection;
	matrix3D MVP;

	int leftY, rightY, bottomY, leftX, rightX, bottomX;
	vector3D vertexOne, vertexTwo, vertexThree;
	vector2D uvOne, uvTwo, uvThree;
	vector3D normOne, normTwo, normThree;
	vector3D diffColorOne, diffColorTwo, diffColorThree;
	vector<Mesh::Vertex> rasterVerticies;
	vector<unsigned int> indices;
	vector<PixelColor> pixels;

	//Functions
	function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)> vertexShader;
	function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)> pixelShader;

	vector<float> zDepth;
	int W, H, N;
	float wOne, wTwo, wThree;
	unsigned char* image;
};