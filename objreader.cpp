#include <fstream>
#include "objreader.h"
#include "vector.h"
#include "triangle.h"
#include <limits>

using namespace std;

ObjReader::ObjReader() {
    bottomY = numeric_limits<double>::max();
}

int ObjReader::read(const char* filename, Color color) {
        vector<string*> coord;
        vector<Vector> vertex;


        ifstream in(filename);
        if(!in.is_open()) {
                cout << "Failed openning file" << filename << endl;
                return -1;
        }

        char buf[256];
        while(!in.eof()) {
                in.getline(buf,256);
                coord.push_back(new string(buf));
        }

        for(unsigned int i=0; i < coord.size(); i++) {
            if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') {
                   float tmpx,tmpy,tmpz;
                sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);
                vertex.push_back(Vector(tmpx,tmpy,tmpz));
                if (tmpy < bottomY)
                    bottomY = tmpy;
            } else if(coord[i]->c_str()[0]=='f')   {
                int a,b,c;

                sscanf(coord[i]->c_str(),"f %d %d %d",&c,&b,&a);
                faces.push_back(new Triangle(vertex.at(a-1),vertex.at(b-1),vertex.at(c-1), color));
            }
        }
        return 1;
}

double ObjReader::getBottomY() {
    return bottomY;
}

vector<Primitive *> ObjReader::getFaces() {
    return faces;
}


