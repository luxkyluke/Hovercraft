#include "Terrain.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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


#define NB_MAX_LIGNE 102
#define NB_MAX_COLONNE 202
#define NB_MAX_CHECKPT 30
#define DEFAULT_RAYON_CHECKPT 5.
#define DEFAULT_BUTP1_POS_X 200.
#define DEFAULT_BUTP2_POS_X 0.

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
    int j,i=0;

    t->largeur = NB_MAX_COLONNE;
    t->hauteur = NB_MAX_LIGNE;
    t->texture = texture;
    t->checkpts = (Checkpoint **) malloc(NB_MAX_CHECKPT*sizeof(Checkpoint*));
    t->nbCheckpts = 0;
    int hauteurButG = 0;
    int hauteurButD = 0;
    float butG_pos_y= -1., butD_pos_y=-1.;
    t->butP1 = (But*) malloc(sizeof(But));
    t->butP2 = (But*) malloc(sizeof(But));

    char ligne[NB_MAX_COLONNE];

    while(fgets(ligne, NB_MAX_COLONNE, terrainTxt)) { 
        if(i > NB_MAX_LIGNE){
            printf("Le fichier txtTerrain contient trop de ligne !\n");
            return;
        }
        for(j=0; j < NB_MAX_COLONNE; j++){
            if(ligne[j] == '0'){
                if(t->nbCheckpts >= NB_MAX_CHECKPT){
                    printf("Trop de checkpoints ! 30 Max\n");
                    return;
                }
                Checkpoint chp;
                MakeCheckpoint(PointXY(j, i), DEFAULT_RAYON_CHECKPT, &chp);
                t->checkpts[t->nbCheckpts] = CopyCheckpt(&chp);
                t->nbCheckpts++;
            }
        }
        if(ligne[0] == 'x'){
            if(butG_pos_y < 0)
                butG_pos_y = i;
            hauteurButG++;
        }
        if(ligne[NB_MAX_COLONNE-3] == 'x'){
            if(butD_pos_y < 0)
                butD_pos_y = i;
            hauteurButD++;
        }
        
        t->terrain[i] = str_dup(ligne); 
        //printf("%s\n", ligne);
        i++;
    }
   // printf("%d\n", i);
    
    MakeBut(PointXY(DEFAULT_BUTP2_POS_X, butD_pos_y), PointXY(DEFAULT_BUTP2_POS_X, butD_pos_y+hauteurButD), t->butP2);
    MakeBut(PointXY(DEFAULT_BUTP1_POS_X, butG_pos_y), PointXY(DEFAULT_BUTP1_POS_X, butD_pos_y+hauteurButG), t->butP1);
 }

bool IsWall(Terrain* t, Point2D pos){
    if(pos.x>100. || pos.y>50. || pos.x<-100. || pos.y<-50.)
        return true;
    int x = (int) getXTerrain(pos.x);
    int y = (int) getYTerrain(pos.y);
    //printf("x:%d, y: %d\n",x, y);
    if(x>200 || x<0 || y>100 || y<0){
        printf("Erreur de calcul x terrain et y terrain\n");
        t->pointCollision = pos;
        return true;
    }
    if( t->terrain[y][x] == '-'){
        //printf("x:%d, posx: %3.f\n",x, pos.x);
        t->pointCollision = pos;
        return true;
    }
    return false;
}



bool CercleIsInWall(Terrain* t, Cercle* c){ //xman ect forment un carré ...
    float xmax = c->centre.x + c->radius;
    float xmin = c->centre.x - c->radius;
    float ymax = c->centre.y + c->radius;
    float ymin = c->centre.y - c->radius;

    if(IsWall(t, PointXY(xmax, ymax)) || IsWall(t, PointXY(xmax, ymin)) 
        || IsWall(t, PointXY(xmin, ymax)) || IsWall(t, PointXY(xmin, ymin)) == true){
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
}

