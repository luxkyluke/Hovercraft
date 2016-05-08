#include "Level.h"
#include "../include/Menu.h"

//definition des valeurs par default des véhicules et du ballon
#define DEFAULT_VP1_POS_X 90.
#define DEFAULT_VP1_POS_Y 0.
#define DEFAULT_VP2_POS_Y 0.
#define DEFAULT_VP2_POS_X -90.
#define DEFAULT_VEHICUL_W 5.
#define DEFAULT_VEHICUL_H 5.
#define DEFAULT_BALL_POS_X 0.
#define DEFAULT_BALL_POS_Y 0.
#define DEFAULT_BALL_RADIUS 4.
#define DEFAULT_BALL_TEXTURE_PATH "images/ballon.png"
#define NB_TEXTURE 3

const int JOYSTICK_DEAD_ZONE = 8000;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

//boolean pour préciser quand la camera est en action
bool camera_is_in_work = false;

bool MakeLevel(Level* l, char* nameFichTerrain, int duration, char *pathTexture) {
	if (l == NULL) {
		printf("Impossible de crÃ©er le level, pointeur non allouÃ©\n");
		return false;
	}
	FILE *fileTerrain;
	Terrain* t = (Terrain*) malloc(sizeof(Terrain));
	Ballon *ballon = (Ballon *) malloc(sizeof(Ballon));
	Vehicule* vp1 = (Vehicule *) malloc(sizeof(Vehicule));
	Vehicule *vp2 = (Vehicule *) malloc(sizeof(Vehicule));
	Point2D posVp1, posVp2;
	GLuint imageBallon = loadImage(DEFAULT_BALL_TEXTURE_PATH);
	GLuint textureIdTerrain = loadImage(pathTexture);

	Camera *cam = (Camera *) malloc(sizeof(Camera));

	char terrainTxt[30] = "./levels/";
	strcat(terrainTxt, nameFichTerrain);
	strcat(terrainTxt, ".txt");

	fileTerrain = fopen(terrainTxt, "r");
	if (!fileTerrain) {
		perror("Error while opening the input file.\n");
		return false;
	}

	//création du terrain
	MakeTerrain(textureIdTerrain, fileTerrain, t, &posVp1, &posVp2);
	//création du vehicule player1
	MakeVehicule(posVp1, DEFAULT_VEHICUL_H, DEFAULT_VEHICUL_W, player1, vp1);
	//création vehicule player2
	MakeVehicule(posVp2, DEFAULT_VEHICUL_H, DEFAULT_VEHICUL_W, player2, vp2);
	//creation ballon
	MakeBallon(imageBallon, PointXY(DEFAULT_BALL_POS_X, DEFAULT_BALL_POS_Y),
			ballon, DEFAULT_BALL_RADIUS);
	//creation camera
	MakeCamera(cam);

	l->ballon = ballon;
	l->vp1 = vp1;
	l->vp2 = vp2;
	l->camera = cam;
	l->terrain = t;
	l->duration = duration;
	return true;
}

void CheckTouched(Level* l) {
	CollisionVehiculeVehicule(l->vp1, l->vp2);
	CollisionVehiculeBallon(l->ballon, l->vp1);
	CollisionVehiculeBallon(l->ballon, l->vp2);
	CollisionVehiculeTerrain(l->vp1, l->terrain);
	CollisionVehiculeTerrain(l->vp2, l->terrain);
	Bonus bonusVp1, bonusVp2;
	if (!IsInBonus(l->vp1)) {
		if (CollissionVehiculeCheckpoints(l->vp1, l->terrain, &bonusVp1)) { //si vp1 a pris un bonus
			if (bonusVp1 == freeze) { //si c'est un freeze, on lui retire et on l'applique a vp2
				l->vp2->timerBonus = SDL_GetTicks();
				l->vp2->bonus = bonusVp1;
			} else {//sinon il prend le boost pour lui
				l->vp1->timerBonus = SDL_GetTicks();
				l->vp1->bonus = bonusVp1;
			}
		}
	}
	if (!IsInBonus(l->vp2)) {
		if (CollissionVehiculeCheckpoints(l->vp2, l->terrain, &bonusVp2)) {//idem que pour vp1
			if (bonusVp2 == freeze) {
				l->vp1->timerBonus = SDL_GetTicks();
				l->vp1->bonus = bonusVp2;
			} else {
				l->vp2->timerBonus = SDL_GetTicks();
				l->vp2->bonus = bonusVp2;
			}
		}
	}

	CollisionBallonTerrain(l->ballon, l->terrain);
	//tant que la caméra est en action on ajoute pas de point au score des joueurs
	if (camera_is_in_work)
			return ;
	Player buteur;
	if (CollisionBallonBut(l->ballon, l->terrain, &buteur)) {//si le ballon est entré dans un but
		if (buteur == player1) {
			l->scoreP1 += 1;
		} else {
			l->scoreP2 += 1;
		}

		/*Mix_AllocateChannels(1); //Alloue 1 canal
		 Mix_Volume(1, MIX_MAX_VOLUME);
		 Mix_Chunk *goal; // Crée un pointeur pour stocker un .WAV
		 goal = Mix_LoadWAV("./musiques/GOAL.wav"); // Charge un .WAV dans un pointeur
		 Mix_VolumeChunk(goal, MIX_MAX_VOLUME);
		 Mix_PlayChannel(1, goal, 0);*/

		//démarre le zoom caméra
		l->camera->start = 1;
	}
	//Mix_FreeChunk(goal);
}

