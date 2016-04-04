#include "Collision.h"

bool CollisionCercleCercle(Cercle* c1, Cercle* c2) {
  float distanceCentreCarre = (c1->centre->x-c2->centre->x)*(c1->centre->x-c2->centre->x) + (c1->centre->y-c2->centre->y)*(c1->centre->y-c2->centre->y),
        distanceRadiusCarre = (c1->radiusCarre)+(c2->radiusCarre);
  if(IsZero(distanceCentreCarre - distanceRadiusCarre)) return true;
  return false;
}
