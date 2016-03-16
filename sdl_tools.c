#include "sdl_tools.h"
#include "geometry/geometry.h"

void PutPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    
    Uint8* p = (Uint8*) surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}


Uint32 ColorToPixel(SDL_PixelFormat* format, Color3f color) {
	Uint32 r = 255 * color.r;
	Uint32 g = 255 * color.g;
	Uint32 b = 255 * color.b;
	return SDL_MapRGB(format, CLAMP(r, 0, 255), CLAMP(g, 0, 255), CLAMP(b, 0, 255));
}

