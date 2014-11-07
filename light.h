#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vector4.h"
#include "Vector3.h"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include "Window.h"
#include "Matrix4.h"

class Light
{
protected:
	Vector3 pos;          // model matrix (transforms model coordinates to world coordinates)
	Vector3 color;
	double brightness;


public:
	Light();   // Constructor
	Light(Vector3, double, Vector3);
	Vector3 getColor();
	double getBrightness();
	void setColor(Vector3 color);
	void setBrightness(double);
	Vector3 getPos();
	void setPos(Vector3);
};

#endif
