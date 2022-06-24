#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    q=true;
    ui->textBrowser->hide();
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}
Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    q=false;
    hide();
}
void Dialog::showerror(){
    ui->label->setText(s);
    ui->textBrowser->hide();
    resize(300,100);
    ui->pushButton->setGeometry(width()/2-20,height()-20,40,20);
}

void Dialog::showtable(QString text){
    resize(500,500);
    ui->textBrowser->setGeometry(50,50,400,400);
    ui->textBrowser->show();
    ui->textBrowser->clear();
    ui->textBrowser->setStyleSheet("font-size: 12pt");
    ui->textBrowser->append(text);
    ui->pushButton->setGeometry(width()/2-20,height()-20,40,20);
}
