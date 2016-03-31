#include <string.h>

#include "Level.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


void MakeLevel(char* nameFichTerrain, char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2, Level *l){
	FILE *fileTerrain;
	Terrain t;
	Ballon ballon;
	Vehicule vp1;
	Vehicule vp2;

	char* terrainTxt = "./" ;
	strcat(terrainTxt, nameFichTerrain);
	strcat(terrainTxt, ".txt");
    fileTerrain = fopen(terrainTxt,"r"); 
    if(!fileTerrain) {
        perror("Error while opening the input file.\n");
        return;
    }

    /*SDL_Surface* imgTerrain = IMG_Load(pathTextureTerrain);
	if(imgTerrain == NULL){
	  	printf("Erreur : impossible de charger imgTerrain '%s' \n", argv[1]);
	    return EXIT_FAILURE;
	}
	GLuint textureIdTerrain, textureIdVp1, textureIdVp2;
	glGenTextures(1,&textureIdTerrain);
	glGenTextures(3,&textureIdVp2);
	glGenTextures(2,&textureIdVp1);
	glBindTexture(GL_TEXTURE_2D, textureId);*/

    MakeTerrain(0, fileTerrain, &t);
    MakeVehicule(PointXY(95.,0.), 5., 5., 0, player1, &vp1);
    MakeVehicule(PointXY(-95.,0.), 5., 5., 0, player1, &vp2);
    MakeBallon(, PointXY(0.,0.), &ballon);

    l->ballon = &ballon;
    l->vp1 = &vp1;
    l->vp2 = &vp2;
    l->terrain= &t;
    l->scoreP1 = 0;	
    l->scoreP2 = 0;
}
