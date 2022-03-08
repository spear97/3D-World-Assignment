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
#include <tuple>
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

//The Bounds that the Ground Exist on
float minBound = -100.f, maxBound = 100.f;

// the key states. These variables will be zero when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

//The ids that will be used to navigate through the menu for spawn Renders
static int submenu_Draw_id;
static int submenu_Scene_id;
static int submenu_CamSpeed_id;
static int submenu_Sim_id;
static int menu_id;

//Determine if Default should be rendered or not
bool useDefault = true;

//Determine if Objects have already been generated in the Scene or Not
bool alreadyGenerate = false;

//Determine if a Simulation is running
bool isSimulating = false;

//Determine if Camera needs to be slowed down
bool slowDown = false;

//The Identifier for the Environment that will need to be rendered
int Env_ID;

/* Red diffuse light. */
GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 0.9};  

/* Infinite light location. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0}; 

//Get a Random Value in range
double RandRange(double min, double max)
{
    return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}

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

//Initialize a Polyhedron Already Loaded into a Scene
void initPolyhedron() {
  Polyhedron p1("models/Pyramid.obj", Vector3d(0,0,0), 0, Vector3d(1,1,0));
  p1.Load();
  p1.Recenter();
  polys.push_back(p1);
}

//Load a File from a given filename
void loadFromFile(string filename, Vector3d center, double rot, Vector3d color) 
{
  Polyhedron p1(filename, center, rot, color);
  p1.Load();
  p1.Recenter();
  polys.push_back(p1);
}

//What needs to be rendered for Environemnt1
void Environment1()
{
    glColor3f(0.f, 1.f, 0.f);
    glBegin(GL_QUADS);
    glVertex3f(minBound, 0.0f, minBound);
    glVertex3f(minBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, minBound);
    glEnd();

    //Verify if Objects have already been generated or not
    if (!alreadyGenerate)
    {
        alreadyGenerate = true;
        for (int i = 0; i < 10; i++)
        {
            switch (i)
            {
            case 0: //Grass Patch
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/Grass.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                    loadFromFile("models/Grass.obj", Vector3d(x+1, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 1: //Rocks
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/RockSmallBAlt.obj", Vector3d(x, 0.5f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 2: //Grass
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/Grass.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 3: //Military Vehicle
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/MilitaryVehicle.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                }
                break;
            case 4: //tree4
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                    loadFromFile("models/tree4-top.obj", Vector3d(x, 4.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 5: //stone2_L
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 6: //stone1_S
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_S.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 7: //stone1_M
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_M.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 8: //stone2_L2-scaled
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L2-scaled.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 9: //PalmTreeTrunk
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                    loadFromFile("models/tree4-top.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            }
        }
    }
}

//What needs to be rendered for Environemnt1
void Environment2()
{
    glColor3f(0.588f, 0.294f, 0.f);
    glBegin(GL_QUADS);
    glVertex3f(minBound, 0.0f, minBound);
    glVertex3f(minBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, minBound);
    glEnd();


    //Verify if Objects have already been generated or not
    if (!alreadyGenerate)
    {
        alreadyGenerate = true;
        for (int i = 0; i < 10; i++)
        {
            switch (i)
            {
            case 0: //Bush
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4-top.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 1: //Rocks
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/RockSmallBAlt.obj", Vector3d(x, 0.5f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 2: //Grass
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/Grass.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 3: //Tree
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                    loadFromFile("models/tree4-top.obj", Vector3d(x, 4.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 4: //tree4
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4.obj", Vector3d(x, 2.5f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                }
                break;
            case 5: //stone2_L
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 6: //stone1_S
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_S.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 7: //stone1_M
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_M.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 8: //stone2_L2-scaled
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L2-scaled.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 9: //Military Vehicles
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/MilitaryVehicle.obj", Vector3d(x, 0.21f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            }
        }
    }
}

//What needs to be rendered for Environemnt1
void Environment3()
{
    glColor3f(0.761f, 0.698f, 0.502f);
    glBegin(GL_QUADS);
    glVertex3f(minBound, 0.0f, minBound);
    glVertex3f(minBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, minBound);
    glEnd();

    //Verify if Objects have already been generated or not
    if (!alreadyGenerate)
    {
        alreadyGenerate = true;
        for (int i = 0; i < 10; i++)
        {
            switch (i)
            {
            case 0: //Cacti
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/Cactus.obj", Vector3d(x, 0.5f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 1: //Rocks
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/RockSmallBAlt.obj", Vector3d(x, 0.5f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 2: //Grass
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/Grass.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 3: //PalmTree
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/PalmTreeTrunk.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                    loadFromFile("models/PalmTreeTop.obj", Vector3d(x, 2.25f, z), 0, Vector3d(0.f, 1.f, 0.f));
                }
                break;
            case 4: //tree4
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/tree4.obj", Vector3d(x, 2.5f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                }
                break;
            case 5: //stone2_L
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.5f, 0.5f, 0.5f));
                }
                break;
            case 6: //stone1_S
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_S.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 7: //stone1_M
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone1_M.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 8: //stone2_L2-scaled
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/stone2_L2-scaled.obj", Vector3d(x, 0.f, z), 0, Vector3d(0.75f, 0.75f, 0.75f));
                }
                break;
            case 9: //PalmTreeTrunk
                for (int j = 0; j < 4; j++)
                {
                    double x = RandRange(minBound, maxBound), z = RandRange(minBound, maxBound);
                    loadFromFile("models/PalmTreeTrunk.obj", Vector3d(x, 0.25f, z), 0, Vector3d(0.588f, 0.294f, 0.f));
                }
                break;
            }
        }
    }
}

//What needs to be rendered for the Default Environment
void DefaultEnvironment()
{
    glColor3f(0.85f, 0.85f, 0.85f);
    glBegin(GL_QUADS);
    glVertex3f(minBound, 0.0f, minBound);
    glVertex3f(minBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, maxBound);
    glVertex3f(maxBound, 0.0f, minBound);
    glEnd();
}

//Render changes to the current Scene
void renderScene(void) {

    //If there is a Position Change
    if (deltaMove)
    {
        //TODO: Generate Vector3d Object Based on Postion 
        computePos(deltaMove);
    }

    //If there is an Angle Chage
    if (deltaAngle)
    {
        //TODO: Generate Vector3d Object Based on Rotation 
        computeDir(deltaAngle);
    }

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f, z+lz, 0.0f, 1.0f,  0.0f);

    //Render Environment Based on User Selection
    if (useDefault) //Default - Rendering
    {
        DefaultEnvironment();
    }
    else
    {
        switch (Env_ID)
        {
        case 0: //Environment 1 - Rendering
            Environment1();
            break;
        case 1: //Environment 2 - Rendering
            Environment2();
            break;

        case 2: //Environment 3 - Rendering
            Environment3();
            break;
        }
    }

    //Draw Polygons
    for(int i=0; i < (int)polys.size(); i++) 
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
        if (slowDown)
        {
            deltaAngle = -0.0001f;
        }
        else
        {
            deltaAngle = -0.001f;
        }
        break;

    //On Right Key Pressed, turn Camera to the Right
    case GLUT_KEY_RIGHT: 
        if (slowDown)
        {
            deltaAngle = 0.0001f;
        }
        else
        {
            deltaAngle = 0.001f;
        }
        break;

    //On Up Key Pressed, move Camera forward
    case GLUT_KEY_UP: 
        if (slowDown)
        {
            deltaMove = 0.005f;
        }
        else
        {
            deltaMove = 0.05f;
        }
        break;

    //On Down Key Pressed, turn Camera backward
    case GLUT_KEY_DOWN: 
        if (slowDown)
        {
            deltaMove = -0.005f;
        }
        else
        {
            deltaMove = -0.05f;
        }
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

//Menu for Program to perform different Events
void menu(int num)
{
    switch (num)
    {
    case 0:
        exit(0);
    case 1:
        if (!polys.empty())
        {
            polys.clear();
            initPolyhedron();
        }
        break;
    case 2:
        loadFromFile("models/Grass.obj", Vector3d(x+lx, 0.5f, z+lz), 0, Vector3d(0.f, 1.f, 0.f));
        break;
    case 3:
        loadFromFile("models/Wukong.obj", Vector3d(x+lx, 1.5f, z+lz), 0, Vector3d(0.75f, 0.75f, 0.75f));
        break;
    case 4:
        loadFromFile("models/MilitaryVehicle.obj", Vector3d(x+lx, 0.21f, z+lz), 0, Vector3d(0.75f, 0.75f, 0.75f));
        break;
    case 5:
        loadFromFile("models/patrick.obj", Vector3d(x+lx, 0.5f, z+lz), 0, Vector3d(1.f, 0.753f, 0.796f));
        break;
    case 6:
        loadFromFile("models/Sonic.obj", Vector3d(x+lx, 0.5f, z+lz), 0, Vector3d(0.f, 0.f, 1.f));
        break;
    case 7:
        if (!polys.empty())
        {
            polys.clear();
        }
        alreadyGenerate = false;
        initPolyhedron();
        useDefault = false;
        Env_ID = 0;
        break;
    case 8:
        if (!polys.empty())
        {
            polys.clear();
        }
        alreadyGenerate = false;
        initPolyhedron();
        useDefault = false;
        Env_ID = 1;
        break;
    case 9:
        if (!polys.empty())
        {
            polys.clear();
        }
        alreadyGenerate = false;
        initPolyhedron();
        useDefault = false;
        Env_ID = 2;
        break;
    case 10:
        if (!polys.empty())
        {
            polys.clear();
        }
        alreadyGenerate = false;
        initPolyhedron();
        useDefault = true;
        break;
    case 11:
        if (slowDown)
        {
            slowDown = false;
        }
        break;
    case 12:
        if (!slowDown)
        {
            slowDown = true;
        }
        break;
    }

    glutPostRedisplay();
}

//Render Menu for Progrma
void createMenu(void)
{
    submenu_Draw_id = glutCreateMenu(menu);
    glutAddMenuEntry("Grass", 2);
    glutAddMenuEntry("Wukong", 3);
    glutAddMenuEntry("Military Vehicle", 4);
    glutAddMenuEntry("Patrick", 5);
    glutAddMenuEntry("Sonic", 6);
    submenu_Scene_id = glutCreateMenu(menu);
    glutAddMenuEntry("Scene 1", 7);
    glutAddMenuEntry("Scene 2", 8);
    glutAddMenuEntry("Scene 3", 9);
    glutAddMenuEntry("Default Scene", 10);
    submenu_CamSpeed_id = glutCreateMenu(menu);
    glutAddMenuEntry("Fast", 11);
    glutAddMenuEntry("Slow", 12);
    menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Draw", submenu_Draw_id);
    glutAddSubMenu("Environments", submenu_Scene_id);
    glutAddSubMenu("Camera Speed", submenu_CamSpeed_id);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
  createMenu();

  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}