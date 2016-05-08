#ifndef LEVEL_H_
#define LEVEL_H_

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string.h>
#include <time.h>

#include "Camera.h"
#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"
#include "Point2D.h"
#include "bool.h"
#include "Collision.h"
#include "sdl_tools.h"
#include "Camera.h"
#include "Checkpoint.h"
#include "Vehicule.h"
#include "glut_tools.h"
#include <SDL/SDL_mixer.h>



typedef struct {
	Terrain* terrain;
	Vehicule* vp1;	//véhicule Player1
	Vehicule* vp2;	//véhicule Player2
	Ballon* ballon;
	int scoreP1;
	int scoreP2;
	Camera* camera;
	int duration; 	//durée d'un niveau
} Level;

/**
 * @brief Creer un level avec le pointeur de Level passé en paramètre
 * @param l - le pointeur du Level à créer
 * @param nameFichTerrain - le fichier txt du terrain du level
 * @param duration - la durée du level
 * @param pathTexture - la texure du terrain du level
 * @return true si la création c'est bien passé, false sinon
 */
bool MakeLevel(Level* l, char* nameFichTerrain, int duration, char *pathTexture);

/**
 * @brief Verifie s'il y a eu une colision entre les éléments du niveau et agis en conséquence (ex:but = scrore+1)
 * @param l - le pointeur du Level à vérifier
 */
void CheckTouched(Level *l);

/**
 * @brief Libere les pointeur du Level
 * @param l - le pointeur du level à liberer
 */
void FreeLevel(Level* l);

/**
 * @brief Dessine le Level passé en param
 * @param l - le pointeur du Level à déssiner
 * @param duration - temps qui s'est ecoule depuis le debut de la partie
 */
void DessinLevel(Level* l, Uint32 duration);

/**
 * @brief Met a jour tous les elements du niveau
 * @param l - le pointeur du Level a mettre a jour
 */
void UpdateLevel(Level* l);

/**
 * @brief Lance le niveau
 * @param l - le pointeur sur le level a lancer
 * @param i - le numero du niveau
 * @param cross - indique si l'utilisateur click sur la croix
 * @param joystick - joystick
 * @return false si l'utilisateur a interrompue la partie avant la fin du temps imparti
 *
 */
bool PlayLevel(Level* l, int i, bool* cross, SDL_Joystick* joystick);

/**
 * @brief Réinitialise le niveau comme au début
 * @param l - le pointeur sur le level a reset
 */
void ResetLevel(Level* l);

/**
 * @brief met a jour la camera du niveau
 * @param level - le pointeur sur le level a mettre a jour
 */
void UpdateCameraLevel(Level* level);

/**
 * @brief Dessin la mini-carte du niveau
 * @param level - le pointeur sur le level a dessiner
 */
void DessinMinimap(Level* l);

/**
 * @brief Verifie l'etat des bonus des véhicules
 * @param level - le pointeur du le Level à checker
 */
void CheckBonus(Level* level);

#endif
