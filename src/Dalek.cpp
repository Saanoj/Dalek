#include "Dalek.h"
#include <stdio.h>
#include <stdlib.h>
#include "Block.h"
#include "Map.h"
#include <time.h>
#include <math.h>
void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void Dalek::LoadTextures()
{

    ListeTextures[0] = SOIL_load_OGL_texture("img/cliff.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/cliff.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[2] = SOIL_load_OGL_texture("img/darkgrass.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[3] = SOIL_load_OGL_texture("img/darkwoodplanks.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[4] = SOIL_load_OGL_texture("img/Wasteland.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);

}

void Dalek::SetTexture(int nb, GLuint texture)
{
    textures[nb] = texture;
}

Dalek::Dalek()
{
    longueur = 17;
    longueur2 = 1;
    angle =90;
    angleval=0;
    longueurval= 0;
    brasangle = 0;
    bras = 0;
    extend = 0.2;
    exte = 0;
    jmp = 0;

    shoot = 0;
    moveDalek=0;
    moveForward=0;
    moveSide=0;

    angleh = 0.0f;
    dirx = 0.0f;
    diry = 0.0f;
    dirz = -1.0f;

    deltaAnglex = 0.0f;
    deltaAngley = 0.0f;

}

Dalek::Draw()
{

// Couleurs sur le dalek sans les bras mais pas bon
//
//        glEnable(GL_TEXTURE_2D);
//        glColor3f(1.0f, 1.0f, 1.0f);
//        glBindTexture(GL_TEXTURE_2D, ListeTextures[1]);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

// Textures du bras



    glTranslatef(moveForward,exte*10,moveSide);
    glPushMatrix();
    //glTranslatef(moveForward,exte*10,moveSide);
        //glTranslatef(10,-0.5,0);
        glRotatef(angle,0,1,0);
        glPushMatrix();
            float j = 1;
            glRotatef(270,1,0,0);
            for(int i = 0; i<10;i++){

                glTranslatef(0,0,extend);
                glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glutSolidTorus(j/2,j,10,10);
                glDisable(GL_TEXTURE_GEN_S); //disable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
                //############"
     //           glTranslatef(0,0,extend);
       //         glutSolidTorus(j/2,j,10,10);
                j=j-0.05;
            }

               glPushMatrix();
                glBindTexture(GL_TEXTURE_2D,ListeTextures[4]);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

                GLUquadric* params = gluNewQuadric();
                gluQuadricTexture(params,GL_TRUE);
                glTranslatef(0,0,0.2);
                glScalef(0.7,0.7,0.7);
                gluSphere(params,1,100,100);
            glPopMatrix();

        /**bras gauche**/
        glPushMatrix();
            glRotatef(brasangle,0,1,0);
            glPushMatrix();
                glTranslatef(-0.5,exte*10,0);
                glTranslatef(longueur2,1.5,0.5);
                glScalef(longueur,0.1,0.1);
                //glutSolidCube(2);
                Block *brasG = new Block(1.0f, 2.0f, 2.0f);
                brasG->SetTexture(FRONT, ListeTextures[1]);
                brasG->SetTexture(BACK, ListeTextures[1]);
                brasG->SetTexture(TOP, ListeTextures[1]);
                brasG->SetTexture(BOT, ListeTextures[1]);
                brasG->SetTexture(RIGHT, ListeTextures[1]);
                brasG->SetTexture(LEFT, ListeTextures[1]);
                brasG->Draw();
            glPopMatrix();
        glPopMatrix();
        /**bras droit**/
        glPushMatrix();
            glTranslatef(-0.5,exte*10,0);
            glTranslatef(1,1.5,-0.5);
            glScalef(0.5,0.1,0.1);
            Block *brasD = new Block(1.0f, 2.0f, 2.0f);
            brasD->SetTexture(FRONT, ListeTextures[1]);
            brasD->SetTexture(BACK, ListeTextures[1]);
            brasD->SetTexture(TOP, ListeTextures[1]);
            brasD->SetTexture(BOT, ListeTextures[1]);
            brasD->SetTexture(RIGHT, ListeTextures[1]);
            brasD->SetTexture(LEFT, ListeTextures[1]);
            brasD->Draw();
        glPopMatrix();


        glPushMatrix();
            glTranslatef(0,exte*10,0);

            glScalef(0.25,0.1,0.1);
            glutSolidCube(2);
        glPopMatrix();

    glPopMatrix();



}

Dalek::Update(){

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
    if (jmp == 1){
        extend +=0.1;
        exte +=0.1;
        if (extend > 0.5 && exte >0.3){
            extend = 0.5;
            exte = 0.3;
        }
    }
    if (jmp == 0){
        extend -=0.1;
        exte -=0.1;
        if (extend < 0.2 && exte < 0){
            extend = 0.2;
            exte = 0;
        }
    }
    if(shoot == 1 ){

    }

    if (angleval==1){
        angle = angle+1;
        dirx = sin(angleh + angle)*cos(0 + angle);
        dirz = -cos(angleh + angle)*cos(0 + angle);
    }
    if (moveDalek || moveDalekSide)
    {
// ca fais crash le dalek reflechie jonas
/*
        moveForward += moveDalek * (dirx/cos(angle)) * MOVE_SPEED;
        moveSide += moveDalek * (dirz/cos(angle)) * MOVE_SPEED;
        moveForward += moveDalekSide * (dirz/cos(angle)) * MOVE_SPEED;
        moveSide -= moveDalekSide * (dirx/cos(angle)) * MOVE_SPEED;
*/
        moveForward += moveDalek * dirx * MOVE_SPEED;
        moveSide += moveDalek * dirz * MOVE_SPEED;
        moveForward -= moveDalekSide * dirz * MOVE_SPEED;
        moveSide -= moveDalekSide * dirx * MOVE_SPEED;



        glutPostRedisplay();
    }
}
/*
    if (moveDalek == 1
    {

        moveForward -=0.1;
        if (moveForward < -49)
        {
            moveForward += 0.1;
        }
    }

    if (moveDalek == -1)
    {
          moveForward +=0.1;
        if (moveForward < -49)
        {
            moveForward -= 0.1;
        }
    }

     if (moveDalekSide == 3)
    {
          moveSide -=0.1;
        if (moveSide < -49)
        {
            moveSide += 0.1;
        }
    }

     if (moveDalekSide == 4)
    {
          moveSide +=0.1;
        if (moveSide < -49)
        {
            moveSide -= 0.1;
        }
    }


}*/
