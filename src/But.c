#include "But.h"
#include <stdio.h>


void MakeBut(int hauteur, Point2D pos, But* b) {
    if (b == NULL) {
        printf("Le but est NULL\n");
        return;
    }
    b->hauteur = hauteur;
    b->position = pos;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    if(ball->cercle->centre.x > but->position.x
        && ball->cercle->centre.y < (but->position.y + but->hauteur/2.)
        && ball->cercle->centre.y > (but->position.y - but->hauteur/2.))
        return true;
    return false;
}