void FreeLevel(Level * l) {
	FreeTerrain(l->terrain);
	FreeBallon(l->ballon);
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

void DessinMinimap(Level *l) {
	glPushMatrix();
	glTranslatef(0, -42, 0);
	glScalef(0.15, 0.15, 1);
	glPushMatrix();
	glScalef(190, 100, 1);
	dessinCarre(0, ColorRGBA(0., 0., 0., 1.));
	glPopMatrix();

	glPushMatrix();
	glTranslatef(l->ballon->cercle->centre.x, l->ballon->cercle->centre.y, 0);
	glScalef(10, 10, 1);
	dessinCercle(50, ColorRGBA(0., 0., 0., 1.), 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(l->vp1->position.x, l->vp1->position.y, 0);
	glScalef(10, 10, 1);
	dessinCercle(50, ColorRGBA(0.1, 0.5, 0.8, 1.), 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(l->vp2->position.x, l->vp2->position.y, 0);
	glScalef(10, 10, 1);
	dessinCercle(50, ColorRGBA(0.9, 0.6, 0.1, 1.), 1);
	glPopMatrix();
	glPopMatrix();
}

void DessinLevel(Level* l, Uint32 duration) {
	DessinTerrain(l->terrain);
	DessinVehicule(l->vp1);
	DessinVehicule(l->vp2);
	DessinBallon(l->ballon);

	DessinMinimap(l);

	int min = (int) (l->duration - duration) / 60000;
	int nbSec = (int) (l->duration - duration) / 1000;
	int sec = (int) nbSec - (min * 60);

	char time[10];
	sprintf(time, "%d : %d", min, sec + 1);

	char scoreP1[2];
	sprintf(scoreP1, "%d", l->scoreP1);
	char scoreP2[2];
	sprintf(scoreP2, "%d", l->scoreP2);

	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glColor3d(1, 1, 1);
	vBitmapOutput(-2, 45, time, GLUT_BITMAP_HELVETICA_18);
	glPushMatrix();
	glTranslatef(7, -1, 0);
	vBitmapOutput(6, 45, scoreP1, GLUT_BITMAP_HELVETICA_18);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, -1, 0);
	vBitmapOutput(-6, 45, scoreP2, GLUT_BITMAP_HELVETICA_18);
	glPopMatrix();
	glPopMatrix();

}

void UpdateLevel(Level* l) {
	//vp1
	UpdateVehicule(l->vp1);
	//vp2
	UpdateVehicule(l->vp2);
	//Camera
	UpdateCameraLevel(l);
}

void ResetLevel(Level* l) {
	// Reset first vehicule.
	ResetVehicule(l->vp1);
	// Reset second vehicule.
	ResetVehicule(l->vp2);

	ResetTerrain(l->terrain);
	// Reset ball.
	ResetBallon(l->ballon);
	// Reset Camera
	ResetCamera(l->camera);
}

//Reset le niveau en remettant les scores à 0
void FullResetLevel(Level* l) {
	l->scoreP1 = 0;
	l->scoreP2 = 0;
	ResetLevel(l);
}

//Ralenti le level
void RalentiLevel(Level* level) {
	level->vp1->vitesse = DivVector(level->vp1->vitesse, 1.1);
	level->vp2->vitesse = DivVector(level->vp2->vitesse, 1.1);
	level->ballon->vitesse = DivVector(level->ballon->vitesse, 1.1);
}

void UpdateCameraLevel(Level* level) {
	if (level->camera->zoomLevel < 4 && level->camera->start == 1) {
		camera_is_in_work = true;
		LookAt(level->camera, level->ballon->cercle->centre,
				level->camera->zoomLevel);
		level->camera->zoomLevel += 0.01;
		RalentiLevel(level);
	} else if (level->camera->zoomLevel >= 4) {
		ResetLevel(level);
		camera_is_in_work = false;
	}
}

void CheckBonus(Level* level) {
	CheckBoost(level->vp1);
	CheckBoost(level->vp2);
	CheckFreeze(level->vp1);
	CheckFreeze(level->vp2);
}

bool PlayLevel(Level* level, int id, bool* cross, SDL_Joystick* joystick) {
	if (!level)
		return false;

	Vehicule* VP1 = level->vp1;
	Vehicule* VP2 = level->vp2;
	srand(time(NULL));

	// Titre de la fenÃªtre
	char windowname[30];
	sprintf(windowname, "HoverLigue Niveau %d !", id + 1);

	SDL_WM_SetCaption(windowname, NULL);
	FullResetLevel(level);

	Menu* menuPause = (Menu *) malloc(sizeof(Menu));
	if (!MakeMenu(1300, 650, menuPause, pause))
		return EXIT_FAILURE;

	// Boucle d'affichage
	int loop = 1;
	Uint32 timeStartLevel = SDL_GetTicks();
	Uint32 duration = SDL_GetTicks() - timeStartLevel;
	Uint32 timerStartPause = SDL_GetTicks();
	while (loop && duration < level->duration) {
		// RÃ©cupÃ©ration du temps au dÃ©but de la boucle
		Uint32 startTime = SDL_GetTicks();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//verification des collisions
		CheckTouched(level);

		//verificatoin des bonus vehicules
		CheckBonus(level);

		//mise a jour des position des elements
		UpdateLevel(level);

		//dessin du niveau
		DessinLevel(level, duration);

		// Echange du front et du back buffer : mise Ã  jour de la fenÃªtre
		SDL_GL_SwapBuffers();

		// Boucle traitant les evenements
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			// L'utilisateur ferme la fenÃªtre

			// Quelques exemples de traitement d'evenements :
			switch (e.type) {

			case SDL_QUIT :
				loop = 0;
				*cross = true;
				break;

			//evenement joystick
			case SDL_JOYAXISMOTION:
        		if(e.jaxis.axis == 0) {
        			//X axis motion
        			if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
        			    VP2->tourne = -1;
        			else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
        			    VP2->tourne =  1;
        			else
        			    VP2->tourne = 0;
        		}

        		//Y axis motion
        		else if( e.jaxis.axis == 1 ) {
        		    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
        		        VP2->avance = 1;
        		    else
        		        VP2->avance = 0;
        		}

        		if(e.jaxis.axis == 2) {
        			//X axis motion
        			if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
        			    VP1->tourne = -1;
        			else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
        			    VP1->tourne =  1;
        			else
        			    VP1->tourne = 0;
        		}

        		//Y axis motion
        		else if( e.jaxis.axis == 3) {
        		    if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
        		        VP1->avance = 1;
        		    else
        		        VP1->avance = 0;
        		}
        		break;

			// Touche clavier
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_z) {
					VP2->avance = 1;
					break;
				}
				if (e.key.keysym.sym == SDLK_UP){
					VP1->avance = 1;
					break;
				}
				if (e.key.keysym.sym == SDLK_RIGHT){
					VP1->tourne = 1;
					break;
				}
				if (e.key.keysym.sym == SDLK_LEFT){
					VP1->tourne = -1;
					break;
				}
				if (e.key.keysym.sym == SDLK_d){
					VP2->tourne = 1;
					break;
				}
				if (e.key.keysym.sym == SDLK_q){
					VP2->tourne = -1;
					break;
				}
				break;

			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_z){
					VP2->avance = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_UP){
					VP1->avance = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_RIGHT){
					VP1->tourne = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_LEFT){
					VP1->tourne = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_q){
					VP2->tourne = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_d){
					VP2->tourne = 0;
					break;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					timerStartPause = SDL_GetTicks();
					if (!CallMenuPause(menuPause)) {
						*cross = true;
						loop = 0;
					}
					timeStartLevel += SDL_GetTicks() - timerStartPause;
					e.key.keysym.sym = SDLK_t;
					break;
				}
				break;

			// touche joystick
			case SDL_JOYBUTTONDOWN:
				if(e.jbutton.button == 1 || e.jbutton.button == 2) {
					timerStartPause = SDL_GetTicks();
					if (CallMenuPause(menuPause) == false) {
						*cross = true;
						loop = 0;
					}
					timeStartLevel += SDL_GetTicks() - timerStartPause;
					break;
				}
				break;

			default:
				break;
			}
		}

		// Calcul du temps Ã©coulÃ©
		Uint32 elapsedTime = SDL_GetTicks() - startTime;

		// Si trop peu de temps s'est Ã©coulÃ©, on met en pause le programme
		if (elapsedTime < FRAMERATE_MILLISECONDS) {
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
		duration = SDL_GetTicks() - timeStartLevel;
	}

	camera_is_in_work = false;

	return (loop);

}
