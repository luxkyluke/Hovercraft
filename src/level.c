#include <string.h>

#include "Level.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


void MakeLevel(char* nameFichTerrain, char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2, Level *l, int nbLevel){
	FILE *fileTerrain;
	Terrain t;
	Ballon ballon;
	Vehicule vp1;
	Vehicule vp2;
    GLuint imageBallon = loadImage("images/ballon.png");
    char picsToLoad[21];
    sprintf(picsToLoad, "./images/terrain%d.png", nbLevel);
    GLuint textureIdTerrain = loadImage(picsToLoad);

	char* terrainTxt = "./" ;
	strcat(terrainTxt, nameFichTerrain);
	strcat(terrainTxt, ".txt");
    fileTerrain = fopen(terrainTxt,"r");
    if(!fileTerrain) {
        perror("Error while opening the input file.\n");
        return;
    }

    MakeTerrain(textureIdTerrain, fileTerrain, &t);
    MakeVehicule(PointXY(95.,0.), 5., 5., 0, player1, &vp1);
    MakeVehicule(PointXY(-95.,0.), 5., 5., 0, player1, &vp2);
    MakeBallon(imageBallon, PointXY(0.,0.), &ballon);

    l->ballon = &ballon;
    l->vp1 = &vp1;
    l->vp2 = &vp2;
    l->terrain= &t;
    l->scoreP1 = 0;
    l->scoreP2 = 0;
    l->nbLevel=nbLevel;
}
