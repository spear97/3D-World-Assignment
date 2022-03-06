#include "ObjLoader.h"

#include <fstream>

//Allow for an Object to be loaded
void ObjLoader::Load() {
    if (filename == "") {
        cout << "Cannot load. empty file name!" << endl;
        exit(-1);
    }
    //cout << "ObjLoader::Loading file: " << filename << endl;
    ifstream infile;
    infile.open(filename.c_str());
    string stmp;
    while (infile >> stmp) {
        if (stmp == "v") {
            Vector3d v;
            infile >> v;
            verts.push_back(v);
        }
        else if (stmp == "vn") {
            Vector3d v;
            infile >> v;
            vns.push_back(v);
        }
        else if (stmp == "vt") {
            pair<double, double> tmpPair;
            infile >> tmpPair.first >> tmpPair.second;
            vts.push_back(tmpPair);
        }
        else if (stmp == "f") {
            //assume triangle
            Face f;
            for (int i = 0; i < 3; i++) {
                int vid = -1;
                int nid = -1;
                int tid = -1;
                infile >> vid;//first read vertex id
                bool done = false;
                char c = infile.peek();
                if (c == '/') {
                    infile.get(c); //should read '/' 
                    c = infile.peek();
                    if (c == '/') { //no texture coordinate
                        infile.get(c); //grab '/'
                        infile >> nid;
                        done = true;
                    }
                    else {
                        infile >> tid;
                        c = infile.peek();
                        if (c == '/') {
                            infile.get(c);
                            infile >> nid;
                            done = true;
                        }
                        else done = true;
                    }
                }
                else if (c == ' ') {
                    done = true;
                }
                if (done) {
                    f.ids.push_back(vid);
                    f.texIds.push_back(tid);
                    f.normalIds.push_back(nid);
                }
            }//endfor i
            faces.push_back(f);
        }
        else {
            //skip this line if it doesn't start with v, vn, vt, f
            getline(infile, stmp);
        }
    }
    infile.close();
    //cout << "-done! ObjLoader::Loading file: " << filename << endl;
}

//Output Object information
void ObjLoader::Print() 
{
  //Output that this function is being called
  cout << "ObjLoader::Print()" << endl;

  //Output the number of vertices exist
  cout << "#verts " << verts.size() << endl;

  //Iterate through each vertex's information, and display vertex information
  for(int i=0; i<verts.size(); i++) 
  {
    cout << "v " << verts[i] << endl;
  }
  cout << endl;

  //Output the number of normals that exist for the vertices
  cout << "#normals " << vns.size() << endl;

  //Iterate through each vertex's information, and display normal information
  for(int i=0; i<vns.size(); i++) 
  {
    cout << "vn " << vns[i] << endl;
  }

  //Output the number of texture coordinates that exist
  cout << "#texture coordinates " << vts.size() << endl;

  //Iterate through vertex pairs, and display their positions
  for(int i=0; i<vts.size(); i++) 
  {
    cout << "vt " << vts[i].first << " " << vts[i].second << endl;
  }

  //Output the number of faces
  cout << "#faces " << faces.size() << endl;

  //Iterate through the faces, and display their information
  for(int i=0; i<faces.size(); i++) 
  {
    //Declare and Initialize Current Face
    Face& f = faces[i];

    //Output information regarding Current face
    cout << "f ";
    for(int i=0; i<f.ids.size(); i++) 
    {
      cout << f.ids[i] << "/" << f.texIds[i] << "/" << f.normalIds[i] << " ";
    }
    cout << endl;
  }
}