#define LMB 0x0001
#define RMB 0x0002
#define MMB 0x0004

#include "Renderer.h"

//Default constructor
Renderer::Renderer()
{
	window_Width = 800;
	window_Height = 600;
	
	lightPTR = new Light;

	view = matrix3D();
	projection = matrix3D();

	//CAMERA
	camPos = vector3D(0, 0, 0);
	camTargetPos = vector3D(0, 0, 1);
	oldCamTargetPos = vector3D(0, 0, 1);
	oldRotX = 0;
	oldRotY = 0;
	FOV = 90;

	//COLOR
	incrementRGB = 1.1f;
	colorRGB = vector3D(0, 0, 0);
}

Renderer::Renderer(float resX, float resY)
{
	lightPTR = new Light;
	lightPTR->PointLight();

	window_Width = resX;
	window_Height = resY;

	view = matrix3D();
	projection = matrix3D();

	//CAMERA
	camPos = vector3D(0, 0, 0);
	camTargetPos = vector3D(0, 0, 1);
	oldCamTargetPos = vector3D(0, 0, 1);
	oldRotX = 0;
	oldRotY = 0;
	FOV = 90;

	//COLOR
	incrementRGB = 1.1f;
	colorRGB = vector3D(0, 0, 0);
}

Renderer::~Renderer()
{

}

//Update values for color anim, rot, etc
void Renderer::Update()
{
	//COLOR ANIM
	if (colorRGB.vecOrigin[0] > 1.0f)
		incrementRGB = -0.02f;
	else if (colorRGB.vecOrigin[0] < -1.0f)
		incrementRGB = 0.02f;

	colorRGB.vecOrigin[0] += incrementRGB;

	//Setup the vital parts for MVP, Model + View + Projection
	SetView(vector3D(camPos.vecOrigin[0], camPos.vecOrigin[1], camPos.vecOrigin[2]), vector3D(camPos.vecOrigin[0] - camTargetPos.vecOrigin[0], camPos.vecOrigin[1] - camTargetPos.vecOrigin[1], camPos.vecOrigin[2] - camTargetPos.vecOrigin[2]));
	SetProjection(90.0f);
}

//Add en entity to the render list of entities
void Renderer::AddEntity(Entity ent)
{
	entityList.push_back(ent);
	printf("An entity has been added to the list : It can now be drawn by the renderer!\n");
}

//Get a list of all entities
vector<Entity> Renderer::GetEntityList()
{
	return vector<Entity>();
}

//Set pos of the light source
void Renderer::SetLightPos(vector3D pos)
{
	lightPTR->currentLight.Position = pos;
}

//Set pos of the camera
void Renderer::SetCamPos(vector3D origin)
{
	camPos = origin;
}

//Set the position and target location of the camera
void Renderer::SetView(vector3D origin, vector3D target)
{
	this->view = matrix3D::LookAt(origin, target, vector3D(0.0f, 1.0f, 0.0f));
}

//Set the FOV
void Renderer::SetProjection(float FOV)
{
	this->projection = matrix3D::perspectiveProj(FOV, this->window_Width, this->window_Height, 0.1f, 100.0f).transpose();
}

//Draw all data to the screen
void Renderer::Draw()
{
	Update();

	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i].Update(this->projection, this->view, lightPTR, camPos, colorRGB);
		entityList[i].Draw();
	}
}

//Clear the screen from previous data
void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

//Get the MVP for current Entity
matrix3D Renderer::GetMVP(matrix3D transform)
{
	return this->projection * this->view * transform;
}

//Get the Model View for current Entity
matrix3D Renderer::GetModelView(matrix3D transform)
{
	return this->view * transform;
}

matrix3D Renderer::GetProj()
{
	return this->projection;
}

Light* Renderer::GetLightRef()
{
	return lightPTR;
}

// * * * PRIVATE FUNCTIONS * * *

//Bind buffers for current entity
void Renderer::Bind(int index)
{
	entityList[index].Bind();
}

//Unbind data so other entities can Bind their data and spare memory
void Renderer::Unbind(int index)
{
	entityList[index].Unbind();
}