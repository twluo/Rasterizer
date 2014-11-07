#include "Vector4.h"
#include "Vector3.h"
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include "Window.h"
#include "Matrix4.h"
#include "light.h"

Light::Light() {

}
Light::Light(Vector3 c, double b, Vector3 p) {
	color = c;
	brightness = b;
	pos = p;
}
Vector3 Light::getColor() {
	return color;
}
double Light::getBrightness(){
	return brightness;
}
void Light::setColor(Vector3 cr){
	color = cr;
}
void Light::setBrightness(double b){
	brightness = b;
}
Vector3 Light::getPos(){
	return pos;
}
void Light::setPos(Vector3 p){
	pos = p;
}