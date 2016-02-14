#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"

using namespace std;

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
      for (int j = 0; j < intersections.size(); j++) {
          if (intersections.at(j) > 0 && intersections.at(j) < min) {
              min = intersections.at(j);
              index = j;
          }
      }

      return index;
}

Color getColorAt(Vector intersectionPoint, Vector camera_ray_direction, vector<Object *> objects, long index_of_closest_object, vector<Light *> light_sources, double accuracy, double ambientLight) {
    /*for (int light_i = 0; light_i < light_sources.size(); light_i++) {
        Vector light_direction = light_sources.at(light_i)->pos().add(intersectionPoint.negative()).normalize();
        Object *closest_object = objects.at(index_of_closest_object);
        Vector closest_object_normal = closest_object->getNormalAt(intersectionPoint);
        float cossine = closest_object_normal.dotProduct(light_direction);
    }*/

    return Color(0, 0, 0, 0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int W = 640;
    int H = 480;
    double aspectRatio = (double)W/(double)H;
    double ambientLight = 0.2;
    double accuracy = 0.000001;

    QImage image = QImage(W, H, QImage::Format_RGB16);
    QGraphicsScene * graphic = new QGraphicsScene(this);

    //std::cout << "About to enter main loop" << std::endl;

    Vector O(0, 0, 0);
    Vector X(1, 0, 0);
    Vector Y(0, 1, 0);
    Vector Z(0, 0, 1);

    Vector camera_position(3, 1.5, -4);

    //cout << camera_position << endl;

    Vector look_at(0, 0, 0);
    Vector diff_btw (camera_position.x() - look_at.x(),
                     camera_position.y() - look_at.y(),
                     camera_position.z() - look_at.z());

    Vector camera_direction = diff_btw.negative().normalize();
    Vector camera_right = Y.crossProduct(camera_direction).normalize();
    Vector camera_down = camera_right.crossProduct(camera_direction).negative();

    Camera camera(camera_position, camera_direction, camera_right, camera_down);

    Color white(1.0, 1.0, 1.0, 0);
    Color green(0.5, 1.0, 0.5, 0.3);
    Color brown(0.5, 0.2, 0.25, 0);
    Color gray(0.5, 0.5, 0.5, 0);
    Color black(0, 0, 0, 0);
    Color red(1, 0.5, 0.5, 0.3);

    Vector light_position(-7, 10, -10);
    Light light1(light_position, white);
    Light light2(Vector(10, -7, 10), red);

    vector<Light *> light_sources;
    light_sources.push_back(dynamic_cast<Light *>(&light1));
    light_sources.push_back(dynamic_cast<Light *>(&light2));

    // Instancia os bjetos abaixo
    Sphere ball(O, 1, green);
    Sphere little_ball(O.add(Vector(1, -0.5, -1)), 0.5, red);
    Sphere moon(O.add(Vector(2, 2, 2)), 0.2, Color(0.8, 0.8, 0.8, 0.5));
    Plane ground(Y, -1, brown);

    // Cria a lista de objetos
    vector<Object *> objects;
    objects.push_back(dynamic_cast<Object *>(&ball));
    objects.push_back(dynamic_cast<Object *>(&ground));
    objects.push_back(dynamic_cast<Object *>(&little_ball));
    objects.push_back(dynamic_cast<Object *>(&moon));

    double xamnt, yamnt;
    Vector camera_ray_origin = camera.getCameraPosition();

    for (int j = 0; j < H; j++) {
        for (int i = 0; i < W; i++) {
//            double r = 1;
//            double g = 0.3;
//            double b = 0.2;
//            QRgb qtRGB = qRgb(r * 255, g * 255, b * 255);

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
            for (long index = 0; index < objects.size(); index++) {
                intersections.push_back(objects.at(index)->findIntersection(camera_ray));
            }

            long index_of_closest_object = getIndexOfClosestObject(intersections);

            //cout << index_of_closest_object << endl;
            Color c;
            if (index_of_closest_object < 0)
                c = black;
            else {
                Vector intersectionPoint = camera_ray_origin.add(camera_ray_direction.multiply(intersections.at(index_of_closest_object)));
                // obter a cor do objeto:
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
