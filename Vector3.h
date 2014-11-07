#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "string"

#define M_PI 3.14159265358979323846

class Vector3 {
	protected:
		double v[3];   // array elements

	public:
		Vector3();
		Vector3(double, double, double);
		Vector3& operator+(const Vector3&);
		Vector3& operator-(const Vector3&);
		void negate();
		void scale(double);
		double dot(const Vector3&, const Vector3&);
		Vector3 cross(const Vector3&, const Vector3&);
		double length();
		void normalize();
		void print(std::string);
		double getX();
		double getY();
		double getZ();
		void translate(double, double, double);
		void reset();
		double get(int);
		void orbit(double);
		void set(double, double, double);
		Vector3 comp(Vector3, Vector3);
		void set(Vector3);
};

#endif