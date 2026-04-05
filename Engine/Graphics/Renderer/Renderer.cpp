#include "renderer.h"

#include <algorithm>

static RendererInfo info;
static uint32_t* framebuffer;

void InitRenderer(int width, int height)
{
	info.width = width;
	info.height = height;

	//create an array 1d of uint32_t to represent the framebuffer, where each element corresponds to a pixel
	//calculate the total number of pixels needed to fill the screen and allocate memory for the framebuffer
	framebuffer = new uint32_t[width * height];
};

//frees the memory allocated for the framebuffer (an array of all pixels needed to fill the scren) when the renderer is shut down
void ShutdownRenderer()
{
	delete[] framebuffer;
	framebuffer = nullptr;
}

RendererInfo GetRendererInfo()
{
	return info;
}

//fills the entire framebuffer with the specified color, effectively clearing the screen to that color
void Clear(uint32_t color)
{
	//loop through each pixel in the framebuffer and set it to the specified color
	for (int i = 0; i < info.width * info.height; i++)
		framebuffer[i] = color;
}

//sets the pixel at (x, y) to the specified color
void SetPixel(int x, int y, uint32_t color)
{
	if (x < 0 || x >= info.width || y < 0 || y >= info.height)
		return;

	//convert the 2D coordinates (x, y) to a 1D index in the framebuffer array and set that pixel to the specified color
	//line(x) * width + column(y) = index in the 1D array
	framebuffer[y * info.width + x] = color;
}

//returns a pointer to the framebuffer, wich is an array of uint32_t representing each pixel on the screen
uint32_t* GetFramebuffer()
{
	return framebuffer;
}

float EdgeFunction(int Vec1X, int Vec1Y, int Vec2X, int Vec2Y, int Px, int Py)
{
#pragma region EdgeFunctionExplained

	//// tells which side of the line AB the point P is on

	//// example:
	//// A(2,2) → B(6,2)


	//		y
	//		↑

	//		5 |      * P(4,5)
	//		4 |      
	//		3 |  A(2,2)  B(6,2)
	//		2 |  *-------* 
	//      1 |_ _ _ _ _ _
	//		   1 2 3 4 5 6 → x
	//		    


	// vector AB:
	// (Vec2X - Vec1X, Vec2Y - Vec1Y) = 6 - 2, 2 - 2 = (4, 0)

	//// vector AP:
	// (Px - Vec1X, Py - Vec1Y) = 4 - 2, 5 - 2 = (2, 3)


	//// edge function:
	// (Px - Vec1X)*(Vec2Y - Vec1Y) - (Py - Vec1Y)*(Vec2X - Vec1X)

	//// calculation:

	// (2 * 0) - (3 * 4)
	// 0 - 12 = -12

	// AB define a direction →
	//// Edge direction: A → B

	//		y
	//		↑
	//		5 |     *P(negative)
	//		4 |
	//		3 |
	//		2 |  A -----> B
	//		1 |	    *P(positive)
	//			_ _ _ _ _ _
	//			1 2 3 4 5 6  → x


	//		y
	//		↑
	//		5 |     *P(positive)
	//		4 |
	//		3 |
	//		2 |  A <----- B
	//		1 |	    *P(negative)
	//			_ _ _ _ _ _
	//			1 2 3 4 5 6  → x

	// "left" and "right" are RELATIVE to the edge direction



#pragma endregion
	return (Px - Vec1X) * (Vec2Y - Vec1Y) - (Py - Vec1Y) * (Vec2X - Vec1X);
}

