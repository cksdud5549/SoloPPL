#include "stdafx.h"
#include "utils.h"

namespace TTYONE_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	float getAngle(POINTFLOAT pos1, POINTFLOAT pos2)
	{
		float x = pos2.x - pos1.x;
		float y = pos2.y - pos1.y;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (pos2.y > pos1.y)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}


}