#include "common.h"


float getXTerrain(float x){
    return x + 100.;
}

float getYTerrain(float y){
    float ret = abs(y - 50);
    return ret;
}

float getXSDL(int x){
    return (float) x - 100;
}

float getYSDL(int y){
    float ret = (float) 50 - y ;
    return ret;
}


