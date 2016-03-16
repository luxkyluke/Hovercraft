#ifndef SDL_TOOLS_H_
#define SDL_TOOLS_H_

#include <SDL/SDL.h>
#include "geometry/Color3f.h"

void PutPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
Uint32 ColorToPixel(SDL_PixelFormat* format, Color3f color);

#endif
