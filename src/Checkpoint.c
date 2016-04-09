#include "Checkpoint.h"

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt){
	checkpt->cercle = (Cercle *) malloc(sizeof(Cercle));
	MakeCercle(checkpt->cercle, pos, r);
}
bool IsCheckpoint(Point2D pos);
void FreeCheckpoint(Checkpoint* checkpt){
	
}