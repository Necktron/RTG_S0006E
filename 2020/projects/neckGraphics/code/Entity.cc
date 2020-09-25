#define ERROR_TRIGGER __debugbreak();
#include "Entity.h"

Entity::Entity(string name)
{
	entityName = name;
	rotFloat = 0.0f;
	rotSpeed = 1.0f;
	angleOfRot = 1.0f;
	incrementRGB = 0.01f;
	controlAccess = false;

	//SHARED POINTERS
	meshPTR = make_shared<Mesh>();
	texturePTR = make_shared<Texture>();
	shaderPTR = make_shared<Shader>();

	//MODEL
	pos = vector3D();
	scale = vector3D();
	rotVec = vector3D();
	transform = matrix3D();
	MVP = matrix3D();
}

Entity::~Entity()
{

}

void Entity::Update(matrix3D projection, matrix3D view, Light* lightInst, vector3D camPos, vector3D colorRGB)
{
	Bind();

	//Set MVP for current mesh
	MVP = projection * view * transform;
	shaderPTR->SetUniformMat4fv("u_MVP", MVP);

	//ROT MOVE
	if (this->angleOfRot > 360.0f)
		this->angleOfRot = 0.0f;

	this->angleOfRot += 1.0f;

	this->rotFloat = this->angleOfRot * this->rotSpeed;

	//Print out matrix values per frame
	if (shaderPTR->m_DEBUG)
	{
		printf("MATRIX VALUES\n");
		printf("%f	%f	%f	%f\n", MVP.mxOrigin[0][0], MVP.mxOrigin[0][1], MVP.mxOrigin[0][2], MVP.mxOrigin[0][3]);
		printf("----------------\n");
		printf("%f	%f	%f	%f\n", MVP.mxOrigin[1][0], MVP.mxOrigin[1][1], MVP.mxOrigin[1][2], MVP.mxOrigin[1][3]);
		printf("----------------\n");
		printf("%f	%f	%f	%f\n", MVP.mxOrigin[2][0], MVP.mxOrigin[2][1], MVP.mxOrigin[2][2], MVP.mxOrigin[2][3]);
		printf("----------------\n");
		printf("%f	%f	%f	%f\n", MVP.mxOrigin[3][0], MVP.mxOrigin[3][1], MVP.mxOrigin[3][2], MVP.mxOrigin[3][3]);
		printf("----------------\n");
	}

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::PULSE_COLOR)
		shaderPTR->SetUniform4f("u_Color", colorRGB.vecOrigin[0], 0.0f, 0.0f, 1.0f);

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::BLINN_PHONG && lightInst->lightSource == Light::LightSource::POINT_LIGHT)
	{
		shaderPTR->SetUniform3f("u_LightPos", lightInst->currentLight.Position.vecOrigin[0], lightInst->currentLight.Position.vecOrigin[1], lightInst->currentLight.Position.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_CamPos", camPos.vecOrigin[0], camPos.vecOrigin[1], camPos.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_AmbientColor", lightInst->currentLight.Ambient.vecOrigin[0], lightInst->currentLight.Ambient.vecOrigin[1], lightInst->currentLight.Ambient.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_DiffuseColor", lightInst->currentLight.Diffuse.vecOrigin[0], lightInst->currentLight.Diffuse.vecOrigin[1], lightInst->currentLight.Diffuse.vecOrigin[2]);
		shaderPTR->SetUniform3f("u_SpecularColor", lightInst->currentLight.Specular.vecOrigin[0], lightInst->currentLight.Specular.vecOrigin[1], lightInst->currentLight.Specular.vecOrigin[2]);
		shaderPTR->SetUniform1f("u_AmbientIntensity", lightInst->currentLight.AmbientIntensity);
		shaderPTR->SetUniform1f("u_DiffuseIntensity", lightInst->currentLight.DiffuseIntensity);
		shaderPTR->SetUniform1f("u_SpecularIntensity", lightInst->currentLight.SpecularIntensity);
	}

	SetTransform(this->pos, this->scale, this->rotVec);
}

