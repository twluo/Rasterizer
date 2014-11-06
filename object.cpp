#include "Object.h"
#include "Matrix4.h"
#include "Vector4.h"
#include <GL/glut.h>

using namespace std;

Object::Object()
{
	center = new Vector3(0.0, 0.0, 0.0);
	rotation = true;
}

Matrix4& Object::getMatrix()
{
	return model2world;
}

void Object::spin(double deg)   // deg is in degrees
{
	Matrix4 mat;
	mat.makeRotateY(deg);
	model2world = model2world * mat;
}

void Object::spinX(double deg)   // deg is in degrees
{
	Matrix4 mat;
	mat.makeRotateX(deg);
	model2world = model2world * mat;
}

void Object::move(double x, double y, double z) {
	Matrix4 mat;
	mat.makeTranslate(x, y, z);
	model2world = mat * model2world;
	center->translate(x, y, z);
}

void Object::reset() {
	model2world.identity();
	center->reset();
	rotation = true;
}

void Object::orbit(bool counter) {
	Matrix4 mat;
	const Vector3* axis = new Vector3(0, 0, 1);
	if (counter) {
		mat.makeRotate(10, *axis);
		center->orbit(10);
	}
	else {
		mat.makeRotate(-10, *axis);
		center->orbit(-10);
	}
	model2world = mat * model2world;
}

void Object::scale(double x) {
	Matrix4 mat;
	mat.makeScale(x, x, x);
	model2world = model2world * mat;
}

bool Object::getRotation() {
	return rotation;
}

void Object::flipRotation() {
	rotation = !rotation;
}

