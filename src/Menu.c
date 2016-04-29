#include "../include/Menu.h"
#define DURATION_TIME 180000

#define PATH_TEXTURE_DEBUT "./images/menu_deb.jpg"
#define PATH_TEXTURE_FIN "./images/menu_fin.jpg"
#define PATH_TEXTURE_PAUSE "./images/menu_pause.jpg"
#define PATH_TEXTURE_DEBUT_BTN_1 "./images/menu_deb_button1.jpg"
// #define PATH_TEXTURE_DEBUT_TER_1 "./images/menu_deb_terrain1.png"
// #define PATH_TEXTURE_DEBUT_TER_2 "./images/menu_deb_terrain2.png"
#define PATH_TEXTURE_FIN_BTN_1 "./images/menu_fin_button1.jpg"
#define PATH_TEXTURE_PAUSE_BTN_1 "./images/menu_pause_button1.jpg"
#define PATH_TEXTURE_DEBUT_BTN_2 "./images/menu_deb_button2.jpg"
#define PATH_TEXTURE_FIN_BTN_2 "./images/menu_fin_button2.jpg"
#define PATH_TEXTURE_PAUSE_BTN_2 "./images/menu_pause_button2.jpg"
#define POS_BTN1_TOP 71
#define POS_BTN1_BOTTOM 96
#define POS_BTN2_TOP 148
#define POS_BTN2_BOTTOM 175
#define POS_BTN_RIGHT 815
#define POS_BTN_LEFT 455

/* Nombre de bits par pixel de la fen�tre */
static const unsigned int BIT_PER_PIXEL = 32;

void reshape(unsigned int windowWidth, unsigned int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100., 100., -100. * (float) windowHeight / (float) windowWidth,
			100. * (float) windowHeight / (float) windowWidth);
}

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
	if (NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL,
	SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
		exit(EXIT_FAILURE);
	}
}

bool MakeMenu(int width, int height, Menu* menu, TypeMenu type) {
	if (!menu) {
		printf("Impossible de créer le menu, pointeur non alloué\n");
		return false;
	}

	menu->largeur = width;
	menu->hauteur = height;

	menu->type = type;
	switch (type) {
	case debut:
		/* Initialisation de la SDL */
		if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
			fprintf(stderr,
					"Impossible d'initialiser la SDL. Fin du programme.\n");
			return false;
		}
		/* Ouverture d'une fenêtre et création d'un contexte OpenGL */
		setVideoMode(menu->largeur, menu->hauteur);
		reshape(menu->largeur, menu->hauteur);
		InitGameMenu(menu, DURATION_TIME);
		menu->texture = loadImage(PATH_TEXTURE_DEBUT);
		menu->texture_btn1 = loadImage(PATH_TEXTURE_DEBUT_BTN_1);
		menu->texture_btn2 = loadImage(PATH_TEXTURE_DEBUT_BTN_2);
		// menu->texture_ter1 = loadImage(PATH_TEXTURE_DEBUT_TER_1);
		// menu->texture_ter2 = loadImage(PATH_TEXTURE_DEBUT_TER_2);
		break;

	case pause:
		menu->texture = loadImage(PATH_TEXTURE_PAUSE);
		menu->texture_btn1 = loadImage(PATH_TEXTURE_PAUSE_BTN_1);
		menu->texture_btn2 = loadImage(PATH_TEXTURE_PAUSE_BTN_2);
		break;

	case fin:
		menu->texture = loadImage(PATH_TEXTURE_FIN);
		menu->texture_btn1 = loadImage(PATH_TEXTURE_FIN_BTN_1);
		menu->texture_btn2 = loadImage(PATH_TEXTURE_FIN_BTN_2);
		break;

	default:
		break; //InitGameMenu(menu, DURATION_TIME);
	}

	//InitGameMenu(menu, DURATION_TIME);
//	menu->game = (Game *) malloc(sizeof(Game));
//	if(!MakeGame(menu->game, DURATION_TIME)){
//		printf("Erreur MakeGame !!");
//		return false;
//	}

	return true;

	//return true;
}

bool InitGameMenu(Menu* m, int duration) {
	m->game = (Game *) malloc(sizeof(Game));
	if (!MakeGame(m->game, duration)) {
		printf("Erreur MakeGame !!");
		return false;
	}
	return true;
}

