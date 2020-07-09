#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include <memory>

class Renderer
{
public:
	int window_Width;
	int window_Height;

	std::shared_ptr<Mesh> meshPTR;
	std::shared_ptr<Texture> texturePTR;
	std::shared_ptr<Shader> shaderPTR;

	//Setup and handle
	void Init();
	void ConfigUniforms();
	void InputScan();

	//Set functions
	void SetMesh(const char* filepath); //Set a mesh from file path
	void SetMesh(int meshType); //Set a mesh from predefined types
	void SetTexture();
	void SetShader();
	void SetTransform(int option, vector3D values); //Set a specific part of the transform
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform

	void GetMesh(); //Get current mesh
	void GetTexture(); //Get current texture
	void GetShader(); //Get current shader
	void GetTransform(); //Get everything from the transform
	void GetTransform(int option); //Get a specific part of the transform

	//Rendering
	void Draw();
	void Clear() const;

	void Bind();
	void Unbind();

private:
	vector3D color;
	matrix3D transform;
	matrix3D view;
	matrix3D projection;
	matrix3D MVP;
	float rot;
	float rotSpeed;
	float angleOfRot;
	float incrementRGB;
	float incrementPOSX;
	float incrementPOSZ;
};