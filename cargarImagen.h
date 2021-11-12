#ifndef IMAGERECOVERY_CARGARIMAGEN_H
#define IMAGERECOVERY_CARGARIMAGEN_H


#include "opencv2/opencv.hpp"

using namespace cv;

class cargarImagen {
public:
    int x = 200;
    int y = 200;
    int w = 100;
    int h = 100;
    cargarImagen();
    void cargar();
    Mat borrarImagen();
    Mat mostrar(Mat matriz1, Mat matriz2, int _x, int _y);
    Mat img = imread("/home/gustavo/ImageRecovery/Imagenes/patron.jpeg", IMREAD_COLOR);//imagen completa
    Mat image = img(Rect(x, y, w, h));//parte eliminada
    Mat imagenObjetivo = img(Rect(x+100, y+100, w, h));//imagen objetivo

};


#endif //IMAGERECOVERY_CARGARIMAGEN_H
