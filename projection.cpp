#include "projection.h"
#include "Matrix4.h"
#include "Vector3.h"

Projection::Projection() {
	camera2projection.identity();
}

void Projection::set(double fov, double aspect, double near, double far) {
	double temp = 0;
	temp = 1 / (aspect*tan((fov*M_PI/180) / 2));
	camera2projection.set(0, 0, temp);
	temp = 1 / (tan((fov*M_PI / 180) / 2));
	camera2projection.set(1, 1, temp);
	temp = (near + far) / (near - far);
	camera2projection.set(2, 2, temp);
	temp = (2 * near*far) / (near - far);
	camera2projection.set(2, 3, temp);
	camera2projection.set(3, 2, -1);
	camera2projection.set(3, 3, 0);
}

Matrix4& Projection::getMatrix() {
	return camera2projection;
}