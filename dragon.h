#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "Matrix4.h"
#include "Vector3.h"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include "Window.h"
#include "Matrix4.h"

class Dragon
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)


public:
	Dragon();   // Constructor
	std::vector<Vector3> points;
	std::vector<Vector3> normals;
	double sX, sY, sZ, lX, lY, lZ;
	Vector3 *color;
	Matrix4& getMatrix();
	void draw(double, double);
	void load(double);
	void scale(double);
	void move(double, double, double);
	void reset();
};

#endif
