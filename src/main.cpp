#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#include "Camera.h"
#include "Map.h"
#include "Dalek.h"

#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include <unistd.h>





float angle = 0.0;
float angle2 = -0.5;
float alpha=0.0;
float beta=0.0;
float x=0;
float y=0;
float z=5;
int d=10;
float phi=0;
float teta=0;

float longueur = 0.5;
float longueur2 = 1;

/* prototypes de fonctions */
void initRendering();
void display(void);
void reshape(int w,int h);
void update(int value);
void keyboard(unsigned char key, int x, int y);

/* Initialisation d'OpenGL pour le rendu de la scène */
void initRendering() {

    /* Active le z-buffer */
    glEnable(GL_DEPTH_TEST);

	/* Activation des couleurs */
	glEnable(GL_COLOR_MATERIAL);


	/* définit la couleur d'effacement et la couleur de fond */
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/* Activation des lumières */
	//glEnable(GL_LIGHTING);          // Activation du mode
	//glEnable(GL_LIGHT0);            // Activation lumière n°0
	//glEnable(GL_LIGHT1);            // Activation lumière n°1
	//glEnable(GL_LIGHT2);            // Activation lumière n°2

	/* Les normales (crées par glNormal(*)) sont automatiquement unitaires */
	glEnable(GL_NORMALIZE);


	/* Activation du mode ombrage (shading) et lissage (smooth) des couleur */
	glShadeModel(GL_SMOOTH);

	/*  définit la taille d'un pixel*/
	glPointSize(2.0);

}






/*  Mise en forme de la scène pour l'affichage */
void reshape(int w, int h){
	glViewport(0, 0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0,	200.0);



}

void navigation()
{


    x = d * cos(phi) * sin(teta);
    y = d * sin(phi);
    z = d * cos(phi) * cos(teta);
    printf("%lf",x);
}



// Objet Camera
Camera *cam = new Camera();
// Objet Scène
Map *m = new Map();
Dalek *dalek = new Dalek();


/** GESTION FENETRE **/
void reshapeWindow(int w, int h)
{
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 348.0f);
    glMatrixMode(GL_MODELVIEW);
}

/** FONCTIONS DE GESTION CLAVIER **/
void KeyboardDown(unsigned char key, int xx, int yy)
{
    switch(key)
    {
    case 'w': // Unlock Camera
        cam->locked = (cam->locked)?0:1;
        break;
    case 'z':
        cam->deltaForward = 1;
        break;
    case 's':
        cam->deltaForward = -1;
        break;
    case 'd':
        cam->deltaStrafe = -1;
        break;
    case 'q':
        cam->deltaStrafe = 1;
        break;
    case 'f':
        dalek->bras=2;
        break;
    case 'h':
        dalek->bras =1;
        break;
    case 't':
        dalek->extend +=0.2;
        dalek->exte +=0.2;

        if(dalek->extend>0.6||dalek->exte>0.6){
            dalek->extend -=0.2;
            dalek->exte -=0.2;
        }
        glutPostRedisplay();
        break;
    case 'g':
        dalek->extend -=0.2;
        dalek->exte -=0.2;
        if(dalek->extend<0||dalek->exte<0){
            dalek->extend +=0.2;
            dalek->exte +=0.2;
        }
        glutPostRedisplay();
        break;
    case ' ':
        dalek->Saut();
        break;

    }
}
void KeyboardUp(unsigned char key, int xx, int yy)
{
    switch(key)
    {
    case 'z':
    case 's':
        cam->deltaForward = 0;
        break;
    case 'q':
    case 'd':
        cam->deltaStrafe = 0;
        break;
    case 'r':
        dalek->angleval =0;
        break;
    case 'a':

    case 'e':
        dalek->longueurval =0;
        break;
    case 'f':
    case 'h':
        dalek->bras = 0;
        break;
     case ' ':
       dalek->Saut();
    break;

    }
}
void SpecialDown(int key, int xx, int yy)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        cam->deltaForward = 1;
        break;
    case GLUT_KEY_DOWN:
        cam->deltaForward = -1;
        break;
    case GLUT_KEY_RIGHT:
        cam->deltaStrafe = -1;
        break;
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 1;
        break;
    }
}
void SpecialUp(int key, int xx, int yy)
{
    switch(key)
    {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        cam->deltaForward = 0;
        break;
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        cam->deltaStrafe = 0;
        break;
    }
}

/** FONCTIONS DE GESTION SOURIS (ORIENTATION CAMERA) **/
void mouseMove(int x, int y)
{
    // Rentres uniquement lors du clic
    cam->orienterCam(x, y);
}
void mouseButton(int button, int state, int x, int y)
{
    // Gestion camera en fonction du clic souris
    if (button == GLUT_LEFT_BUTTON)
    {
        // Relacher la camera
        if (state == GLUT_UP)
        {
            cam->releaseCam();
        }
        // Mise à jour origine du clic
        else
        {
            cam->grabCam(x, y);
        }
    }
}

/** GESTION DEPLACEMENT CAMERA **/
void computePos(int inutile)
{
    dalek->Update();
    cam->updatePos();
    glutTimerFunc(10, computePos, 0);
}

/** AFFICHAGE **/
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Définition de la caméra
    gluLookAt(  cam->posx, cam->posy, cam->posz,
                cam->posx+cam->dirx, cam->posy+cam->diry,  cam->posz+cam->dirz,
                0.0f, 1.0f,  0.0f
                );

    m->DrawGround();
    dalek->Draw();
    m->DrawSkybox(cam);
    glutSwapBuffers();
}

void LoadTextures()
{
    m->LoadTextures();
}

int main(int argc, char **argv)
{
    /** CREATION FENETRE **/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Implémentation :: Textures");

    /* Initialisation d'OpenGL */
	initRendering();







    /** FONCTIONS GLUT **/
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshapeWindow);
    glutIdleFunc(renderScene);
    glutTimerFunc(10, computePos, 0);

    /** GESTION CLAVIER **/
    //glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(KeyboardDown);
    glutKeyboardUpFunc(KeyboardUp);
    glutSpecialFunc(SpecialDown);
    glutSpecialUpFunc(SpecialUp);

    /** GESTION SOURIS **/
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    /** INIT TEXTURES **/
    LoadTextures();

    /** INIT GL STATES **/
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glutMainLoop();




    return (1);
}


