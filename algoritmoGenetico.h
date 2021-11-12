#ifndef IMAGERECOVERY_ALGORITMOGENETICO_H
#define IMAGERECOVERY_ALGORITMOGENETICO_H

#include "opencv2/opencv.hpp"
#include "cargarImagen.h"

using namespace cv;
using namespace std;

class algoritmoGenetico {
public:
    double fitness;
    int Indice;

    void inicializar(int filas, int columnas);
    void mutacion();
    void funcionFitness();
    Mat colorPixel(Mat image);
    void principal();
};
void cruce(int pos, algoritmoGenetico padre, algoritmoGenetico madre);
bool aptitud(algoritmoGenetico i1, algoritmoGenetico i2);



#endif //IMAGERECOVERY_ALGORITMOGENETICO_H
