#include "Dalek.h"
#include <stdio.h>
#include <stdlib.h>
Dalek::Dalek()
{
    longueur = 1;
    longueur2 = 1;
    angle =180;
    angleval=0;
    longueurval= 0;
    brasangle = 0;
    bras = 0;
    extend = 0.2;
    exte = 0;
}

Dalek::Draw()
{

    glPushMatrix();
    glTranslatef(0,exte*10,0);
        //glTranslatef(10,-0.5,0);
        glRotatef(angle,0,1,0);
        glPushMatrix();
            float j = 1;
            glRotatef(270,1,0,0);
            for(int i = 0; i<10;i++){
                glTranslatef(0,0,extend);
                glutSolidTorus(j/2,j,10,10);
                j=j-0.05;
            }
            glPushMatrix();
                glTranslatef(0,0,0.2);
                glScalef(0.7,0.7,0.7);
                glutSolidSphere(1,10,10);
            glPopMatrix();
        glPopMatrix();

        /**bras gauche**/
        glPushMatrix();
            glRotatef(brasangle,0,1,0);
            glPushMatrix();
                glTranslatef(0,exte*10,0);
                glTranslatef(longueur2,1.5,0.5);
                glScalef(longueur,0.1,0.1);
                glutSolidCube(2);
            glPopMatrix();
        glPopMatrix();
    /**bras droit**/
        glPushMatrix();
            glTranslatef(0,exte*10,0);
            glTranslatef(1,1.5,-0.5);
            glScalef(0.5,0.1,0.1);
            glutSolidCube(2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,exte*10,0);
            glTranslatef(0.5,2.5,0.25);
            glScalef(0.25,0.1,0.1);
            glutSolidCube(2);
        glPopMatrix();

    glPopMatrix();


}

Dalek::Update(){
    if (angleval==1){
        angle = angle+1;
    }
    if (longueurval==1){
        longueur +=0.1;
        longueur2 +=0.1;
        if(longueur2>1.5||longueur>1.5){
            longueur2 = 1.5;
            longueur = 1.5;
        }
    }
    if (longueurval==2){
        longueur -=0.1;
        longueur2 -=0.1;
        if(longueur2<0.5||longueur<1){
            longueur2 = 0.5;
            longueur = 1;
        }
    }
    if (bras==1){
        brasangle +=1;
        if (brasangle > 30){
            brasangle=30;
        }
    }
    if (bras==2){
        brasangle -=1;
        if (brasangle < -30){
            brasangle=-30;
        }
    }
    glutPostRedisplay();
}
Dalek::Saut(){
    int i;
    for(i = 0;i<3;i++){
        extend +=0.2;
        exte +=0.2;
        glutPostRedisplay();
        Sleep(1);

    }
    for(i = 0;i<3;i++){
        extend -=0.2;
        exte -=0.2;
        glutPostRedisplay();
        Sleep(1);
    }
}
