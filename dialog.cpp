#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(int t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    if(t){
    ui->label->setText("It has been sharped!");
    ui->setupUi(this);
    }
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    this->hide();


}
