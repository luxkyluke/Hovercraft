#ifndef _GLUT_TOOLS_H_
#define _GLUT_TOOLS_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#include "Color3f.h"


void initGlut(int argc, char** argv);
void vBitmapOutput(int x, int y, char *string, void *font);
//void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font, Color3f color);
void drawOnGlut(int x, int y, char *string, void *font);

#endif
