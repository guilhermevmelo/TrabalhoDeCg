#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "cube.h"

using namespace std;

/* Globals */
vector<Object *> objects;
const bool render_shadows = true;
double bottomY = numeric_limits<double>::max();

vector<Object*> loadObject(const char* filename, Color color) {
        vector<string*> coord;        //read every single line of the obj file as a string
        vector<Vector> vertex;
        vector<Object*> faces;


        ifstream in(filename);     //open the .obj file
        if(!in.is_open())       //if not opened, exit with -1
        {
                cout << "Nor oepened" << endl;
                return faces;
        }

        char buf[256];
        //read in every line to coord
        while(!in.eof())
        {
                in.getline(buf,256);
                coord.push_back(new string(buf));
        }
        //go through all of the elements of coord, and decide what kind of element is that
        for(int i=0;i<coord.size();i++)
        {
                if(coord[i]->c_str()[0]=='#')   //if it is a comment (the first character is #)
                        continue;       //we don't care about that
                else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') //if vector
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read in the 3 float coordinate to tmpx,tmpy,tmpz
                        vertex.push_back(Vector(tmpx,tmpy,tmpz));       //and then add it to the end of our vertex list
                        if (tmpy < bottomY)
                            bottomY = tmpy;
                }else if(coord[i]->c_str()[0]=='f')     //if face
                {
                        int a,b,c;

                        sscanf(coord[i]->c_str(),"f %d %d %d",&c,&b,&a);
                                faces.push_back(new Triangle(vertex.at(a-1),vertex.at(b-1),vertex.at(c-1), color));     //read in, and add to the end of the face list
                }
        }
        cout << bottomY << endl;
        return faces;
}

long  getIndexOfClosestObject(vector<double>  intersections) {
    // para se nao toca em nada
    if (intersections.size() == 0)
        return -1;

    if (intersections.size() == 1) {
        if (intersections.at(0) > 0)
            return 0;
       return -1;
    }

//    double max = 0;
//    for (int i = 0; i < intersections.size(); i++) {
//        if (max < intersections.at(i))
//            max = intersections.at(i);
//    }

      double min = numeric_limits<double>::max();
      double index = -1;
      for (unsigned int j = 0; j < intersections.size(); j++) {
          if (intersections.at(j) > 0 && intersections.at(j) < min) {
              min = intersections.at(j);
              index = j;
          }
      }

      return index;
}

Color getColorAt(Vector intersectionPoint, Vector camera_ray_direction, vector<Object *> objects, long index_of_closest_object, vector<Light *> light_sources, double accuracy, double ambientLight) {

    Object *closest_object = objects.at(index_of_closest_object);
    Vector n = closest_object->getNormalAt(intersectionPoint);
    Color closest_object_color = closest_object->getColor();

    Color color = closest_object_color.scale(ambientLight);

    for (int light_i = 0; light_i < light_sources.size(); light_i++) {
        Vector l = light_sources.at(light_i)->pos().add(intersectionPoint.negative()).normalize();
        float cossine = n.dotProduct(l);
        //cout << "cos = " << cossine << endl;

        if (cossine > 0) {
            // testar as sombras
            bool shadowed = false;

            if (render_shadows) {

                Vector distance_to_light = light_sources.at(light_i)->pos().add(intersectionPoint.negative());
                float dtl_mag = distance_to_light.magnitude();

                Ray shadow_ray(intersectionPoint, distance_to_light.normalize());

                vector<double> intersections;

                for (int i = 0; i < objects.size(); i++) {
                    intersections.push_back(objects.at(i)->findIntersection(shadow_ray));
                }

                for (int c = 0; c < intersections.size(); c++) {
                    if (intersections.at(c) > accuracy) {
                        if(intersections.at(c) <= dtl_mag) {
                            //cout << " BREAK" << endl;
                            shadowed = true;
                        }
                        break;
                    }
                }
            }

            if (shadowed == false) {
                //cout << "FALSE" << endl;
                Color object_color = closest_object->getColor();
                Color light_color = light_sources.at(light_i)->col();
                color = color.add(object_color.multiply(light_color.scale(cossine)));
                //cout << "shadowed color " << closest_object_color.s() << endl;

                if (closest_object_color.s() > 0 && closest_object_color.s() <= 1.0) {
                    // Shinenness: special = ]0 - 1]
                    //cout << "SPECIAL ]0 - 1]" << endl;

                    double dot1 = n.dotProduct(camera_ray_direction.negative());
                    Vector scalar1 = n.multiply(dot1);
                    Vector add1 = scalar1.add(camera_ray_direction);
                    Vector scalar2 = add1.multiply(2);
                    Vector add2 = camera_ray_direction.negative().add(scalar2);
                    Vector r = add2.normalize();

                    double specular = r.dotProduct(l);

                    //cout << specular << endl;

                    if (specular > 0) {
                        specular = pow(specular, closest_object_color.s() * 10);
                        Color light_color = light_sources.at(light_i)->col();
                        color = color.add(light_color.scale(specular * closest_object_color.s()));

                        //cout << color << endl;
                    }
                }
            }
        }
    }

    return color.clip();
}

