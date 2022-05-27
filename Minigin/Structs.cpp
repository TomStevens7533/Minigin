#include "MiniginPCH.h"
#include "structs.h"
#include "MathHelper.h"

using namespace dae;
bool Rectf::operator==(const Rectf& rhs)
{
	if (MathHelper::AreEqual(x, rhs.x) && MathHelper::AreEqual(y, rhs.y) && MathHelper::AreEqual(width, rhs.width) && MathHelper::AreEqual(height, rhs.height))
		return true;

	return false;
	
}

