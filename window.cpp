#ifdef _WIN32
#include <windows.h>
#endif

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

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];
Bunny* bunny = new Bunny();
Dragon* dragon = new Dragon();
House* house = new House();
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
	bunny->load();
	dragon->load();
	house->load();

	camera.set(Vector3(0.0, 10.0, 10.0), Vector3(0, 0, 0), Vector3(0, 1, 0));
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

void rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	Matrix4 m;
	cout << "TEST" << endl;
	m.identity();
	m = viewport.getMatrix() * projection.getMatrix() * camera.getMatrix() * object.getMatrix();
	Vector3 *temp = new Vector3(0,0,0);
	Vector4 *temp4 = new Vector4(0,0,0,0);
	if (show == 0) {
		for (unsigned i = 0; i < house->color.size(); i++) {
			*temp = house->color[i];
			temp4->set(*temp);
			*temp4 = m * *temp4;
			drawPoint(temp4->get(0), temp4->get(1), 255, 0, 0);
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
// Called whenever the window size changes
void reshapeCallback(int new_width, int new_height)
{
	window_width = new_width;
	window_height = new_height;
	delete[] pixels;
	pixels = new float[window_width * window_height * 3];
	projection.set(60.0, double(window_width) / double(window_height), 1.0, 1000.0);
	viewport.set(0, 0, double(new_width), double(new_height));
	displayCallback();
}

void keyboardCallback(unsigned char key, int, int)
{
	cerr << "Key pressed: " << key << endl;
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
	glutMainLoop();
}