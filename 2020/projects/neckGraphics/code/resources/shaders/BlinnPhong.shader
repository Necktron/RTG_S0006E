#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 normal;

out vec3 v_Pos;
out vec2 v_TexCoord;
out vec3 v_Normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform vec4 u_Move;

void main()
{
	gl_Position = (u_MVP * position) + u_Move;
	v_Pos = vec4(u_Model * position).xyz;
	v_TexCoord = texCoord;
	v_Normal = mat3(u_Model) * vec3(normal);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Pos;
in vec2 v_TexCoord;
in vec3 v_Normal;

uniform sampler2D u_Texture;

uniform vec3 u_CamPos;
uniform vec3 u_LightPos;
uniform vec3 u_AmbientColor;
uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecularColor;
uniform float u_AmbientIntensity;
uniform float u_DiffuseIntensity;
uniform float u_SpecularIntensity;

void main()
{
	vec3 posToLightDirVec = normalize(v_Pos - u_LightPos);
	float diffuse = clamp(dot(-posToLightDirVec, v_Normal), 0, 1);
	vec3 diffuseFinal = (u_DiffuseColor * diffuse) * u_DiffuseIntensity;

	//Specular light
	vec3 lightToPosDirVec = normalize(u_LightPos - v_Pos);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_Normal)));
	vec3 posToViewDirVec = normalize(v_Pos - u_CamPos);
	float specularConst = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = (u_SpecularColor * specularConst) * u_SpecularIntensity;

	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = texColor * (vec4(u_AmbientColor, 1.0f) * u_AmbientIntensity) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.0f);
}