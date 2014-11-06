#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
protected:
	Matrix4 world2camera;            // model matrix (transforms model coordinates to world coordinates)
	Vector3*  e;
	Vector3* d;
	Vector3* up;

public:
	Camera();   // Constructor
	Matrix4& getMatrix();
	void set(Vector3&, Vector3&, Vector3&);
};

#endif

