#include "Terrain.h"
#include <string.h>
#include <stdio.h>

char *str_dup(char const *s){
    char *pc = NULL;
 
    if (s != NULL){
        pc = malloc((strlen(s) + 1) * sizeof *pc);
        if (pc != NULL) {
            strcpy(pc, s);
        }
    }
    return pc;
}


#define NB_MAX_LIGNE 100
#define NB_MAX_COLONNE 200
void MakeTerrain(GLuint texture, FILE* terrainTxt, Terrain* t){
	if(!t) {
		printf("Impossible de créer le terrain, pointeur non alloué\n"); 
		return;
	}
	if(terrainTxt == NULL){
		printf("Erreur fichier terrain\n");
		return;
	}
	//char* tablignes[NB_MAX_LIGNE];
	t->terrain = (char **) malloc(NB_MAX_LIGNE*NB_MAX_COLONNE*sizeof(char*));
	int i=0;

    t->largeur = NB_MAX_COLONNE;
    t->hauteur = NB_MAX_LIGNE;
    t->texture = texture;

    char ligne[NB_MAX_COLONNE];
	while(fgets(ligne, NB_MAX_COLONNE, terrainTxt))	{	
		if(i>=NB_MAX_LIGNE){
			printf("Le fichier txtTerrain contient trop de ligne !\n");
			return;
		}
		t->terrain[i] = str_dup(ligne);	
		i++;
	}
	/*t->checkpts;
	t->nbCheckpts = 0;
	t->butP1;
	t->butP2;*/
}

bool IsWall(Terrain* t, Point2D pos){
	return false;
}

void FreeTerrain(Terrain* t){
	int i;
	for(i=0; i<NB_MAX_LIGNE; i++){
		free(t->terrain[i]);
		t->terrain[i] = NULL;
	}
	free(t->terrain);
	printf("FreeTerrain OK\n");
	/*for(i=0; i<t->nbCheckpts; i++){
		FreeCheckpoint(t->checkpts[i]);
	}*/
}

<<<<<<< HEAD
void DessinTerrain(Terrain* t, unsigned int windowWidth, unsigned int windowHeight) {
    glPushMatrix();
	    glEnable(GL_TEXTURE_2D);
	    //float test = (float)windowWidth - (float)windowWidth/2;
	    //printf("hrllo %f \n", 100.*(float)windowHeight/(float)windowWidth);
	    glColor3f(255, 255, 255);
	    glBindTexture(GL_TEXTURE_2D, t->texture);
	   
	    glScalef(2, 2, 1.f);
	    glBegin(GL_QUADS);
	        glTexCoord2f(1,0); glVertex2f(100*0.5 , 50.*.5);
	        glTexCoord2f(1,1); glVertex2f(100*0.5 , -50.*.5);
	        glTexCoord2f(0,1); glVertex2f(-100*0.5, -50.*.5);
	        glTexCoord2f(0,0); glVertex2f(-100*0.5, 50.*.5);
	    glEnd();
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
=======
void DessinTerrain(Terrain* t, GLuint texture, unsigned int windowWidth, unsigned int windowHeight) {
    glEnable(GL_TEXTURE_2D);
    float test = (float)windowWidth - (float)windowWidth/2;
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
>>>>>>> 5e75ec0799037d210b2de730de49a213eb9d379d
}

 
