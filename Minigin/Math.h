#pragma once
#include <cmath>
bool AreEqual(float A, float B, float epsilon = 0.005f)
{
	return (std::fabs(A - B) < epsilon);
}