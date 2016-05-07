#ifndef COLOR3F_H_
#define COLOR3F_H_

typedef struct {
    float r, g, b, alpha;
} Color4f;

Color4f ColorRGB(float r, float g, float b);
Color4f ColorGrey(float grey);
Color4f AddColors(Color4f lhs, Color4f rhs);
Color4f SubColors(Color4f lhs, Color4f rhs);
Color4f MultColors(Color4f lhs, Color4f rhs);
Color4f DivColors(Color4f lhs, Color4f rhs);
Color4f MultColor(Color4f c, float a);
Color4f DivColor(Color4f c, float a);

Color4f ColorRGBA(float r, float g, float b, float alpha);

extern Color4f BLACK, WHITE, RED, GREEN, BLUE;

#endif
