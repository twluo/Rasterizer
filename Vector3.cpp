#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include "Vector3.h"
#include "Vector4.h"

Vector3::Vector3() {

}

Vector3::Vector3(double x, double y, double z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3& Vector3::operator+(const Vector3& v2) {
	Vector3 temp;
	for (int i = 0; i < 3; i++) {
		temp.v[i] = v[i] + v2.v[i];
	}
	return temp;
}

Vector3& Vector3::operator-(const Vector3& v2) {
	Vector3 temp;
	for (int i = 0; i < 3; i++) {
		temp.v[i] = v[i] - v2.v[i];
	}
	return temp;
}


void Vector3::negate() {
	for (int i = 0; i < 3; i++) {
		v[i] = v[i] * (-1);
	}
}

void Vector3::scale(double s) {
	for (int i = 0; i < 3; i++) {
		v[i] = v[i] * s;
	}
}

double Vector3::dot(const Vector3& v1, const Vector3& v2) {
	double result = 0;

	for (int i = 0; i < 3; i++) {
		result += (v1.v[i] * v2.v[i]);
	}

	return result;
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
	Vector3 temp;
	
	double x= (v1.v[1] * v2.v[2]) - (v1.v[2] * v2.v[1]);
	double y = - (v1.v[0] * v2.v[2]) + (v1.v[2] * v2.v[0]);
	double z = (v1.v[0] * v2.v[1]) - (v1.v[1] * v2.v[0]);
	temp.set(x, y, z);
	return temp;
}

double Vector3::length() {
	double len = 0;

	for (int i = 0; i < 3; i++) {
		len += v[i] * v[i];
	}

	return sqrt(len);
}

void Vector3::normalize() {
	scale(1 / length());
}

void Vector3::print(std::string cmt) {
	std::cout << cmt << "\n" << v[0] << ", " << v[1] << ", " << v[2]
		<<  std::endl;
}

double Vector3::getX() {
	return v[0];
}

double Vector3::getY() {
	return v[1];
}

double Vector3::getZ() {
	return v[2];
}

void Vector3::translate(double tx, double ty, double tz) {
	v[0] += tx;
	v[1] += ty;
	v[2] += tz;
}

void Vector3::reset() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

void Vector3::orbit(double angle) {
	angle = angle / 180.0 * M_PI;  // convert from degrees to radians

	double x = v[0];
	double y = v[1];

	v[0] = x * cos(angle) + y * -sin(angle);
	v[1] = x * sin(angle) + y * cos(angle);
	v[2] = v[2];
}

double Vector3::get(int x) {
	return v[x];
}

void Vector3::set(double x, double y, double z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3 Vector3::comp(Vector3 x, Vector3 y) {
	Vector3 temp;
	temp.set(x.v[0] * y.v[0], x.v[1] * y.v[1], x.v[2] * y.v[2]);
	return temp;
}

void Vector3::set(Vector3 temp) {
	v[0] = temp.v[0];
	v[1] = temp.v[1];
	v[2] = temp.v[2];
}