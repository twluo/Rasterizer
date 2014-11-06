#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "string"
#include "Vector3.h"
#include "Vector4.h"

#define M_PI 3.14159265358979323846

class Matrix4
{
  protected:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    Matrix4();     
    Matrix4& operator=(const Matrix4&);
    double* getPointer(); 
    void identity(); 
    void transpose();
    void makeRotateY(double);

	Matrix4& operator*(const Matrix4&);
	Vector4& operator*(const Vector4&);

	void makeRotateX(double);
	void makeRotateZ(double);
	void makeRotate(double, const Vector3&);
	void makeScale(double, double, double);
	void makeTranslate(double, double, double);
	void print(std::string);
	double get(int, int);
	void set(int, int, double);
	
};

#endif