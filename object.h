#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Matrix4.h"
#include "Vector3.h"

class Object
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
	Vector3* center;                 // center of cube
	bool rotation;

public:
	Object();   // Constructor
	Matrix4& getMatrix();
	void spin(double);      // spin cube [degrees]
	void move(double, double, double);
	void reset();
	void orbit(bool);
	void scale(double);
	bool getRotation();
	void flipRotation();
	void spinX(double);
};

#endif