void Entity::Draw()
{
	shaderPTR->SetUniform4f("u_Move", 0.0f, 0.0f, 0.0f, 1.0f);

	if (shaderPTR->shaderEFK == Shader::ShaderEffect::BLINN_PHONG)
		shaderPTR->SetUniformMat4fv("u_Model", transform);

	//Rast Triangle
	if (meshPTR->meshOBJ == Mesh::OBJ::RAST_TRIANGLE)
		glDrawElements(GL_TRIANGLES, meshPTR->indices.size() * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	//Triangle
	else if (meshPTR->meshOBJ == Mesh::OBJ::TRIANGLE)
		glDrawElements(GL_TRIANGLES, 3 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	//Quad
	else if (meshPTR->meshOBJ == Mesh::OBJ::QUAD)
		glDrawElements(GL_TRIANGLES, 6 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	//Cube
	else if (meshPTR->meshOBJ == Mesh::OBJ::CUBE)
		glDrawElements(GL_TRIANGLES, 36 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	//Custom mesh
	else if (int(meshPTR->meshOBJ) >= 3)
		glDrawElements(GL_TRIANGLES, meshPTR->indices.size() * sizeof(unsigned int), GL_UNSIGNED_INT, 0);

	else
		printf("No mesh assigned, nothing to render\n");

	Unbind();
}

//Set a mesh from the pre-defined types, triangle / quad / cube
void Entity::SetMesh(Mesh::OBJ obj)
{
	//WIP
	switch (int(obj))
	{
	case -1:
		printf("No OBJ selected\n");
		break;

	//Rast Triangle
	case 0:
		meshPTR->RastTriangle();
		break;

	//Triangle
	case 1:
		meshPTR->Triangle();
		break;

	//Quad
	case 2:
		meshPTR->Quad();
		break;

	//Cube
	case 3:
		meshPTR->Cube();
		break;

	//Cat
	case 4:
		meshPTR->CustomMesh("resources/meshes/cat.obj");
		break;

	//Stool
	case 5:
		meshPTR->CustomMesh("resources/meshes/Stool.obj");
		break;

	//CUBE
	case 6:
		meshPTR->CustomMesh("resources/meshes/cubeLow.obj");
		break;

	//WINDMILL
	case 7:
		meshPTR->CustomMesh("resources/meshes/windmill.obj");
		break;

	//PENGUIN
	case 8:
		meshPTR->CustomMesh("resources/meshes/Penguin.obj");
		break;
	}

	this->meshPTR->meshOBJ = obj;
}

//Set texture from a specific path
void Entity::SetTexture(Texture::TextureImage texture)
{
	switch (int(texture))
	{
	case -1:
		printf("No texture assigned!\n");
		break;

	case 0:
		texturePTR->SetupTexture("resources/textures/YellowBrickWall.jpg");
		break;

	case 1:
		texturePTR->SetupTexture("resources/textures/TurquoiseWoodWall.jpg");
		break;

	case 2:
		texturePTR->SetupTexture("resources/textures/KoreanFlag.png");
		break;

	case 3:
		texturePTR->SetupTexture("resources/textures/Blueberries.jpg");
		break;

	case 4:
		texturePTR->SetupTexture("resources/textures/OpenGLLogo.png");
		break;

	case 5:
		texturePTR->SetupTexture("resources/textures/InstaTransparent.png");
		break;

		//CAT
	case 6:
		texturePTR->SetupTexture("resources/textures/cat_diff.tga");
		break;

	case 7:
		texturePTR->SetupTexture("resources/textures/IKEA.jpg");
		break;

	case 8:
		texturePTR->SetupTexture("resources/textures/Richard.jpg");
		break;

	case 9:
		texturePTR->SetupTexture("resources/textures/Micke.jpg");
		break;

		//BOX
	case 10:
		texturePTR->SetupTexture("resources/textures/cubeLow.jpg");
		break;

		//WINDMILL
	case 11:
		texturePTR->SetupTexture("resources/textures/windmill.jpg");
		break;

		//PENGUIN
	case 12:
		texturePTR->SetupTexture("resources/textures/Penguin.png");
		break;
	}

	this->texturePTR->textureImage = texture;
}

//Set shader from a specific path
void Entity::SetShader(Shader::ShaderEffect shader)
{
	printf("[SHADER FOR RENDER: %s ]\n", entityName);

	switch (int(shader))
	{
		//Rainbow Static
	case 0:
		shaderPTR->SetupShader("resources/shaders/StaticRainbow.shader");
		break;

		//Pulse Color
	case 1:
		shaderPTR->SetupShader("resources/shaders/PulseColor.shader");
		break;

		//Texture from file
	case 2:
		shaderPTR->SetupShader("resources/shaders/ImageTexture.shader");
		break;

		//Bling bling!
	case 3:
		shaderPTR->SetupShader("resources/shaders/BlinnPhong.shader");
		break;

	case 4:
		shaderPTR->SetupShader("resources/shaders/RasterCanvas.shader");
		break;
	}

	if (int(texturePTR->textureImage) != -1)
	{
		shaderPTR->SetUniform1i("u_Texture", 0);
	}

	this->shaderPTR->shaderEFK = shader;
}

//Set the transform of the model with Position / Scale / Rotation directions
void Entity::SetTransform(vector3D pos, vector3D scale, vector3D rot)
{
	this->pos = pos;
	this->scale = scale;
	this->rotVec = rot;

	this->transform = matrix3D::translate(this->pos) * matrix3D::scale(this->scale) * matrix3D::mxRotX(this->rotVec.vecOrigin[0]) * matrix3D::mxRotY(this->rotVec.vecOrigin[1]) * matrix3D::mxRotZ(this->rotVec.vecOrigin[2]);
}

//Return current Mesh data
shared_ptr<Mesh> Entity::GetMesh()
{
	return meshPTR;
}

//Return current Texture data
shared_ptr<Texture> Entity::GetTexture()
{
	return texturePTR;
}

//Return current Shader data
shared_ptr<Shader> Entity::GetShader()
{
	return shaderPTR;
}

//Return current Transform
matrix3D Entity::GetTransform()
{
	return transform;
}

//Bind
void Entity::Bind()
{
	shaderPTR->Bind();
	meshPTR->Bind();

	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}
}

//Unbind
void Entity::Unbind()
{
	if (int(texturePTR->textureImage) != -1)
	{
		texturePTR->Bind();
	}

	meshPTR->Unbind();
	shaderPTR->Unbind();
}
