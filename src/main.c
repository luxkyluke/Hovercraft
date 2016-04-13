/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "../include/Geometry.h"
#include "../include/Vehicule.h"
#include "../include/Player.h"
#include "../include/Ballon.h"
#include "../include/Terrain.h"
#include "../include/Collision.h"
#include "../include/Level.h"
#include "../include/Game.h"




int main(int argc, char** argv) {


  Game* game = (Game *) malloc(sizeof(Game));
  
  MakeGame(game, 300);
  //MakeLevel(level1, "fond", "./images/terrain1.jpg", "./images/vp1.png", "./images/vp2.png");
  AddLevel(game, "fond", "./images/terrain1.jpg", "./images/vp1.png", "./images/vp2.png");
 
  PlayGame(game);

  FreeGame(game);

  return EXIT_SUCCESS;
}
