#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"
#include "Player.h"

typedef struct {
	Point2D top; 		//position superieur de la ligne d'en but
	Point2D bottom;		//position inferieur de la ligne d'en but
	Player player;
}But;

/**
 * @brief Cree un but avec le pointeur de but passé en paramètre
 * @param top - la position superieur de la ligne d'en but
 * @param bottom - la position inferieur de la ligne d'en but
 * @param b - le pointeur du but à créer
 * @param p - le player qui doit defendre le but
 */
void MakeBut(Point2D top, Point2D bottom, But* b, Player p);

/**
 * @brief Vérifie si le ballon est dans le but
 * @param but - le but a interroger
 * @param ball - la ballon concerné
 * @return true si le ballon est dans le but, false sinon
 */
bool BallIsInGoal(But* but, Ballon* ball);

//void DessinBut(But* b, int largeur);

#endif
