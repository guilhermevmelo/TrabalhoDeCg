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
const bool render_shadows = true;

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

Color getColorAt(Vector intersectionPoint, Vector camera_ray_direction, vector<Primitive *> objects, long index_of_closest_object, vector<Light *> light_sources, double accuracy, double ambientLight) {

    Primitive *closest_object = objects.at(index_of_closest_object);
    Vector n = closest_object->getNormalAt(intersectionPoint);
    Color closest_object_color = closest_object->getColor();

    Color color = closest_object_color.scale(ambientLight);

    for (unsigned int light_i = 0; light_i < light_sources.size(); light_i++) {
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

                for (unsigned int i = 0; i < objects.size(); i++) {
                    intersections.push_back(objects.at(i)->findIntersection(shadow_ray));
                }

                for (unsigned int c = 0; c < intersections.size(); c++) {
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

void addPrimitive(Primitive * primitive) {
    objects.push_back(primitive);
}

void addObject(Object object) {
    vector<Primitive *> faces = object.getFaces();
    for(unsigned int i = 0; i < faces.size(); i++) {
        addPrimitive(faces.at(i));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int W = 600;
    int H = 400;
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
    //Vector camera_position(1, 0.5, 1);
    //Vector camera_position(1, 0.5, -1);
    //Vector camera_position(1, 0, 0);
    Vector camera_position(6, 2, 0);

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
    Light light2(Vector(0, 10, 0), white);

    vector<Light *> light_sources;
    light_sources.push_back(dynamic_cast<Light *>(&light1));
    light_sources.push_back(dynamic_cast<Light *>(&light2));

    // Instancia os bjetos abaixo
//    Sphere ball(O, 1, green);
//    Sphere little_ball(O.add(Vector(1.2, -0.7, 0)), 0.3, red);
//    Sphere moon(O.add(Vector(2, 2, 2)), 0.2, Color(0.8, 0.8, 0.8, 0.5));

//    Triangle triangle(Vector(3,0,0), Vector(0,3,0), Vector(0,0,3), orange);

//    Cube cube(Vector(1,1,1), Vector(-1,-1,-1), orange);
//    cube.translate(-1,1,1);
//    addObject(cube);


//    objects.push_back(dynamic_cast<Primitive *>(&ball));

//    objects.push_back(dynamic_cast<Primitive *>(&little_ball));
//    objects.push_back(dynamic_cast<Primitive *>(&moon));
//    objects.push_back(dynamic_cast<Primitive *>(&triangle));

//    Congresso congresso;
//    addObject(congresso);

    Torus torus;
    addObject(torus);

//    Plane ground(Y, congresso.getBottomY(), green);
//    objects.push_back(dynamic_cast<Primitive *>(&ground));

//    Plane sky(Z, -100, blue);
//    objects.push_back(dynamic_cast<Primitive *>(&sky));


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
