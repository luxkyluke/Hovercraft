#include <string.h>

#include "Level.h"
#include "Collision.h"
#include "sdl_tools.h"
#include "Camera.h"
#include "Checkpoint.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#define DEFAULT_VP1_POS_X 90.
#define DEFAULT_VP1_POS_Y 0.
#define DEFAULT_VP2_POS_Y 0.
#define DEFAULT_VP2_POS_X -90.
#define DEFAULT_VEHICUL_W 5.
#define DEFAULT_VEHICUL_H 5.
#define DEFAULT_BALL_POS_X 0.
#define DEFAULT_BALL_POS_Y 0.
#define DEFAULT_BALL_RADIUS 2.
#define DEFAULT_BALL_TEXTURE_PATH "images/ballon.png"
#define DEFAULT_VP1_TEXTURE_PATH "images/vp1.png"
#define DEFAULT_VP2_TEXTURE_PATH "images/vp2.png"

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

//boolean pour pr�ciser quand la camera est en action
bool camera_is_in_work = false;

void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100.*(float)windowHeight/(float)windowWidth, 100.*(float)windowHeight/(float)windowWidth);
}

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
  Camera *cam = (Camera *) malloc(sizeof(Camera));

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
    MakeVehicule(PointXY(DEFAULT_VP2_POS_X, DEFAULT_VP2_POS_Y), DEFAULT_VEHICUL_H, DEFAULT_VEHICUL_W, textureVP2, player2, vp2);
    MakeBallon(imageBallon, PointXY(DEFAULT_BALL_POS_X,DEFAULT_BALL_POS_Y), ballon, DEFAULT_BALL_RADIUS);
    MakeCamera(cam);


    l->ballon = ballon;
    l->vp1 = vp1;
    l->vp2 = vp2;
    l->camera = cam;
    l->terrain= t;
    l->scoreP1 = 0;
    l->scoreP2 = 0;
}

