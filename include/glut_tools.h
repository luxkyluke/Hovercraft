#ifndef _GLUT_TOOLS_H_
#define _GLUT_TOOLS_H_

#include <GL/gl.h>
#include <GL/glut.h>


void initGlut(int windowW, int windowH);
void vBitmapOutput(int x, int y, char *string, void *font);
void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);

#endif
