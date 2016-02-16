#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "primitive.h"
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
#include "congresso.h"
#include "torus.h"

using namespace std;

/* Globals */
vector<Primitive *> objects;
vector<Light *> light_sources;

const bool render_shadows = true;
double ambientLight = 0.2;
double accuracy = 0.0000000001;

int W = 600;
int H = 400;

Color white(1.0, 1.0, 1.0, 0);
Color green(0.5, 1.0, 0.5, 0.3);
Color brown(0.5, 0.2, 0.25, 0);
Color gray(0.5, 0.5, 0.5, 0.3);
Color black(0, 0, 0, 0);
Color red(1, 0.5, 0.5, 0.3);
Color orange(0.94, 0.75, 0.31, 0.3);
Color blue(0.3, 0.4, 0.8, 0.4);

Vector X(1, 0, 0);
Vector Y(0, 1, 0);
Vector Z(0, 0, 1);
Vector O(0, 0, 0);

long  getIndexOfClosestObject(vector<double>  intersections) {
    // para se nao toca em nada
    if (intersections.size() == 0)
        return -1;

    if (intersections.size() == 1) {
        if (intersections.at(0) > 0)
            return 0;
       return -1;
    }

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

Color getColorAt(Vector intersectionPoint, Vector camera_ray_direction, long index_of_closest_object) {
    Primitive *closest_object = objects.at(index_of_closest_object);
    Vector n = closest_object->getNormalAt(intersectionPoint);
    Color object_color = closest_object->getColor();

    Color color = object_color.scale(ambientLight);

    for (unsigned int light_i = 0; light_i < light_sources.size(); light_i++) {
        Color light_color = light_sources.at(light_i)->col();
        Vector l = light_sources.at(light_i)->pos().add(intersectionPoint.negative()).normalize();
        float cossine = n.dotProduct(l);

        if (cossine > 0) {
            // testar as sombras
            bool shadowed = false;

            if (render_shadows) {

                Vector distance_to_light = light_sources.at(light_i)->pos().add(intersectionPoint.negative());
                float dtl_mag = distance_to_light.magnitude();

                Ray shadow_ray(intersectionPoint, distance_to_light.normalize());

                vector<double> intersections;

                for (unsigned int i = 0; i < objects.size(); i++) {
                    intersections.push_back(objects.at(i)->findIntersection(shadow_ray));
                }

                for (unsigned int c = 0; c < intersections.size(); c++) {
                    if (intersections.at(c) > accuracy) {
                        if(intersections.at(c) <= dtl_mag) {
                            shadowed = true;
                        }
                        break;
                    }
                }
            }

            if (shadowed == false) {
                color = color.add(object_color.multiply(light_color.scale(cossine)));


                //Modelo de iluminação de Phong
                Vector v = camera_ray_direction.negative();
                double _2ln = 2*l.dotProduct(n);
                Vector _2lnn = n.multiply(_2ln);
                Vector r = _2lnn.add(l.negative()).normalize();

                double specular = r.dotProduct(v);

                if (specular > 0) {
                    specular = pow(specular, object_color.s() * 10);
                    color = color.add(light_color.scale(specular * object_color.s()));
                }
            }
        }
    }

    return color.clip();
}

void addPrimitive(Primitive * primitive) {
    objects.push_back(primitive);
}

void addObject(Object object) {
    vector<Primitive *> faces = object.getFaces();
    for(unsigned int i = 0; i < faces.size(); i++) {
        addPrimitive(faces.at(i));
    }
}

void addLight(Light &light) {
    light_sources.push_back(dynamic_cast<Light *>(&light));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //Cenário final

    //Congresso congresso;
    //addObject(congresso);

    Plane ground(Vector(0,1,0), -3, brown);
    objects.push_back(dynamic_cast<Primitive *>(&ground));

//    Plane sky(Vector(0, 0, 1), -100, blue);
//    objects.push_back(dynamic_cast<Primitive *>(&sky));

    Triangle t(X, Y, Z, blue);
    objects.push_back(dynamic_cast<Primitive *>(&t));


    Cube cube(Vector(-3, -2, -3), Vector(-2, -1,-2), orange);
    //cube.translate();
    addObject(cube);

    Sphere little_ball(Vector(0, 0, 0), 1, orange);
    //objects.push_back(dynamic_cast<Primitive *>(&little_ball));

//    Torus

//    Torus torus;
//    addObject(torus);

    double aspectRatio = (double)W / (double)H;

//    Vector camera_position(0, 0, 5);
//    Vector camera_position(1, 0.5, 1); //Camera do Congresso
//    Vector camera_position(1, 0.5, -1);
    Vector camera_position(5, 5, 5);

//    Vector camera_position(-6, 4, 3); //Camera do Torus
    Vector look_at(0, 0, 0);
    Vector up(0, 1, 0);

    Camera camera(camera_position, look_at, up);

    Light light1(Vector(0, 0, 10), white);
    Light light2(Vector(0, 10, 0), white);

    addLight(light1);
    addLight(light2);

    QImage image = QImage(W, H, QImage::Format_RGB32);
    QGraphicsScene * graphic = new QGraphicsScene(this);

    double xamnt, yamnt;

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

            Ray camera_ray = camera.createRay(xamnt, yamnt);

            vector<double> intersections;
            for (unsigned int index = 0; index < objects.size(); index++) {
                intersections.push_back(objects.at(index)->findIntersection(camera_ray));
            }

            long index_of_closest_object = getIndexOfClosestObject(intersections);

            Color c;
            if (index_of_closest_object < 0)
                c = black;
            else {
                Vector intersectionPoint = camera_ray.origin().add(camera_ray.direction().multiply(intersections.at(index_of_closest_object)));
                // obter a cor pura do objeto sem interacao com o cenario:
                //c = objects.at(index_of_closest_object)->getColor();
                // obter a cor da interaçao com o cenario
                c = getColorAt(intersectionPoint, camera_ray.direction(), index_of_closest_object);

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
