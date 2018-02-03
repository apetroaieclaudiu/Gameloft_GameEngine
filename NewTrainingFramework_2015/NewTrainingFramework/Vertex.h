#pragma once
#include "../Utilities/Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vector2 uv_blend;
public:
	Vertex(const Vertex &a) :pos(a.pos), norm(a.norm), binorm(a.binorm), tgt(a.tgt), uv(a.uv), uv_blend(a.uv_blend)
	{
	}
	Vertex()
	{

	}
	
};