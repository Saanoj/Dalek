#include "Dalek.h"
#include <stdio.h>
#include <stdlib.h>
#include "Block.h"
#include <time.h>
#include <math.h>

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void Dalek::LoadTextures()
{

    // Textures utilisables
    ListeTextures[0] = SOIL_load_OGL_texture("img/cliff.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[1] = SOIL_load_OGL_texture("img/dalek.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    ListeTextures[2] = SOIL_load_OGL_texture("img/darkgrass.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[3] = SOIL_load_OGL_texture("img/darkwoodplanks.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[4] = SOIL_load_OGL_texture("img/darkwoodtiles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[5] = SOIL_load_OGL_texture("img/deadgrass.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[6] = SOIL_load_OGL_texture("img/floorbrick.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[7] = SOIL_load_OGL_texture("img/graybrick.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[8] = SOIL_load_OGL_texture("img/graybricktiles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[9] = SOIL_load_OGL_texture("img/greybrick.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[10] = SOIL_load_OGL_texture("img/greybricktiles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[11] = SOIL_load_OGL_texture("img/Wasteland.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[12] = SOIL_load_OGL_texture("img/lightwoodplanks.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[13] = SOIL_load_OGL_texture("img/lightwoodtiles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[14] = SOIL_load_OGL_texture("img/mossbricktiles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[15] = SOIL_load_OGL_texture("img/pavement.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[16] = SOIL_load_OGL_texture("img/pebbles.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[17] = SOIL_load_OGL_texture("img/redbrick.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[18] = SOIL_load_OGL_texture("img/metalgate.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    //ListeTextures[19] = SOIL_load_OGL_texture("img/betonurban.bmp",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    ListeTextures[19] = SOIL_load_OGL_texture("img/terre.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
}

Dalek::Dalek()
{
    longueur = 1;
    longueur2 = 1;
    angle =90;
    angleval=0;
    longueurval= 0;
    brasangle = 0;
    bras = 0;
    extend = 0.2;
    exte = 0;
    jmp = 0;
    tirFlag=1;

    shoot = 0;
    shootx=1.0f;
    shooty=2.0f;
    shootz=2.0f;
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

    glEnable(GL_TEXTURE_2D);


    glPushMatrix();
    glTranslatef(moveForward,exte*10,moveSide);
        //glTranslatef(10,-0.5,0);
        glRotatef(angle,0,1,0);
        glPushMatrix();
            float j = 1;
            glRotatef(270,1,0,0);
            for(int i = 0; i<10;i++){




                glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
                glEnable(GL_TEXTURE_GEN_T);
                glBindTexture(GL_TEXTURE_2D, ListeTextures[1]);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_SPHERE_MAP | GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_SPHERE_MAP | GL_LINEAR);
                glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
                glTranslatef(0,0,extend);
                glutSolidTorus(j/2,j,10,10);
                glDisable(GL_TEXTURE_GEN_S); //disable texture coordinate generation
                glDisable(GL_TEXTURE_GEN_T);
                j=j-0.05;


            }

            glPushMatrix();
                glTranslatef(0,0,0.2);
                glScalef(0.7,0.7,0.7);
                GLUquadric* params = gluNewQuadric();
                gluQuadricTexture(params,GL_TRUE);
                gluSphere(params,1,10,10);
            glPopMatrix();
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
                brasG->DrawBras();
            glPopMatrix();
        glPopMatrix();

            /** TIR */

//          glPushMatrix();
//            glRotatef(brasangle,0,1,0);
//            glPushMatrix();
//                glTranslatef(-0.5,exte*10,0);
//                glTranslatef(tir,1.5,0.5);
//                glScalef(longueur,0.1,0.1);
//                glutSolidCube(2);
//                Block *tir = new Block(shootx,shooty,shootz);
//                tir->DrawBras();
//            glPopMatrix();
//            glPopMatrix();



        /**bras droit**/
        glPushMatrix();
            glTranslatef(-0.5,exte*10,0);
            glTranslatef(1,1.5,-0.5);
            glScalef(0.5,0.1,0.1);
            Block *brasD = new Block(1.0f, 2.0f, 2.0f);


            glPushMatrix();
            glTranslatef(tir,0,0);
            Block *tir = new Block(1.0f, 2.0f, 2.0f);
            tir->DrawBras();
            glPopMatrix();

            brasD->SetTexture(FRONT, ListeTextures[1]);
            brasD->SetTexture(BACK, ListeTextures[1]);
            brasD->SetTexture(TOP, ListeTextures[1]);
            brasD->SetTexture(BOT, ListeTextures[1]);
            brasD->SetTexture(RIGHT, ListeTextures[1]);
            brasD->SetTexture(LEFT, ListeTextures[1]);

            brasD->DrawBras();
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
        tirFlag++;
    }
     if (tirFlag >= 2 && tirFlag <5)
        {
            tir +=0.2f;

        }
        else
        {
            tir=0;
            tirFlag = 1;
        }

    if (angleval==1){
        angle = angle+1;
        dirx = sin(angleh + angle)*cos(0 + angle);
        dirz = -cos(angleh + angle)*cos(0 + angle);
    }
    if (moveDalek || moveDalekSide)
    {
/* ca fais crash le dalek reflechie jonas
        moveForward += moveDalek * (dirx/cos(angle)) * MOVE_SPEED;
        moveSide += moveDalek * (dirz/cos(angle)) * MOVE_SPEED;
        moveForward += moveDalekSide * (dirz/cos(angle)) * MOVE_SPEED;
        moveSide -= moveDalekSide * (dirx/cos(angle)) * MOVE_SPEED;

*/
        moveForward += moveDalek * dirx * MOVE_SPEED;
        moveSide += moveDalek * dirz * MOVE_SPEED;
      //  moveForward += moveDalekSide * dirz * MOVE_SPEED;
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
