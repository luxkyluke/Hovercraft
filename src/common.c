#include "common.h"


int getXTerrain(float x){
    return (int)x + 100;
}

int getYTerrain(float y){
    int ret = abs((int)y - 50);
    return ret;
}

float getXSDL(int x){
    return (float) x - 100;
}

float getYSDL(int y){
    float ret = (float) 50 - y ;
    return ret;
}

bool EstDansSDL(Point2D pos){
	return (pos.x<100 && pos.x>-100 && pos.y>-50 && pos.y<50);
}

