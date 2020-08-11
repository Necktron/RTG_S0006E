#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
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

*/

class Rasterizer
{
public:
	int window_Width;
	int window_Height;

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

	std::vector<Rasterizer::PixelColor> pixelRetriver();

	shared_ptr<Texture> texturePTR;
	shared_ptr<Shader> shaderPTR;
	shared_ptr<Light> lightPTR;
	shared_ptr<unsigned int> fboPTR;

	//PART 1.
	//Set the Rasterizers Mesh buffer with data, triangle with texture and light applied 
	void Init(float x, float y); //DONE
	void SetupRasterizerBuffer(); //Mesh + Texture + Shader + Light source - DONE
	void SetupFrameBuffer(); // Setup FBO with arbitrary dimensions - DONE
	unsigned int* GetFrameBufferPointer(); //Retrieve a pointer to the FBO - DONE
	string GetFrameBufferSize(); //Retrieve the size of the FBO - DONE
	void SetVertexShader(const function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)>& func); //Set vertex shader by lambda function as argument - DONE
	void SetPixelShader(const function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)>& func); //Set pixel shader by lambda function as argument - DONE
	void SetupMVP(); //Set MVP matrix for rasterizer object - DONE
	void SetupTexture(Texture::TextureImage texture); //Set a texture to the triangle - DONE
	void IndexToFrame(/* INSERT IBO AS ARGUMENT */); //CALLS FUNCTION BELOW FOR EACH TRIANGLE
	void Rasterize( /* 3x vertecies with pos, tex, norm */); //REQUIERED VS AND FS SET
	bool ToggleFrameBuffer(); //DONE
	void Draw();
	void Flush();
	
	/*
		PART 2 - RASTER TRIANGLE:
			1. Interpolate normals and texture smoothly over the surface, "Barycentric coords"
			2. Raster it using scanline functions. Use Bresenham algorithm
			3. Call vertex shader for each vertex and fragment shader for each pixel, store color results in framebuffer

			To be continued...

		PART 3 - SetVertexShader - "DONE", make sure it works
			1. Take a single vertex with 3D pos, TexCoord and normal
			2. Transform vertex attributes using MVP matrix
			3. Return data needed for Pixel Shader

		PART 4 - SetPixelShader - "DONE", make sure it works
			1. Take TexCoord, Normal and Texture as argument
			2. Return a pixel color
			3. Shader it with Blinn-Phong
			4. Texture it with the texture provided

		PART 5 - Frame Buffer
			Have a accompanying z-Buffer used for depth test to discard useless pixels

		PART 6 - Add clipping
			1. RasterTriangle will discard pixels outside of the view
			2. (OPTIONAL) - The draw function should discard any triangles that are entirely outside the view

		PART 7 - Functionality for move and rotation of the rasterizer OBJ
			* TODO: Copy / Paste code from Renderer class

		PART 8 - Render the Rasterizer OBJ framebuffer onto a quad as a texture
			Add this code:
			* rastPTR->draw(MatrixA, MatrixRasterizer); // Render the RastOBJ
			* texPTR->loadFromRast(rastPTR); //Set the texture of the Quad
	*/

	//Transform and such
	vector3D rotation;
	matrix3D transform;
	matrix3D view;
	matrix3D projection;
	matrix3D MVP;

	unsigned int vbo; //VBO
	unsigned int vao; //VAO
	unsigned int ibo; //IBO

	unsigned int fbo; //FBO
	unsigned int tcb; //Texture Color Buffer
	unsigned int rbo; //Render Buffer Object

	//Functions
	function<vector3D(vector3D pos, vector3D normal, matrix3D normalMatrix)> vertexShader;
	function<PixelColor(vector2D texture, vector3D normal, unsigned char* image, int w, int h, int n)> pixelShader;

private:
	bool frameBufferToggle;
};