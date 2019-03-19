#ifndef DALEK_H
#define DALEK_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"

class Dalek
{
    public:

        Dalek();
        Draw();
        Update();
        Saut();
        Up();
        Down();
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
        float moveForward;
        float moveSide;
        int jmp;
    protected:

    private:
};

#endif // DALEK_H
