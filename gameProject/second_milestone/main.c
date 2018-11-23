#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<stdbool.h>
#include <math.h>
#include <time.h>
#define MAX_NO_TEXTURES 25 //Definindo o numero maximo de texturas

GLuint texture_id[MAX_NO_TEXTURES];

bool head_right_done , head_left_done, rot_head_flag;
float rot_speed= 2;
float head_ang = 0, head_rotval ;

bool   rightHand_up_done = 0 ,  rightHand_flag = 0,
       rightElbow_up_done=0 , rightElbow_flag=0,
       leftHand_up_done=0, leftHand_flag=0,
       leftElbow_up_done=0, leftElbow_flag=0,
       rightLeg_up_done =0, rightLeg_flag=0,
       rightKnee_up_done=0, rightKnee_flag=0,
       leftLeg_up_done =0, leftLeg_flag=0,
       leftKnee_up_done=0, leftKnee_flag =0;

float leftHand_ang , leftElbow_ang , rightHand_ang , rightElbow_ang, rightLeg_ang,
      rightKnee_ang , leftLeg_ang  ,  leftKnee_ang ;

float leftHand_rotVal= 1.2, leftElbow_rotVal= 1.2, rightHand_rotVal= 1.2, rightElbow_rotVal=1.2, rightLeg_rotVal=1.2,
      rightKnee_rotVal= 1.2, leftLeg_rotVal = 1.2,  leftKnee_rotVal =1.2;

float angle = 45, fAspect, angx = 0, angy = 0, angz = 0,
     moveZ = -5.0, eyeZ = 0.0, eyeX = 0.0,
      eyeY = 0.0,  moveX = 0.0, tamTela = 400.0, eye_centerX = 0.0, eye_centerY = 0.0,
      eye_centerZ = 0.0;



GLfloat ambient_light2[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat ambient_light[4] = {0.0, 0.0, 0.0, 1.0};

GLfloat difuse_light[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat dspec_light[4] = {0.3, 0.3, 0.3, 1.0};

GLfloat light_pos0[4] = {2.0, 4.0, -5.0, 1.0};
GLfloat light_dir0[4] = {-2.0, -4.0, -5.0, 1.0};

GLfloat light_pos1[4] = {-2.0, 4.0, -3.0, 1.0};
GLfloat light_dir1[4] = {3.0, -5.0, -3.0, 1.0};

GLfloat light_pos2[4] = {-2.0, 4.0, -12.0, 1.0};
GLfloat light_dir2[4] = {3.0, -5.0, -12.0, 1.0};

GLfloat light_pos3[4] = {2.0, 4.0, -18.0, 1.0};
GLfloat light_dir3[4] = {-2.0, -4.0, -18.0, 1.0};

GLfloat light_pos4[4] = {0.0, 1.0, -5.0, 1.0};

GLfloat obj_Amb[4] = {0.3, 0.2, 0.1, 1.0};
GLfloat obj_Dif[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat obj_Esp[4] = {0.1, 0.1, 0.1, 1.0};


/// texture struct
typedef struct IMGdata_ {
    int   width;
    int   height;
    char *data;
}IMGdata;

void getIMGdata( char *pFileName, IMGdata *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    ( (pFile = fopen(pFileName, "rb") ) == NULL );

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    ( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 );

     ( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 );

     ( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 );

     ( nNumPlanes != 1 );

     ( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 );

     ( nNumBPP != 24 );

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

     ( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 );

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}

void loadTexture(char* Filename, int id)
{

    IMGdata textura;

    getIMGdata( Filename, &textura);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture_id[id]);

    glBindTexture(GL_TEXTURE_2D, texture_id[id]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width, textura.height, 0,
                                    GL_RGB, GL_UNSIGNED_BYTE, textura.data);
    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenf(GL_T,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

}


void Viewing()	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle,fAspect,0.1,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


    gluLookAt( eyeX,eyeY,eyeZ -10,
               eye_centerX,eye_centerY,eye_centerZ,
               0,1,0);

}

void ChangeSize(GLsizei w, GLsizei h)	{

	if ( h == 0 )
		h = 1;
        glViewport(0, 0, w, w);

	fAspect = (GLfloat)w/(GLfloat)h;
	Viewing();
	tamTela = w/2.0;
}



void init(void) {
glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);

    leftHand_rotVal= rot_speed, leftElbow_rotVal= rot_speed, rightHand_rotVal= rot_speed, rightElbow_rotVal=rot_speed, rightLeg_rotVal=rot_speed,
    rightKnee_rotVal= - rot_speed, leftLeg_rotVal = rot_speed,  leftKnee_rotVal = -rot_speed , head_rotval = rot_speed;

    glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difuse_light );
    glLightfv(GL_LIGHT0, GL_SPECULAR, dspec_light );
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos0 );
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, difuse_light );
    glLightfv(GL_LIGHT1, GL_SPECULAR, dspec_light );
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1 );
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);

    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, difuse_light );
    glLightfv(GL_LIGHT2, GL_SPECULAR, dspec_light );
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, difuse_light );
    glLightfv(GL_LIGHT3, GL_SPECULAR, dspec_light );
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos3);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_dir3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient_light2);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, difuse_light);
    glLightfv(GL_LIGHT4, GL_SPECULAR, dspec_light);
    glLightfv(GL_LIGHT4, GL_POSITION, light_pos4);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obj_Amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obj_Dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obj_Esp);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 2);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT4);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_DEPTH_TEST);

}




