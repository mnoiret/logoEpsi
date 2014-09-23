//g++ main.cpp  -I/usr/local/Cellar/freeglut/2.8.1/include  -L/usr/local/Cellar/freeglut/2.8.1/lib -w -framework OpenGL -lGLUT

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Includes ** ** ** ** ** ** ** ** ** ** ** ** ** */

#include <iostream>
#include <GL/glut.h>     // The GL Utility Toolkit (GLUT) Header
#include <vector>
#include <math.h>

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Constantes ** ** ** ** ** ** ** ** ** ** ** ** ** */

#define KEY_ESCAPE 27

double rotate_y=0;
double rotate_x=0;

typedef struct {
  int width;
  int height;
  char* title;

  float field_of_view_angle;
  float z_near;
  float z_far;
} glutWindow;

glutWindow win;

struct Position{
    float x;
    float y;
    Position(){};
    Position(float x, float y): x(x),y(y){};
};

struct Couleur{
    float r;
    float g;
    float b;
    // Constructeur
    Couleur(){};
    Couleur(float r, float g, float b): r(r),g(g),b(b){};
};

struct Forme{
    std::vector<Position> sommets;
    Couleur couleur;
    Position position;
    float rotation;
};

struct Geometrie{
    std::vector<Forme> formes;
    float epaisseur;
};

struct Application{
    Geometrie logoEpsi;
    Geometrie modele;
    Geometrie logoGames;
    float temps;
    float vitesse;
};
Application application;

/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Prototypes ** ** ** ** ** ** ** ** ** ** ** ** ** */

void specialKeys( int key, int x, int y );
void display();
void afficherGeometrie(Geometrie& geometrie);
void chargerLogos();
void gestionTranslation(const Geometrie& depart, const Geometrie& arrivee, Geometrie& modele, float t);


/* ** ** ** ** ** ** ** ** ** ** ** ** ** ** Functions ** ** ** ** ** ** ** ** ** ** ** ** ** */

void display()
{
    // on efface l'écran
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialiser le type de la matrice pour les modèles 3D
    glMatrixMode( GL_MODELVIEW );

  // initialiser la matrice de la caméra
  glLoadIdentity();
  // positionnement de la caméra
  glTranslatef(0.0f,0.0f,-5.0f);

  // Tourne la caméra sur l'axe  X et Y
  glRotatef( rotate_x, 1.0, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 1.0, 0.0 );

    gestionTranslation(application.logoEpsi, application.logoGames, application.modele, application.temps);

    afficherGeometrie(application.modele);

  glFlush();
  glutSwapBuffers();

}

