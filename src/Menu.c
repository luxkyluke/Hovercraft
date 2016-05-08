#include "../include/Menu.h"

//definition des textures
#define PATH_TEXTURE_DEBUT "./images/menu_deb.png"
#define PATH_TEXTURE_FIN "./images/menu_fin.png"
#define PATH_TEXTURE_PAUSE "./images/menu_pause.png"
#define PATH_TEXTURE_DEBUT_BTN_1 "./images/menu_deb_button1.png"
#define PATH_TEXTURE_FIN_BTN_1 "./images/menu_fin_button1.png"
#define PATH_TEXTURE_PAUSE_BTN_1 "./images/menu_pause_button1.png"
#define PATH_TEXTURE_DEBUT_BTN_2 "./images/menu_deb_button2.png"
#define PATH_TEXTURE_FIN_BTN_2 "./images/menu_fin_button2.png"
#define PATH_TEXTURE_PAUSE_BTN_2 "./images/menu_pause_button2.png"

//definition des positions des boutons
#define POS_BTN1_TOP 100
#define POS_BTN1_BOTTOM 140
#define POS_BTN2_TOP 190
#define POS_BTN2_BOTTOM 230
#define POS_BTN_RIGHT 930
#define POS_BTN_LEFT 565

/* Nombre de bits par pixel de la fen�tre */
static const unsigned int BIT_PER_PIXEL = 32;

//redimenssionne la fenetre SDL
void reshape(unsigned int windowWidth, unsigned int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100., 100., -100. * (float) windowHeight / (float) windowWidth,
			100. * (float) windowHeight / (float) windowWidth);
}

//Ouvre la fenetre SDL
void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
	if (NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL,
	SDL_OPENGL | SDL_GL_DOUBLEBUFFER | 1)) {
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
		if (-1 == SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
			fprintf(stderr,"Impossible d'initialiser la SDL. Fin du programme.\n");
			return false;
		}
		/* Ouverture d'une fenêtre et création d'un contexte OpenGL */
		setVideoMode(menu->largeur, menu->hauteur);
		reshape(menu->largeur, menu->hauteur);
		//InitGameMenu(menu);
		menu->texture = loadImage(PATH_TEXTURE_DEBUT);
		menu->texture_btn1 = loadImage(PATH_TEXTURE_DEBUT_BTN_1);
		menu->texture_btn2 = loadImage(PATH_TEXTURE_DEBUT_BTN_2);
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

	return true;
}


#define POS_SCORE_X -5
#define POS_SCORE_Y 12
void AfficheScoreMenu(int score1, int score2) {
	char scoreP1[2];
	sprintf(scoreP1, "%d", score1);
	char scoreP2[2];
	sprintf(scoreP2, "%d", score2);
	glPushMatrix();
		glPushMatrix();
			glColor3f(1, 1, 1);
			vBitmapOutput(-POS_SCORE_Y-1, POS_SCORE_X, scoreP2, GLUT_BITMAP_TIMES_ROMAN_24);
			glColor3f(1, 1, 1);
		glPopMatrix();
		glPushMatrix();
			glColor3f(1, 1., 1.);
			vBitmapOutput(POS_SCORE_Y, POS_SCORE_X, scoreP1, GLUT_BITMAP_TIMES_ROMAN_24);
		glPopMatrix();
	glPopMatrix();
	glColor3f(1, 1, 1);
}


void DessinMenu(Menu* menu, GLuint texture, int scoreP1, int scoreP2) {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
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
		if(menu->type == fin)
			AfficheScoreMenu(scoreP1, scoreP2);
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

//boucle d'affichage d'un menu avec la gestion des evenements relatif a chaque boutons
bool LoopMenu(Menu* menu, Game* game, int scoreP1, int scoreP2) {
	GLuint texture = menu->texture;
	bool ret = false; //indique si l'utilisateur veut quitter (croix rouge ou echap);
	int souris_x = 0;
	int souris_y = 0;
	/* Boucle d'affichage */
	int loop = 1;
	while (loop) {
		/* Récupération du temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();

		//Dessin du menu
		DessinMenu(menu, texture, scoreP1, scoreP2);

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

			//touche du joystick
			case SDL_JOYBUTTONDOWN:
					if(e.jbutton.button == 1) {
						switch (menu->type){
							case debut :
								if(!PlayGame(game, menu->largeur, menu->hauteur))
									loop = 0;
								break;
							case fin :
								ret = true;
								loop = 0;
							case pause :
								loop = 0;
								ret = true;
								break;
						}
					} else if (e.jbutton.button == 2) {
						ret = false;
						loop = 0;
					}
			        break;

			//mouvement de la sourie
			case SDL_MOUSEMOTION:
				souris_x = e.button.x;
				souris_y = e.button.y;
				if (IsOnButton2(souris_x, souris_y)) {
					texture = menu->texture_btn2;
				} else if (IsOnButton1(souris_x, souris_y)) {
					texture = menu->texture_btn1;
				}

				else {
					texture = menu->texture;
				}
				break;

			/* Touche clavier */
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE){
					ret = false;
					loop = 0;
					break;
				}
				break;

			//click de la sourie
			case SDL_MOUSEBUTTONDOWN:
				if (IsOnButton1(souris_x, souris_y) ){
					switch (menu->type){
						case debut :
							if(!PlayGame(game, menu->largeur, menu->hauteur))
								loop = 0;
							break;
						case fin :
							ret = true;
							loop = 0;
							break;
						case pause :
							loop = 0;
							ret = true;
							break;
					}
				}
				if (IsOnButton2(souris_x, souris_y)) {
					ret = false;
					loop = 0;
				}
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

void CallMenuDemarrage(Menu* menu, Game* game) {
	/* Titre de la fenêtre */
	SDL_WM_SetCaption("Bienvenue dans HoverLigue !!!!!!!", NULL);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)
			== -1) { // Initialisation de SDL_Mixer
		printf("%s", Mix_GetError());
	}

	Mix_Music *musique;
	musique = Mix_LoadMUS("./musiques/musique.mp3");
	Mix_PlayMusic(musique, -1);
	Mix_VolumeMusic(30);

	//lance le menu de démarrage avec le jeu a démarrer
	LoopMenu(menu, game,0,0);

	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	/* Liberation des ressources associées à la SDL */
	SDL_Quit();
}

bool CallMenuPause(Menu* menu) {
	//lance le menu pause
	return LoopMenu(menu, NULL, 0, 0);
}

bool CallMenuFin(Menu* menu, int scoreP1, int scoreP2) {
	//lance le menu de fin avec le score des joueurs
	return LoopMenu(menu, NULL, scoreP1, scoreP2);
}

