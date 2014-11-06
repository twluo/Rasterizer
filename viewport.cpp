#include "viewport.h"
#include "Matrix4.h"
#include "Vector3.h"

Viewport::Viewport() {
	projection2viewport.identity();
}

void Viewport::set(double x0, double x1, double y0, double y1) {
	double temp = 0;
	temp = (x1 - x0) / 2;
	projection2viewport.set(0, 0, temp);
	temp = (y1 - y0) / 2;
	projection2viewport.set(1, 1, temp);
	projection2viewport.set(2, 2, 1 / 2);
	temp = (x0 + x1) / 2;
	projection2viewport.set(3, 0, temp);
	temp = (y0 + y1) / 2;
	projection2viewport.set(3, 1, temp);
	projection2viewport.set(3, 2, 1 / 2);
}

Matrix4& Viewport::getMatrix() {
	return projection2viewport;
}