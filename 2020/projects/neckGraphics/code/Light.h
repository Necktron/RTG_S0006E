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
		vector3D Position;
		vector3D Ambient;
		vector3D Diffuse;
		vector3D Specular;
		float AmbientIntensity;
		float DiffuseIntensity;
		float SpecularIntensity;
	};

	LightSource lightSource = LightSource::NONE;
	Lighting currentLight;

	void PointLight();
};