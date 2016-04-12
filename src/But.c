#include "But.h"
#include <stdio.h>


void MakeBut(Point2D top, Point2D bottom, But* b) {
    if (b == NULL) {
        printf("Le but est NULL\n");
        return;
    }
    b->top = top;
    b->bottom = bottom;
}

bool BallIsInGoal(But* but, Ballon* ball) {
    float x = ball->cercle->centre.x + 100;
    float y = ball->cercle->centre.y + 50;
    if(abs(x) > abs(but->top.x)
        && abs(x) > abs(but->bottom.x)
        && y < but->bottom.y
        && y > but->top.y)
        return true;
    return false;
}
