#ifndef  IJ_H_
#define  IJ_H_

#include "cocos2d.h"
#include "defs.h"

/*
 * Key for the sparse matrix, made from i and j values.
 */
struct IJ {
	int i, j;

	IJ(int i, int j) : i(i), j(j) {}

	// Comparison operators (required for map use).
	bool operator==(const IJ& other) const;
	bool operator<(const IJ& other) const;

	// Convert to world point
	cocos2d::Point toPoint() const;

	// Get the i,j coordinates in which the point is contained.
	static IJ IJ::fromPoint(const cocos2d::Point& point);
	static IJ fromPoint(float x, float y);
};

#endif  IJ_H_