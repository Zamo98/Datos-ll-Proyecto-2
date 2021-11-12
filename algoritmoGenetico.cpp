/**
 * @file algoritmoGenetico.cpp
 * @version 1.0
 * @date 10/11/2021
 * @authors Yaritza Lopez y Gustavo Zamora
 */

#include "algoritmoGenetico.h"
#include "cargarImagen.h"


int cantidadPoblacion;
int probabilidadMutacion = 2;
int filas,columnas;
int indice;
int longitudMat;

Vec3b** objetivo;
Vec3b*** genes, ***nuevosGenes;

cargarImagen* obj = nullptr;

int *matriz;

/**
 * @brief inicializar metodo que genera genes aleatorios
 * @param filas
 * @param columnas
 */
void algoritmoGenetico::inicializar(int filas, int columnas) {
    indice = Indice;
    for(int i = 0;  i < filas; i++){
        for(int j = 0; j < columnas; j++){
            genes[indice][i][j][0] = rand() % 256;
            genes[indice][i][j][1] = rand() % 256;
            genes[indice][i][j][2] = rand() % 256;

        }
        indice++;
    }
}

/**
 * @brief funcionFitness genera el valor del fitness
 */
void algoritmoGenetico::funcionFitness() {
    int contador = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(genes[Indice][i][j][0] == objetivo[i][j][0] || genes[Indice][i][j][1] == objetivo[i][j][1] || genes[Indice][i][j][2] == objetivo[i][j][2]){
                contador++;
            }
        }
    }
    fitness = 1000 * contador / (filas * columnas);
    fitness = (fitness * fitness) / 1000;
}

/**
 * @brief colorPixel interpreta los colores de la imagen
 * @param image
 * @return
 */
Mat algoritmoGenetico::colorPixel(Mat image) {
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            image.at<Vec3b>(i,j)[0] = genes[Indice][i][j][0];
            image.at<Vec3b>(i,j)[1] = genes[Indice][i][j][1];
            image.at<Vec3b>(i,j)[2] = genes[Indice][i][j][2];
        }
    }
    return image;
}

/**
 * @brief mutacion se encarga de realizar la mutacion
 */
void algoritmoGenetico::mutacion() {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(rand() % 100 < probabilidadMutacion){
                nuevosGenes[Indice][i][j][0] = rand() % 256;
                nuevosGenes[Indice][i][j][1] = rand() % 256;
                nuevosGenes[Indice][i][j][2] = rand() % 256;
            }
        }
    }
}

/**
 * @brief cruce se encarga de hacer los cruces
 * @param pos posicion
 * @param padre individuo padre a partir del cual se hará el cruce
 * @param madre individuo madre a partir del cual se hará el cruce
 */
void cruce(int pos, algoritmoGenetico padre, algoritmoGenetico madre) {
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++) {
            for (int k = 0; k < 3; k++) {
                if((genes[padre.Indice][i][j][k] == objetivo[i][j][k]) || (genes[madre.Indice][i][j][k] == objetivo[i][j][k])){
                    if(rand() % 10 == 0){
                        nuevosGenes[pos][i][j][k] = objetivo[i][j][k];
                    }
                    else{
                        goto branch;
                    }
                }
                else{
                    branch:
                    if(rand() % 2 == 0){
                        nuevosGenes[pos][i][j][k] = genes[padre.Indice][i][j][k];
                    }
                    else{
                        nuevosGenes[pos][i][j][k] = genes[madre.Indice][i][j][k];
                    }
                }
            }
        }
    }
}
algoritmoGenetico* poblacion;
/**
 * @brief aptitud metodo que revisa el que tiene mejor aptitud
 * @param i1 individuo 1
 * @param i2 individuo 2
 * @return
 */
bool aptitud(algoritmoGenetico i1, algoritmoGenetico i2) {
    return i1.fitness > i2.fitness;
}
/**
 * @brief se encarga del funcionamiento del programa
 */
void algoritmoGenetico::principal() {
    srand(time(NULL));
    obj = new cargarImagen();
    cargarImagen i;
    Mat img = obj->borrarImagen();
    obj->cargar();
    Mat imagenBase;
    imagenBase = obj->imagenObjetivo;
    filas = imagenBase.rows;
    columnas = imagenBase.cols;
    objetivo = new Vec3b * [filas];
    for(int i = 0; i < filas; i++){
        objetivo[i] = new Vec3b[columnas];
    }
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas;j++){
            objetivo[i][j][0] = imagenBase.at<Vec3b>(i,j)[0];
            objetivo[i][j][1] = imagenBase.at<Vec3b>(i,j)[1];
            objetivo[i][j][2] = imagenBase.at<Vec3b>(i,j)[2];
        }
    }
    cantidadPoblacion = 130;
    matriz = new int[cantidadPoblacion * (cantidadPoblacion+1)/2];
    genes = new Vec3b * *[cantidadPoblacion + 10];
    nuevosGenes = new Vec3b * *[cantidadPoblacion + 10];
    for(int i = 0; i < cantidadPoblacion+10; i++){
        genes[i] = new Vec3b *[filas];
        nuevosGenes[i] = new Vec3b *[filas];
        for(int j = 0; j < filas; j++){
            genes[i][j] = new Vec3b [columnas];
            nuevosGenes[i][j] = new Vec3b [columnas];
        }
    }
    poblacion = new algoritmoGenetico[cantidadPoblacion];
    for(int i = 0; i < cantidadPoblacion; i++){
        poblacion[i].inicializar(filas, columnas);
        poblacion[i].funcionFitness();
    }
    int generaciones = 0;
    while(true) {
        generaciones++;
        for (int i = 0; i < cantidadPoblacion; i++) {
            poblacion[i].funcionFitness();
        }
        sort(poblacion, poblacion + cantidadPoblacion, aptitud);
        cout << "Fitness: " << poblacion[0].fitness << "  |  " << "Generación: " << generaciones << endl;
        if (poblacion[0].fitness > 1000) {
            break;
        }

        imshow("Soluciones", obj->mostrar(img, poblacion[0].colorPixel(obj->image), obj->x, obj->y));
        waitKey(1);

        longitudMat = 0;

        for(int i = 0; i < cantidadPoblacion; i++){
            for(int j = 0; j < cantidadPoblacion - i; j++){
                matriz[longitudMat] = i;
                longitudMat += 1;
            }
        }
        for(int i = 0; i < cantidadPoblacion; i++){
            int a = rand() % longitudMat, b = rand() % longitudMat;
            cruce(i, poblacion[matriz[a]], poblacion[matriz[b]]);
        }
        for(int i = 0; i < cantidadPoblacion; i++){
            poblacion[i].mutacion();
        }
        swap(genes, nuevosGenes);
    }
    delete nuevosGenes;
    delete genes;
}
