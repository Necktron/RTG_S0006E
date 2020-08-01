#shader vertex
#version 430

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 normal;

out vec3 v_NormalInterp;
out vec3 v_VertPos;
out vec4 v_VertPos4;
out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform mat4 u_Projection;
uniform mat4 u_ModelView;
uniform vec4 u_Move;

void main()
{
	gl_Position = (u_MVP * position) + u_Move;
	v_TexCoord = texCoord;
	v_VertPos4 = u_ModelView * position;
	v_VertPos = vec3(v_VertPos4) / v_VertPos4.w;
	v_NormalInterp = normalize(vec3(normal));
}

#shader fragment
#version 430

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_NormalInterp;
in vec3 v_VertPos;

uniform sampler2D testTex;
uniform vec4 u_Color;
uniform sampler2D u_Texture;

uniform vec3 u_LightOrigin;
uniform vec3 u_AmbientColor;
uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecColor;
const float shiny = 10.0f;
const float screenGamma = 2.2f;

void main()
{
	vec3 normal = normalize(v_NormalInterp);
	vec3 lightDirection = normalize(u_LightOrigin - v_VertPos);

	float lambertian = max(dot(lightDirection, normal), 0.0f);
	float specular = 0.0f;

	if (lambertian > 0.0f)
	{
		vec3 viewDirection = normalize(-v_VertPos);

		vec3 halfDirection = normalize(lightDirection + viewDirection);
		float specularAngle = max(dot(halfDirection, normal), 0.0f);
		specular = pow(specularAngle, shiny);
	}

	vec3 col = texture(testTex, vec2(v_TexCoord.x, 1.0f - v_TexCoord.y)).rgb;
	vec3 colorLinear = (u_AmbientColor + lambertian * u_DiffuseColor + specular * u_SpecColor) * col;

	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));

	color = vec4(colorGammaCorrected, 1.0f);
}