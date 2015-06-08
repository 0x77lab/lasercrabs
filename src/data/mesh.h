#pragma once

#include "array.h"
#include "types.h"
#include <GL/glew.h>
#include "lmath.h"

#include <BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>

struct Mesh
{
	Array<int> indices;
	Array<Vec3> vertices;
	Array<Vec2> uvs;
	Array<Vec3> normals;
	btTriangleIndexVertexArray physics;
};