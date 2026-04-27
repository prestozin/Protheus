#include "Projection.h"

Vector2D Project(const Vector3D& point, int screenWidth, int screenHeight)
{
#pragma region CameraSetupExplained

	//// Imagine the camera (your eye) is at the origin (0,0,0).
	//// The screen is like a glass window you are looking through.
	//// 'focalLength' is the distance from your eye to that glass window.
	////
	////    Eye (0,0,0)
	////     * ////      \  <- focalLength -> |
	////       \                   | Screen
	////        \                  |                 * Point(x,y,z)
	////         \                 |                /
	////          -----------------|---------------/--> Z axis (Depth)

#pragma endregion

	float focalLenght = 200.0f;
	float z = point.z; // depth of the point 

	if (z <= 0.1f)
	{
		z = 0.1f;
	}

#pragma region NearClippingExplained

	//// If a point gets behind the camera (Z is negative), it would draw upside down.
	//// If a point is exactly ON the camera (Z is 0), dividing by 0 breaks the math.
	//// We force Z to be at least a tiny bit in front of the camera (0.1f) to fix this.
	////
	////   * (Z < 0)  <- No!       Eye * ->   | Screen      * (Z > 0) <- Yes!

#pragma endregion

	Vector2D projectedPoint;

	projectedPoint.x = (point.x / z) * focalLenght;
	projectedPoint.y = (point.y / z) * focalLenght;

#pragma region PerspectiveDivideExplained

	//// This is what makes things look smaller as they get further away
	//// By dividing X and Y by Z, distant points are pulled closer to the center
	////  Z=1 (Close)         Z=2 (Farther)
	////  +-------+           +---+
	////  |       | X / 1     |   | X / 2  -> Object becomes half the size
	////  +-------+           +---+
	////
	//// We then multiply by focalLength to scale those tiny math values 
	//// up to actual visible screen sizes

#pragma endregion

	projectedPoint.x += screenWidth / 2.0f;
	projectedPoint.y += screenHeight / 2.0f;

#pragma region ScreenCenteringExplained

	//// In 3D math, the center of the world (0,0) is exactly in the middle.
	//// But on computer monitors, pixel (0,0) is at the TOP-LEFT corner!
	////
	////   Math World:            Screen Pixels:
	////        +Y                 (0,0) +X
	////         |                   +---+---+
	////   -X ---0--- +X     ->    +Y| O |   |  <- Without shift, the center is top-left!
	////         |                   +---+---+
	////        -Y                   
	////
	//// By adding half the width and height, we shift the center (0,0) 
	//// to the actual middle of the screen monitor.

#pragma endregion

	return projectedPoint;
}