#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <memory>

class Renderer
{
public:
	void Draw(const std::shared_ptr<Mesh> meshRef, const std::shared_ptr<Shader> shaderRef) const;
	void Clear();
};