bool CheckTouched(Level* l){
    CollisionVehiculeVehicule(l->vp1, l->vp2);
    CollisionVehiculeBallon(l->ballon, l->vp1);
    CollisionVehiculeBallon(l->ballon, l->vp2);
    CollisionVehiculeTerrain(l->vp1, l->terrain);
    CollisionVehiculeTerrain(l->vp2, l->terrain);
    CollisionBallonTerrain(l->ballon, l->terrain);
    Player buteur;
    if(CollisionBallonBut(l->ballon, l->terrain, &buteur)) {
	  if(buteur == player1){
		  l->scoreP1 += 1;
		  printf("score P1 : %d\n", l->scoreP1);
	  }
	  else{
		  l->scoreP2 += 1;
		  printf("score P2 : %d\n", l->scoreP2);
	  }
	  l->camera->start=1;
    }
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

void DessinLevel(Level* l){
    DessinTerrain(l->terrain);
    DessinVehicule(l->vp1);
    DessinVehicule(l->vp2);
    DessinBallon(l->ballon);

}

void UpdateLevel(Level* l){
    UpdateVehicule(l->vp1);
    UpdateVehicule(l->vp2);
}

// Reset Vehicule position and ball
void ResetLevel(Level* l) {
    // Reset first vehicule.
    l->vp1->position = PointXY(DEFAULT_VP1_POS_X, DEFAULT_VP1_POS_Y);
    l->vp1->vitesse = VectorXY(0,0);
    l->vp1->angle = 0;
    l->vp1->direction = VectorXY(0,1);
    // Reset second vehicule.
    l->vp2->position = PointXY(DEFAULT_VP2_POS_X, DEFAULT_VP2_POS_Y);
    l->vp2->vitesse = VectorXY(0,0);
    l->vp2->angle = 0;
    l->vp2->direction = VectorXY(0,1);
    // Reset ball.
    l->ballon->cercle->centre = PointXY(0,0);
    l->ballon->vitesse = VectorXY(0,0);
    // Reset Camera
    l->camera->zoomLevel=1;
    l->camera->start=0;
}

void RalentiLevel(Level* level) {
  level->vp1->vitesse=DivVector(level->vp1->vitesse,1.1);
  level->vp2->vitesse=DivVector(level->vp2->vitesse,1.1);
  level->ballon->vitesse=DivVector(level->ballon->vitesse,1.1);
}

void UpdateCameraLevel(Level* level) {
//	if(level->camera->zoomLevel<4 && level->camera->start == 1)
//		UpdateCamera(level->camera, level->ballon);
//	else if(level->camera->zoomLevel>=4){
//	      ResetLevel(level);
//	}
    if(level->camera->zoomLevel<4 && level->camera->start == 1) {
    	camera_is_in_work = true;
    	LookAt(level->camera, level->ballon->cercle->centre, level->camera->zoomLevel);
    	level->camera->zoomLevel+=0.01;
    	RalentiLevel(level);
    }
    else if(level->camera->zoomLevel>=4){
      ResetLevel(level);
      camera_is_in_work = false;
    }
}

void PlayLevel(Level* level, int windowWidth, int windowHeight, int id){

    if(!level)
        return;

  Vehicule* VP1 = level->vp1;
  Vehicule* VP2 = level->vp2;




  // Titre de la fenêtre
  char windowname[30];
  sprintf(windowname, "HoverLigue Niveau %d !", id+1);
  SDL_WM_SetCaption(windowname, NULL);

  // Boucle d'affichage
  int loop = 1;

  while(loop) {
    // Récupération du temps au début de la boucle
    Uint32 startTime = SDL_GetTicks();

    // Placer ici le code de dessin
    glClearColor(0, 0 , 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //Camera//
    glPushMatrix();
    glLoadIdentity();
    UpdateCameraLevel(level);






//ZONE DE TEST//////////
    glBegin(GL_LINES);
      glColor3f(0.,1.,0.);
        glVertex2f(0,0);
        glVertex2f(level->vp1->direction.x, level->vp1->direction.y);
    glEnd();

    glPushMatrix();
        glTranslatef(level->ballon->cercle->centre.x, level->ballon->cercle->centre.y, 0);
        glScalef(level->ballon->cercle->radius, level->ballon->cercle->radius, 0.);
        dessinCercle(100, 0.8, 0.4, 0.1, 0);
    glPopMatrix();

///////////////////////////




    UpdateLevel(level);

    DessinLevel(level);
    if(!camera_is_in_work)
    	CheckTouched(level);

    glPopMatrix();


    // Echange du front et du back buffer : mise à jour de la fenêtre
    SDL_GL_SwapBuffers();



    // Boucle traitant les evenements
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      // L'utilisateur ferme la fenêtre :
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      // Quelques exemples de traitement d'evenements :
      switch(e.type) {
        // Clic souris
        case SDL_MOUSEBUTTONUP:

          break;

        // move the mouse

        // Touche clavier
        case SDL_KEYDOWN:
          //printf("touche pressée (code = %d)\n", e.key.keysym.unicode);
          if(e.key.keysym.sym ==  SDLK_z)
            VP2->avance = 1;
          if(e.key.keysym.sym == SDLK_UP)
            VP1->avance = 1;

          if(e.key.keysym.sym == SDLK_RIGHT)
            VP1->tourne = 1;
          if(e.key.keysym.sym == SDLK_LEFT)
            VP1->tourne = -1;
          if(e.key.keysym.sym == SDLK_d)
            VP2->tourne = 1;
          if(e.key.keysym.sym == SDLK_q)
            VP2->tourne = -1;
          break;

        case SDL_KEYUP:
          //printf("touche lachée (code = %d)\n", e.key.keysym.unicode);
          if(e.key.keysym.sym == SDLK_z)
            VP2->avance = 0;
          if(e.key.keysym.sym == SDLK_UP)
            VP1->avance = 0;

          if(e.key.keysym.sym == SDLK_RIGHT)
            VP1->tourne = 0;
          if(e.key.keysym.sym == SDLK_LEFT)
            VP1->tourne = 0;
          if(e.key.keysym.sym == SDLK_q)
            VP2->tourne = 0;
          if(e.key.keysym.sym == SDLK_d)
            VP2->tourne = 0;
          if(e.key.keysym.sym == SDLK_r)
            ResetLevel(level);
          if(e.key.keysym.sym == SDLK_t)
            level->camera->start=1;
          if(e.key.keysym.sym == SDLK_y)
            RalentiLevel(level);
          if(e.key.keysym.sym == SDLK_p){
            level->terrain->checkpts[0]->checked = true;
            level->terrain->checkpts[0]->interceptedTime = SDL_GetTicks();
          }
          break;

        // resize window
        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          reshape(windowWidth, windowHeight);
          break;

        default:
          break;
      }
    }

    // Calcul du temps écoulé
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    // Si trop peu de temps s'est écoulé, on met en pause le programme
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  // Liberation des ressources associées à la SDL
  SDL_Quit();

}