void addCube(Cube cube) {

    for(unsigned int i = 0; i < cube.getFaces().size(); i++) {
        objects.push_back(cube.getFaces().at(i));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int W = 200;
    int H = 200;
    double aspectRatio = (double)W/(double)H;
    double ambientLight = 0.2;
    double accuracy = 0.0000000001;


    QImage image = QImage(W, H, QImage::Format_RGB32);
    QGraphicsScene * graphic = new QGraphicsScene(this);


    //cout << "About to enter main loop" << endl;

    Vector O(0, 0, 0);
    Vector X(1, 0, 0);
    Vector Y(0, 1, 0);
    Vector Z(0, 0, 1);

    //Vector camera_position(0, 0, 5);
    Vector camera_position(3, 2, 3);
    //cout << camera_position << endl;

    Vector look_at(0, 0, 0);
    Vector diff_btw (camera_position.x() - look_at.x(),
                     camera_position.y() - look_at.y(),
                     camera_position.z() - look_at.z());

    Vector camera_direction = diff_btw.negative().normalize();
    //Vector camera_right = Y.crossProduct(camera_direction).normalize();
    Vector camera_right = camera_direction.crossProduct(Y).normalize();
    Vector camera_down = camera_right.crossProduct(camera_direction);

    //camera_down = Vector(camera_down.x(), camera_down.y(), camera_down.z());

    Camera camera(camera_position, camera_direction, camera_right, camera_down);

    Color white(1.0, 1.0, 1.0, 0);
    Color green(0.5, 1.0, 0.5, 0.3);
    Color brown(0.5, 0.2, 0.25, 0);
    Color gray(0.5, 0.5, 0.5, 0.3);
    Color black(0, 0, 0, 0);
    Color red(1, 0.5, 0.5, 0.3);
    Color orange(0.94, 0.75, 0.31, 0);
    Color blue(0.3, 0.4, 0.8, 0.4);


    Light light1(Vector(0, 0, 10), white);
    Light light2(Vector(0, 100, 0), white);

    vector<Light *> light_sources;
    light_sources.push_back(dynamic_cast<Light *>(&light1));
    light_sources.push_back(dynamic_cast<Light *>(&light2));


    // Instancia os bjetos abaixo
//    Sphere ball(O, 1, green);
//    Sphere little_ball(O.add(Vector(1.2, -0.7, 0)), 0.3, red);
//    Sphere moon(O.add(Vector(2, 2, 2)), 0.2, Color(0.8, 0.8, 0.8, 0.5));
    Plane ground(Y, bottomY, green);
//    Triangle triangle(Vector(3,0,0), Vector(0,3,0), Vector(0,0,3), orange);

//    Cube cube(Vector(1,1,1), Vector(-1,-1,-1), orange);
//    cube.translate(-1,1,1);
//    addCube(cube);



//    objects.push_back(dynamic_cast<Object *>(&ball));

//    objects.push_back(dynamic_cast<Object *>(&little_ball));
//    objects.push_back(dynamic_cast<Object *>(&moon));
//    objects.push_back(dynamic_cast<Object *>(&triangle));


    objects = loadObject("/Users/guilherme/Developer/Trabalho/congresso2_0_07.obj", gray);
    objects.push_back(dynamic_cast<Object *>(&ground));
    double xamnt, yamnt;
    Vector camera_ray_origin = camera.getCameraPosition();

    for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {

            if (W > H) {
                xamnt = ((i + 0.5)/W)*aspectRatio - ((W - H)/(double)H)/2;
                yamnt = ((H - j) + 0.5)/H;
            } else if (H > W){
                xamnt = (i + 0.5)/W;
                yamnt = (((H - j) + 0.5)/H)/aspectRatio - (((H - W)/(double)W)/2);
            } else {
                xamnt = (i + 0.5)/W;
                yamnt = ((H - j) + 0.5)/H;
            }

            Vector camera_ray_direction = camera_direction.add(camera_right.multiply(xamnt - 0.5).add(camera_down.multiply(yamnt - 0.5))).normalize();

            Ray camera_ray(camera_ray_origin, camera_ray_direction);

            vector<double> intersections;
            for (unsigned int index = 0; index < objects.size(); index++) {
                intersections.push_back(objects.at(index)->findIntersection(camera_ray));
            }

            long index_of_closest_object = getIndexOfClosestObject(intersections);

            //cout << index_of_closest_object << endl;
            Color c;
            if (index_of_closest_object < 0)
                c = black;
            else {
                Vector intersectionPoint = camera_ray_origin.add(camera_ray_direction.multiply(intersections.at(index_of_closest_object)));
                // obter a cor pura do objeto sem interacao com o cenario:
                //c = objects.at(index_of_closest_object)->getColor();
                // obter a cor da interaçao com o cenario
                c = getColorAt(intersectionPoint, camera_ray_direction, objects, index_of_closest_object, light_sources, accuracy, ambientLight);

            }

            QRgb qtRGB = qRgb(c.r()*255, c.g()*255, c.b()*255);
            image.setPixel(i, j, qtRGB);
         }
    }

    graphic->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(graphic);
}

MainWindow::~MainWindow()
{
    delete ui;
}
