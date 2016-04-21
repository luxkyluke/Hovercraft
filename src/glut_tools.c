#include "glut_tools.h"






void initGlut(int argc, char** argv) {
	glutInit(&argc, argv);
}

void vBitmapOutput(int x, int y, char *string, void *font) {
	int len, i; // len donne la longueur de la chaîne de caractères

	glRasterPos2f(x, y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]); // Affiche chaque caractère de la chaîne
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font) {
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisées pour sauvegarder
	// et restaurer les systèmes de coordonnées non translatés
	glTranslatef(x, y, 0); // Positionne le premier caractère de la chaîne
	for (p = string; *p; p++)
		glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	glPopMatrix();
}
