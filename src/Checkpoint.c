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
	CheckResetCheckpoint(checkpt);
	if(!checkpt->checked){
		glPushMatrix();
			glTranslatef(checkpt->cercle->centre.x, checkpt->cercle->centre.y, 0);
			glScalef(checkpt->cercle->radius, checkpt->cercle->radius, 1);
			Color3f color, colorBoost, colorFreeze;
			colorBoost = ColorRGB(1., 0.23, 0.21);
			colorFreeze = ColorRGB(0.01, 0.66, 0.95);
			if(checkpt->type == freeze)
				color = colorFreeze;
			else if(checkpt->type == boost)
				color = colorBoost;
			dessinCercle(100, color, 1);
		glPopMatrix();
	}
}

void ResetCheckpoint(Checkpoint* checkpt){
	checkpt->checked = false;
	checkpt->timerReset = 0;
}
