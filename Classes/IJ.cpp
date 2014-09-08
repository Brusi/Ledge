#include "IJ.h"

USING_NS_CC;

bool IJ::operator==(const IJ& other) const
{
	return this->i == other.i && this->j == other.j;
}

bool IJ::operator<(const IJ& other) const
{
	if (this->i != other.i) {
		return this->i < other.i;
	}
	return this->j < other.j;
}

Point IJ::toPoint() const
{
	return Point(this->i * defs::SIZE + defs::RADIUS,
				 this->j * defs::SIZE + defs::RADIUS);
}

IJ IJ::fromPoint(float x, float y)
{
	int i = floor(x / defs::SIZE);
	int j = floor(y / defs::SIZE);

	return IJ(i, j);
}

IJ IJ::fromPoint(const cocos2d::Point& point)
{
	return IJ::fromPoint(point.x, point.y);
}