#ifndef LEVEL_H_
#define LEVEL_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string.h>
#include <time.h>

#include "Camera.h"
#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"
#include "Point2D.h"
#include "bool.h"
#include "Collision.h"
#include "sdl_tools.h"
#include "Camera.h"
#include "Checkpoint.h"
#include "Vehicule.h"
#include "glut_tools.h"
#include <SDL/SDL_mixer.h>



typedef struct {
	Terrain* terrain;
	Vehicule* vp1;
	Vehicule* vp2;
	Ballon* ballon;
	int scoreP1;
	int scoreP2;
	Camera* camera;
	int duration;
} Level;

bool MakeLevel(Level *l, char* nameFichTerrain, int duration);

//verifie si il y a eu une colision entre les éléments
//Ajouter des scores si but etc...
bool CheckTouched(Level *l);
void reshape(unsigned int windowWidth, unsigned int windowHeight);
void AddScoreP1(Level* l, int score);
void AddScoreP2(Level* l, int score);
void FreeLevel(Level* l);
void DessinLevel(Level* l, Uint32 duration);
void UpdateLevel(Level* l);
bool PlayLevel(Level* l, int windowWidth, int windowHeight, int i);
void ResetLevel(Level* l);
void UpdateCameraLevel(Level* level);
void DessinMinimap(Ballon* ballon, Vehicule* vp1, Vehicule* vp2);
void CheckBonus(Level* level);

#endif
