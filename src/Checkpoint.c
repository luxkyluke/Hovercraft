#include "Checkpoint.h"
#include "Geometry.h"

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt){
	checkpt->cercle = (Cercle *) malloc(sizeof(Cercle));
	MakeCercle(checkpt->cercle, pos, r);
	checkpt->checked = false;
}
bool IsCheckpoint(Point2D pos);

void FreeCheckpoint(Checkpoint* checkpt){
	free(checkpt->cercle);
	checkpt->cercle = NULL;
}

Checkpoint* CopyCheckpt(Checkpoint* checkpt){
	Checkpoint *chpt = NULL;
	if(checkpt != NULL){
		chpt = (Checkpoint*) malloc(sizeof(Checkpoint));
		if(chpt != NULL){
			MakeCheckpoint(checkpt->cercle->centre, checkpt->cercle->radius, chpt);
		}
	}
	return chpt;
}

void DessinCheckpoint(Checkpoint* checkpt){
	if(!checkpt->checked){
		glPushMatrix();
			glTranslatef(checkpt->cercle->centre.x, checkpt->cercle->centre.y, 0);
			glScalef(checkpt->cercle->radius, checkpt->cercle->radius, 1);
			dessinCercle(100, 0., 0., 1., 1);
		glPopMatrix();
	}
}
