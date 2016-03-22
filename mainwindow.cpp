#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include "BMP.h"
#include "dialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);

    this->image = new QImage();

    //connect(ui->input,SIGNAL(clicked()),this,SLOT(on_input_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete image;
}



void MainWindow::on_input_clicked()
{
    //“打开文件”窗口，获取文件名
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home",
                                                tr("Images (*.bmp)"));
    char file2[] = "result.bmp"; //保存的灰度图的名字
    char* ch = new char();       //打开的文件名由QString强转而来
    QString temp2;               //将file2[]强转为QString的值
    //强转file
    QByteArray temp = file.toLatin1();
    ch = temp.data();
    if(file!="")
    {
        BMP* bmp = new BMP();  //声明BMP
        bmp->readbmp(ch);      //调用读图函数
        bmp->greybmp(file2);   //调用转灰度图函数
        temp2 = QString(QLatin1String(file2));//强转file2
        if(image->load(temp2))
        {
            //显示到系统窗口中
            QGraphicsScene *scene = new QGraphicsScene;
            scene->addPixmap(QPixmap::fromImage(*image));
            ui->pre->setScene(scene);
            //ui->pre->resize(image->width() + 10, image->height() + 10);
            ui->pre->show();
        }
        delete bmp;
        BMP::isImported = 1;

    }
    //delete ch;
}

void MainWindow::on_sharpen_clicked()
{

    char file2[] = "result.bmp"; //保存的灰度图的名字
    //char* ch = new char();       //打开的文件名由QString强转而来

    QString temp2;               //将file2[]强转为QString的值
    /*
     * //强转file
    QByteArray temp = file2.toLatin1();
    ch = temp.data();
    */

        BMP* bmp = new BMP();  //声明BMP
        if(BMP::isImported==1)
        {
            bmp->readbmp(file2);      //调用读图函数
            bmp->smoothbmp(file2);   //调用转灰度图函数
            temp2 = QString(QLatin1String(file2));//强转file2
            if(image->load(temp2))
            {
                //显示到系统窗口中
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->fol->setScene(scene);
                //ui->pre->resize(image->width() + 10, image->height() + 10);
                ui->fol->show();
            }
            delete bmp;
        }
        else
        {
            //提示窗口
            Dialog * d = new Dialog;
            d->show();
        }

    //delete ch;
}

void MainWindow::on_smooth_clicked()
{
    char file2[] = "result.bmp"; //保存的灰度图的名字
    //char* ch = new char();       //打开的文件名由QString强转而来

    QString temp2;               //将file2[]强转为QString的值
    /*
     * //强转file
    QByteArray temp = file2.toLatin1();
    ch = temp.data();
    */

        BMP* bmp = new BMP();  //声明BMP
        if(BMP::isImported==1)
        {
            bmp->readbmp(file2);      //调用读图函数
            bmp->sharpbmp(file2);   //调用转灰度图函数
            temp2 = QString(QLatin1String(file2));//强转file2
            if(image->load(temp2))
            {
                //显示到系统窗口中
                QGraphicsScene *scene = new QGraphicsScene;
                scene->addPixmap(QPixmap::fromImage(*image));
                ui->fol->setScene(scene);
                //ui->pre->resize(image->width() + 10, image->height() + 10);
                ui->fol->show();
            }
            delete bmp;
            //BMP::isSharped = 1;
        }
        else if(!BMP::isImported)
        {
            //提示
            Dialog * d = new Dialog;
            d->show();
        }

}


