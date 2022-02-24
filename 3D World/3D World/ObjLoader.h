#ifndef OBJ_LOADER__
#define OBJ_LOADER__

#include "Vector.h"
using namespace mathtool;

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Face 
{
  void Print() 
  {
    cout << "face ids: ";
    for(int i=0; i<(int)ids.size(); i++) 
    {
        cout << ids[i] << " ";
    }
    cout << endl;
  }
  vector<int> ids;
  vector<int> texIds;
  vector<int> normalIds;
};

class ObjLoader 
{
public:
  ObjLoader() { }
  ObjLoader(string _fname) { filename = _fname; }

  void Load(); 
  void Print();

protected:
  string filename;
  vector<Vector3d> verts;
  vector< pair<double, double> > vts;
  vector<Vector3d> vns;
  vector<Face> faces;
};


#endif
