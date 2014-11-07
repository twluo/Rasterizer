#ifdef _WIN32
#include <windows.h>
#endif
#include <fstream>
#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "bunny.h"
#include "dragon.h"
#include "house.h"
#include "camera.h"
#include "projection.h"
#include "viewport.h"
#include "object.h"
#include "light.h"

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
static double* zBuffer = new double[window_width * window_height];
Bunny* bunny = new Bunny();
Dragon* dragon = new Dragon();
House* house = new House();
Light* light = new Light(Vector3(1,1,1),20.0, Vector3(-3,15,0));
boolean shadow = false;
boolean zBuff = false;
boolean drawBig = false;
using namespace std;
static int show = 0;
static Camera camera;
static Projection projection;
static Viewport viewport;
static Object object;

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};
void loadData()
{
	bunny->load(double(window_width)/double(window_height));
	dragon->load(double(window_width) / double(window_height));
	house->load();
	projection.set(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
	viewport.set(0, 0, double(window_width), double(window_height));
	camera.set(Vector3(0.0, 0.0, 20), Vector3(0, 0, 0), Vector3(0, 1, 0));
	object.reset();
}

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}
int size(double z) {
	return 2 / z;
}
// Draw a point into the frame buffer


void clearZBuffer() {
	for (int i = 0; i < window_width*window_height; ++i) {
		zBuffer[i] = 1.0;
	}
}

boolean setZBuffer(int x, int y, double z) {
	int index = y*window_width + x;
	if (!zBuff)
		return true;
	else {
		if (index < 0 || index > window_width*window_height) {
			return false; 
		}
		if (zBuffer[index] >= z) {
			zBuffer[index] = z;
			return true;
		}
		else
			return false;
	}
}
int calculateSize(double z) {
	int size = 0;
	if (z < 1) {
		size = 1;
	}
	if (z < 0.98) {
		size = 3;
	}
	if (z < 0.96) {
		size = 5;
	}
	if (z < 0.94) {
		size = 7;
	}
	if (z < 0.92) {
		size = 9;
	}
	if (z < 0.90) {
		size = 11;
	}
	if (z < 0.88) {
		size = 13;
	}
	if (z < 0.86) {
		size = 15;
	}
	if (z < 0.84) {
		size = 17;
	}
	if (z < 0.82) {
		size = 19;
	}
	if (z < 0.80) {
		size = 21;
	}
	if (z < 0.78) {
		size = 23;
	}
	if (z < 0.76) {
		size = 25;
	}
	if (z < 0.74) {
		size = 27;
	}
	if (z < 0.72) {
		size = 29;
	}
	if (z < 0.70) {
		size = 31;
	}
	return size;
}
void drawPoint(int x, int y, float r, float g, float b, double z)
{
	if (!drawBig) {
		int offset = y*window_width * 3 + x * 3;
		pixels[offset] = r;
		pixels[offset + 1] = g;
		pixels[offset + 2] = b;
	}
	else {
		int scale = calculateSize(z);
		for (int i = y - scale; i < y + scale; i++) {
			for (int j = x - scale; j < x + scale; j++) {
				if (setZBuffer(j, i, z)) {
					int offset = i*window_width * 3 + j * 3;
					if (offset < window_width * window_height * 3 - 3 && offset > 0) {
						pixels[offset] = r;
						pixels[offset + 1] = g;
						pixels[offset + 2] = b;
					}
				}
			}
		}
	}
}
 Vector3 applyLightning(Vector3 point, Vector3 normal, Vector3 color) {
	 if (!shadow)
		 return color;
	 else {
		 double brightness = light->getBrightness();
		 Matrix4 o2w = object.getMatrix();
		 Vector4 point4;
		 point4.setPoint(point);
		 point4 = o2w * point4;
		 Vector4 normal4;
		 normal4.setVector(normal);
		 normal4 = o2w * normal4;
		 Vector4 light4;
		 light4.setPoint(light->getPos());
		 Vector3 light3;
		 light3.set(light4.get(0), light4.get(1), light4.get(2));
		 Vector3 point3;
		 point3.set(point4.get(0), point4.get(1), point4.get(2));
		 Vector3 normal3; 
		 normal3.set(normal4.get(0), normal4.get(1), normal4.get(2));
		 Vector3 L;
		 //light4->print("l4");
		 //light3->print("l3");
		 //point3->print("p3");
		 //normal3->print("n3");
		 L.set(light3 - point3);
		 //L->print("L");
		 double s = L.length();
		 //cout << "length = " << s << endl;
		 L.normalize();

		 //L->print("noraml L");
		 s = s * M_PI;
		 s = brightness / s;
		 //cout << "dot " << L->dot(*L, *normal3) << endl;
		 s = s * L.dot(L, normal3);
		// cout << "Scale " << s << endl;
		 Vector3 newColor;
		 newColor.set(color.comp(color, light->getColor()));
		 newColor.scale(s);
		 //newColor->print("COLOR");
		 return newColor;
	 }

}
void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	Matrix4 m;
	m = projection.getMatrix() * camera.getMatrix() * object.getMatrix();
	Vector3 temp;
	Vector4 temp4;
	double z = 0;
	if (show == 0) {
		vector<Vector3> point = bunny->points;
		vector<Vector3> normal = bunny->normals;
		Vector3 *Bcolor = bunny->color;
		for (unsigned i = 0; i < point.size(); i++) {
			temp = point[i];
			temp4.setPoint(temp);
			temp4 = m * temp4;
			temp4.dehomogenize();
			temp4 = viewport.getMatrix() * temp4;
			if (temp4.get(0) < window_width && temp4.get(0) > 0 && temp4.get(1) < window_height && temp4.get(1) > 0) {
				if (setZBuffer(temp4.get(0), temp4.get(1), temp4.get(2))) {
					Vector3 color = applyLightning(point[i], normal[i], *Bcolor);
					drawPoint(temp4.get(0), temp4.get(1), color.getX(), color.getY(), color.getZ(), temp4.get(2));
				}
			}
		}
	}
	else if (show == 1) {
		vector<Vector3> point = dragon->points;
		vector<Vector3> normal = dragon->normals;
		Vector3 *Bcolor = dragon->color;
		for (unsigned i = 0; i < point.size(); i++) {
			temp = point[i];
			temp4.setPoint(temp);
			temp4 = m * temp4;
			temp4.dehomogenize();
			temp4 = viewport.getMatrix() * temp4;
			if (temp4.get(0) < window_width && temp4.get(0) > 0 && temp4.get(1) < window_height && temp4.get(1) > 0) {
				if (setZBuffer(temp4.get(0), temp4.get(1), temp4.get(2))) {
					Vector3 color = applyLightning(point[i], normal[i], *Bcolor);
					drawPoint(temp4.get(0), temp4.get(1), color.getX(), color.getY(), color.getZ(), temp4.get(2));
				}
			}
		}
	}
}

