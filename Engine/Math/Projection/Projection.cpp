#include "Projection.h"

Vector2D Project(const Vector3D& point, int screenWidth, int screenHeight)
{
	float focalLenght = 200.0f; 
	float z = point.z; // depth of the point 

	if (z <= 0.1f)
	{
		// if the point is too close to the camera, we set a minimum depth to avoid division by zero or negative values that would cause the projection to be distorted or inverted.
		z = 0.1f;	
	}
		
	
	Vector2D projectedPoint;

	projectedPoint.x = (point.x / z) * focalLenght; 
	projectedPoint.y = (point.y / z) * focalLenght; 

	projectedPoint.x += screenWidth / 2.0f;
	projectedPoint.y += screenHeight / 2.0f;

	return projectedPoint;
}
