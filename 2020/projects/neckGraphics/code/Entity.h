#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"

class Entity
{
public:
	//Entity variables
	string entityName;
	matrix3D transform;
	matrix3D MVP;
	shared_ptr<Mesh> meshPTR;
	shared_ptr<Texture> texturePTR;
	shared_ptr<Shader> shaderPTR;
	bool controlAccess;

	Entity(string name);
	~Entity();

	void Update(matrix3D projection, matrix3D view, Light* lightInst, vector3D camPos, vector3D colorRGB);
	void Draw();

	//Set functions
	void SetMesh(Mesh::OBJ); //Set a mesh from the pre-defined types, triangle / quad / cube / custom
	void SetTexture(Texture::TextureImage); //Set texture from a specific path
	void SetShader(Shader::ShaderEffect); //Set shader from a specific path
	void SetTransform(vector3D pos, vector3D scale, vector3D rot); //Set everything for the transform

	//Get functions
	shared_ptr<Mesh> GetMesh(); //Get current mesh
	shared_ptr<Texture> GetTexture(); //Get current texture
	shared_ptr<Shader> GetShader(); //Get current shader
	matrix3D GetTransform(); //Get everything from the transform

	void Bind(); //Bind buffers for render
	void Unbind(); //Unbind data so other Renderers can Bind() their data and spare memory

	//MODEL
	vector3D pos;
	vector3D scale;
	vector3D rotVec;
	vector3D oldRotVec;

private:
	float rotFloat;
	float rotSpeed;
	float angleOfRot;
	float incrementRGB;
};