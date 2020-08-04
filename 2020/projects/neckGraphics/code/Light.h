#pragma once
#include "core/app.h"
#include "resources/mathLibrary/Vector3D.h"
#include <stdio.h>
#include <algorithm>

class Light
{
public:
	Light();
	~Light();

	enum class LightSource
	{
		NONE = -1,
		POINT_LIGHT = 0
	};

	struct Lighting
	{
		vector3D Position = vector3D(0.0f, 0.0f, 0.0f);;
		vector3D Ambient = vector3D(0.1f, 0.1f, 0.1f);;
		vector3D Diffuse = vector3D(0.0f, 0.0f, 0.0f);;
		vector3D Specular = vector3D(0.0f, 0.0f, 0.0f);
		float AmbientIntensity = 0.1f;
		float DiffuseIntensity = 0.1f;
	};

	LightSource lightSource = LightSource::NONE;
	Lighting currentLight;

	void PointLight();
};