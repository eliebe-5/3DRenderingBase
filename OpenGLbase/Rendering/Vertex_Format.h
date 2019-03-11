#ifndef VertexFormat_H_
#define VertexFormat_H_

#include "glm\glm.hpp"

namespace Rendering
{
	struct Vertex_Format
	{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normals;
		Vertex_Format(const glm::vec3 &pos, const glm::vec2 &uv_cord = glm::vec2(0.f, 0.f), const glm::vec3 &norms = glm::vec3(1.f, 1.f, 1.f)) : position(pos), uv(uv_cord), normals(norms)
		{
		}
	};
}
#endif