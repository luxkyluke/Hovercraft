#include "common.h"


float getXTerrain(float x){
    return x + 100;
}

float getYTerrain(float y){
    float ret = abs(y - 50);
    return ret;
}

float getXSDL(int x){
    return x - 100.;
}

float getYSDL(int y){
    float ret = 50. - y ;
    //printf("RET !! %3.f\n", ret);
    return ret;
}


