#include "glut_tools.h"

void initGlut(int windowW, int windowH) {
//	int argc = 0;
//	char** argv = (char**) malloc(sizeof(char*));
//	argv[0] = (char*) calloc(20, sizeof(char));
//	sprintf(argv[0], "imagimp");
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
//	float width = glutGet(GLUT_SCREEN_WIDTH);
//	float height = glutGet(GLUT_SCREEN_HEIGHT);
//	glutInitWindowPosition(width / 2 - screen.width / 2,
//			height / 2 - screen.height / 2);
//	glutInitWindowSize(screen.width, screen.height);
//
//	if (glutCreateWindow("IMAGIMP") == GL_FALSE) {
//		printf("Impossible de cr�er la fenetre GL\n");
//		exit(1);
//	}
//	initDisplay();
//
//	/* association de la fonction de dimensionnement */
//	glutReshapeFunc(reshapeFunc);
//
//	/* association de la fonction d'affichage */
//	glutDisplayFunc(drawScene_GLIMAGIMP);
//
//	/* association de la fonction d'�v�nement souris */
//	glutMouseFunc(clickMouse_GLIMAGIMP);
//
//	/* association de la fonction de DRAG */
//	glutPassiveMotionFunc(motionMouse_GLIMAGIMP);
//	glutMotionFunc(motionMouse_GLIMAGIMP);
//
//	/* association de la fonction d'�v�nement du clavier */
//	glutKeyboardFunc(kbdFunc_GLIMAGIMP);
//
//	/* association de la fonction de traitement des touches*/
//	/* sp�ciales du clavier                                */
//	glutSpecialFunc(kbdSpFunc_GLIMAGIMP);
//
//	/* fonction d'attente */
//	glutIdleFunc(idleFunc);
//
//	if (fullscreen) {
//		glutFullScreen();
//	}
}

void vBitmapOutput(int x, int y, char *string, void *font) {
	int len, i; // len donne la longueur de la cha�ne de caract�res

	glRasterPos2f(x, y); // Positionne le premier caract�re de la cha�ne
	len = (int) strlen(string); // Calcule la longueur de la cha�ne
	for (i = 0; i < len; i++)
		glutBitmapCharacter(font, string[i]); // Affiche chaque caract�re de la cha�ne
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font) {
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilis�es pour sauvegarder
	// et restaurer les syst�mes de coordonn�es non translat�s
	glTranslatef(x, y, 0); // Positionne le premier caract�re de la cha�ne
	for (p = string; *p; p++)
		glutStrokeCharacter(font, *p); // Affiche chaque caract�re de la cha�ne
	glPopMatrix();
}
