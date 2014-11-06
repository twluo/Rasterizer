#include <iostream>

#include <GL/glut.h>
#include <GL/GL.h>
#include "Window.h"
#include "bunny.h"
#include "Matrix4.h"
#include <vector>
#include <fstream>
#include <iostream>

Bunny::Bunny()
{

	std::vector<Vector3> points = std::vector<Vector3>();
	std::vector<Vector3> normals = std::vector<Vector3>();
	sX = 0;
	sY = 0;
	sZ = 0;
	lX = 0;
	lY = 0;
	lZ = 0;
}

Matrix4& Bunny::getMatrix()
{
	return model2world;
}

void Bunny::draw(double width, double height) {
	glBegin(GL_POINTS);
	Matrix4 mat;
	for (unsigned i = 0; i < normals.size(); i++) {
		glNormal3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
		glColor3d(normals[i].getX(), normals[i].getY(), normals[i].getZ());
		glVertex3d(points[i].getX(), points[i].getY(), points[i].getZ());
	}
	glEnd();
}


void Bunny::load() {
	std::ifstream file;
	Vector3* normal;
	Vector3* point;
	file.open("bunny.xyz");
	normals.clear();
	points.clear();
	sX = 10;
	sY = 10;
	sZ = 10;
	lX = 0;
	lY = 0;
	lZ = 0;
	std::cout << "Read" << std::endl;
	double x, y, z, nX, nY, nZ;
	while (file >> x >> y >> z >> nX >> nY >> nZ) {
		normal = new Vector3(nX, nY, nZ);
		point = new Vector3(x, y, z);
		normal->normalize();
		normals.push_back(*normal);
		points.push_back(*point);
		if (x < sX)
			sX = x;
		if (x > lX)
			lX = x;
		if (y < sY)
			sY = y;
		if (y > lY)
			lY = y;
		if (z < sZ)
			sZ = z;
		if (z > lZ)
			lZ = z;
	}
}
void Bunny::reset() {
	model2world.identity();
}
void Bunny::scale(double x) {
	Matrix4 mat;
	mat.makeScale(x, x, x);
	model2world = model2world * mat;
}
void Bunny::move(double x, double y, double z) {
	Matrix4 mat;
	mat.makeTranslate(x, y, z);
	model2world = mat * model2world;
}