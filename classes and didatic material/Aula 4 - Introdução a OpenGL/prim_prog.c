
void desenha (){

}


int main(int argc, char *argv[] ){
    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

// define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

//define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);

   glutInitWindowSize(400,300); //define largura e altura da janela

   glutCreateWindow("Primeiro programa usando OpenGL"); 

   glutDisplayFunc(desenha);//define funcao q/ desenhara o obj.

   glutMainLoop (); // Mostra tudo e espera

   return 0;  
 }