#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadImage_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg)")); //variable que guarda el nombre del archivo

    if(QString::compare(filename, QString()) != 0) //verifica si el archivo seleccionado está vacío
    {
        QImage image;
        bool valid = image.load(filename);

        if(valid) // verifica si carga correctamente
        {
            image = image.scaledToWidth(ui->lbl_Image->width(), Qt::SmoothTransformation); //acomoda la imagen
            ui->lbl_Image->setPixmap(QPixmap::fromImage(image));
        }
    }
}
