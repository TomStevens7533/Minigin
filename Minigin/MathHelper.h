#pragma once
#include <random>
#include "structs.h"

namespace MathHelper
{
	inline bool AreEqual(float A, float B, float epsilon = 0.005f)
	{
		return (std::fabs(A - B) < epsilon);
	}

	inline bool AreRectsOverlapping(dae::Rectf lhs, dae::Rectf rhs)
	{

		// If one rectangle is on left side of the other
		if ((lhs.x + lhs.width) < rhs.x || (rhs.x + rhs.width) < lhs.x)
		{
			return false;
		}

		// If one rectangle is under the other
		if (lhs.y > (rhs.y + rhs.height) || rhs.y > (lhs.y + lhs.height))
		{
			return false;
		}

		return true;
	}
	inline bool IsPointInRect(dae::Rectf lhs, glm::vec2 point)
	{
		if (point.x >= lhs.x && point.x <= (lhs.x + lhs.width) && point.y >= lhs.y && point.y <= (lhs.y + lhs.height))
			return true;

		return false;
	}

	//https://stackoverflow.com/a/56072726
	inline bool RandomBool(const float probabilty = 0.5f) {
		static auto dev = std::random_device();
		static auto gen = std::mt19937{ dev() };
		static auto dist = std::uniform_real_distribution<float>(0, 1);
		return (dist(gen) < probabilty);
	}
}