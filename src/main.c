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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/Geometry.h"
#include "../include/Vehicule.h"
#include "../include/Player.h"

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100., 100., -50., 50.);
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

  /* Boucle d'affichage */
  int loop = 1;

  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //Mouvement de l'Vehicule
    UpdateVehicule(VP1);
    glPushMatrix();
      //glRotatef(90, 0, 0, 1);
      glTranslatef(VP1->position->x, VP1->position->y, 0);
      glScalef(VP1->largeur,VP1->hauteur, 0.);
      DessinVehicule(VP1);
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
          if(e.key.keysym.sym == SDLK_q)
            loop = 0;
          if(e.key.keysym.sym == 273)
            VP1->avance = 1;

          if(e.key.keysym.sym == 275)
            VP1->tourne = 1;
          if(e.key.keysym.sym == 276)
            VP1->tourne = -1;
          break;

        case SDL_KEYUP:
          printf("touche lachée (code = %d)\n", e.key.keysym.sym);
          if(e.key.keysym.sym == SDLK_q)
            loop = 0;
          if(e.key.keysym.sym == 273)
            VP1->avance = 0;

          if(e.key.keysym.sym == 275)
            VP1->tourne = 0;
          if(e.key.keysym.sym == 276)
            VP1->tourne = 0;
          break;

        /* resize window */
        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          setVideoMode(windowWidth, windowHeight);
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
