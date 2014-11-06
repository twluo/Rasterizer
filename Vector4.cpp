#include <math.h>
#include <iostream>
#include "Vector4.h"

Vector4::Vector4(double x, double y, double z, double w) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Vector4& Vector4::operator+(const Vector4& v2) {
	for (int i = 0; i < 4; i++) {
		v[i] = v[i] + v2.v[i];
	}
	return *this;
}

Vector4& Vector4::operator-(const Vector4& v2) {
	for (int i = 0; i < 4; i++) {
		v[i] = v[i] - v2.v[i];
	}
	return *this;
}


double Vector4::getValue(int i){
	return v[i];
}

void Vector4::dehomogenize() {
	for (int i = 0; i < 4; i++) {
		v[i] = (v[i] / v[3]);
	}
}

void Vector4::print(std::string cmt){
	std::cout << cmt << "\n" << v[0] << ", " << v[1] << ", " << v[2]
		<< ", " << v[3] << std::endl;
}


void Vector4::setValue(int pos, double val) {
	v[pos] = val;
}

void Vector4::translate(double tx, double ty, double tz) {
	v[0] = tx;
	v[1] = ty;
	v[2] = tz;
}

void Vector4::reset() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

double Vector4::get(int x) {
	return v[x];
}

void Vector4::set(Vector3 temp) {
	v[0] = temp.getX();
	v[1] = temp.getY();
	v[2] = temp.getZ();
	v[3] = 1;
}