#ifndef VEHICULE_H_
#define VEHICULE_H_

#include "Point2D.h"
#include "Player.h"
#include "Vector2D.h"
#include "Geometry.h"
#include "bool.h"
#include "Bonus.h"
#include <math.h>
#define PI 3.14

/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */

typedef struct {
	float hauteur;
	float largeur;
	Cercle* cercle;
    Cercle* facticeCercle;
	float angle;
	Point2D position;
	Point2D defaultPosition;
	Vector2D direction;
	Vector2D vitesse;
	Vector2D acceleration;
	int avance, tourne;
	Player player;
    Bonus bonus;
    int timerBonus;
    GLuint texture;
}Vehicule;

/**
 * @brief Cree un vehicule avec le pointeur de vehicule passe en parametre
 * @param pos - la position de depart du vehicule
 * @param hauteur - la hauteur du vehicule
 * @param largeur - le largeur du vehicule
 * @param p - le joueur du véhicule
 * @param v - le pointeur du vehicule a creer
 */
void MakeVehicule(Point2D pos, float hauteur, float largeur, Player p, Vehicule* v);

/**
 * @brief Dessine le vehicule passe en param
 * @param v - le pointeur du vehicule a dessiner
 */
void DessinVehicule(Vehicule * v);

/**
 * @brief met a jour l'acceleration du vehicule
 * @param h - le vehicule a mettre à jour
 */
void UpdateAcceleration(Vehicule* h);

/**
 * @brief met a jour la vitesse du vehicule
 * @param h - le vehicule à mettre à jour
 */
void UpdateVitesse(Vehicule* h);

/**
 * @brief met a jour la position du vehicule
 * @param h - le vehicule à mettre à jour
 */
void UpdatePosition(Vehicule* h);

/**
 * @brief met a jour la rotation du vehicule
 * @param h - le vehicule à mettre à jour
 */
void UpdateRotation(Vehicule* h);

/**
 * @brief met a jour les valeurs du vehicule
 * @param h - le vehicule à mettre à jour
 */
void UpdateVehicule(Vehicule* h);

/**
 * @brief Libere les pointeurs du vehicule
 * @param checkpt - le pointeur du vehicule a  liberer
 */
void FreeVehicule(Vehicule *h);

/**
 * @brief met a jour les cercles du vehicule
 * @param v - le vehicule à mettre à jour
 */
void UpdateCercle(Vehicule *v);

/**
 * @brief Reinitialise le vehicule comme au debut
 * @param v - le pointeur sur le vehicule a reset
 */
void ResetVehicule(Vehicule* v);

/**
 * @brief freeze le vehicule pour la periode de bonus
 * @param v- le vehicule à freezer
 */
void FreezeVehicule(Vehicule* v);

/**
 * @brief Verifie si la durer du boost n'est pas dépassee,
 * si c'est le cas elle réinitialise les valeurs raltives au bonus
 * @param v- le vehicul a verifier
 */
void CheckBoost(Vehicule* v);

/**
 * @brief Verifie si la durer du freeze n'est pas dépassee,
 * si c'est le cas elle réinitialise les valeurs raltives au bonus
 * sinon elle freeze le vehicule
 * @param v - le vehicul a verifier
 */
void CheckFreeze(Vehicule* v);

/**
 * @brief Verifie si le vehicule est en periode de bonus ou non
 * @param v - le vehicule a tester
 * @return true si le vehicule est en periode de bonus, false sinon
 */
bool IsInBonus(Vehicule* v);

#endif
