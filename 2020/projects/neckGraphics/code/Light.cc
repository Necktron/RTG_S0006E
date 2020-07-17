#include "config.h"
#include "Light.h"

Light::Light()
{

}

Light::~Light()
{

}

void Light::GetPointLight()
{
	Lighting lightOutput;
	PointLight lightSource;

	//Unless the light
	if (lightSource.diffuseIntensity > 0)
	{
		vector3D lightDirection = lightSource.sourcePos - targetPos;
		float distance = lightDirection.vecLength();
		lightDirection = lightDirection / distance;
		distance = distance * distance;

		//Intensity of the diffuse light. Saturate is to keep it within 0 - 1 range
		float normalDotDirection = normal.dotProd(lightDirection);

		//Clamp intensity
		float intensity = GLclampf(normalDotDirection);

		//Calculate the diffuse light factoring in light color, power and the attenuation
		lightOutput.Diffuse = (lightSource.diffuseColor * intensity) * lightSource.diffuseIntensity / distance;

		//Calculate the half vector between the light vector and the view vector.
		//This is typically slower than calculating the actual reflection vector due to the normalize function's reciprocal square root
		vector3D halfway = lightDirection.vecNormilisation() + viewDirection.vecNormilisation();

		//Intensity of the specular light
		float normalDotHalfway = normal.dotProd(halfway);

		//Clamp 2.0
		intensity = pow(GLclampf(normalDotHalfway), 1);

		//Sum up the specular light factoring
		lightOutput.Specular = (lightSource.specularColor * intensity) * lightSource.specularIntensity / distance;
	}
}