void bigWall() {

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);

        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
    ///--------------------------------///
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);

        glTranslatef(-3.0, 1.0, -50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
///-----------------------///
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glRotatef(90, 0,1,0);
        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
///----------------------///
 glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[0]);
        glRotatef(-90, 0,1,0);
        glTranslatef(-3.0, 1.0, 50);
        glScalef(500.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(50.0, 0.1, 100.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}

void my_man() {

  //   glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
        glTranslatef(moveX, -0.55, moveZ);
        glRotatef(angx,1.0,0.0,0.0);
        glRotatef(angy,0.0,1.0,0.0);
        glRotatef(angz,0.0,0.0,1.0);
        glScalef(1.2, 0.7, 0.4);


        ///HEAD///

        glPushMatrix();  // head

        glRotatef(head_ang, 0,1,0);
            glPushMatrix();///skull
                glRotatef(90, 1.0, 0.0, 0.0);
                 glColor3f(234/255.0  , 192/255.0, 134/255.0);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix(); /// nose
                glTranslatef(0.0, -0.05, -0.2);
                 glRotatef(50, 1.0, 0.0, 0.0);
                glRotatef(-10, 0.0, 1.0, 0.0);
                glScalef(0.1, 0.1, 0.1);
                glColor3f(1  , 15/255.0, 134/255.0);
                glutSolidSphere(.3, 10,10);
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();///right eye
                glColor3f(0,0,0);
                glTranslatef(0.1, 0.1, -0.2);
                glScalef(0.2, 0.2, 0.2);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
                glScalef(0.5,.5,.8);
                glTranslatef(0,0,-.15);
                glutSolidCube(0.3 );
                glTranslatef(0,0,-.15);
                glColor3f(.1,0.1,0.1);
                glutSolidSphere(.1, 20, 20);
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();/// left eye
                glColor3f(0,0,0);
                glTranslatef(-0.1, 0.1, -0.2);
                glScalef(0.2, 0.2, 0.2);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
                glScalef(0.5,.5,.8);
                glTranslatef(0,0,-.15);
                glutSolidCube(0.3 );
                glTranslatef(0,0,-.15);
                glColor3f(.1,0.1,0.1);
                glutSolidSphere(.1, 20, 20);
                glColor3f(1,1,1);
            glPopMatrix();


        glPopMatrix(); ///head done
        ///mouth///
        glPushMatrix(); ///mouth
            glColor3f(.7,0,0);
            glTranslatef(0.0, -0.25, 0.0);
            glScalef(0.3, 0.2, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
            glColor3f(1,1,1);
        glPopMatrix();
        ///body///
        glPushMatrix();
            glColor3f(17/255.0  , 53/255.0, 114/255.0);
            glTranslatef(0.0, -0.75, 0.0);
            glScalef(0.7, 1.2, 1.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCube(0.4 );
            glColor3f(1,1,1);
        glPopMatrix();
        ///left arm///
        glPushMatrix();
            glTranslatef(0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(-0.2, -0.4, 0.0);
            glRotatef(leftHand_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glTranslatef(0.2, 0.4, 0.0);

            glPushMatrix();

                glColor3f(17/255.0  , 53/255.0, 114/255.0);
                glTranslatef(-0.3, -0.5, 0.0);
                glRotatef(-45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.39, -0.56, 0.0);
                glRotatef(leftElbow_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glRotatef(10, 0.0, 0.0, 1.0);
                glTranslatef(0.39, 0.56, 0.0);
                glPushMatrix(); ///left upper arm
                    glColor3f(17/255.0  , 53/255.0, 114/255.0);
                    glTranslatef(-0.45, -0.65, 0.0);
                    glRotatef(-45, 0.0, 0.0, 1.0);
                    glScalef(0.5, 1.3, 0.8);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                    glColor3f(1,1,1);
                glPopMatrix();
                glPushMatrix(); ///left lower arm
                    glTranslatef(-0.52, -0.72, 0.0);
                    glRotatef(0, 1.0, 0.0, 0.0);
                    glRotatef(0, 0.0, 0.0, 1.0);
                    glTranslatef(0.52, 0.72, 0.0);
                    glPushMatrix(); ///left hand
                        glColor3f(234/255.0  , 192/255.0, 134/255.0);
                        glTranslatef(-0.55, -0.75, 0.0);
                        glRotatef(-45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(90, 1.0, 0.0, 0.0);
                        glutSolidSphere(0.05, 20,20 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix(); /// right arm
            glTranslatef(-0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(0.2, -0.4, 0.0);
            glRotatef(rightHand_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glTranslatef(-0.2, 0.4, 0.0);
            glPushMatrix(); ///right upper arm
                glColor3f(17/255.0  , 53/255.0, 114/255.0);
                glTranslatef(0.3, -0.5, 0.0);
                glRotatef(45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.39, -0.56, 0.0);
                glRotatef(rightElbow_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glRotatef(-10, 0.0, 0.0, 1.0);
                glTranslatef(-0.39, 0.56, 0.0);
                    glPushMatrix(); ///right lower arm
                        glColor3f(17/255.0  , 53/255.0, 114/255.0);
                        glTranslatef(0.45, -0.65, 0.0);
                        glRotatef(45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(  90, 1.0, 0.0, 0.0);
                        glutSolidCube(0.1 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                    glPushMatrix(); ///right hand

                        glTranslatef(-0.52, -0.72, 0.0);
                        glRotatef(0, 1.0, 0.0, 0.0);
                        glRotatef(0, 0.0, 0.0, 1.0);
                        glTranslatef(0.52, 0.72, 0.0);
                        glPushMatrix(); ///right hand
                            glColor3f(234/255.0  , 192/255.0, 134/255.0);
                            glTranslatef(0.55, -0.75, 0.0);
                            glRotatef(45, 0.0, 0.0, 1.0);
                            glScalef(0.5, 1.5, 0.8);
                            glRotatef(90, 1.0, 0.0, 0.0);
                            glutSolidSphere(0.05, 20,20 );
                            glColor3f(1,1,1);
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();
        ///Left leg//
        glPushMatrix(); ///open leg
            glTranslatef(0.05, 0.7, 0);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(-0.03, -1.2, 0.0);
            glRotatef(leftLeg_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glTranslatef(0.03, 1.2, 0.0);
            glPushMatrix(); ///left thigh
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glTranslatef(-0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.03, -1.35, 0.0);
                glRotatef(leftKnee_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glTranslatef(0.03, 1.35, 0.0);
                glPushMatrix(); ///left lower leg
                    glColor3f(139/255.0, 69/255.0, 19.0/255);

                    glTranslatef(-0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(  90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                    glColor3f(1,1,1);
                glPopMatrix();
                glPushMatrix(); ///left foot
                    glColor3f(0.11,.01,0.01);
                    glTranslatef(-0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.19 );
                    glColor3f(1,1,1);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        ///right leg//
        glPushMatrix();
            glTranslatef(-0.05, 0.7, 0);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(0.03, -1.2, 0.0);
            glRotatef(rightLeg_ang, 1.0, 0.0, 0.0);
            glRotatef(0, 0.0, 0.0, 1.0);
            glTranslatef(-0.03, 1.2, 0.0);
            glPushMatrix(); ///right upper leg
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glTranslatef(0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidCube(0.1 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix(); ///right lower leg
                glTranslatef(0.03, -1.35, 0.0);
                glColor3f(139/255.0, 69/255.0, 19.0/255);
                glRotatef(rightKnee_ang, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glTranslatef(-0.03, 1.35, 0.0);
                glPushMatrix();
                    glTranslatef(0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.1 );
                glPopMatrix();
                glPushMatrix();
                    glColor3f(0,0,0);
                    glTranslatef(0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidCube(0.19 );
                glPopMatrix();
            glColor3f(1,1,1);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();

}

void head_rotate_()
{

    if(rot_head_flag){
        head_ang+= head_rotval;
        if(head_ang <= -90)
            head_rotval *=-1 , head_left_done =1;
        if(head_ang >= 90)
            head_rotval *=-1, head_right_done =1 ;
        if( abs(head_ang - 0) <=1 && head_left_done && head_right_done)
        {
            head_left_done = head_right_done = 0;
            rot_head_flag = 0;

        }
    }
}

void  rightHand_moving()
{
    if(rightHand_flag)
    {
        rightHand_ang+= rightHand_rotVal;
        if(rightHand_ang >= 60 || rightHand_ang <= -60)
            rightHand_rotVal*=-1 , rightHand_up_done = 1;
        if(abs(rightHand_ang - 0)<=1 && rightHand_up_done)
            rightHand_up_done = 0, rightHand_ang = 0 ,rightHand_flag =0 , rightHand_rotVal *=-1;
    }
}

void  rightElbow_moving()
{
    if(rightElbow_flag)
    {
        rightElbow_ang+= rightElbow_rotVal;
        if(rightElbow_ang >= 80 || rightElbow_ang <= -80)
            rightElbow_rotVal*=-1 , rightElbow_up_done = 1;
        if(abs(rightElbow_ang - 0)<=1 && rightElbow_up_done)
            rightElbow_up_done = 0, rightElbow_ang = 0 ,rightElbow_flag =0 , rightElbow_rotVal *=-1;
    }
}


void  leftHand_moving()
{
    if(leftHand_flag)
    {
        leftHand_ang+= leftHand_rotVal;
        if(leftHand_ang >= 60 || leftHand_ang <= -60)
            leftHand_rotVal*=-1 , leftHand_up_done = 1;
        if(abs(leftHand_ang - 0)<=1 && leftHand_up_done)
            leftHand_up_done = 0, leftHand_ang = 0 ,leftHand_flag =0 , leftHand_rotVal *=-1;
    }
}

void  leftElbow_moving()
{
    if(leftElbow_flag)
    {
        leftElbow_ang+= leftElbow_rotVal;
        if(leftElbow_ang >= 80 || leftElbow_ang <= -80)
            leftElbow_rotVal*=-1 , leftElbow_up_done = 1;
        if(abs(leftElbow_ang - 0)<=1 && leftElbow_up_done)
            leftElbow_up_done = 0, leftElbow_ang = 0 ,leftElbow_flag =0 , leftElbow_rotVal *=-1;
    }
}

void  leftLeg_moving()
{
    if(leftLeg_flag)
    {
        leftLeg_ang+= leftLeg_rotVal;
        if(leftLeg_ang >= 80 || leftLeg_ang <= -80)
            leftLeg_rotVal*=-1 , leftLeg_up_done = 1;
        if(abs(leftLeg_ang - 0)<=1 && leftLeg_up_done)
            leftLeg_up_done = 0, leftLeg_ang = 0 ,leftLeg_flag =0 , leftLeg_rotVal *=-1;
    }
}

void  leftKnee_moving()
{
    if(leftKnee_flag)
    {
        leftKnee_ang+= leftKnee_rotVal;
        if(leftKnee_ang >= 80 || leftKnee_ang <= -80)
            leftKnee_rotVal*=-1 , leftKnee_up_done = 1;
        if(abs(leftKnee_ang - 0)<=1 && leftKnee_up_done)
            leftKnee_up_done = 0, leftKnee_ang = 0 ,leftKnee_flag =0 , leftKnee_rotVal *=-1;
    }
}

void  rightLeg_moving()
{
    if(rightLeg_flag)
    {
        rightLeg_ang+= rightLeg_rotVal;
        if(rightLeg_ang >= 80 || rightLeg_ang <= -80)
            rightLeg_rotVal*=-1 , rightLeg_up_done = 1;
        if(abs(rightLeg_ang - 0)<=1 && rightLeg_up_done)
            rightLeg_up_done = 0, rightLeg_ang = 0 ,rightLeg_flag =0 , rightLeg_rotVal *=-1;
    }
}

void  rightKnee_moving()
{
    if(rightKnee_flag)
    {
        rightKnee_ang+= rightKnee_rotVal;
        if(rightKnee_ang >= 80 || rightKnee_ang <= -80)
            rightKnee_rotVal*=-1 , rightKnee_up_done = 1;
        if(abs(rightKnee_ang - 0)<=1 && rightKnee_up_done)
            rightKnee_up_done = 0, rightKnee_ang = 0 ,rightKnee_flag =0 , rightKnee_rotVal *=-1;
    }
}

void body_moving()
{
       head_rotate_();
       rightHand_moving();
       rightElbow_moving();
       leftElbow_moving();
       leftHand_moving();
       leftLeg_moving();
       leftKnee_moving();
       rightLeg_moving();
       rightKnee_moving();
}
void playGame(void)	{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //	glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);
    glPushMatrix();
     glTranslatef(0.0, 0.35, 0.0);
        bigWall();
       my_man();
       body_moving();
    glPopMatrix();
    glutSwapBuffers();
}


void menuFunc(GLint test)
{
    switch(test){
        case 1:
            exit(0);
        break ;
        case 2:
            rightHand_flag = 1;
        break;
        case 3:
            leftHand_flag=1;
            break;
        case 4 :
            leftElbow_flag=1;
            break;
        case 5 :
            rightElbow_flag = 1;
            break;
        case 6:
            leftLeg_flag = 1;
            break;
        case 7:
            rightLeg_flag = 1;
            break;
        case 8:
            leftKnee_flag = 1;
            break;
        case 9:
            rightKnee_flag =1;
            break;
        case 10:
            rot_head_flag = 1;
            break;
    }

}

void keyboard (unsigned char key, int x, int y){
  switch (key) {
  case '8':
      moveZ  += .42;
    break;
    case '2':
      moveZ-= .42;
    break;
    case '4':
      moveX+= .42;
    break;
    case '6':
      moveX-= .42;
    break;
   case 'd':
        eye_centerZ -= .1;
        break;
   case 'e':
        eye_centerZ += .1;
        break;
    case 's':
        eye_centerX -= .1;
        break;
    case 'w':
        eye_centerX += .1;
        break;
    case 'q':
        eye_centerY += .1;
        break;
    case 'a':
        eye_centerY -= .1;
        break;

    case 'u':
        eyeX += 0.1;
        break;
    case 'j':
        eyeX -= 0.1;
        break;
    case 'o':
        eyeZ += 0.1;
        break;
    case 'l':
        eyeZ -= 0.1;
        break;

    case 'i':
        eyeY += 0.1;
        break;
    case 'k':
        eyeY -= 0.1;
        break;

}


Viewing();
glutPostRedisplay();
}



void Timer(int extra) {
     glutPostRedisplay();
     glutTimerFunc(20,Timer,10);
}



int  main ( int argc, char** argv ){
    glutInit  (&argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_RGBA);
	glutInitWindowSize(600,600);
	glutCreateWindow("Douglas");

    loadTexture("D:\\ACM\\new_glut\\sky.bmp", 0);
	loadTexture("D:\\ACM\\new_glut\\grama.bmp", 21);

    glutReshapeFunc(ChangeSize);


	init();
	glutDisplayFunc(playGame);
    glutKeyboardFunc(keyboard);
    glutCreateMenu(menuFunc);
        glutAddMenuEntry("Exit", 1);
        glutAddMenuEntry("Rotate Right Arm", 2);
        glutAddMenuEntry("Rotate left Arm", 3) ;
        glutAddMenuEntry("Rotate Left Elbow", 4);
        glutAddMenuEntry("Rotating Right Elbow", 5);
        glutAddMenuEntry("Rotate Left Leg", 6);
        glutAddMenuEntry("Rotate right Leg", 7);
        glutAddMenuEntry("Rotate Left Knee", 8);
        glutAddMenuEntry("Rotate right Knee", 9);
        glutAddMenuEntry("Rotate head", 10);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutTimerFunc(0,Timer,10);
	glutMainLoop();

}
