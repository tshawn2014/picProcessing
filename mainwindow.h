#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BMP.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_input_clicked();

    void on_sharpen_clicked();

    void on_smooth_clicked();


private:
    Ui::MainWindow *ui;
    QImage *image;

public:
    BMP *bmp;

};

#endif // MAINWINDOW_H
