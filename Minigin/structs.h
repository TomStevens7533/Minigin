#pragma once
struct Rectf
{
	float x;
	float y;
	float width;
	float height;

	bool operator==(const Rectf& rhs);
};
