#include "Checkpoint.h"
#include "Geometry.h"
#include "Collision.h"
#include <time.h>
#include <stdlib.h>

#define RESET_DELAY 15000

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt, Bonus b){
	checkpt->cercle = (Cercle *) malloc(sizeof(Cercle));
	MakeCercle(checkpt->cercle, pos, r);
	checkpt->checked = false;
	checkpt->interceptedTime = 1;
	checkpt->type = b;
	//checkpt->timerReset =0;
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
			if(checkpt->type == freeze)
				dessinCercle(100, 0., 0., 1., 1);
			else if(checkpt->type == boost)
				dessinCercle(100, 1., 0.2, 0.2, 1);
			else
				dessinCercle(100, 0.2, 1., 0.5, 1);
		glPopMatrix();
	}
}

void ResetCheckpoint(Checkpoint* checkpt){
	checkpt->checked = false;
	checkpt->timerReset = 0;
}
