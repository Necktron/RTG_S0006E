#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include <memory>
#include <Windows.h>

class Rasterizer
{
public:
	int window_Width;
	int window_Height;

	std::shared_ptr<Mesh> meshPTR;
	std::shared_ptr<Texture> texturePTR;
	std::shared_ptr<Shader> shaderPTR;
	std::shared_ptr<Light> lightPTR;

	//Setup and handle
	void Init(float resX, float resY, string name); //Init all components
	void Update(); //Update values for color anim, rot, etc
	void InputScan();
	void InputScanOnlyCamera();

	//Set functions
	void SetMesh(Mesh::OBJ); //Set a mesh from the pre-defined types, triangle / quad / cube / custom
	void SetTexture(Texture::TextureImage); //Set texture from a specific path
	void SetShader(Shader::ShaderEffect); //Set shader from a specific path
	void SetLight(Light::LightSource); //Set light source
	void SetStartTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetView(vector3D origin, vector3D target);
	void SetProjection(float FOV);

	//Get functions
	std::shared_ptr<Mesh> GetMesh(); //Get current mesh
	std::shared_ptr<Texture> GetTexture(); //Get current texture
	std::shared_ptr<Shader> GetShader(); //Get current shader
	matrix3D GetTransform(); //Get everything from the transform

	//Rendering
	void Draw(); //Draw all data to the screen
	void Clear() const; //Clear the screen from previous data
};