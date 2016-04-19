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

#include "../include/sdl_tools.h"
#include "../include/Geometry.h"
#include "../include/Vehicule.h"
#include "../include/Player.h"
#include "../include/Ballon.h"
#include "../include/Terrain.h"
#include "../include/Collision.h"
#include "../include/Camera.h"
#include "../include/Level.h"
#include "../include/Game.h"
#include "../include/Menu.h"
#include "../include/Bonus.h"

#define DEFAULT_MENU_TEXTURE_PATH "./images/menu.png"
#define DEFAULT_MENU_WIDTH 1300
#define DEFAULT_MENU_HEIGHT 650


int main(int argc, char** argv) {

  Menu* menu = (Menu *) malloc(sizeof(Menu));
  Game* game = (Game *) malloc(sizeof(Game));

  MakeGame(game, 300);
  //MakeLevel(level1, "fond", "./images/terrain1.jpg", "./images/vp1.png", "./images/vp2.png");

  MakeMenu(DEFAULT_MENU_TEXTURE_PATH, DEFAULT_MENU_WIDTH, DEFAULT_MENU_HEIGHT, menu, game);

  CallMenuDemarrage(menu);

  FreeGame(game);
  FreeMenu(menu);

  return EXIT_SUCCESS;
}
