#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void setViewPort(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);

    if(NULL == SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
      fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
      return ;
    }
  }

int main(int argc, char** argv) {

  /* Dimensions de la fenêtre */
  unsigned int windowWidth  = 800;
  unsigned int windowHeight = 600;

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  


  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  
  /* Titre de la fenêtre */
  SDL_WM_SetCaption("OpenGL powa :D", NULL);
  
  /* Boucle d'affichage */
  int loop = 1;
  glClear(GL_COLOR_BUFFER_BIT);
  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    
    /* Placer ici le code de dessin */
    
    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    
    //SDL_GL_SwapBuffers();
    
    /* Boucle traitant les evenements */
    SDL_Event e;
    float r, v=0, b=0;
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
          printf("clic en (%d, %d)\n", e.button.x, e.button.y);
          break;
        case SDL_MOUSEBUTTONDOWN:
          r = (e.button.x%255/255.0);
          b = (e.button.y%255/255.0);
          glColor3ub(r,v,b);
          glBegin(GL_POINTS);
            glVertex2f(-1 + 2. * e.button.x / windowWidth, -(-1 + 2. * e.button.y / windowHeight));
          glEnd();
          break;

        case SDL_VIDEORESIZE:
          setViewPort(e.resize.w, e.resize.h);
          break;

        case SDL_MOUSEMOTION:
          r = (e.button.x%255/255.0);
          b = (e.button.y%255/255.0);
          //glClearColor(r, v, b, 1.0);
          break;


        /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
          if(e.key.keysym.sym == SDLK_q)
            loop=0;
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
  
  return EXIT_SUCCESS;
}
