#ifndef DALEK_H
#define DALEK_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#define MOVE_SPEED 1f
class Dalek
{
    public:

        Dalek();
        Draw();
        Update();
        Saut();
        Up();
        Down();


        void LoadTextures(void);
        GLuint ListeTextures[20];




        float longueur;
        float longueur2;
        float angle;
        float angleval;
        float longueurval;
        float brasangle;
        float bras;
        float extend;
        float exte;
        // Deplacement du dalek
        float moveDalek;
        float moveDalekSide;
        float moveForward;
        float moveSide;
        int jmp;
        int shoot;

        float angleh;
        float dirx;
        float diry;
        float dirz;

        float deltaAnglex;
        float deltaAngley;
    protected:

    private:

};

#endif // DALEK_H
