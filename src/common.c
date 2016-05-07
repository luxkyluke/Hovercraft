#include "common.h"

/**
 * @brief Traduit une coordonné x de l'espce SDL en une coordx pour le tableau2D du terrain
 * @param x - la coordx de l'espace SDL
 * @return la valeur pour le tableau2D du x en question
 */
int getXTerrain(float x){
    return (int)x + 100;
}

/**
 * @brief Traduit une coordonné y de l'espce SDL en une coordy pour le tableau2D du terrain
 * @param y - la coordy de l'espace SDL
 * @return la valeur pour le tableau2D du y en question
 */
int getYTerrain(float y){
    int ret = abs((int)y - 50);
    return ret;
}

/**
 * @brief Traduit une coordonné x du tableau de terrain en une coord x de l'espace SDL
 * @param x - la coordx du tableau2D du terrain
 * @return la valeur dans l'espace SDL du x en question
 */
float getXSDL(int x){
    return (float) x - 100;
}

/**
 * @brief Traduit une coordonné y du tableau de terrain en une coord y de l'espace SDL
 * @param y - la coordy du tableau2D du terrain
 * @return la valeur dans l'espace SDL du y en question
 */
float getYSDL(int y){
    float ret = (float) 50 - y ;
    return ret;
}

/**
 * @brief Verifie si la position est dans l'espace SDL
 * @param pos - la position a tester
 * @return true si la position est dans l'espace SDL, false sinon
 */
bool EstDansSDL(Point2D pos){
	return (pos.x<100 && pos.x>-100 && pos.y>-50 && pos.y<50);
}

