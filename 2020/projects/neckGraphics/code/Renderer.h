#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Rasterizer.h"
#include <memory>
#include <Windows.h>

class Renderer
{
public:
	int window_Width;
	int window_Height;

	bool controlAccess;

	shared_ptr<Mesh> meshPTR;
	shared_ptr<Texture> texturePTR;
	shared_ptr<Shader> shaderPTR;
	shared_ptr<Light> lightPTR;

	//Setup and handle
	void Init(float resX, float resY, string name); //Init all components
	void Update(); //Update values for color anim, rot, etc
	void InputScan();

	//Set functions
	void SetMesh(Mesh::OBJ); //Set a mesh from the pre-defined types, triangle / quad / cube / custom
	void SetTexture(Texture::TextureImage); //Set texture from a specific path
	void SetRastTexture(shared_ptr<Rasterizer> rastRef);
	void SetShader(Shader::ShaderEffect); //Set shader from a specific path
	void SetLight(Light::LightSource); //Set light source
	void SetStartTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform
	void SetView(vector3D origin, vector3D target);
	void SetProjection(float FOV);

	//Get functions
	shared_ptr<Mesh> GetMesh(); //Get current mesh
	shared_ptr<Texture> GetTexture(); //Get current texture
	shared_ptr<Shader> GetShader(); //Get current shader
	matrix3D GetTransform(); //Get everything from the transform
	
	matrix3D GetMVP();
	matrix3D GetModelView();
	matrix3D GetProj();

	//Rendering
	void Draw(); //Draw all data to the screen
	void Clear() const; //Clear the screen from previous data

private:
	void Bind(); //Bind buffers for render
	void Unbind(); //Unbind data so other Renderers can Bind() their data and spare memory

	void MouseScan();
	void KeyboardScan();

	string renderName;

	vector3D rotation;
	matrix3D transform;
	matrix3D view;
	matrix3D projection;
	matrix3D MVP;
	float rot;
	float rotSpeed;
	float angleOfRot;
	float incrementRGB;
	float r;
	float g;
	float b;

	//MODEL
	float moveX;
	float moveY;
	float moveZ;

	float rotX;
	float rotY;
	float rotZ;

	float initPosX;
	float initPosY;
	float initPosZ;

	float initScaleX;
	float initScaleY;
	float initScaleZ;

	float initRotX;
	float initRotY;
	float initRotZ;

	//CAMERA
	float FOV;
	float camX;
	float camY;
	float camZ;

	float camTargetX;
	float camTargetY;
	float camTargetZ;

	//LIGHT
	float lightX;
	float lightY;
	float lightZ;

	float lightAmbientIntensity;
	float lightDiffuseIntensity;

	int colorCounter;

	bool LMB_DOWN;
	bool RMB_DOWN;
	bool MMB_DOWN;
	bool C_DOWN;
	float oldRotX;
	float oldRotY;
	float oldCamTargetX;
	float oldCamTargetY;
	float oldCamTargetZ;
	POINT mousePosOrigin;
	POINT mousePosCurrent;
};