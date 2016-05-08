#include "Checkpoint.h"
#include "Geometry.h"
#include "Collision.h"
#include <time.h>
#include <stdlib.h>


#define RESET_DELAY 20000

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt, Bonus b){
	checkpt->cercle = (Cercle *) malloc(sizeof(Cercle));
	MakeCercle(checkpt->cercle, pos, r);
	checkpt->checked = false;
	checkpt->type = b;
	checkpt->timerReset =0;
}

bool IsCheckpoint(Checkpoint* checkpt, Cercle* c) {
	if(CollisionCercleCercle(checkpt->cercle, c)){
		checkpt->checked = true;
		checkpt->timerReset = SDL_GetTicks();
		return true;
	}
	return false;
}

void FreeCheckpoint(Checkpoint* checkpt){
	free(checkpt->cercle);
	checkpt->cercle = NULL;
}

Checkpoint* CopyCheckpt(Checkpoint* checkpt){
	Checkpoint *chpt = NULL;
	if(checkpt != NULL){
		chpt = (Checkpoint*) malloc(sizeof(Checkpoint));
		if(chpt != NULL){
			MakeCheckpoint(checkpt->cercle->centre, checkpt->cercle->radius, chpt, checkpt->type);
		}
	}
	return chpt;
}

bool IsTimeToReset(Checkpoint* c){
	return SDL_GetTicks() - c->timerReset > RESET_DELAY;
}

void CheckResetCheckpoint(Checkpoint* c){
	if(c->checked && IsTimeToReset(c)){
		c->checked=false;
		c->timerReset = SDL_GetTicks();
	}
}

void DessinCheckpoint(Checkpoint* checkpt){
	glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	CheckResetCheckpoint(checkpt);
	Color4f colorBoost, colorFreeze;
	if(!checkpt->checked){
		colorBoost = ColorRGBA(1., 0.23, 0.21,1);
		colorFreeze = ColorRGBA(0.01, 0.66, 0.95,1);
	} else {
		colorBoost = ColorRGBA(1., 0.23, 0.21,0.2);
		colorFreeze = ColorRGBA(0.01, 0.66, 0.95,0.2);
	}
	glPushMatrix();
		glTranslatef(checkpt->cercle->centre.x, checkpt->cercle->centre.y, 0);
		glScalef(checkpt->cercle->radius, checkpt->cercle->radius, 1);
		Color4f color = ColorRGBA(1,1,1,0);
		if(checkpt->type == freeze)
			color = colorFreeze;
		else if(checkpt->type == boost)
			color = colorBoost;
		dessinCercle(100, color, 1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void ResetCheckpoint(Checkpoint* checkpt){
	checkpt->checked = false;
	checkpt->timerReset = 0;
}
