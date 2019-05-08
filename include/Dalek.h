#ifndef DALEK_H
#define DALEK_H
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#define MOVE_SPEED 0.1f
class Dalek
{
    public:

        Dalek();
        Draw();
        Update();
        Saut();
        Up();
        Down();
        // Textures
        void LoadTextures(void);
        void SetTexture(int nb, GLuint texture);
        GLuint ListeTextures[4];
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
    GLuint textures[4];

};

#endif // DALEK_H
