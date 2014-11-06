#ifndef _HOUSE_H_
#define _HOUSE_H_

#include "Matrix4.h"
#include "Vector3.h"
#include <vector>

class House
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)


public:
	House();   // Constructor
	Matrix4& getMatrix();
	void draw();
	void load();
	std::vector<Vector3> points;
	std::vector<Vector3> color;
};

#endif
