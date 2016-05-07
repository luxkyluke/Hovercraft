#ifndef CAMERA_H_
#define CAMERA_H_

#include "Point2D.h"
#include "Ballon.h"

typedef struct{
    float zoomLevel;
    Point2D direction;
    int start;
}Camera;

/**
 * @brief Cree une camera avec le pointeur de camera passé en paramètre
 * @param a - le pointeur de la camera à créer
 */
void MakeCamera(Camera* a);

/**
 *	@brief zoom sur un point passer en param a un certain niveau
 *	@param c - la camera permettant de zoomer
 *	@param direction - le point vers la camera doit zoomer
 *	@param zoomLevel - le niveau de zoom a ajouter a la camera
 */
void LookAt(Camera* c, Point2D direction, float zoomLevel);

/**
 * @brief Réinitialise la camera comme au début
 * @param c - le pointeur sur la camera a reset
 */
void ResetCamera(Camera* c);
#endif
