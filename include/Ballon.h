#ifndef BALLON_H_
#define BALLON_H_ 

typedef struct {
	GLuint texture;
	float angle;
	Point2D* position;
	float vitesse;
}Ballon;

void MakeBallon(GLuint texture, Point2D* pos, Ballon* ballon);
void DeplacerBallon(flaot angle, flaot acceleration);

#endif