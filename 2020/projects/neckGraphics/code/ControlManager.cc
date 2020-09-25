#include "ControlManager.h"

//Default constructor
ControlManager::ControlManager()
{
	renderInstance = NULL;
	rasterInstance = NULL;

	lightSource = NULL;

	colorCounter = 0;
	maxEntities = 0;
	lastEntityChecked = false;

	LMB_DOWN = false;
	RMB_DOWN = false;
	MMB_DOWN = false;
	C_DOWN = false;
	mousePosOrigin = POINT();
	mousePosCurrent = POINT();
}

ControlManager::ControlManager(Renderer& render)
{
	renderInstance = new Renderer;
	renderInstance = &render;

	rasterInstance = nullptr;

	lightSource = renderInstance->GetLightRef();

	colorCounter = 0;
	maxEntities = 0;
	lastEntityChecked = false;

	LMB_DOWN = false;
	RMB_DOWN = false;
	MMB_DOWN = false;
	C_DOWN = false;
	mousePosOrigin = POINT();
	mousePosCurrent = POINT();
}

ControlManager::ControlManager(Renderer& render, Rasterizer& raster)
{
	renderInstance = new Renderer;
	renderInstance = &render;

	rasterInstance = new Rasterizer;
	rasterInstance = &raster;

	lightSource = renderInstance->GetLightRef();

	colorCounter = 0;
	maxEntities = 0;
	lastEntityChecked = false;

	LMB_DOWN = false;
	RMB_DOWN = false;
	MMB_DOWN = false;
	C_DOWN = false;
	mousePosOrigin = POINT();
	mousePosCurrent = POINT();
}

ControlManager::~ControlManager()
{
}

//Check for keyboard / mouse input overall
void ControlManager::InputScan()
{
	CameraMouseScan();
	CameraKeyboardScan();

	maxEntities = renderInstance->entityList.size() - 1;
	lastEntityChecked = renderInstance->entityList[maxEntities].controlAccess;

	for (int i = 0; i < renderInstance->entityList.size(); i++)
	{
		EntityMouseScan(i);
		EntityKeyboardScan(i);
	}
}

//CHeck mouse input for the camera
void ControlManager::CameraMouseScan()
{
	//ACTIVATE COMMANDS FOR CAMERA
	if (GetAsyncKeyState(RMB) & 0x8000 && !RMB_DOWN)
		RMB_DOWN = true;

	else if (GetAsyncKeyState(RMB) & 0x8000 && RMB_DOWN) {}

	else
		RMB_DOWN = false;

	//MMB
	if (GetAsyncKeyState(MMB) & 0x8000 && !MMB_DOWN)
		MMB_DOWN = true;

	else if (!(GetAsyncKeyState(MMB) & 0x8000) && MMB_DOWN)
		MMB_DOWN = false;
}

