#ifndef _PROJECTION_H_
#define _PROJECTION_H_

#include "Matrix4.h"
#include "Vector3.h"

class Projection
{
protected:
	Matrix4 camera2projection;

public:
	Projection();   // Constructor
	Matrix4& getMatrix();
	void set(double, double, double, double);
};

#endif

