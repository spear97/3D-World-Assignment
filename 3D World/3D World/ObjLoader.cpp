#include "ObjLoader.h"

#include <fstream>

//Allow for an Object to be loaded
void ObjLoader::Load() 
{
  //Declare Local Variables
  ifstream infile;
  string stmp;
  Vector3d v;
  pair<double, double> tmpPair;
  Face f;
  int vid, nid, tid;
  bool done;
  char c;

  //If a file name is not given
  if( filename == "" ) 
  {
    cout << "Cannot load. empty file name!" << endl;
    exit(-1);
  }

  //Output Object File to be opened
  cout << "ObjLoader::Loading file: " << filename << endl;

  //Open Object File
  infile.open(filename.c_str());

  //While Object File is being read
  while( infile >> stmp ) 
  {

    //if Current line encounters a v
    if( stmp == "v" ) 
    {
      infile >> v;
      verts.push_back( v );
    }

    //if Current line encoutners a vn
    else if( stmp == "vn" ) 
    {
      infile >> v;
      vns.push_back( v );
    }

    //if Current line encoutners a vt
    else if( stmp == "vt" ) 
    {
      infile >> tmpPair.first >> tmpPair.second;
      vts.push_back( tmpPair );
    }

    //if Current line encouters a f
    else if( stmp == "f" ) 
    {
      //assume triangle

      //Iterate through the three vertices of triangle
      for(int i=0; i<3; i++) 
      {
        //set vid, nid, and tid to -1
        //initializes these variables
	    vid = -1;
	    nid = -1;
	    tid = -1;

        //first read vertex id
	    infile>>vid;

        //initialize done as false, since iteration is not yet done
	    done = false;

        //Get the next character in the string
	    c = infile.peek();

        //If next character is a '/'
	    if( c == '/' ) 
        {
            //should read '/' 
	        infile.get(c); 

            //Get the next character in the string
	        c = infile.peek();

            //If next character is a '/'
	        if( c == '/' ) 
            { 
                //no texture coordinate
                //Read '/'
	            infile.get(c); 

                //insert file content into nid
	            infile >> nid;

                //set done as true
	            done = true;
	        }

            //If next character is anything else
	        else 
            {
                //insert file content into tid
	            infile >> tid;

                //Get the next character in the string
	            c = infile.peek();

                //If next character is a '/'
	            if( c == '/' ) 
                {
                    //Read '/'
	                infile.get(c);

                    //insert file content into nid
	                infile >> nid;

                    //set done as true
	                done = true;
	            }

                //If anyother character, set done as true
	            else done = true;
	        }
	    }

        //if next character happens to be a space, set done as true
	    else if( c == ' ' )
        {
	        done = true;
	    }

        //if done is true
	    if(done) 
        {
            //push vid into f's ids
            f.ids.push_back( vid );

            //push tid into f.texIds
            f.texIds.push_back( tid );

            //push nid into f.normalIds
	        f.normalIds.push_back( nid );
	       }
      }//endfor i

      //push f into faces
      faces.push_back( f );
    }

    //if Current line encounters anyother characters
    else 
    {
      //skip this line if it doesn't start with v, vn, vt, f
      getline(infile, stmp);
    }
  }

  //Close file to prevent leakage
  infile.close();

  //Output that loading has been completed
  //indicating that file has been closed
  cout << "-done! ObjLoader::Loading file: " << filename << endl;
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