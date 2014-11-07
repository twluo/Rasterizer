#include "camera.h"
#include "Matrix4.h"
#include "Vector3.h"

Camera::Camera() {
	e = new Vector3(0.0, 0.0, 0.0);
	up = new Vector3(0.0, 0.0, 0.0);
	d = new Vector3(0.0, 0.0, 0.0);
	world2camera.identity();
}

void Camera::set(Vector3& a, Vector3& b, Vector3& c) {
	e = &a;
	d = &b;
	up = &c;
	Matrix4 translation;
	Matrix4 rotation;
	translation.identity();
	rotation.identity();
	Vector3* x = new Vector3(0.0, 0.0, 0.0);
	Vector3* y = new Vector3(0.0, 0.0, 0.0);
	Vector3* z = new Vector3(0.0, 0.0, 0.0);
	*z = *e - *d;
	z->normalize();
	*x = x->cross(*up, *z);
	x->normalize();
	*y = y->cross(*z, *x);
	y->normalize();
	e->negate();
	translation.makeTranslate(e->getX(), e->getY(), e->getZ());
	for (int i = 0; i < 3; i++) {
		rotation.set(i, 0, x->get(i));
		rotation.set(i, 1, y->get(i));
		rotation.set(i, 2, z->get(i));
	}
	rotation.transpose();
	world2camera = rotation * translation;

}

Matrix4& Camera::getMatrix() {
	return world2camera;
}