void DessinMenu(Menu* menu, GLuint texture) {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	//glColor3f(255, 255, 255);

	glBindTexture(GL_TEXTURE_2D, texture);
	// glScalef(menu->largeur, menu->hauteur, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex2f(200 * 0.5, 100. * .5);
	glTexCoord2f(1, 1);
	glVertex2f(200 * 0.5, -100. * .5);
	glTexCoord2f(0, 1);
	glVertex2f(-200 * 0.5, -100. * .5);
	glTexCoord2f(0, 0);
	glVertex2f(-200 * 0.5, 100. * .5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

bool IsOnButton2(int x, int y) {
	return (x >= POS_BTN_LEFT && x <= POS_BTN_RIGHT && y >= POS_BTN2_TOP
			&& y <= POS_BTN2_BOTTOM);
}

bool IsOnButton1(int x, int y) {
	return (x >= POS_BTN_LEFT && x <= POS_BTN_RIGHT && y >= POS_BTN1_TOP
			&& y <= POS_BTN1_BOTTOM);
}

// bool IsOnTerrain1(int x, int y) {
// 	return (x >= 255 && x <= 567 && y >= 291
// 			&& y <= 409);
// }

// bool IsOnTerrain2(int x, int y) {
// 	return (x >= 677 && x <= 903 && y >= 291
// 			&& y <= 409);
// }

bool LoopMenu(Menu* menu){

	GLuint texture = menu->texture;

	bool ret = false;
	int souris_x = 0;
	int souris_y = 0;
	/* Boucle d'affichage */
	int loop = 1;
	while (loop) {
		/* Récupération du temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();

		DessinMenu(menu, texture);

		/* glBegin(GL_QUADS);
		 glColor3f(0.,1.,0.);
		 glVertex2f(-30,40);
		 glVertex2f(25,40);
		 glVertex2f(25,35);
		 glVertex2f(-30,35);
		 glEnd();*/

		/* Echange du front et du back buffer : mise à jour de la fenêtre */
		SDL_GL_SwapBuffers();

		/* Boucle traitant les evenements */
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			/* L'utilisateur ferme la fenêtre : */
			if (e.type == SDL_QUIT) {
				loop = 0;
				break;
			}

			/* Quelques exemples de traitement d'evenements : */

			switch (e.type) {

			case SDL_MOUSEMOTION:
				souris_x = e.button.x;
				souris_y = e.button.y;
				if (IsOnButton2(souris_x, souris_y)) {
					texture = menu->texture_btn2;
					//printf("EXIT\n");
				} else if (IsOnButton1(souris_x, souris_y)) {
					texture = menu->texture_btn1;
					//printf("PLAY\n");
				}
				// else if (IsOnTerrain1(souris_x,souris_y)) {
				// 	texture = menu->texture_ter1;
				// } else if (IsOnTerrain2(souris_x,souris_y)) {
				// 	texture = menu->texture_ter2;
				// }

				else {
					texture = menu->texture;
				}
				break;

				/* Touche clavier */
			case SDL_KEYDOWN:
				//printf("touche pressée (code = %d)\n", e.key.keysym.sym);
				if (e.key.keysym.sym == SDLK_ESCAPE)
					loop = 0;
				/*if (e.key.keysym.sym == SDLK_RETURN) {
				 PlayGame(menu->game, menu->largeur, menu->hauteur);*/

				break;

			case SDL_MOUSEBUTTONDOWN:
				//printf("souris-x en %d     souris_y en %d\n", souris_x, souris_y);
				// if ((IsOnButton1(souris_x, souris_y) || IsOnTerrain1(souris_x,souris_y) || IsOnTerrain2(souris_x,souris_y)) && menu->game != NULL) {
				if (IsOnButton1(souris_x, souris_y) && menu->game != NULL) {
					switch (menu->type){
						case debut :
							if(!PlayGame(menu->game, menu->largeur, menu->hauteur))
								loop = 0;
							break;
						case fin :
							ret = true;
							loop = 0;
						case pause :
							loop = 0;
							ret = true;
							//ContinueGame(menu->game);
							break;
					}
				}
				if (IsOnButton2(souris_x, souris_y)) {
					ret = false;
					loop = 0;
					//printf("EXIT\n");
				}
				break;

				/* resize window */
			case SDL_VIDEORESIZE:
				menu->largeur = e.resize.w;
				menu->hauteur = e.resize.h;
				reshape(menu->largeur, menu->hauteur);
				break;

			default:
				break;
			}
		}

		/* Calcul du temps écoulé */
		Uint32 elapsedTime = SDL_GetTicks() - startTime;

		/* Si trop peu de temps s'est écoulé, on met en pause le programme */
		if (elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	}
	return ret;
}

void CallMenuDemarrage(Menu* menu) {

	/* Titre de la fenêtre */
	SDL_WM_SetCaption("Bienvenue dans HoverLigue !!!!!!!", NULL);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
			== -1) { // Initialisation de SDL_Mixer
		printf("%s", Mix_GetError());
	}

	Mix_Music *musique;
	musique = Mix_LoadMUS("./musiques/musique.mp3");
	Mix_PlayMusic(musique, -1);
	Mix_VolumeMusic(0);


	LoopMenu(menu);

	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	/* Liberation des ressources associées à la SDL */
	SDL_Quit();

}

bool CallMenuPause(Menu* menu) {
	return LoopMenu(menu);
}

bool CallMenuFin(Menu* menu) {
	return LoopMenu(menu);
}

void FreeMenu(Menu* m) {
	FreeGame(m->game);
	free(m->game);
	m->game = NULL;
	printf("FreeMenu OK\n");
}
