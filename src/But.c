#include "But.h"

void MakeBut(int hauteur, int largeur, Point2D* pos, But* b) {
    b->hauteur = hauteur;
    b->largeur = largeur;
    b->position = pos;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    if( ball->position->x > (but->position->x - but->largeur/2.)
        && ball->position->x < (but->position->x + but->largeur/2.)
        && ball->position->y < (but->position->y + but->hauteur/2.)
        && ball->position->y > (but->position->y - but->hauteur/2.))
        return true;
    return false;
}
