/**
 * @file cargarImagen.cpp
 * @version 1.0
 * @date 10/11/2021
 * @authors Yaritza Lopez y Gustavo Zamora
 */

#include "cargarImagen.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

/**
 * @brief cargarImagen metodo constructor
 */
cargarImagen ::cargarImagen() {}

/**
 * @brief borrarImagen se encarga de borrar una parte de la imagen
 * @return
 */
Mat cargarImagen::borrarImagen() {

    for (int i = 0; i < image.rows; i++) {
        Vec3b *imgrow = image.ptr<Vec3b>(i);

        for (int j = 0; j < image.cols; j++) {

            uchar white = 255;

            imgrow[j][0] = white;
            imgrow[j][1] = white;
            imgrow[j][2] = white;

        }
    }
    return img;
}
/**
* @brief cargar metodo que se encarga de cargar la imagen con la parte eliminada
*/
void cargarImagen::cargar() {
    imshow("Display Image", img);
    waitKey(0);
}

/**
 * @brief mostrar metodo que muestra en pantalla las soluciones
 * @param m1 matriz 1 que sera utilizada
 * @param m2 matriz 2 que sera utilizada
 * @param x posicion x
 * @param y posicion y
 * @return
 */
Mat cargarImagen::mostrar(Mat matriz1, Mat matriz2, int x, int y) {
    for(int i = x; i < matriz2.rows + x; i++){
        for(int j = y; j < matriz2.cols + y; j++){
            matriz1.at<Vec3b>(i,j) = matriz2.at<Vec3b>(i-x, j-y);
        }
    }
    return matriz1;
}