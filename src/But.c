#include "But.h"

void MakeBut(int hauteur, int largeur, Point2D* pos, But* b) {
    b->hauteur = hauteur;
    b->largeur = largeur;
    b->position = pos;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    // Check if it's left goal or right.

}
