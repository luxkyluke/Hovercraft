#include "Game.h"
#include "sdl_tools.h"

#define NB_MAX_LEVEL 30


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

unsigned int windowHeight= 600;
unsigned int windowWidth = 1200;

void MakeGame(Game* game, float duration){
	if(game == NULL) {	
		printf("Impossible de créer le game, pointeur non alloué\n"); 
		return;
	}

	 // Initialisation de la SDL 
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
	  fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
	  return;
	}

	// Ouverture d'une fenêtre et création d'un contexte OpenGL 
	setVideoMode(windowWidth, windowHeight);
	reshape(windowWidth, windowHeight);

	game->levels = (Level **) malloc(NB_MAX_LEVEL*sizeof(Level*));
	game->nbLevels = 0;
	game->duration = duration;
}

int AddLevel(Game* game, char* nameFichTerrain,  char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2){
	if(!game || !nameFichTerrain || !pathTextureTerrain || !pathTextureVp2 || !pathTextureVp1)
		return -1;
	if(game->nbLevels == NB_MAX_LEVEL){
		printf("Echec de l'ajout - Nombre de level max depasse \n");
		return -1;
	}
	int id = game->nbLevels;
	game->levels[id] = (Level *) malloc(sizeof(Level));
	MakeLevel(game->levels[id], nameFichTerrain, pathTextureTerrain, pathTextureVp1, pathTextureVp2);
	if(game->levels[id]  == NULL){
		printf("Probleme makeLevel dans AddLevel\n");
		return -1;
	}
	game->nbLevels += 1;
	
	return id;
	return 0;
}

void PlayLevel(Game* game, int idLevel){
	
	if(!game || idLevel >= game->nbLevels)
		return;

	

  Level* level = game->levels[idLevel];
  Vehicule* VP1 = level->vp1;
  Vehicule* VP2 = level->vp2;
 

  

  // Titre de la fenêtre 
  char windowname[30];
  sprintf(windowname, "HoverLigue Niveau %d !", idLevel+1);
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



//ZONE DE TEST//////////
    /*glBegin(GL_LINES);
      glColor3f(0.,1.,0.); 
        glVertex2f(level->ballon->cercle->centre.x,level->ballon->cercle->centre.y);
        glVertex2f(level->ballon->direction.x, level->ballon->direction.y);
    glEnd();

    glPushMatrix();
        glTranslatef(level->ballon->cercle->centre.x, level->ballon->cercle->centre.y, 0);
        glScalef(level->ballon->cercle->radius, level->ballon->cercle->radius, 0.);
        dessinCercle(100, 0.8, 0.4, 0.1, 0);
      glPopMatrix();
*/
///////////////////////////



    DessinTerrain(level->terrain, windowWidth, windowHeight);


    //printf("level->terrain-> : %3.f\n", VP1->position.x);
    //Mouvement de l'Vehicule
    UpdateVehicule(VP1);
   
    DessinVehicule(VP1);

    UpdateVehicule(VP2);
    
    DessinVehicule(VP2);
    
    DessinBallon(level->ballon);

    // Echange du front et du back buffer : mise à jour de la fenêtre 
    SDL_GL_SwapBuffers();

    CheckTouched(level);

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

void FreeGame(Game* g){
	int i;
	for(i=0; i< g->nbLevels ; i++){
		FreeLevel(g->levels[i]);
		free(g->levels[i]);
		g->levels[i] = NULL;
	}
	free(g->levels);
	g->levels = NULL;
	printf("FreeGame OK\n");
}
