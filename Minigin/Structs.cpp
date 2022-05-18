#include "MiniginPCH.h"
#include "structs.h"
#include "Math.h"

using namespace dae;
bool Rectf::operator==(const Rectf& rhs)
{
	if (AreEqual(x, rhs.x) && AreEqual(y, rhs.y) && AreEqual(width, rhs.width) && AreEqual(height, rhs.height))
		return true;

	return false;
	
}

