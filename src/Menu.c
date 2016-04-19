#include "../include/Menu.h"

unsigned int windowH= 650;
unsigned int windowW = 1300;

void MakeMenu(char* pathTexture, int width, int height, Menu* menu, Game* game){
	if(!menu) {
		printf("Impossible de créer le menu, pointeur non alloué\n");
		return;
	}
    /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return;
  }

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  setVideoMode(windowW, windowH);
  reshape(windowW, windowH);
    GLuint texture = loadImage(pathTexture);

	menu->game = game;
	menu->largeur = width;
	menu->hauteur = height;
  menu->texture = texture;

}

void DessinMenu(Menu* menu) {
	glPushMatrix();
	    glEnable(GL_TEXTURE_2D);
	    //glColor3f(255, 255, 255);

	    glBindTexture(GL_TEXTURE_2D, menu->texture);
	   // glScalef(menu->largeur, menu->hauteur, 1);
  	    glBegin(GL_QUADS);
            glTexCoord2f(1,0); glVertex2f(200*0.5 , 100.*.5);
            glTexCoord2f(1,1); glVertex2f(200*0.5 , -100.*.5);
            glTexCoord2f(0,1); glVertex2f(-200*0.5, -100.*.5);
            glTexCoord2f(0,0); glVertex2f(-200*0.5, 100.*.5);
        glEnd();
	    glBindTexture(GL_TEXTURE_2D, 0);
	    glDisable(GL_TEXTURE_2D);
   	glPopMatrix();

}

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void CallMenuDemarrage(Menu* menu){


  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Bienvenue dans HoverLigue !!!!!!!", NULL);

  /* Boucle d'affichage */
  int loop = 1;
  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

	DessinMenu(menu);
	/*
	glBegin(GL_LINES);
      glColor3f(0.,1.,0.);
        glVertex2f(0,0);
        glVertex2f(2,2);
    glEnd();
    */

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

        /* Touche clavier */
        case SDL_KEYDOWN:
			printf("touche pressée (code = %d)\n", e.key.keysym.sym);
			if(e.key.keysym.sym == SDLK_ESCAPE)
				loop = 0;
       		if(e.key.keysym.sym == SDLK_RETURN){
              AddLevel(menu->game, "fond", "./images/terrain1.jpg", "./images/vp1.png", "./images/vp2.png");
            	PlayGame(menu->game);
            }
          	break;

        /* resize window */
        case SDL_VIDEORESIZE:
          windowW  = e.resize.w;
          windowH = e.resize.h;
          reshape(windowW, windowH);
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

}



void FreeMenu(Menu* m){
	free(m->game);
	m->game = NULL;
	printf("FreeMenu OK\n");

}
