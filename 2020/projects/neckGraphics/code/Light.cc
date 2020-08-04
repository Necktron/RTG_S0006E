#include "config.h"
#include "Light.h"

Light::Light()
{

}

Light::~Light()
{

}

void Light::PointLight()
{
	currentLight.Position = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.Diffuse = vector3D(0.5f, 0.5f, 0.5f);
	currentLight.Specular = vector3D(0.2f, 0.2f, 0.6f);
	currentLight.Ambient = vector3D(0.1f, 0.1f, 0.1f);
	lightSource = Light::LightSource::POINT_LIGHT;
}