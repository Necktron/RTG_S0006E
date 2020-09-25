#pragma once
#define LMB 0x0001
#define RMB 0x0002
#define MMB 0x0004
#include "Entity.h"
#include "Light.h"
#include "Renderer.h"
#include "Rasterizer.h"
#include <memory>
#include <Windows.h>

class ControlManager
{
public:
	Renderer* renderInstance;
	Rasterizer* rasterInstance;
	Light* lightSource;
	
	ControlManager();
	ControlManager(Renderer& render);
	ControlManager(Renderer& render, Rasterizer& raster);
	~ControlManager();
	
	void InputScan();

private:
	void CameraMouseScan();
	void CameraKeyboardScan();

	void EntityMouseScan(unsigned int index);
	void EntityKeyboardScan(unsigned int index);

	int colorCounter;
	int maxEntities;
	bool lastEntityChecked;

	bool LMB_DOWN;
	bool RMB_DOWN;
	bool MMB_DOWN;
	bool C_DOWN;
	POINT mousePosOrigin;
	POINT mousePosCurrent;
};