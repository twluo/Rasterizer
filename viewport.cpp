#include "viewport.h"
#include "Matrix4.h"
#include "Vector3.h"
#include <iostream>
#include <stdio.h>

Viewport::Viewport() {
	projection2viewport.identity();
}

void Viewport::set(double x0, double y0, double x1, double y1) {
	double temp = 0;
	temp = (x1 - x0) / 2;
	projection2viewport.set(0, 0, temp);
	temp = (y1 - y0) / 2;
	projection2viewport.set(1, 1, temp);
	temp = (1.0 / 2);
	projection2viewport.set(2, 2, temp);
	projection2viewport.set(2, 3, temp);
	temp = (x0 + x1) / 2;
	projection2viewport.set(0, 3, temp);
	temp = (y0 + y1) / 2;
	projection2viewport.set(1, 3, temp);
}

Matrix4& Viewport::getMatrix() {
	return projection2viewport;
}