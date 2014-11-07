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
Bunny* bunny = new Bunny();
Dragon* dragon = new Dragon();
House* house = new House();
Light* light = new Light(Vector3(1,1,1), 20, Vector3(-10,10,0));
boolean shadow = false;
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

// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*window_width * 3 + x * 3;
	pixels[offset] = r;
	pixels[offset + 1] = g;
	pixels[offset + 2] = b;
}
 //applyLightning(vector<Vector3> point, vector<Vector3> normal, Vector3 color) {
	

//}
void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	Matrix4 m;
	m = projection.getMatrix() * camera.getMatrix() * object.getMatrix();
	Vector3 *temp = new Vector3(0,0,0);
	Vector4 *temp4 = new Vector4(0,0,0,0);
	if (show == 0) {
		vector<Vector3> point = bunny->points;
		vector<Vector3> normal = bunny->normals;
		Vector3 *color = bunny->color;
		for (unsigned i = 0; i < point.size(); i++) {
			*temp = point[i];
			temp4->set(*temp);
			*temp4 = m * *temp4;
			temp4->dehomogenize();
			*temp4 = viewport.getMatrix() * *temp4;
			if (temp4->get(0) < window_width && temp4->get(0) > 0 && temp4->get(1) < window_height && temp4->get(1) > 0) {
				if (!shadow) 
					drawPoint(temp4->get(0), temp4->get(1), color->getX(), color->getY(), color->getZ());
			}
		}
	}
	else if (show == 1) {
		vector<Vector3> point = dragon->points;
		Vector3 *color = dragon->color;
		for (unsigned i = 0; i < point.size(); i++) {
			*temp = point[i];
			temp4->set(*temp);
			*temp4 = m * *temp4;
			temp4->dehomogenize();
			*temp4 = viewport.getMatrix() * *temp4;
			if (temp4->get(0) < window_width && temp4->get(0) > 0 && temp4->get(1) < window_height && temp4->get(1) > 0)
				drawPoint(temp4->get(0), temp4->get(1), color->getX(), color->getY(), color->getZ());
		}
	}
}

void displayCallback()
{
	clearBuffer();
	rasterize();

	// glDrawPixels writes a block of pixels to the framebuffer
	glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

	glutSwapBuffers();
}

void idleCallback() {
	displayCallback();
}
// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	projection.set(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
	viewport.set(0, 0, double(window_width), double(window_height));
	displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
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
		break;
	case'2':
		shadow = true;
		cout << "shadow" << endl;
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