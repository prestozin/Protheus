#include "Projection.h"

Vector2D Project(const Vector3D& point, int screenWidth, int screenHeight)
{
	float focalLenght = 200.0f; // focal length (distance from the camera to the projection plane)
	float z = point.z; // depth of the point relative to the camera (distance from the camera to the point)

	if (z <= 0.1f)
	{
		// if the point is too close to the camera, we set a minimum depth to avoid division by zero or negative values that would cause the projection to be distorted or inverted.
		z = 0.1f;	
	}
		
	
	Vector2D projectedPoint;

	projectedPoint.x = (point.x / z) * focalLenght; // project x and center on the screen
	projectedPoint.y = (point.y / z) * focalLenght; // project y and center on the screen

	projectedPoint.x += screenWidth / 2.0f;
	projectedPoint.y += screenHeight / 2.0f;

	return projectedPoint;
}
