/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */

#include "Geometry.h"
#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>

Vector2D Vector(Point2D A, Point2D B) {
    return VectorXY(B.x - A.x, B.y - A.y);
}

Point2D PointPlusVector(Point2D O, Vector2D v) {
    return PointXY(O.x + v.x, O.y + v.y);
}

int IsZero(float x) {
    return x > -EPSILON && x < EPSILON;
}

void dessinCarre(int fill, float r, float v, float b){
  if (fill == 1){
    glBegin(GL_QUADS);
      glColor3f(r,v,b);
      glVertex2f(-0.5,0.5); //point de depart
      glVertex2f(0.5,0.5); //point d’arrive
      glVertex2f(0.5,-0.5);
      glVertex2f(-0.5,-0.5);
    glEnd();
  }
  else{
    glBegin(GL_LINE_LOOP);
      glColor3f(r,v,b);
      glVertex2f(-0.5,0.5); //point de depart
      glVertex2f(0.5,0.5); //point d’arrive
      glVertex2f(0.5,-0.5);
      glVertex2f(-0.5,-0.5);
    glEnd();
  }
}

void dessinCercle(int n, float r, float v, float b, int fill){
  int i;
  double Pi = 3.14;
  float mycos, mysin;
  if (fill == 0){
    glBegin(GL_LINE_LOOP);
    glColor3f(r, v, b);
    for (i=0; i<n; i++){
      mycos = cos(i*2*Pi/n)/2;
      mysin = sin(i*2*Pi/n)/2;
      glVertex2f(mycos, mysin);
    }
    glEnd();
  }
  else{
    glBegin(GL_POLYGON);
    glColor3f(r, v, b);
    for (i=0; i<n; i++){
      mycos = cos(i*2*Pi/n)/2;
      mysin = sin(i*2*Pi/n)/2;
      glVertex2f(mycos, mysin);
    }
  glEnd();
  }
}


void MakeCercle(Cercle* c, Point2D position, float radius) {
  if (c==NULL) {
    printf("Le cercle est NULL\n");
    return;
  }
  c->centre = position;
  c->radius = radius;
  c->radiusCarre = radius*radius;
}

