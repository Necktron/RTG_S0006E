#include "Renderer.h"

void Renderer::Draw(const std::shared_ptr<Mesh> meshRef, const std::shared_ptr<Shader> shaderRef) const
{
	glDrawElements(GL_TRIANGLES, sizeof(meshRef->indexBuff) * sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}