//Check keyboard input for the camera
void ControlManager::CameraKeyboardScan()
{
	//MOVE CAMERA IF RMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[1] += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[0] -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[1] -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[0] += 0.1f;

	if (GetAsyncKeyState('Q') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[2] -= 0.06f;

	if (GetAsyncKeyState('E') & 0x8000 && RMB_DOWN)
		renderInstance->camPos.vecOrigin[2] += 0.06f;

	//MOVE LIGHT IF MMB IS DOWN
	if (GetAsyncKeyState('W') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[1] += 0.15f;

	if (GetAsyncKeyState('A') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[0] -= 0.1f;

	if (GetAsyncKeyState('S') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[1] -= 0.15f;

	if (GetAsyncKeyState('D') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[0] += 0.1f;

	if (GetAsyncKeyState('Q') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[2] -= 0.15f;

	if (GetAsyncKeyState('E') & 0x8000 && MMB_DOWN)
		lightSource->currentLight.Position.vecOrigin[2] += 0.1f;

	//SET DIFFUSE AND AMBIENT INTENSITY
	if (GetAsyncKeyState('I') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.AmbientIntensity < 1.0f)
		{
			lightSource->currentLight.AmbientIntensity += 0.01f;
			printf("Ambient Intensity: %f \n", lightSource->currentLight.AmbientIntensity);
		}
	}

	if (GetAsyncKeyState('J') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.DiffuseIntensity > 0.0f)
		{
			lightSource->currentLight.DiffuseIntensity -= 0.01f;
			printf("Diffusee Intensity: %f \n", lightSource->currentLight.DiffuseIntensity);
		}
	}

	if (GetAsyncKeyState('K') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.AmbientIntensity > 0.0f)
		{
			lightSource->currentLight.AmbientIntensity -= 0.01f;
			printf("Ambient Intensity: %f \n", lightSource->currentLight.AmbientIntensity);
		}
	}

	if (GetAsyncKeyState('L') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.DiffuseIntensity < 1.0f)
		{
			lightSource->currentLight.DiffuseIntensity += 0.01f;
			printf("Diffusee Intensity: %f \n", lightSource->currentLight.DiffuseIntensity);
		}
	}

	//SET SPECULAR INTENSITY
	if (GetAsyncKeyState('Z') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.SpecularIntensity > 0.0f)
		{
			lightSource->currentLight.SpecularIntensity -= 0.01f;
			printf("Specular Intensity: %f \n", lightSource->currentLight.SpecularIntensity);
		}
	}

	if (GetAsyncKeyState('X') & 0x8000 && MMB_DOWN)
	{
		if (lightSource->currentLight.SpecularIntensity < 1.0f)
		{
			lightSource->currentLight.SpecularIntensity += 0.01f;
			printf("Specular Intensity: %f \n", lightSource->currentLight.SpecularIntensity);
		}
	}

	//SWITCH COLOR
	if (GetAsyncKeyState('C') < 0 && MMB_DOWN && !C_DOWN)
	{
		switch (colorCounter)
		{
			//RED
		case 0:
			lightSource->currentLight.Diffuse.vecOrigin[0] = 0.3f;
			lightSource->currentLight.Diffuse.vecOrigin[1] = 0.0f;
			lightSource->currentLight.Diffuse.vecOrigin[2] = 0.0f;

			lightSource->currentLight.Specular.vecOrigin[0] = 0.5f;
			lightSource->currentLight.Specular.vecOrigin[1] = 0.0f;
			lightSource->currentLight.Specular.vecOrigin[2] = 0.0f;
			break;

			//GREEN
		case 1:
			lightSource->currentLight.Diffuse.vecOrigin[0] = 0.0f;
			lightSource->currentLight.Diffuse.vecOrigin[1] = 0.3f;
			lightSource->currentLight.Diffuse.vecOrigin[2] = 0.0f;

			lightSource->currentLight.Specular.vecOrigin[0] = 0.0f;
			lightSource->currentLight.Specular.vecOrigin[1] = 0.5f;
			lightSource->currentLight.Specular.vecOrigin[2] = 0.0f;
			break;

			//BLUE
		case 2:
			lightSource->currentLight.Diffuse.vecOrigin[0] = 0.0f;
			lightSource->currentLight.Diffuse.vecOrigin[1] = 0.0f;
			lightSource->currentLight.Diffuse.vecOrigin[2] = 0.3f;

			lightSource->currentLight.Specular.vecOrigin[0] = 0.0f;
			lightSource->currentLight.Specular.vecOrigin[1] = 0.0f;
			lightSource->currentLight.Specular.vecOrigin[2] = 0.5f;
			break;

			//WHITE
		case 3:
			lightSource->currentLight.Diffuse.vecOrigin[0] = 0.3f;
			lightSource->currentLight.Diffuse.vecOrigin[1] = 0.3f;
			lightSource->currentLight.Diffuse.vecOrigin[2] = 0.3f;

			lightSource->currentLight.Specular.vecOrigin[0] = 0.5f;
			lightSource->currentLight.Specular.vecOrigin[1] = 0.5f;
			lightSource->currentLight.Specular.vecOrigin[2] = 0.5f;
			break;
		}

		colorCounter++;

		if (colorCounter > 3)
			colorCounter = 0;

		C_DOWN = true;
	}

	if (GetAsyncKeyState('C') == 0 && C_DOWN)
		C_DOWN = false;
}

//Check mouse input for current entity
void ControlManager::EntityMouseScan(unsigned int index)
{
	if (!renderInstance->entityList[index].controlAccess) {}

	else if (!lastEntityChecked && (rasterInstance != NULL && rasterInstance->controlAccess))
	{
		//ROTATION FOR MODEL, RASTER
		if (GetAsyncKeyState(LMB) & 0x8000 && !LMB_DOWN)
		{
			GetCursorPos(&mousePosOrigin);
			rasterInstance->oldRotVec.vecOrigin[0] = rasterInstance->rotVec[0];
			rasterInstance->oldRotVec.vecOrigin[1] = rasterInstance->rotVec[1];
			LMB_DOWN = true;
		}

		else if (GetAsyncKeyState(LMB) & 0x8000 && LMB_DOWN)
		{
			GetCursorPos(&mousePosCurrent);

			float currX = mousePosCurrent.x - mousePosOrigin.x;
			float currY = mousePosCurrent.y - mousePosOrigin.y;

			rasterInstance->rotVec.vecOrigin[0] = -currY + rasterInstance->oldRotVec[0];
			rasterInstance->rotVec.vecOrigin[1] = -currX + rasterInstance->oldRotVec[1];
		}

		else
			LMB_DOWN = false;
	}

	else
	{
		//ROTATION FOR MODEL, ENTITY
		if (GetAsyncKeyState(LMB) & 0x8000 && !LMB_DOWN)
		{
			GetCursorPos(&mousePosOrigin);
			renderInstance->entityList[index].oldRotVec.vecOrigin[0] = renderInstance->entityList[index].rotVec[0];
			renderInstance->entityList[index].oldRotVec.vecOrigin[1] = renderInstance->entityList[index].rotVec[1];
			LMB_DOWN = true;
		}

		else if (GetAsyncKeyState(LMB) & 0x8000 && LMB_DOWN)
		{
			GetCursorPos(&mousePosCurrent);

			float currX = mousePosCurrent.x - mousePosOrigin.x;
			float currY = mousePosCurrent.y - mousePosOrigin.y;

			renderInstance->entityList[index].rotVec.vecOrigin[0] = -currY + renderInstance->entityList[index].oldRotVec[0];
			renderInstance->entityList[index].rotVec.vecOrigin[1] = -currX + renderInstance->entityList[index].oldRotVec[1];
		}

		else
			LMB_DOWN = false;
	}
}

//Check keyboard input for current entity
void ControlManager::EntityKeyboardScan(unsigned int index)
{
	if (!renderInstance->entityList[index].controlAccess) {}

	else if (!lastEntityChecked && (rasterInstance != NULL && rasterInstance->controlAccess))
	{
		//MOVE MODEL IF LMB IS DOWN
		if (GetAsyncKeyState('W') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[1] += 0.15f;

		if (GetAsyncKeyState('A') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[0] -= 0.1f;

		if (GetAsyncKeyState('S') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[1] -= 0.15f;

		if (GetAsyncKeyState('D') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[0] += 0.1f;

		if (GetAsyncKeyState('Q') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[2] -= 0.15f;

		if (GetAsyncKeyState('E') & 0x8000 && LMB_DOWN)
			rasterInstance->pos.vecOrigin[2] += 0.1f;
	}

	else
	{
		//MOVE MODEL IF LMB IS DOWN
		if (GetAsyncKeyState('W') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[1] += 0.15f;

		if (GetAsyncKeyState('A') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[0] -= 0.1f;

		if (GetAsyncKeyState('S') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[1] -= 0.15f;

		if (GetAsyncKeyState('D') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[0] += 0.1f;

		if (GetAsyncKeyState('Q') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[2] -= 0.15f;

		if (GetAsyncKeyState('E') & 0x8000 && LMB_DOWN)
			renderInstance->entityList[index].pos.vecOrigin[2] += 0.1f;
	}
}