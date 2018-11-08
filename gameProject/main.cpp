#include<windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<stdbool.h>
#include <math.h>
#include <time.h>
bool head_right_done , head_left_done, rot_head_flag;

float angle = 45, fAspect, angx = 0, angy = 0, angz = 0,
     moveZ = -5.0, eyeZ = 0.0, eyeX = 0.0,
      eyeY = 0.0,  moveX = 0.0, tamTela = 400.0, eye_centerX = 0.0, eye_centerY = 0.0,
      eye_centerZ = 0.0;
float head_rotate = 0, head_rotval=-1.2 ;

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

    glEnable(GL_DEPTH_TEST);

}



void my_man() {

  //   glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
        glTranslatef(moveX, -1.0, moveZ);
        glRotatef(angx,1.0,0.0,0.0);
        glRotatef(angy,0.0,1.0,0.0);
        glRotatef(angz,0.0,0.0,1.0);
        glScalef(1.2, 0.7, 0.4);


        ///HEAD///

        glPushMatrix();  // head

        glRotatef(head_rotate, 0,1,0);
            glPushMatrix();///skull
                glRotatef(90, 1.0, 0.0, 0.0);
                 glColor3f(234/255.0  , 192/255.0, 134/255.0);
                glutSolidCube(0.3 );
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix(); /// nose
                glTranslatef(0.0, -0.05, -0.3);
                 glRotatef(50, 1.0, 0.0, 0.0);
                glRotatef(-10, 0.0, 1.0, 0.0);
                glScalef(0.1, 0.1, 0.1);
                glColor3f(1  , 15/255.0, 134/255.0);
                glutSolidTetrahedron();
                glColor3f(1,1,1);
            glPopMatrix();
            glPushMatrix();///right eye
                glColor3f(0,0,0);
                glTranslatef(0.1, 0.1, -0.3);
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
                glTranslatef(-0.1, 0.1, -0.3);
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
            glRotatef(0, 1.0, 0.0, 0.0);
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
                glRotatef(0, 1.0, 0.0, 0.0);
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
                glPopMatrix(); ///Fecha antebraco
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
                        glutSolidCube(0.05 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(0.2, -0.4, 0.0);
            glRotatef(0, 1.0, 0.0, 0.0);
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
                glRotatef(0, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glRotatef(-10, 0.0, 0.0, 1.0);
                glTranslatef(-0.39, 0.56, 0.0);
                    glPushMatrix(); ///right lower arm
                        glColor3f(17/255.0  , 53/255.0, 114/255.0);
                        glTranslatef(0.45, -0.65, 0.0);
                        glRotatef(45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(90, 1.0, 0.0, 0.0);
                        glutSolidCube(0.1 );
                        glColor3f(1,1,1);
                    glPopMatrix();
                    glPushMatrix(); ///right hand

                        glTranslatef(-0.52, -0.72, 0.0);
                        glRotatef(0, 1.0, 0.0, 0.0);
                        glRotatef(0, 0.0, 0.0, 1.0);
                        glTranslatef(0.52, 0.72, 0.0);
                        glPushMatrix(); ///hummer
                            glColor3f(0,0,0);
                            glTranslatef(0.55, -0.75, 0.0);
                            glRotatef(45, 0.0, 0.0, 1.0);
                            glScalef(0.5, 1.5, 0.8);
                            glRotatef(90, 1.0, 0.0, 0.0);
                            glutSolidCube(0.15 );
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
            glRotatef(0, 1.0, 0.0, 0.0);
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
                glRotatef(0, 1.0, 0.0, 0.0);
                glRotatef(0, 0.0, 0.0, 1.0);
                glTranslatef(0.03, 1.35, 0.0);
                glPushMatrix(); ///left lower leg
                    glColor3f(139/255.0, 69/255.0, 19.0/255);

                    glTranslatef(-0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
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
            glRotatef(0, 1.0, 0.0, 0.0);
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
                glRotatef(0, 1.0, 0.0, 0.0);
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
        head_rotate+= head_rotval;
        if(head_rotate <= -90)
            head_rotval *=-1 , head_left_done =1;
        if(head_rotate >= 90)
            head_rotval *=-1, head_right_done =1 ;
        if( abs(head_rotate - 0) <=1 && head_left_done && head_right_done)
        {
            head_left_done = head_right_done = 0;
            rot_head_flag = 0;

        }
        printf("hiii\n");
     }
}




void playGame(void)	{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glClearColor(141/255.0f, 131/255.0, 122/255.0, 1.0f);
    glPushMatrix();
     glTranslatef(0.0, 0.35, 0.0);

       my_man();
       head_rotate_();
    glPopMatrix();
    glutSwapBuffers();
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

    case 'h':
        rot_head_flag = 1;
        break;
    case 'z':
        head_rotate+=.8;
        head_rotate  = head_rotate > 90 ? 90 : head_rotate;
        break;
    case'x' :
        head_rotate -= .8;
        head_rotate = head_rotate< -90 ? -90 : head_rotate;
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
    glutReshapeFunc(ChangeSize);


	init();
	glutDisplayFunc(playGame);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0,Timer,10);
	glutMainLoop();

}
