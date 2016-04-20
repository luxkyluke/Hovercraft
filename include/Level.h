#ifndef LEVEL_H_
#define LEVEL_H_

#include "Camera.h"
#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"
#include "Point2D.h"
#include "bool.h"

typedef struct {
	Terrain* terrain;
	Vehicule* vp1;
	Vehicule* vp2;
	Ballon* ballon;
	int scoreP1;
	int scoreP2;
    Camera* camera;
    int nbLevel;
}Level;

void MakeLevel(Level *l, char* nameFichTerrain,  char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2);


//verifie si il y a eu une colision entre les éléments
//Ajouter des scores si but etc...
bool CheckTouched(Level *l);
void reshape(unsigned int windowWidth, unsigned int windowHeight) ;
void AddScoreP1(Level* l, int score);
void AddScoreP2(Level* l, int score);
void FreeLevel(Level* l);
void DessinLevel(Level* l);
void UpdateLevel(Level* l);
void PlayLevel(Level* l, int windowWidth, int windowHeight, int i);
void ResetLevel(Level* l);
void UpdateCameraLevel(Level* level);
void DessinMinimap(Ballon* ballon, Vehicule* vp1, Vehicule* vp2);
void CheckBonus(Level* level);

#endif
