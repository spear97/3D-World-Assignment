#include <GL/glut.h>  // (or others, depending on the system in use)

#include "Polyhedron.h"

//Constructor for Polyhedron
Polyhedron::Polyhedron(string _fname, Vector3d _c, double _rotY, Vector3d _clr) : ObjLoader(_fname) 
{
  //cout << "Polyhedron constructor. " << endl;
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
	cout << "sum = " << sum << endl;
	Vector3d modelledCenter = sum / (1.0 * verts.size());
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
}
