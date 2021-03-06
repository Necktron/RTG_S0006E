#version 430
layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 myTexture;
layout(location = 2) in vec4 inputNormal;
out vec3 normalInterp;
out vec3 vertPos;
out vec4 vertPos4;

out vec2 texCoord;

uniform mat4 matrix, projection, modelView;

void main()
{
	vec4 v = pos;
	gl_Position = (projection * modelView * pos);
	texCoord = myTexture;
	vertPos4 = modelView * pos;
	vertPos = vec3(vertPos4) / vertPos4.w;
	normalInterp = normalize(vec3(matrix * inputNormal));
}

//FRAGMENT

#version 430
layout(location = 0) out vec4 Color;
in vec2 texCoord;
in vec3 normalInterp;
in vec3 vertPos;

uniform sampler2D testTex;

precision mediump float;

uniform int mode;

const vec3 lightPos = vec3(21.0, 21.0, 0.0);
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 diffuseColor = vec3(0.1, 0.1, 0.1);
const vec3 specColor = vec3(0.1, 0.1, 0.1);
const float shininess = 16.0;
const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space

void main()
{
	vec3 normal = normalize(normalInterp);
	vec3 lightDir = normalize(lightPos - vertPos);

	float lambertian = max(dot(lightDir, normal), 0.0);
	float specular = 0.0;

	if (lambertian > 0.0)
	{
		vec3 viewDir = normalize(-vertPos);

		//This is blinn phong
		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, normal), 0.0);
		specular = pow(specAngle, shininess);
	}

	vec3 col = texture(testTex, vec2(texCoord.x, 1.0 - texCoord.y)).rgb;
	vec3 colorLinear = (ambientColor + lambertian * diffuseColor + specular * specColor) * col;

	// apply gamma correction (assume ambientColor, diffuseColor and specColor
	// have been linearized, i.e. have no gamma correction in them)
	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));

	// use the gamma corrected color in the fragment
	Color = vec4(colorGammaCorrected, 1.0);
}