void displayCallback()
{
	clearBuffer();
	clearZBuffer();
	rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

void idleCallback() {
	//object.spin(10);
	displayCallback();
}
// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	delete[] zBuffer;
	zBuffer = new double[window_width*window_height];
	pixels = new float[window_width * window_height * 3];
	projection.set(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
	viewport.set(0, 0, double(window_width), double(window_height));
	displayCallback();
}

void keyboardCallback(unsigned char key, int x, int y)
{
	switch (key) {
		// toggles direction of spin between clockwise and counterclockwise
	case 't':
		object.flipRotation();
		break;
		// moves cube left
	case 'x':
		object.move(1, 0, 0);
		break;
		// moves cube right
	case 'X':
		object.move(-1, 0, 0);
		break;
		// moves cube down
	case 'y':
		object.move(0, 1, 0);
		break;
		// moves cube up
	case 'Y':
		object.move(0, -1, 0);
		break;
		// moves cube towards screen
	case 'z':
		object.move(0, 0, -1);
		break;
		// moves cube away from screen
	case 'Z':
		object.move(0, 0, 1);
		break;
		// resets cube position
	case 'r':
		object.reset();
		break;
		// orbits cube counterclockwise
	case 'o':
		object.orbit(true);
		break;
		// orbits cube clockwise
	case 'O':
		object.orbit(false);
		break;
		// scales cube down
	case 's':
		object.scale(10.0 / 11.0);
		break;
		// scales cube up
	case 'S':
		object.scale(11.0 / 10.0);
		break;
	case'1':
		shadow = false;
		zBuff = false;
		drawBig = false;
		cout << "normal" << endl;
		break;
	case'2':
		shadow = true;
		zBuff = false;
		drawBig = false;
		cout << "shadow" << endl;
		break;	  
	case'3':
		zBuff = true;
		shadow = true;
		drawBig = false;
		cout << "zBuff" << endl;
		break;
	case '4':
		zBuff = true;
		shadow = true;
		drawBig = true;
		cout << "drawBig" << endl;
		break;
	case 'q':
		object.spin(5.0);
		break;
	case 'Q':
		object.spin(-5.0);
		break;
	case 'w':
		object.spinX(5.0);
		break;
	case 'W':
		object.spinX(-5.0);
		break;
	}

}
void funcKeyboardCallback(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		show = 0;
		break;
	case GLUT_KEY_F2:
		show = 1;
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("Rasterizer");

	loadData();
	glutReshapeFunc(reshapeCallback);
	glutDisplayFunc(displayCallback);
	glutKeyboardFunc(keyboardCallback);
	glutIdleFunc(idleCallback);
	glutSpecialFunc(funcKeyboardCallback);
	glutMainLoop();
}