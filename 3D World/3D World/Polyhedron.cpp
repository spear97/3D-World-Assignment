#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"

//Constructor for Polyhedron
Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) 
{
  center = _c;
  rotY = _rotY;
  color = _clr;
}

//Overloading Constructor for Polyhedron
Polyhedron::Polyhedron(const Polyhedron& other) {
  //cout << "Polyhedron copy constructor. " << endl;
  center = other.center;
  rotY = other.rotY;
  color = other.color;
  filename = other.filename;

  //////////////////////////////////////////////////////////
  //other data from obj loader

  verts = other.verts;
  vts = other.vts;
  vns = other.vns;
  faces = other.faces;
}

//Recenter Polyhedron 
void Polyhedron::Recenter() 
{
	Vector3d sum(0, 0, 0);
	for (int i = 0; i < verts.size(); i++)
	{
		sum += verts[i];
	}
	Vector3d modelledCenter = sum / (1.0 * verts.size());
	Vector3d avg = modelledCenter / verts.size();

	for (int i = 0; i < verts.size(); i++)
	{
		sum += verts[i];
	}
	cout << "sum = " << sum << endl;

	cout << "modelledCenter = " << modelledCenter << endl;

	//Loop through verts
	//for eah v in verts
	//	v -= modelledCenter
}

//Recenter Polyhedron values at X-Axis and Y-Axis
void Polyhedron::RecenterXZ() {
  //TODO 
}

//Render the Polyhedron
void Polyhedron::Draw() {
  //TODO 
  //cout << "Polyhedron::Draw color = " << color << endl;
	glColor3d(color.GetX(), color.GetY(), color.GetZ());
	glPushMatrix();
	glTranslated(center.GetX(), center.GetY(), center.GetZ());
	glPointSize(4.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < verts.size(); i++)
	{
		glVertex3d(verts[i].GetX(), verts[i].GetY(), verts[i].GetZ());
	}
	glEnd();
	glPopMatrix();
}
