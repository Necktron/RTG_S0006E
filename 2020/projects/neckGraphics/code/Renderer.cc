#include "Renderer.h"

void Renderer::Init()
{
	this->meshPTR = std::make_shared<Mesh>();
	this->shaderPTR = std::make_shared<Shader>();
	this->texturePTR = std::make_shared<Texture>();

	this->transform = matrix3D();
	this->view = matrix3D();
	this->projection = matrix3D();
}

void Renderer::ConfigUniforms()
{
	//RENDERING PROCESS AND SETUP
	if (int(shaderPTR->shaderEFK) == 1)
		shaderPTR->SetUniform4f("u_Color", color.vecOrigin[0], color.vecOrigin[1], color.vecOrigin[2], 1.0f);

	shaderPTR->SetUniformMat4fv("u_MVP", MVP);
	shaderPTR->SetUniform4f("u_Move", 0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::Draw()
{
	Bind();

	this->shaderPTR->SetUniformMat4fv("u_MVP", this->MVP);

	glDrawElements(GL_TRIANGLES, 36 * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);

	//COLOR ANIM
	if (this->color.vecOrigin[0] > 1.5f)
		this->incrementRGB = -0.02f;
	else if (this->color.vecOrigin[0] < -1.5f)
		this->incrementRGB = 0.02f;

	this->color.vecOrigin[0] += this->incrementRGB;

	//POS MOVE X
	if (this->transform.mxOrigin[0][3] > 1.0f)
		this->incrementPOSX = -0.01f;
	else if (this->transform.mxOrigin[0][3] < -1.0f)
		this->incrementPOSX = 0.01f;

	this->transform.mxOrigin[0][3] += this->incrementPOSX;

	//POS MOVE Z
	if (this->transform.mxOrigin[2][3] > 1.0f)
		this->incrementPOSZ = -0.01f;
	else if (this->transform.mxOrigin[2][3] < -1.0f)
		this->incrementPOSZ = 0.01f;

	this->transform.mxOrigin[2][3] += this->incrementPOSZ;

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
	this->view = matrix3D::LookAt(vector3D(0.0f, 0.0f, 1.0f), vector3D(0.0f, 0.0f, 0.0f), vector3D(0.0f, 1.0f, 0.0f));
	SetTransform(vector3D(this->transform.mxOrigin[3][0], this->transform.mxOrigin[3][1], this->transform.mxOrigin[3][2]), vector3D(this->transform.mxOrigin[0][0], this->transform.mxOrigin[1][1], this->transform.mxOrigin[2][2]), vector3D(1.0f, 1.0f, 1.0f));
	this->projection = matrix3D::perspectiveProj(90.0f, window_Width, window_Height, 0.1f, 100.0f).transpose();

	//Merge the matrixes to create MVP. It's now ready to be sent in to the shader
	this->MVP = this->projection * this->view * this->transform;

	Unbind();
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
	this->transform = matrix3D::translate(vector3D(pos.vecOrigin[0], pos.vecOrigin[1], pos.vecOrigin[2])) * matrix3D::scale(vector3D(scale.vecOrigin[0], scale.vecOrigin[1], scale.vecOrigin[2])) * matrix3D::mxRotAroundVec(vector3D(rot.vecOrigin[0], rot.vecOrigin[1], rot.vecOrigin[2]), 0);
}