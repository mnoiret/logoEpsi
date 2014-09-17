//g++ main.cpp  -I/usr/local/Cellar/freeglut/2.8.1/include  -L/usr/local/Cellar/freeglut/2.8.1/lib -w -framework OpenGL -lGLUT

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Includes ** ** ** ** ** ** ** ** ** ** ** ** ** */

#include <stdio.h>
#include <GL/glut.h>     // The GL Utility Toolkit (GLUT) Header

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Constantes ** ** ** ** ** ** ** ** ** ** ** ** ** */

#define KEY_ESCAPE 27

typedef struct {
    int width;
  int height;
  char* title;

  float field_of_view_angle;
  float z_near;
  float z_far;
} glutWindow;

glutWindow win;

void display() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear Screen and Depth Buffer
  glLoadIdentity();
  glTranslatef(0.0f,0.0f,-2.0f);      

  /*
   * Triangle code starts here
   * 3 verteces, 3 colors.
   */

  // Triangle Rouge
  glBegin(GL_TRIANGLES);          
    glColor3f(0.87f,0.13f,0.22f);
    //Face avant      
    glVertex3f(-1.0f,1.0f, 0.0f);  
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(0.0f,1.0f, 0.0f);   
    //Face arrière      
    glVertex3f(-1.0f,1.0f, -0.2f);  
    glVertex3f(-1.0f,0.0f, -0.2f);  
    glVertex3f(0.0f,1.0f, -0.2f);   
    //Face droite      
    glVertex3f(-1.0f,1.0f, 0.0f);  
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(-1.0f,1.0f, -0.2f);  
    glVertex3f(-1.0f,0.0f, -0.2f);  
    //Face gauche      
    glVertex3f(-1.0f,1.0f, 0.0f);  
    glVertex3f(0.0f,1.0f, 0.0f);   
    glVertex3f(-1.0f,1.0f, -0.2f);  
    glVertex3f(0.0f,1.0f, -0.2f);   
    //Face hypothénuse      
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(0.0f,1.0f, 0.0f);   
    glVertex3f(-1.0f,0.0f, -0.2f);  
    glVertex3f(0.0f,1.0f, -0.2f);   
  glEnd();
  // Triangle Vert
  glBegin(GL_TRIANGLES);          
    glColor3f(0.0f,0.68f,0.30f);  
    //Face Avant 
    glVertex3f(0.0f,0.0f, 0.0f);     
    glVertex3f(1.0f,1.0f, 0.0f);  
    glVertex3f(1.0f,-1.0f, 0.0f);   
    //Face arrière 
    glVertex3f(0.0f,0.0f, -0.2f);     
    glVertex3f(1.0f,1.0f, -0.2f);  
    glVertex3f(1.0f,-1.0f, -0.2f);   
    //Face droite 
    glVertex3f(0.0f,0.0f, 0.0f);     
    glVertex3f(1.0f,1.0f, 0.0f);  
    glVertex3f(0.0f,0.0f, -0.2f);     
    glVertex3f(1.0f,1.0f, -0.2f);  
    //Face gauche 
    glVertex3f(0.0f,0.0f, 0.0f);    
    glVertex3f(1.0f,-1.0f, 0.0f); 
    glVertex3f(0.0f,0.0f, -0.2f);    
    glVertex3f(1.0f,-1.0f, -0.2f);  
    //Face hypothénuse 
    glVertex3f(1.0f,1.0f, 0.0f);    
    glVertex3f(1.0f,-1.0f, 0.0f); 
    glVertex3f(1.0f,1.0f, -0.2f);    
    glVertex3f(1.0f,-1.0f, -0.2f);   
  glEnd();
  // Triangle Bleu
  glBegin(GL_TRIANGLES);          
    glColor3f(0.0f,0.64f,0.80f);   
    //Face Avant
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(-1.0f,-1.0f, 0.0f);  
    glVertex3f(1.0f,-1.0f, 0.0f);   
    //Face arrière
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(-1.0f,-1.0f, -0.2f);  
    glVertex3f(1.0f,-1.0f, -0.2f);    
    //Face droite
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(-1.0f,-1.0f, 0.0f);  
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(-1.0f,-1.0f, -0.2f);  
    //Face gauche
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(1.0f,-1.0f, 0.0f);  
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(1.0f,-1.0f, -0.2f);  
    //Face hypothénuse
    glVertex3f(-1.0f,-1.0f, 0.0f);  
    glVertex3f(1.0f,-1.0f, 0.0f);  
    glVertex3f(-1.0f,-1.0f, -0.2f);  
    glVertex3f(1.0f,-1.0f, -0.2f);    
  glEnd();
  // Triangle Orange
  glBegin(GL_TRIANGLES);          
    glColor3f(0.93f,0.50f,0.19f); 
    //Face Avant  
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(0.5f,0.5f, 0.0f);  
    glVertex3f(-0.5f,0.5f, 0.0f); 
    //Face Arrière   
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(0.5f,0.5f, -0.2f);  
    glVertex3f(-0.5f,0.5f, -0.2f); 
    //Face droite  
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,0.5f, 0.0f); 
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(-0.5f,0.5f, -0.2f); 
    //Face gauche  
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(0.5f,0.5f, 0.0f);
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(0.5f,0.5f, -0.2f);   
    //Face hypothénuse  
    glVertex3f(0.5f,0.5f, 0.0f);  
    glVertex3f(-0.5f,0.5f, 0.0f);    
    glVertex3f(0.5f,0.5f, -0.2f);  
    glVertex3f(-0.5f,0.5f, -0.2f);    
  glEnd();
  // Forme Jaune
  glBegin(GL_POLYGON);          
    glColor3f(0.99f,0.89f,0.18f); 
    //Face Avant  
    glVertex3f(0.0f,1.0f, 0.0f); 
    glVertex3f(1.0f,1.0f, 0.0f); 
    glVertex3f(0.5f,0.5f, 0.0f); 
    glVertex3f(-0.5f,0.5f, 0.0f);    
    //Face Arrière  
    glVertex3f(0.0f,1.0f, -0.2f); 
    glVertex3f(1.0f,1.0f, -0.2f); 
    glVertex3f(0.5f,0.5f, -0.2f); 
    glVertex3f(-0.5f,0.5f, -0.2f);    
    //Face haute  
    glVertex3f(0.0f,1.0f, 0.0f); 
    glVertex3f(1.0f,1.0f, 0.0f); 
    glVertex3f(0.0f,1.0f, -0.2f); 
    glVertex3f(1.0f,1.0f, -0.2f);  
    //Face droite  
    glVertex3f(1.0f,1.0f, 0.0f); 
    glVertex3f(0.5f,0.5f, 0.0f);  
    glVertex3f(1.0f,1.0f, -0.2f); 
    glVertex3f(0.5f,0.5f, -0.2f);   
    //Face basse  
    glVertex3f(0.5f,0.5f, 0.0f); 
    glVertex3f(-0.5f,0.5f, 0.0f); 
    glVertex3f(0.5f,0.5f, -0.2f); 
    glVertex3f(-0.5f,0.5f, -0.2f);    
    //Face gauche  
    glVertex3f(0.0f,1.0f, 0.0f); 
    glVertex3f(-0.5f,0.5f, 0.0f); 
    glVertex3f(0.0f,1.0f, -0.2f); 
    glVertex3f(-0.5f,0.5f, -0.2f);    
  glEnd();
  // Forme Violette
  glBegin(GL_POLYGON);          
    glColor3f(0.62f, 0.2f, 0.54f); 
    //face Avant
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,-0.5f, 0.0f);  
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,0.5f, 0.0f);  
    //face Arrière
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(-0.5f,-0.5f, -0.2f);  
    glVertex3f(-1.0f,0.0f, -0.2f);  
    glVertex3f(-0.5f,0.5f, -0.2f);  
    //face haute droite
    glVertex3f(0.0f,0.0f, 0.0f);   
    glVertex3f(-0.5f,0.5f, 0.0f); 
    glVertex3f(0.0f,0.0f, -0.2f);   
    glVertex3f(-0.5f,0.5f, -0.2f);  
    //face basse droite
    glVertex3f(0.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,-0.5f, 0.0f);  
    glVertex3f(0.0f,0.0f, -0.2f);  
    glVertex3f(-0.5f,-0.5f, -0.2f);  
    //face basse gauche
    glVertex3f(-0.5f,-0.5f, 0.0f);  
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,-0.5f, -0.2f);  
    glVertex3f(-1.0f,0.0f, -0.2f);  
    //face haute gauche
    glVertex3f(-1.0f,0.0f, 0.0f);  
    glVertex3f(-0.5f,0.5f, 0.0f);     
    glVertex3f(-1.0f,0.0f, -0.2f);  
    glVertex3f(-0.5f,0.5f, -0.2f);     
  glEnd();
  // Triangle Violet
  glBegin(GL_TRIANGLES);          
    glColor3f(0.39f, 0.15f, 0.4f); 
    //Face Avant
    glVertex3f(-1.3f,0.0f, 0.0f); 
    glVertex3f(-0.8f,-0.5f, 0.0f); 
    glVertex3f(-1.3f,-1.0f, 0.0f);     
    //Face Arrière   
    glVertex3f(-1.3f,0.0f, -0.2f); 
    glVertex3f(-0.8f,-0.5f, -0.2f); 
    glVertex3f(-1.3f,-1.0f, -0.2f);
    //Face haute  
    //Face basse   
    //Face Hypothénuse  
  glEnd();

  glutSwapBuffers();
}

void initialize () 
{
    glMatrixMode(GL_PROJECTION);                        // select projection matrix
    glViewport(0, 0, win.width, win.height);                  // set the viewport
    glMatrixMode(GL_PROJECTION);                        // set matrix mode
    glLoadIdentity();                             // reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
  gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);   // set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);                         // specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );                           // specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );            // specify implementation-specific hints
  glClearColor(0.0, 0.0, 0.0, 1.0);                     // specify clear values for the color buffers               
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )   
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;      

    default:      
      break;
  }
}

int main(int argc, char **argv) 
{
  // set window values
  win.width = 600;
  win.height = 600;
  win.title = "TP1 - Logo EPSI ";
  win.field_of_view_angle = 90;
  win.z_near = 1.0f;
  win.z_far = 500.0f;

  // initialize and run program
  glutInit(&argc, argv);                                      // GLUT initialization
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
  glutInitWindowSize(win.width,win.height);         // set window size
  glutCreateWindow(win.title);                // create Window
  glutDisplayFunc(display);                 // register Display Function
  glutIdleFunc( display );                  // register Idle Function
    glutKeyboardFunc( keyboard );               // register Keyboard Handler
  initialize();
  glutMainLoop();                       // run GLUT mainloop
  return 0;
}