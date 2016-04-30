#include "Terrain.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "sdl_tools.h"



#define NB_MAX_LIGNE 100
#define NB_MAX_COLONNE 202
#define NB_MAX_CHECKPT 30
#define DEFAULT_RAYON_CHECKPT 5.
#define DEFAULT_BUTG_POS_X 189.
#define DEFAULT_BUTD_POS_X 10.
#define DEFAULT_LARGEUR_BUT 10
#define DEFAULT_BUTP2_TEXTURE_PATH "images/butD.png"
#define DEFAULT_BUTP1_TEXTURE_PATH "images/butG.png"

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

void MakeTerrain(GLuint texture, FILE* terrainTxt, Terrain* t, Point2D* vp1_pos, Point2D* vp2_pos){
    if(!t) {
        printf("Impossible de creer le terrain, pointeur non alloué\n");
        return;
    }
    if(terrainTxt == NULL){
        printf("Erreur fichier terrain\n");
        return;
    }
    //char* tablignes[NB_MAX_LIGNE];
    t->terrain = (char **) malloc(NB_MAX_LIGNE*NB_MAX_COLONNE*sizeof(char*));
    int j,i=0;

    t->largeur = NB_MAX_COLONNE;
    t->hauteur = NB_MAX_LIGNE;
    t->texture = texture;
    t->pointCollision = PointXY(-1,-1);
    t->checkpts = (Checkpoint **) malloc(NB_MAX_CHECKPT*sizeof(Checkpoint*));
    t->nbCheckpts = 0;
    int hauteurButG = 0;
    int hauteurButD = 0;
    float butG_pos_y= -1., butD_pos_y=-1.;
    t->butP1 = (But*) malloc(sizeof(But));
    t->butP2 = (But*) malloc(sizeof(But));
    GLuint textureButP1 = loadImage(DEFAULT_BUTP1_TEXTURE_PATH);
    GLuint textureButP2 = loadImage(DEFAULT_BUTP2_TEXTURE_PATH);

    char ligne[NB_MAX_COLONNE];

    while(fgets(ligne, NB_MAX_COLONNE, terrainTxt)) {
        if(i > NB_MAX_LIGNE){
            printf("Le fichier txtTerrain contient trop de ligne !\n");
            return;
        }
        for(j=0; j < NB_MAX_COLONNE; j++){
        	if(ligne[j] == '1'){
        		*vp1_pos = PointXY(getXSDL(j), getYSDL(i+1));
        	}
        	else if(ligne[j] == '2'){
        		*vp2_pos = PointXY(getXSDL(j), getYSDL(i+1));
        	}
        	else if(ligne[j] == 'F' || ligne[j]=='B'){
                if(t->nbCheckpts >= NB_MAX_CHECKPT){
                    printf("Trop de checkpoints ! 30 Max\n");
                    return;
                }
                Bonus b;
                if(ligne[j] == 'F')
                	b=freeze;
                else
                	b=boost;
                Checkpoint chp;
                MakeCheckpoint(PointXY(getXSDL(j), getYSDL(i+1)), DEFAULT_RAYON_CHECKPT, &chp, b);
                t->checkpts[t->nbCheckpts] = CopyCheckpt(&chp);
                t->nbCheckpts++;
            }
        }
        t->largeur = j;
        if(ligne[(int)DEFAULT_BUTD_POS_X] == 'x'){
            if(butG_pos_y < 0)
                butG_pos_y = i;
            hauteurButG++;
        }
        if(ligne[(int)DEFAULT_BUTG_POS_X] == 'x'){
            if(butD_pos_y < 0)
                butD_pos_y = i;
            hauteurButD++;
        }

        t->terrain[i] = str_dup(ligne);
        //printf("%s\n", ligne);
        i++;
    }
    t->hauteur=i;
   // printf("%d\n", i);

    MakeBut(PointXY(DEFAULT_BUTG_POS_X,butG_pos_y),
    		PointXY(DEFAULT_BUTG_POS_X, butG_pos_y+hauteurButG),
			t->butP2, player2, textureButP2);
    MakeBut(PointXY(DEFAULT_BUTD_POS_X,butD_pos_y),
    		PointXY(DEFAULT_BUTD_POS_X, butD_pos_y+hauteurButD),
			t->butP1, player1, textureButP1);
 }

bool EstDansTerrain(Terrain* t, Point2D pos){
	if(pos.x>t->largeur || pos.y>t->hauteur || pos.x<-(t->largeur) || pos.y<-(t->hauteur))
		return false;
	return true;
}


bool IsWall(Terrain* t, Point2D pos){
    if(!EstDansTerrain(t, pos))
        return false;
    int x = (int) getXTerrain(pos.x);
    int y = (int) getYTerrain(pos.y);
    //printf("x:%df, y: %d\n",x, y);
    if(x>200 || x<0 || y>100 || y<0){
        printf("Erreur de calcul x terrain et y terrain\n");
        return false;
    }
    if( t->terrain[y][x] == '-' || t->terrain[y][x] == '|'){
        //printf("posx:%3.f, posy: %3.f\n",pos.x, pos.y);
        t->pointCollision = pos;
        return true;
    }
    return false;
}




bool CercleIsInWall(Terrain* t, Cercle* c){
    float xmax = c->centre.x + c->radius;
    float xmin = c->centre.x - c->radius;
    float ymax = c->centre.y + c->radius;
    float ymin = c->centre.y - c->radius;

    if(IsWall(t, c->centre) || IsWall(t, PointXY(xmax, ymax)) || IsWall(t, PointXY(xmax, ymin))
        || IsWall(t, PointXY(xmin, ymax)) || IsWall(t, PointXY(xmin, ymin))){
            //printf("x=%3.f, y=%3.f\n", c->centre.x, c->centre.y);
            return  true;
    }
    return false;
}

void FreeTerrain(Terrain* t){
    int i;
    for(i=0; i<NB_MAX_LIGNE; i++){
        free(t->terrain[i]);
        t->terrain[i] = NULL;
    }
    free(t->terrain);
    for(i=0; i < t->nbCheckpts; i++){
        FreeCheckpoint(t->checkpts[i]);
        t->checkpts[i]=NULL;
    }
    printf("FreeTerrain OK\n");
}

void DessinTerrain(Terrain* t) {
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1, 1, 1);
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

    glColor3f(255,255,255);
	DessinBut(t->butP1, DEFAULT_LARGEUR_BUT);
    glColor3f(255,255,255);
	DessinBut(t->butP2, DEFAULT_LARGEUR_BUT);

    int i;
    for(i=0; i<t->nbCheckpts; i++){
        DessinCheckpoint(t->checkpts[i]);
    }
}

char getCaraTerrain(Terrain *t, Point2D pos){
	int x = (int) getXTerrain(pos.x);
	int y = (int) getYTerrain(pos.y);
	return t->terrain[y][x];
}

void ResetTerrain(Terrain* t){
	int i;
	for(i=0; i<t->nbCheckpts; i++){
		ResetCheckpoint(t->checkpts[i]);
	}
}
