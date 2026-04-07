#pragma once

#pragma once

#include "Math/Vectors/Vector3d.h"

Vector3D RotateY(const Vector3D& p, float angle);
Vector3D RotateX(const Vector3D& p, float angle);
Vector3D RotateZ(const Vector3D& p, float angle);

Vector3D Translate(const Vector3D& p, const Vector3D& offset);