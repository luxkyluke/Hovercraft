#include "Ballon.h"
#include "common.h"


void MakeBallon(GLuint texture, Point2D pos, Ballon* ballon, float ballRadius){
	if(!ballon) {
		printf("Impossible de créer le ballon, pointeur non alloué\n"); 
		return;
	}
    ballon->texture = texture;
    ballon->direction = VectorXY(0,ballRadius);
    ballon->vitesse = VectorXY(0,0);
    ballon-> acceleration = VectorXY(0,0.);
    ballon->cercle = (Cercle*) malloc(sizeof(Cercle));
    MakeCercle(ballon->cercle, pos, ballRadius);
}


void UpdateVitesseBall(Ballon* h){
		h-> vitesse = AddVectors(h-> vitesse, h-> acceleration);
		h-> vitesse = SubVectors(h-> vitesse, DivVector(h-> vitesse, 300.));
	return;
}

void UpdatePositionBall(Ballon* h){
	/*if(!EstDansTerrain(PointXY(h->cercle->centre.x += h-> vitesse.x, h->cercle->centre.y += h-> vitesse.y))){
		h->cercle->centre.x -= h-> vitesse.x;
		h->cercle->centre.y -= h-> vitesse.y;
		return;
	}*/
	h->cercle->centre.x += h-> vitesse.x;
	h->cercle->centre.y += h-> vitesse.y;
	return;
}


void UpdateBallon(Ballon* b){
	UpdateVitesseBall(b);
	UpdatePositionBall(b);
    return;
}

void DessinBallon(Ballon* ball) {
	float angle, radian=0,x,y,tx,ty,xcos,ysin;
	glPushMatrix();
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, ball->texture);
	    glTranslatef(ball->cercle->centre.x, ball->cercle->centre.y, 0);
	    glScalef(ball->cercle->radius, ball->cercle->radius, 1);
	    glColor3f(255, 255, 255);
	    glBegin(GL_POLYGON);
	        for (angle=0.0; angle<360.0; angle+=2.0) {
	            radian = angle * (3.14/180.0f);
	            xcos = (float)cos(radian);
	            ysin = (float)sin(radian);
	            x = xcos;
	            y = ysin;
	            tx = xcos * 0.5 + 0.5;
	            ty = ysin * 0.5 + 0.5;
	            glTexCoord2f(tx, ty);
	            glVertex2f(x, y);
	        }
	    glEnd();
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_TEXTURE_2D);
   	glPopMatrix();

}


