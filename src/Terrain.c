#include "Terrain.h"

#define NB_MAX_LIGNE 100
#define NB_MAX_COLONNE 200
void MakeTerrain(GLuint text, FILE* terrainTxt, Terrain* t){
	if(terrainTxt == NULL)
		return;
	char* tablignes[NB_MAX_LIGNE];
	char ligne[NB_MAX_COLONNE];
	int i;

    t->largeur = 200;
    t->hauteur = 100;
    t->texture = texture;

	for(i=0; i<NB_MAX_LIGNE; i++){
		fgets(ligne, NB_MAX_COLONNE, terrainTxt);
		printf("%s\n", ligne);
		tablignes[i]= &ligne;
	}
	t->terrain = &tablignes;
}

bool IsWall(Terrain* t, Point2D* pos){
	return false;
}

void FreeTerrain(Terrain* t){

}

void DessinTerrain(Terrain* t, GLuint texture, unsigned int windowWidth, unsigned int windowHeight) {
    glEnable(GL_TEXTURE_2D);
    float test = (float)windowWidth - (float)windowWidth/2;
    printf("hrllo %f \n", 100.*(float)windowHeight/(float)windowWidth);
    glBindTexture(GL_TEXTURE_2D, texture);
    glScalef(2, 2, 1.f);
    glBegin(GL_QUADS);
        glTexCoord2f(1,0); glVertex2f(100*0.5 , 50.*.5);
        glTexCoord2f(1,1); glVertex2f(100*0.5 , -50.*.5);
        glTexCoord2f(0,1); glVertex2f(-100*0.5, -50.*.5);
        glTexCoord2f(0,0); glVertex2f(-100*0.5, 50.*.5);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


GLuint loadImage(char* image){
    SDL_Surface* myTexture = IMG_Load(image);
    if (myTexture == NULL){
        fprintf(stderr, "Impossible d'afficher l'image. Fin du programme.\n");
        return EXIT_FAILURE;
    } else {
        printf("L'image a été chargée correctement\n");
    }

    GLuint textures;
    glGenTextures(1, &textures);

    glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLenum format;
    printf("Format : %d\n", myTexture->format->BytesPerPixel);
    switch(myTexture->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_BGRA;
            break;
        default:
            fprintf(stderr, "Format des pixels de l’image non pris en charge\n");
            exit(-1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myTexture->w, myTexture->h, 0, format, GL_UNSIGNED_BYTE, myTexture->pixels);
    printf("Tout est OK ! :D\n");

    SDL_FreeSurface(myTexture);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textures;
}
