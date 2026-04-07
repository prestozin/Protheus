#include "Transform.h"
#include <cmath>

Vector3D RotateX(const Vector3D& p, float angle)
{
    Vector3D result;

    result.y = p.y * cos(angle) - p.z * sin(angle);
    result.z = p.y * sin(angle) + p.z * cos(angle);
    result.x = p.x;

    return result;
}
Vector3D RotateY(const Vector3D& p, float angle)
{
    Vector3D result;

    result.x = p.x * cos(angle) - p.z * sin(angle);
    result.z = p.x * sin(angle) + p.z * cos(angle);
    result.y = p.y;

    return result;
}

Vector3D RotateZ(const Vector3D& p, float angle)
{
    Vector3D result;

    result.x = p.x * cos(angle) - p.y * sin(angle);
    result.y = p.x * sin(angle) + p.y * cos(angle);
    result.z = p.z;

    return result;
}

Vector3D Translate(const Vector3D& p, const Vector3D& offset)
{
    return {
        p.x + offset.x,
        p.y + offset.y,
        p.z + offset.z
    };
}
