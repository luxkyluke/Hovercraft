#include <string.h>

#include "Level.h"
#include "Collision.h"
#include "sdl_tools.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#define DEFAULT_VP1_POS_X 95.
#define DEFAULT_VP1_POS_Y 0.
#define DEFAULT_VP2_POS_Y 0.
#define DEFAULT_VP2_POS_X -95.
#define DEFAULT_VEHICUL_W 5.
#define DEFAULT_VEHICUL_H 5.
#define DEFAULT_BALL_POS_X 0.
#define DEFAULT_BALL_POS_Y 0.
#define DEFAULT_BALL_RADIUS 2.
#define DEFAULT_BALL_TEXTURE_PATH "images/ballon.png"
#define DEFAULT_VP1_TEXTURE_PATH "images/vp1.png"
#define DEFAULT_VP2_TEXTURE_PATH "images/vp2.png"

void MakeLevel(Level* l, char* nameFichTerrain, char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2){
	if(l == NULL) {
		printf("Impossible de créer le level, pointeur non alloué\n");
		return;
	}
	FILE *fileTerrain;
	Terrain* t = (Terrain*) malloc(sizeof(Terrain));
	Ballon *ballon = (Ballon *) malloc(sizeof(Ballon));
	Vehicule* vp1 = (Vehicule *) malloc(sizeof(Vehicule));
	Vehicule *vp2 = (Vehicule *) malloc(sizeof(Vehicule));
    GLuint imageBallon = loadImage(DEFAULT_BALL_TEXTURE_PATH);
    GLuint textureIdTerrain = loadImage(pathTextureTerrain);
    GLuint textureVP1 = loadImage(DEFAULT_VP1_TEXTURE_PATH);
    GLuint textureVP2 = loadImage(DEFAULT_VP2_TEXTURE_PATH);

	char terrainTxt[30] = "./";
	strcat(terrainTxt, nameFichTerrain);
	strcat(terrainTxt, ".txt");

    fileTerrain = fopen(terrainTxt,"r");
    if(!fileTerrain) {
        perror("Error while opening the input file.\n");
        return;
    }

    MakeTerrain(textureIdTerrain, fileTerrain, t);
    MakeVehicule(PointXY(DEFAULT_VP1_POS_X, DEFAULT_VP1_POS_Y), DEFAULT_VEHICUL_H, DEFAULT_VEHICUL_W, textureVP1, player1, vp1);
    MakeVehicule(PointXY(DEFAULT_VP2_POS_X, DEFAULT_VP2_POS_Y), DEFAULT_VEHICUL_H, DEFAULT_VEHICUL_W, textureVP2, player1, vp2);
    MakeBallon(imageBallon, PointXY(DEFAULT_BALL_POS_X,DEFAULT_BALL_POS_Y), ballon, DEFAULT_BALL_RADIUS);

    l->ballon = ballon;
    l->vp1 = vp1;
    l->vp2 = vp2;
    l->terrain= t;
    l->scoreP1 = 0;
    l->scoreP2 = 0;
}

bool CheckTouched(Level* l){
    CollisionVehiculeVehicule(l->vp1, l->vp2);
    CollisionVehiculeBallon(l->ballon, l->vp1);
    CollisionVehiculeBallon(l->ballon, l->vp2);
    return true;
}

void FreeLevel(Level * l){
	FreeTerrain(l->terrain);
	free(l->terrain);
    l->terrain = NULL;
	free(l->vp2);
    l->vp2 = NULL;
	free(l->vp1);
    l->vp1 = NULL;
	free(l->ballon);
    l->ballon = NULL;
    printf("FreeLevel OK\n");
}
