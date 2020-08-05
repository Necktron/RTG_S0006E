#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include <memory>
#include <Windows.h>

/*
	SOURCES OF GUIDES AND INFO FOR RASTERIZER:
		- FBO: https://www.khronos.org/opengl/wiki/Framebuffer_Object
		- LAMBDA FUNCTIONS: https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=vs-2019

*/

class Rasterizer
{
public:
	int window_Width;
	int window_Height;

	std::shared_ptr<Mesh> meshPTR;
	std::shared_ptr<Texture> texturePTR;
	std::shared_ptr<Shader> shaderPTR;
	std::shared_ptr<Light> lightPTR;

	//Set the Rasterizers Mesh buffer with data, triangle with texture and light applied 
	void SetupRasterizerBuffer(); //Mesh + Texture + Shader + Light source
	void SetupFrameBuffer(); // Setup FBO with arbitrary dimensions
	void GetFrameBufferPointer(); //Retrieve a pointer to the FBO
	void GetFrameBufferSize(); //Retrieve the size of the FBO
	void SetShader(/* INSERT LAMBDA FUNCTION */); //Set vertex and pixel shader by lambda function as argument
	void SetupMVP(); //Set MVP matrix for rasterizer object
	void SetupTexture(); //Set a texture to the triangle
	void IndexToFrame(/* INSERT IBO AS ARGUMENT */); //Write data from IBO to FBO
	void Rasterize(); // Final rasterizing
	void RasterTriangle( /* 3x vertecies with pos, tex, norm */);

	/*
		RASTER TRIANGLE:
			1. Interpolate normals and texture smoothly over the surface, "Barycentric coords"
			2. Raster it using scanline functions. Use Bresenham algorithm
			3. Call vertex shader for each vertex and fragment shader for each pixel, store color results in framebuffer

			To be continued...
	
	*/

	unsigned int fbo; //FBO
};