void DrawLine(int x1, int y1, int x2, int y2, uint32_t color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	// dx and dy (difference between points)

	// dx = movement in X
	// dy = movement in Y

	// ex: A(2,1) → B(6,4)

	// dx = 6 - 2 = 4
	// dy = 4 - 1 = 3

	//visual:

	//		4 |          * B
	//		3 |
	//		2 |
	//		1 |  * A
	//		   _ _ _ _ _ _ 
	//		   1 2 3 4 5 6 



	int steps = std::max(std::abs(dx), std::abs(dy));

	//get the bigger of the two differences (dx and dy) to determine how many steps we need to take to draw the line.
	// dx = 4, dy = 3 → steps = 4(the bigger one)

	float xIncrement = dx / static_cast<float>(steps);
	float yIncrement = dy / static_cast<float>(steps);

	//calculate how much we need to increment x and y for each step to move from the starting point to the ending point in equal increments.

	// xIncrement = 4 / 4 = 1
	// yIncrement = 3 / 4 = 0.75

	//// visual:

	//		4 |         *
	//		3 |      *
	//		2 |   *
	//		1 | *
	//		   2 3 4 5 6

	//// X: 2 → 3 → 4 → 5 → 6
	//// Y: 1 → 1.75 → 2.5 → 3.25 → 4

	float x = x1;
	float y = y1;

	//convert the starting point (x1, y1) to float to allow for fractional increments when drawing the line.
	//only integer values can be used, the float values will be stored and will be used when they become a integer after the increments.
	//ignoring the fractional part until it becomes a whole number to set the pixel.

	for (int i = 0; i <= steps; i++)
	{
		SetPixel((int)x, (int)y, color);
		x += xIncrement;
		y += yIncrement;

		// each iteration = one point of the line
		// one step = one point = one pixel

		// step by step:

		// i = 0
		// real: (2.00, 1.00) → draw (2,1)

		//visual:

		//		4 |
		//		3 |
		//		2 |
		//		1 |  *
		//		   _ _ _ _ _ _
		//		   1 2 3 4 5 6


		//// i = 1
		// real: (3.00,1.75) → draw (3,2)

		//		4 |
		//		3 |
		//		2 |   
		//		1 |  * *
		//		   _ _ _ _ _ _
		//		   1 2 3 4 5 6


		//// i = 2
		// real: (4.00,2.50) → draw (4,2)

		//		4 |
		//		3 |
		//		2 |      *
		//		1 |  * *
		//		   _ _ _ _ _ _
		//		   1 2 3 4 5 6
	}
}

void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, uint32_t color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
}

void DrawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, uint32_t color)
{
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x3, y3, color);
	DrawLine(x3, y3, x1, y1, color);
	DrawLine(x4, y4, x1, y1, color);
}

void DrawFilledTriangle(Vertex v1, Vertex v2, Vertex v3)
{

#pragma region BoudingBoxExplained

	// bounding box:
	// ex: A(2,2) B(6, 2), C(4,7)

	// minX = 2, maxX = 6
	// minY = 2, maxY = 7

	//		y
	//		↑

	//		7 |		 C(4,7)
	//		6 |      *
	//		5 |     / \
	//		4 |    /   \
	//		3 |   /     \ 
	//		2 |  *A(2,2) *B(6, 2)
	//		1 |_ _ _ _ _ _
	//		   1 2 3 4 5 6 → x

	//// this defines a rectangle that fully contains the triangle


	//   (2,7) ----------(6,7)
	//	   |      C        |
	//	   |      *        |
	//	   |     / \       |
	//	   |    /   \      |
	//	   |   *     *     |
	//	   |  A       B    |
	//	 (2,2) ----------(6,2)


	//// we iterate through ALL pixels inside this box
	//// using a 2D loop (y and x)

	//// for each y from 2 to 7
	//// for each x from 2 to 6


	//		7 | *  *  *  *  * ->
	//		6 | *  *  *  *  * ->
	//		5 | *  *  *  *  * ->
	//		4 | *  *  *  *  * ->
	//		3 | *  *  *  *  * ->
	//		2 | *  *  *  *  * ->
	//			2  3  4  5  6


	//// after this, each pixel is tested:
	//// - if inside triangle → draw
	//// - if outside → discard

	//// this test uses barycentric coordinates
	//// computed with the edge function

#pragma endregion

	//bounding box
	int minX = std::min(v1.Position.x, std::min(v2.Position.x, v3.Position.x));
	int maxX = std::max(v1.Position.x, std::max(v2.Position.x, v3.Position.x));

	int minY = std::min(v1.Position.y, std::min(v2.Position.y, v3.Position.y));
	int maxY = std::max(v1.Position.y, std::max(v2.Position.y, v3.Position.y));

	float area = EdgeFunction(v1.Position.x, v1.Position.y, v2.Position.x, v2.Position.y, v3.Position.x, v3.Position.y);

	if (area == 0.0f) return;

	float invArea = 1.0f / area;

	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			float baryWeight0 = EdgeFunction(v2.Position.x, v2.Position.y, v3.Position.x, v3.Position.y, x, y);
			float baryWeight1 = EdgeFunction(v3.Position.x, v3.Position.y, v1.Position.x, v1.Position.y, x, y);
			float baryWeight2 = EdgeFunction(v1.Position.x, v1.Position.y, v2.Position.x, v2.Position.y, x, y);

			float weight0 = baryWeight0 * invArea;
			float weight1 = baryWeight1 * invArea;
			float weight2 = baryWeight2 * invArea;

			if (weight0 >= 0 && weight1 >= 0 && weight2 >= 0 ||
				(weight0 <= 0 && weight1 <= 0 && weight2 <= 0))
			{

				Color finalColor =
					v1.Color * weight0 +
					v2.Color * weight1 +
					v3.Color * weight2;

				SetPixel(x, y, ToUint32(finalColor));
			}
		}
	}
}


