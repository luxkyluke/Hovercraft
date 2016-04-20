#include "But.h"
#include "Geometry.h"
#include <stdio.h>


void MakeBut(Point2D top, Point2D bottom, But* b, Player p) {
    if (b == NULL) {
        printf("Le but est NULL\n");
        return;
    }
    b->top = top;
    b->bottom = bottom;
    b->player = p;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    float x = getXSDL(but->top.x);
    float topy = getYSDL(but->top.y);
    float bottomy = getYSDL(but->bottom.y);

    if(ball->cercle->centre.y < bottomy && ball->cercle->centre.y > topy){
    	return false;
    }
    if(x>0){
    	if(ball->cercle->centre.x >= x){
			//printf("GOAAAAL pour player%d!\n", but->player);
    		return true;
    	}
    }
	else if (ball->cercle->centre.x <= x){
		//printf("GOAAAAL pour player%d!\n", but->player);
		return true;
	}
    return false;
}

void DessinBut(But* b){
	int testy= (int)b->top.y;
    float top_y = getYSDL(testy);
//    printf("top_y : %3.f\n", top_y);
    float bottom_x = getXSDL((int)b->bottom.x);
    float bottom_y = getYSDL((int)b->bottom.y);
    float hauteur = (b->bottom.y) - (b->top.y);
    float translate_y = (abs(bottom_y) - abs(top_y))*0.5;
    //printf("bottom_y %3.5f\n", bottom_y);
    //printf("translate_y %3.f\n", translate_y);
    glPushMatrix();
//        glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, b->texture);

    	glTranslatef(bottom_x, translate_y, 0);
        glScalef(2, hauteur, 1);
        dessinCarre(1, 255, 0, 0);

        //glColor3f(255, 0, 0);

//        glBindTexture(GL_TEXTURE_2D, 0);
//        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