void initialize ()
{
    // set window values
  win.width = 600;
  win.height = 600;
  win.title = "TP1 - Logo EPSI ";
  win.field_of_view_angle = 45;
  win.z_near = 1.0f;
  win.z_far = 500.0f;

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
  glutInitWindowSize(win.width,win.height);         // set window size
  glutCreateWindow(win.title);                // create Window


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

void specialKeys( int key, int x, int y ) {

  //  Right arrow - increase rotation by 5 degree
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;

  //  Left arrow - decrease rotation by 5 degree
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;

  else if (key == GLUT_KEY_UP)
    rotate_x += 5;

  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
  else if (key == GLUT_KEY_PAGE_DOWN)
    application.temps -= application.vitesse;
  else if (key == GLUT_KEY_PAGE_UP)
    application.temps += application.vitesse;

  //  Request display update
  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  // On créer les logos
    chargerLogos();

  // initialise Glut
  glutInit(&argc, argv);
  initialize();
  // fait le lien entre le programme et l'affichage Glut
  glutDisplayFunc(display);
  glutIdleFunc(display);
  // gestion des évènements clavier
  glutSpecialFunc(specialKeys);
  glutMainLoop();
  return 0;
}

void afficherGeometrie(Geometrie& geometrie)
{
    // On affiche chaque forme
    std::vector<Forme>::iterator it;
    for(it = geometrie.formes.begin() ; it != geometrie.formes.end() ; it++)
    {
        glColor3f(it->couleur.r,it->couleur.g,it->couleur.b);

        // On applique la rotation et les translations
        glPushMatrix();

        // on doit d'abord faire le translate avant le rotate
        glTranslatef(it->position.x, it->position.y, 0);
        glRotatef( it->rotation, 0.0, 0.0, 1.0 );

        // Face avant
        glBegin(GL_POLYGON);
        std::vector<Position>::iterator sommet;
        for(sommet = it->sommets.begin() ; sommet != it->sommets.end() ; sommet++)
            glVertex3f( sommet->x, sommet->y , +geometrie.epaisseur / 2.f );
        glEnd();

        // Contour
        std::vector<Position>::iterator sommet2;
        for(sommet = it->sommets.begin() ; sommet != it->sommets.end() ; sommet++)
        {
            glBegin(GL_POLYGON);
            for(sommet2 = it->sommets.begin()+1 ; sommet2 != it->sommets.end() ; sommet2++)
            {
                glVertex3f( sommet2->x, sommet2->y , +geometrie.epaisseur / 2.f );
                glVertex3f( sommet->x, sommet->y , +geometrie.epaisseur / 2.f );
                glVertex3f( sommet->x, sommet->y , -geometrie.epaisseur / 2.f );
                glVertex3f( sommet2->x, sommet2->y , -geometrie.epaisseur / 2.f );
            }
            glEnd();
        }

        // Face arriere
        glBegin(GL_POLYGON);
        for(sommet = it->sommets.begin() ; sommet != it->sommets.end() ; sommet++)
            glVertex3f( sommet->x, sommet->y , -geometrie.epaisseur / 2.f );
        glEnd();

        glPopMatrix();
    }
}

void chargerLogos()
{
    application.logoEpsi.epaisseur = 0.2f;
    application.temps = 0;
    application.vitesse = 15;

    /************************************************
    //      Logo EPSI
    ************************************************/

    Forme triangleRouge;
    triangleRouge.couleur = Couleur(0.87f,0.13f,0.22f);
    triangleRouge.sommets.push_back(Position(-1.0f,-0.5f));
    triangleRouge.sommets.push_back(Position(0.0f,0.5f));
    triangleRouge.sommets.push_back(Position(1.0f,-0.5f));
    triangleRouge.position = Position(-1.0f,1.0f);
    triangleRouge.rotation = 45;
    application.logoEpsi.formes.push_back(triangleRouge);

    Forme triangleOrange;
    triangleOrange.couleur = Couleur(0.93f,0.50f,0.19f);
    triangleOrange.sommets.push_back(Position(-0.5f,-0.25f));
    triangleOrange.sommets.push_back(Position(0.0f,0.25f));
    triangleOrange.sommets.push_back(Position(0.5f,-0.25f));
    triangleOrange.position = Position(0.0f,0.5f);
    triangleOrange.rotation = 180;
    application.logoEpsi.formes.push_back(triangleOrange);

    Forme polygoneViolet;
    polygoneViolet.couleur = Couleur(0.62f, 0.2f, 0.54f);
    polygoneViolet.sommets.push_back(Position(-0.5f,-0.5f));
    polygoneViolet.sommets.push_back(Position(-0.5f,0.5f));
    polygoneViolet.sommets.push_back(Position(0.5f,0.5f));
    polygoneViolet.sommets.push_back(Position(0.5f,-0.5f));
    polygoneViolet.position = Position(-0.5f,0.0f);
    polygoneViolet.rotation = 45;
    application.logoEpsi.formes.push_back(polygoneViolet);

    /************************************************
    //      Logo test
    ************************************************/
    application.logoGames = application.logoEpsi;
    application.modele = application.logoEpsi;

    application.logoGames.formes.at(0).position = Position(0.5f,0.5f);
    application.logoGames.formes.at(0).rotation = 405;

    application.logoGames.formes.at(1).position = Position(1,1.3f);
    application.logoGames.formes.at(1).rotation = -90;

    application.logoGames.formes.at(2).position = Position(0.5f,-1.5f);
    application.logoGames.formes.at(2).rotation = 9494956;
/*
    Forme triangleRouge;
    triangleRouge.couleur = Couleur(0.87f,0.13f,0.22f);
    triangleRouge.sommets.push_back(Position(-1.0f,1.0f));
    triangleRouge.sommets.push_back(Position(-1.0f,0.0f));
    triangleRouge.sommets.push_back(Position(0.0f,1.0f));
    application.logoEpsi.formes.push_back(triangleRouge);

    Forme triangleOrange;
    triangleOrange.couleur = Couleur(0.93f,0.50f,0.19f);
    triangleOrange.sommets.push_back(Position(-0.5f,0.5f));
    triangleOrange.sommets.push_back(Position(0.5f,0.5f));
    triangleOrange.sommets.push_back(Position(0.0f,0.0f));
    application.logoEpsi.formes.push_back(triangleOrange);

    Forme triangleVert;
    triangleVert.couleur = Couleur(0.0f,0.68f,0.30f);
    triangleVert.sommets.push_back(Position(1.0f,1.0f));
    triangleVert.sommets.push_back(Position(1.0f,-1.0f));
    triangleVert.sommets.push_back(Position(0.0f,0.0f));
    application.logoEpsi.formes.push_back(triangleVert);

    Forme triangleBleu;
    triangleBleu.couleur = Couleur(0.0f,0.64f,0.80f);
    triangleBleu.sommets.push_back(Position(1.0f,-1.0f));
    triangleBleu.sommets.push_back(Position(-1.0f,-1.0f));
    triangleBleu.sommets.push_back(Position(0.0f,0.0f));
    application.logoEpsi.formes.push_back(triangleBleu);

    Forme polygoneViolet;
    polygoneViolet.couleur = Couleur(0.62f, 0.2f, 0.54f);
    polygoneViolet.sommets.push_back(Position(-0.5f,0.5f));
    polygoneViolet.sommets.push_back(Position(0.0f,0.0f));
    polygoneViolet.sommets.push_back(Position(-0.5f,-0.5f));
    polygoneViolet.sommets.push_back(Position(-1.0f,0.0f));
    application.logoEpsi.formes.push_back(polygoneViolet);

    Forme polygoneJaune;
    polygoneJaune.couleur = Couleur(0.99f,0.89f,0.18f);
    polygoneJaune.sommets.push_back(Position(0.0f,1.0f));
    polygoneJaune.sommets.push_back(Position(1.0f,1.0f));
    polygoneJaune.sommets.push_back(Position(0.5f,0.5f));
    polygoneJaune.sommets.push_back(Position(-0.5f,0.5f));
    application.logoEpsi.formes.push_back(polygoneJaune);

    Forme triangleViolet;
    triangleViolet.couleur = Couleur(0.39f,0.15f,0.4f);
    triangleViolet.sommets.push_back(Position(-1.3f,0.0f));
    triangleViolet.sommets.push_back(Position(-0.8f,-0.5f));
    triangleViolet.sommets.push_back(Position(-1.3f,-1.0f));
    application.logoEpsi.formes.push_back(triangleViolet);*/

}

void gestionTranslation(const Geometrie& depart, const Geometrie& arrivee, Geometrie& modele, float t)
{
    if(depart.formes.size() != arrivee.formes.size())
        return;
    if(depart.formes.size() != modele.formes.size())
        return;

    float d = 1000;
    if( t > d )
        t = d;
    else if( t < 0 )
        t = 0;

    for(int i = 0 ; i<modele.formes.size() ; i++)
    {
        // Calcul la trajectoire de façon linéaire
        float cx = arrivee.formes.at(i).position.x - depart.formes.at(i).position.x;
        float cy = arrivee.formes.at(i).position.y - depart.formes.at(i).position.y;
        float x = cx*t/d + depart.formes.at(i).position.x;
        float y = cy*t/d + depart.formes.at(i).position.y;
        modele.formes.at(i).position = Position(x, y);

        // Calcul de la rotation de façon linéaire
        float rx = arrivee.formes.at(i).rotation - depart.formes.at(i).rotation;
        float r = rx*t/d + depart.formes.at(i).rotation;
        modele.formes.at(i).rotation = r;
    }
}
