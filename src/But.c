#include "But.h"
#include "Geometry.h"
#include "Color3f.h"
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
	float x = but->top.x;
	float topy = but->top.y;
	float bottomy = but->bottom.y;

//    printf("ball y %3.f / bas y %3.f / haut y %3.f\n", ball->cercle->centre.y, bottomy, topy);

	if (!(ball->cercle->centre.y > bottomy && ball->cercle->centre.y < topy))
		return false;

	if (x > 0) {
		if (ball->cercle->centre.x >= x) {
			//printf("GOAAAAL pour player%d!\n", but->player);
			return true;
		}
	} else if (ball->cercle->centre.x <= x) {
		//printf("GOAAAAL pour player%d!\n", but->player);
		return true;
	}
	return false;
}

//void DessinBut(But* b, int largeur) {
//	int testy = (int) b->top.y;
//	float top_x = getXSDL((int) b->top.x);
//	float top_y = getYSDL(testy);
//	float bottom_x = getXSDL((int) b->bottom.x);
//	float bottom_y = getYSDL((int) b->bottom.y);
//	float hauteur = (b->bottom.y) - (b->top.y);
//	float translate_y = (abs(bottom_y) - abs(top_y)) * 0.5;
//	glPushMatrix();
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, b->texture);
//	int x_centre = bottom_x;
//	Point2D top_manquant, bottom_manquant;
//	if (bottom_x > 0) {
//		x_centre += largeur / 2;
//		top_manquant = PointXY(top_x + largeur, top_y);
//		bottom_manquant = PointXY(bottom_x + largeur, bottom_y);
////    		printf("top x:%3.f, y%3.f / bottom x%3.f, y%3.f "
////    				"/ topmanque x:%3.f, y%3.f / botmanque x%3.f, y%3.f\n",
////					top_x, top_y, bottom_x, bottom_y, top_manquant.x,
////					top_manquant.y, bottom_manquant.x, bottom_manquant.y);
//	} else {
//		x_centre -= largeur / 2;
//		top_manquant = PointXY(top_x - largeur, top_y);
//		bottom_manquant = PointXY(bottom_x - largeur, bottom_y);
//	}
//	glTranslatef(x_centre, translate_y, 0);
//	glScalef(largeur, hauteur, 1);
//	dessinCarre(1, ColorRGB(255, 0, 0));
//	glBegin(GL_QUADS);
//	glTexCoord2f(1, 0);
//	glVertex2f(top_x * 0.5, top_y * 0.5);
//	glTexCoord2f(1, 1);
//	glVertex2f(bottom_x * 0.5, bottom_y * 0.5);
//	glTexCoord2f(0, 1);
//	glVertex2f(bottom_manquant.x * 0.5, bottom_manquant.y * 0.5);
//	glTexCoord2f(0, 0);
//	glVertex2f(top_manquant.x * 0.5, top_manquant.y * 0.5);
//	glEnd();
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glDisable(GL_TEXTURE_2D);
//	glPopMatrix();
//}
