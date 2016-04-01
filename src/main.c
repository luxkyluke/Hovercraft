/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/Geometry.h"
#include "../include/Vehicule.h"
#include "../include/Player.h"
#include "../include/Ballon.h"
#include "../include/Terrain.h"
#include "../include/Level.h"

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -100.*(float)windowHeight/(float)windowWidth, 100.*(float)windowHeight/(float)windowWidth);
}

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char** argv) {


  /* Dimensions de la fenêtre */
  unsigned int windowWidth  = 1800;
  unsigned int windowHeight = 900;

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  setVideoMode(windowWidth, windowHeight);
  reshape(windowWidth, windowHeight);

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("HoverLigue !", NULL);

  Vehicule *VP1 = (Vehicule*) malloc(sizeof(Vehicule));
  MakeVehicule(PointXY(95.,0.), 5., 5., 0, player1, VP1);

  Vehicule *VP2 = (Vehicule*) malloc(sizeof(Vehicule));
  MakeVehicule(PointXY(-95.,0.), 5., 5., 0, player2, VP2);

  /* Level.c*/
  Ballon *ball = (Ballon*) malloc(sizeof(Ballon));
  GLuint imageBallon = loadImage("images/ballon.png");
  MakeBallon(imageBallon,PointXY(0.,0.), ball);

  char picsToLoad[22];
  int nbLevel = 1;
  sprintf(picsToLoad, "./images/terrain%d.jpg", nbLevel);

  GLuint textureIdTerrain = loadImage("./images/terrain1.jpg");
  Terrain t;
  FILE *fileTerrain = fopen("./fond.txt","r");
  if(!fileTerrain) {
      perror("Error while opening the input file.\n");
      return 1;
  }
  MakeTerrain(textureIdTerrain, fileTerrain, &t);

  /* Boucle d'affichage */
  int loop = 1;

  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
      DessinTerrain(&t,textureIdTerrain, windowWidth, windowHeight);
    glPopMatrix();


    //Mouvement de l'Vehicule
    UpdateVehicule(VP1);
    glPushMatrix();
      glTranslatef(VP1->position->x, VP1->position->y, 0);
      glRotatef(VP1->angle,0.,0.,1.);
      glScalef(VP1->largeur,VP1->hauteur, 0.);
      DessinVehicule(VP1);
    glPopMatrix();

    UpdateVehicule(VP2);
    glPushMatrix();
      glTranslatef(VP2->position->x, VP2->position->y, 0);
      glRotatef(VP2->angle,0.,0.,1.);
      glScalef(VP2->largeur,VP1->hauteur, 0.);
      DessinVehicule(VP2);
    glPopMatrix();

    glPushMatrix();
      glColor3f(1.,1.,1.);
      glTranslatef(0.,0.,0.);
      DessinBallon(ball, imageBallon);
    glPopMatrix();

    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    SDL_GL_SwapBuffers();

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenêtre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {
        /* Clic souris */
        case SDL_MOUSEBUTTONUP:

          break;

        /* move the mouse */

        /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
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
          printf("touche lachée (code = %d)\n", e.key.keysym.sym);
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
          break;

        /* resize window */
        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          reshape(windowWidth, windowHeight);
          break;

        default:
          break;
      }
    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  /* Liberation des ressources associées à la SDL */
  SDL_Quit();

  FreeVehicule(VP1);

  return EXIT_SUCCESS;
}
