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
		vector3D Diffuse;
		vector3D Specular;
	};

	struct PointLight
	{
		vector3D sourcePos;
		vector3D diffuseColor;
		vector3D specularColor;
		float  diffuseIntensity;
		float  specularIntensity;
	};

	LightSource lightSource = LightSource::NONE;

	void GetPointLight();

	vector3D targetPos;
	vector3D viewDirection;
	vector3D normal;
};