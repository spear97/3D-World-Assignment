#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "Polyhedron.h"

//Collection of polygons for a given object
vector<Polyhedron> polys;

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;

// the key states. These variables will be zero when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

/* Red diffuse light. */
GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 0.9};  

/* Infinite light location. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; 

//Update the Size of the Window
void changeSize(int w, int h) 
{

  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
    if (h == 0)
    {
        h = 1;
    }
    float ratio = w * 1.0 / h;

  // Use the Projection Matrix
  glMatrixMode(GL_PROJECTION);

  // Reset Matrix
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the correct perspective.
  gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

  // Get Back to the Modelview
  glMatrixMode(GL_MODELVIEW);
}

//Draw a 3-Dimensional SnowMan 
void drawSnowMan() 
{
  //glColor3f(1.0f, 1.0f, 1.0f);
  glColor3f(1.0f, 0.0f, 0.0f);

  // Draw Body
  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

  // Draw Nose
  glColor3f(1.0f, 0.5f , 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.08f,0.5f,10,2);
}

//Coputer Position for X and Z
void computePos(float deltaMove) 
{
  //Calculate the value for X
  x += deltaMove * lx * 0.2f;

  //Calculate the value for Z
  z += deltaMove * lz * 0.2f;
}

//Compute Direction 
void computeDir(float deltaAngle) 
{
  //Calculate the value for angle
  angle += deltaAngle;

  //Calculate the value for lx
  lx = sin(angle);

  //Calculate the value for lz
  lz = -cos(angle);
}

//Initialize Environment Parameters
void init() 
{
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glShadeModel (GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

//Initialize a Polyhedron
void initPolyhedron() {
  //TODO
  Polyhedron p1("models/cube.obj", Vector3d(-5,5,0), 0, Vector3d(1,0,0));
  p1.Load();
  p1.Recenter();
  p1.Print();
  polys.push_back(p1);
}

//Load a File from a given filename
void loadFromFile(string filename) 
{
  //TODO
}

//Render a Given Scene
void renderScene(void) {

    //If there is a Position Change
    if (deltaMove)
    {
        computePos(deltaMove);
    }

    //If there is an Angle Chage
    if (deltaAngle)
    {
        computeDir(deltaAngle);
    }

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f, z+lz, 0.0f, 1.0f,  0.0f);

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    //Draw 36 SnowMen
    if (0)
    {
        for (int i = -3; i < 3; i++)
        {
            for (int j = -3; j < 3; j++)
            {
                glPushMatrix();
                glTranslatef(i * 10.0, 0, j * 10.0);
                drawSnowMan();
                glPopMatrix();
            }
        }
    }
       
  //Draw Polygons
  for(int i=0; i<(int)polys.size(); i++) 
  {
    polys[i].Draw();
  }

  //Update to the current frame
  glutSwapBuffers();
}

//When a Key is pressed determine what needs to be done
void pressKey(int key, int xx, int yy) {
    
  //Determine which key has been pressed
  switch (key) 
  {
    //On Left Key Pressed, turn Camera to the left
    case GLUT_KEY_LEFT: 
        deltaAngle = -0.001f; 
        break;

    //On Right Key Pressed, turn Camera to the Right
    case GLUT_KEY_RIGHT: 
        deltaAngle = 0.001f; 
        break;

    //On Up Key Pressed, move Camera forward
    case GLUT_KEY_UP: 
        deltaMove = 0.05f; 
        break;

    //On Down Key Pressed, turn Camera backward
    case GLUT_KEY_DOWN: 
        deltaMove = -0.05f; 
        break;
  }
}

//When a Key is released determine what needs to be done
void releaseKey(int key, int x, int y) {

  //Determine which key has been released
  switch (key) 
  {
    //On Left Key Pressed, set deltaAngle to 0
    case GLUT_KEY_LEFT:
        deltaAngle = 0.f;
        break;

    //On Right Key Pressed, set deltaAngle to 0
    case GLUT_KEY_RIGHT: 
        deltaAngle = 0.f;
        break;

    //On Up Key Pressed, set deltaMove to 0
    case GLUT_KEY_UP:
        deltaMove = 0.f;
        break;

    //On Down Key Pressed, set deltaMove to 0
    case GLUT_KEY_DOWN: 
        deltaMove = 0.f;
        break;
  }
}

//When a Key is released determine what needs to be done
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    
    //Kill Program
    case 'q':
        exit(0);
        break;

    //Kill Program
    // ESCAPE key
    case 27:            
      exit(0);
      break;
  }
}

//Main Driver
int main(int argc, char **argv) {

  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(640,640);
  glutCreateWindow("3D World");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(pressKey);

  // here are the new entries
  glutIgnoreKeyRepeat(1);
  glutSpecialUpFunc(releaseKey);

  // OpenGL init
  glEnable(GL_DEPTH_TEST);
  init();
  initPolyhedron();
  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}
