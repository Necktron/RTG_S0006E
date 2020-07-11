#include "Renderer.h"

void Renderer::Init()
{
	this->meshPTR = std::make_shared<Mesh>();
	this->shaderPTR = std::make_shared<Shader>();
	this->texturePTR = std::make_shared<Texture>();

	this->rot = 0.0f;
	this->rotSpeed = 1.0f;
	this->angleOfRot = 0.0f;
	this->incrementRGB = 0.0f;
	this->incrementPosX = 0.0f;
	this->incrementPosY = 0.0f;
	this->incrementPosZ = 0.0f;
	this->moveX = 1.6f;
	this->moveY = 0.0f;
	this->moveZ = 1.1f;
	this->r = 1.1f;
	this->g = 0.0f;
	this->b = 0.0f;

	this->transform = matrix3D();
	this->view = matrix3D();
	this->projection = matrix3D();
	this->MVP = matrix3D();
}

void Renderer::ConfigUniforms()
{
	//RENDERING PROCESS AND SETUP
	/*if (int(this->shaderPTR->shaderEFK) == 1)
		this->shaderPTR->SetUniform4f("u_Color", r, g, b, 1.0f);*/

	this->shaderPTR->SetUniformMat4fv("u_MVP", this->MVP);
	this->shaderPTR->SetUniform4f("u_Move", moveX, moveY, moveZ, 1.0f);
}

void Renderer::Update()
{
	//COLOR ANIM
	if (r > 1.5f)
		incrementRGB = -0.02f;
	else if (r < -1.5f)
		incrementRGB = 0.02f;

	r += incrementRGB;

	//POS MOVE X
	if (this->moveX > 1.5f)
		incrementPosX = -0.02f;
	else if (this->moveX < -1.5f)
		incrementPosX = 0.02f;

	this->moveX += incrementPosX;

	//POS MOVE Z
	if (this->moveZ > 1.0f)
		this->incrementPosZ = -0.02f;
	else if (this->moveZ < -1.0f)
		this->incrementPosZ = 0.02f;

	this->moveZ += this->incrementPosZ;

	//ROT MOVE
	if (this->angleOfRot > 360.0f)
		this->angleOfRot = 0.0f;

	this->angleOfRot += 1.0f;

	this->rot = this->angleOfRot * this->rotSpeed;

	//Print out matrix values per frame
	if (meshPTR->m_DEBUG)
	{
		std::cout << "MATRIX VALUES" << std::endl;
		std::cout << MVP.mxOrigin[0][0] << " " << MVP.mxOrigin[0][1] << " " << MVP.mxOrigin[0][2] << " " << MVP.mxOrigin[0][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[1][0] << " " << MVP.mxOrigin[1][1] << " " << MVP.mxOrigin[1][2] << " " << MVP.mxOrigin[1][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[2][0] << " " << MVP.mxOrigin[2][1] << " " << MVP.mxOrigin[2][2] << " " << MVP.mxOrigin[2][3] << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << MVP.mxOrigin[3][0] << " " << MVP.mxOrigin[3][1] << " " << MVP.mxOrigin[3][2] << " " << MVP.mxOrigin[3][3] << std::endl;
		std::cout << "                " << std::endl;
	}

	//Setup the vital parts for MVP, Model + View + Projection
	this->view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.5f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
	this->transform = matrix3D::translate(vector3D(moveX, moveY, moveZ)) * matrix3D::scale(vector3D(0.5f, 0.5f, 0.5f)) * matrix3D::mxRotAroundVec(vector3D(1.0f, 1.0f, 1.0f), 0.0f);
	//SetTransform(vector3D(moveX, 0.0f, moveZ), vector3D(1.0f, 1.0f, 1.0f), vector3D(1.0f, 1.0f, 1.0f));
	this->projection = matrix3D::perspectiveProj(90.0f, this->window_Width, this->window_Height, 0.1f, 100.0f).transpose();

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;
}

void Renderer::Draw()
{
	this->shaderPTR->SetUniformMat4fv("u_MVP", this->MVP);
	this->shaderPTR->SetUniform4f("u_Move", 0.0f, 0.0f, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 36 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::Bind()
{
	this->shaderPTR->Bind();
	this->meshPTR->Bind();
	this->texturePTR->Bind();
}

void Renderer::Unbind()
{
	this->texturePTR->Unbind();
	this->meshPTR->Unbind();
	this->shaderPTR->Unbind();
}

void Renderer::SetTransform(vector3D pos, vector3D scale, vector3D rot)
{
	transform = matrix3D::translate(vector3D(pos.vecOrigin[0], pos.vecOrigin[1], pos.vecOrigin[2])) * matrix3D::scale(vector3D(scale.vecOrigin[0], scale.vecOrigin[1], scale.vecOrigin[2])) * matrix3D::mxRotAroundVec(vector3D(rot.vecOrigin[0], rot.vecOrigin[1], rot.vecOrigin[2]), 0);
}

matrix3D Renderer::GetTransform()
{
	return transform;
}