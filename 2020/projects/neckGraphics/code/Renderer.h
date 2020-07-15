#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include <memory>
#include <Windows.h>

class Renderer
{
public:
	int window_Width;
	int window_Height;

	std::shared_ptr<Mesh> meshPTR;
	std::shared_ptr<Texture> texturePTR;
	std::shared_ptr<Shader> shaderPTR;

	//Setup and handle
	void Init(float resX, float resY); //Init all components
	void Update(); //Update values for color anim, rot, etc
	void InputScan();

	//Set functions
	void SetMesh(int meshType); //Set a mesh from the pre-defined types, triangle / quad / cube
	void SetMesh(const char* filepath); //Set a mesh from file path, load OBJ, next assignment
	void SetTexture(Texture::TextureImage); //Set texture from a specific path
	void SetShader(Shader::ShaderEffect); //Set shader from a specific path
	void SetStartTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetView(vector3D origin, vector3D target);
	void SetProjection(float FOV);

	//Get functions
	Mesh GetMesh(); //Get current mesh
	Texture GetTexture(); //Get current texture
	Shader GetShader(); //Get current shader
	matrix3D GetTransform(); //Get everything from the transform

	//Rendering
	void Draw(); //Draw all data to the screen
	void Clear() const; //Clear the screen from previous data

private:
	void Bind(); //Bind buffers for render
	void Unbind(); //Unbind data so other Renderers can Bind() their data and spare memory

	void MouseScan();
	void KeyboardScan();

	vector3D rotation;

	matrix3D transform;
	matrix3D view;
	matrix3D projection;
	matrix3D MVP;
	float rot;
	float rotSpeed;
	float angleOfRot;
	float incrementRGB;
	float moveX;
	float moveY;
	float moveZ;
	float rotX;
	float rotY;
	float rotZ;
	float r;
	float g;
	float b;

	float initPosX;
	float initPosY;
	float initPosZ;

	float initScaleX;
	float initScaleY;
	float initScaleZ;

	float initRotX;
	float initRotY;
	float initRotZ;

	float zoomCam;
};