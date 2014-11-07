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
Light::Light(Vector3 color, double brightness, Vector3 pos) {
	color = color;
	brightness = brightness;
	pos = pos;
}
Vector3 Light::getColor() {
	return color;
}
double Light::getBrightness(){
	return brightness;
}
void Light::setColor(Vector3 color){
	color = color;
}
void Light::setBrightness(double brightness){
	brightness = brightness;
}
Vector3 Light::getPos(){
	return pos;
}
void Light::setPos(Vector3 pos){
	pos = pos;
}