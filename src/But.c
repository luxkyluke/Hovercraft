#include "But.h"
#include "Geometry.h"
#include <stdio.h>


void MakeBut(Point2D top, Point2D bottom, But* b) {
    if (b == NULL) {
        printf("Le but est NULL\n");
        return;
    }
    b->top = top;
    b->bottom = bottom;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    float x = getXTerrain(ball->cercle->centre.x);
    float y = getYTerrain(ball->cercle->centre.y);
    if(abs(x) < but->top.x
        && abs(x) > but->bottom.x
        && y < but->bottom.y
        && y > but->top.y){
        printf("GOAAAAL !\n");
        return true;
    }
    return false;
}

void DessinBut(But* b){
	int testy= (int)b->top.y;
    float top_y = getYSDL(testy);
    float bottom_x = getXSDL((int)b->bottom.x);
    float bottom_y = getYSDL((int)b->bottom.y);
    float hauteur = (b->bottom.y) - (b->top.y);
    float translate_y = 0.;
    translate_y = (bottom_y - top_y)*0.5;

    glPushMatrix();
//        glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, b->texture);

    	glTranslatef(bottom_x, 0, 0);
        glScalef(2, hauteur, 1.f);
        dessinCarre(1, 255, 0, 0);

        //glColor3f(255, 0, 0);

//        glBindTexture(GL_TEXTURE_2D, 0);
//        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
