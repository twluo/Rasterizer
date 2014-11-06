#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Matrix4.h"
#include "Vector3.h"

class Viewport
{
protected:
	Matrix4 projection2viewport;

public:
	Viewport();   // Constructor
	Matrix4& getMatrix();
	void set(double, double, double, double);
};

#endif

