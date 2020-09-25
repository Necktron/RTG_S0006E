#pragma once
#include "Light.h"
#include "Entity.h"
#include <memory>
#include <Windows.h>

class Renderer
{
public:
	int window_Width;
	int window_Height;

	vector<Entity> entityList;
	Light* lightPTR;

	//Setup and handle
	Renderer();
	Renderer(float resX, float resY);
	~Renderer();

	void Update(); //Update values for color anim, rot, etc
	void AddEntity(Entity ent);
	vector<Entity> GetEntityList();

	//Set functions
	void SetLightPos(vector3D pos);
	void SetCamPos(vector3D origin);
	void SetView(vector3D origin, vector3D target);
	void SetProjection(float FOV);

	//Get functions
	matrix3D GetMVP(matrix3D transform);
	matrix3D GetModelView(matrix3D transform); //Get View Model for current Entity
	matrix3D GetProj();
	Light* GetLightRef();

	//Rendering
	void Draw(); //Draw all data to the screen
	void Clear() const; //Clear the screen from previous data

	//CAMERA
	vector3D camPos;
	vector3D camTargetPos;

private:
	void Bind(int index); //Bind buffers for render
	void Unbind(int index); //Unbind data so other Renderers can Bind() their data and spare memory

	matrix3D view;
	matrix3D projection;

	//CAMERA
	float FOV;

	float oldRotX;
	float oldRotY;
	vector3D oldCamTargetPos;

	float incrementRGB;
	vector3D colorRGB;
};