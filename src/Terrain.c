#include "Terrain.h"

void MakeTerrain(GLuint text, FILE* terrainTxt, Terrain* t){

}

bool IsWall(Terrain* t, Point2D* pos){
	return false;
}

void FreeTerrain(Terrain* t){

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
            format = GL_BGR;
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
