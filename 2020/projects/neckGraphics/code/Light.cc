#include "config.h"
#include "Light.h"

Light::Light()
{
	currentLight.Position = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.Diffuse = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.Specular = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.Ambient = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.AmbientIntensity = 0.0f;
	currentLight.DiffuseIntensity = 0.0f;
	currentLight.SpecularIntensity = 0.0f;
	lightSource = Light::LightSource::NONE;
}

Light::~Light()
{

}

void Light::PointLight()
{
	currentLight.Position = vector3D(0.0f, 0.0f, 0.0f);
	currentLight.Diffuse = vector3D(0.3f, 0.3f, 0.3f);
	currentLight.Specular = vector3D(0.5f, 0.5f, 0.5f);
	currentLight.Ambient = vector3D(0.1f, 0.1f, 0.1f);
	currentLight.AmbientIntensity = 0.5f;
	currentLight.DiffuseIntensity = 0.5f;
	currentLight.SpecularIntensity = 0.3f;
	lightSource = Light::LightSource::POINT_LIGHT;
}